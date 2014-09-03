# IisGzip

IisGzip is a command line wrapper around the [gzip compression library](http://msdn.microsoft.com/en-us/library/dd692872.aspx) used by Microsoft IIS.

## Usage

```
IisGzip.exe [-1..10] < in.txt > out.txt.gz
```

Default compression level is 10. Make sure you have IIS installed.

## Performance

I wrote this mainly to see if it made sense to write a custom DLL for IIS that compresses
better than the one shipped with IIS, e.g. [Zopfli](https://code.google.com/p/zopfli/).
As it turns out, the default IIS compressor is already pretty good :)

|   | Input size (bytes) | gzip -9 | 7-zip -tgzip -mx=9 | IisGzip -10 | Zopfli (default)|
|:--|:-----------|:--------|:-------------------|:----|:------|
|[enwik8](http://mattmahoney.net/dc/textdata.html)|100 000 000|36 445 248|35 102 884|35 065 645|34 995 107|
|Savings compared to gzip|||3.7%|3.8%|4.0%
|Compression Time||6.6s|89s|18s|404s
|jquery-1.11.1.min.js|95 786|33 083|32 191|32 358|32 207
|Savings compared to gzip|||2.7%|2.2%|2.6%
|Compression Time (100 times)||1.9s|9.0s|3.0s|38s