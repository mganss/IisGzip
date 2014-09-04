# IisGzip

IisGzip is a command line wrapper around the [gzip compression library](http://msdn.microsoft.com/en-us/library/dd692872.aspx) used by Microsoft IIS.

## Usage

```
IisGzip.exe [-1..10] [-dPathToDll] < in.txt > out.txt.gz
```

Default compression level is 10. Make sure you have IIS installed.

## Performance

Here are a few completely unscientific benchmarks:

|   | Input size (bytes) | [gzip](http://www.gzip.org/) 1.4 -9 | [7-zip](http://www.7-zip.org) 9.20 -tgzip -mx=9 | IisGzip -10 | [Zopfli](https://code.google.com/p/zopfli/) b87006b (numiterations=15)|
|:--|:-----------|:--------|:-------------------|:----|:------|
|[enwik8](http://mattmahoney.net/dc/textdata.html)|100 000 000|36 445 248|35 102 884|35 065 645|34 987 671|
|Savings compared to gzip|||3.7%|3.8%|4.0%
|Compression Time||6.6s|89s|18s|503s
|jquery-1.11.1.min.js|95 786|33 083|32 191|32 358|32 091
|Savings compared to gzip|||2.7%|2.2%|3.0%
|Compression Time (100 times)||1.9s|9.0s|3.0s|33s