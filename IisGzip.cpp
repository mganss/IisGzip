#include "stdafx.h"
#include <io.h>
#include <fcntl.h>
#include "httpcompression.h"

const int buffer_size = 32768;

void Error(const char *error, int exit_code = 1)
{
	fprintf_s(stderr, error);
	fprintf_s(stderr, "\n");
	exit(exit_code);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int compression_level = 10;
	HMODULE gzip = NULL;
	
	for (int i = 1; i < argc; i++)
	{
		auto arg = argv[i];
		if (wcslen(arg) > 1 && arg[0] == '-')
		{
			auto opt = arg[1];

			if (opt >= L'1' && opt <= L'9')
			{
				compression_level = _wtoi(arg + 1);
				if (compression_level < 1 || compression_level > 10) compression_level = 10;
			}
			else if (opt == L'd')
			{
				gzip = LoadLibrary(arg + 2);
				if (gzip == NULL) Error("Error loading gzip dll");
			}
		}
	}

	if (gzip == NULL)
	{
		auto gzip_env_path = L"%Windir%\\system32\\inetsrv\\gzip.dll";
		wchar_t gzip_path[256];
		auto path_len = ExpandEnvironmentStrings(gzip_env_path, gzip_path, 255);
		if (path_len == 0 || path_len > 255) Error("Error expanding gzip.dll path");
		gzip = LoadLibrary(gzip_path);
		if (gzip == NULL) Error("Error loading gzip.dll");
	}

	auto ProcInitCompression = (InitCompression)GetProcAddress(gzip, "InitCompression");
	if (ProcInitCompression == NULL) Error("Error getting address of InitCompression()");
	auto ProcCreateCompression = (CreateCompression)GetProcAddress(gzip, "CreateCompression");
	if (ProcCreateCompression == NULL) Error("Error getting address of CreateCompression()");
	auto ProcCompress = (Compress)GetProcAddress(gzip, "Compress");
	if (ProcCompress == NULL) Error("Error getting address of Compress()");
	auto ProcDestroyCompression = (DestroyCompression)GetProcAddress(gzip, "DestroyCompression");
	if (ProcDestroyCompression == NULL) Error("Error getting address of DestroyCompression()");
	auto ProcDeInitCompression = (DeInitCompression)GetProcAddress(gzip, "DeInitCompression");
	if (ProcDeInitCompression == NULL) Error("Error getting address of DeInitCompression()");

	if (_setmode(_fileno(stdin), _O_BINARY) < 0) Error("Error setting stdin to binary mode");
	if (_setmode(_fileno(stdout), _O_BINARY) < 0) Error("Error setting stdout to binary mode");

	PVOID compression_context;
	auto input_buf = new byte[buffer_size];
	if (input_buf == NULL) Error("Error getting input buffer");
	auto output_buf = new byte[buffer_size];
	if (output_buf == NULL) Error("Error getting output buffer");
	if (ProcInitCompression() != S_OK) Error("Error calling InitCompression()");
	// set reserved to 1 to enable gzip file format
	if (ProcCreateCompression(&compression_context, 1) != S_OK) Error("Error calling CreateCompression()");
	LONG input_used = 0, output_used = 0, bytes_compressed = 0;
	HRESULT compression_result;
	size_t bytes_read = 0;

	do
	{
		if (!feof(stdin) && (bytes_compressed == bytes_read))
		{
			bytes_compressed = 0;
			bytes_read = fread_s(input_buf, buffer_size, 1, buffer_size, stdin);
			if (ferror(stdin)) Error("Error reading from stdin");
		}

		compression_result = ProcCompress(compression_context, input_buf + bytes_compressed, (LONG)(bytes_read - bytes_compressed), output_buf, buffer_size, &input_used, &output_used, compression_level);

		bytes_compressed += input_used;

		if (output_used > 0)
		{
			auto bytes_written = fwrite(output_buf, 1, output_used, stdout);
			if (ferror(stdout)) Error("Error writing to stdout");
		}
	} 
	while (compression_result == S_OK);

	if (compression_result != S_FALSE) Error("Error compressing data");

	ProcDestroyCompression(compression_context);
	ProcDeInitCompression();

	return 0;
}
