# IisGzip

IisGzip is a command line wrapper around the [gzip compression library](http://msdn.microsoft.com/en-us/library/dd692872.aspx) used by Microsoft IIS.

If you're looking for a way to let IIS compress content using a different compressor, check out [this other project](https://github.com/mganss/ZopfliDll).

## Usage

```
IisGzip.exe [-0..10] [-dPathToDll] < in.txt > out.txt.gz
```

Default compression level is 10. Make sure you have IIS installed.

## Performance

Here are a few completely unscientific benchmarks:

<table>
<tr><th></th><th>Input</th><th><a href="http://www.gzip.org/">gzip</a> 1.4 -9</th><th><a href="http://www.7-zip.org">7-Zip</a> 9.20 -tgzip -mx=9</th><th>IisGzip -10</th><th><a href="https://code.google.com/p/zopfli/">Zopfli</a> b87006b (numiterations=15)</th></tr>
<tr><td colspan="12" align="center"><a href="http://mattmahoney.net/dc/textdata.html">enwik8</a></td></tr>
<tr><td>Size (bytes)</td><td>100'000'000</td><td>36'445'248</td><td>35'102'884</td><td>35'065'645</td><td>34'987'671</td></tr>
<tr><td>Savings compared to gzip</td><td></td><td></td><td>3.7%</td><td>3.8%</td><td>4.0%</tr>
<tr><td>Compression Time</td><td></td><td>6.6s</td><td>89s</td><td>18s</td><td>503s</tr>
<tr><td colspan="12" align="center">jquery-1.11.1.min.js</td></tr>
<tr><td>Size (bytes)</td><td>95'786</td><td>33'083</td><td>32'191</td><td>32'358</td><td>32'091</tr>
<tr><td>Savings compared to gzip</td><td></td><td></td><td>2.7%</td><td>2.2%</td><td>3.0%</tr>
<tr><td>Compression Time (100 runs)</td><td></td><td>1.9s</td><td>9.0s</td><td>3.0s</td><td>33s</tr>
</table>

Here's a benchmark of the different compression levels offered by the IIS gzip library:

<table>
<tr><th>Compression Level</th><th>0</th><th>1</th><th>2</th><th>3</th><th>4</th><th>5</th><th>6</th><th>7</th><th>8</th><th>9</th><th>10</th></tr>
<tr><td colspan="12" align="center">jquery-1.11.1.min.js</td></tr>
<tr><td>Compression Time (100 runs), in s</td><td>14.6</td><td>14.4</td><td>14.7</td><td>15.0</td><td>15.4</td><td>16.4</td><td>17.5</td><td>17.8</td><td>18.2</td><td>18.5</td><td>28.5</td></tr>
<tr><td>Size (bytes)</td><td>42'748</td><td>40'949</td><td>39'437</td><td>38'451</td><td>34'383</td><td>33'662</td><td>33'349</td><td>33'311</td><td>33'293</td><td>33'293</td><td>32'358</td></tr>
<tr><td>Savings compared to level 0</td><td></td><td>5%</td><td>8%</td><td>11%</td><td>20%</td><td>22%</td><td>22%</td><td>23%</td><td>23%</td><td>23%</td><td>25%</td></tr>
<tr><td colspan="12" align="center">enwik8</td></tr>
<tr><td>Compression Time (s)</td><td>1.7</td><td>1.8</td><td>2.1</td><td>2.8</td><td>3.0</td><td>4.5</td><td>6.9</td><td>7.8</td><td>8.4</td><td>8.4</td><td>18.2</td></tr>
<tr><td>Size (bytes)</td><td>47'524'214</td><td>43'999'420</td><td>42'452'501</td><td>41'284'376</td><td>38'132'424</td><td>37'200'509</td><td>36'667'333</td><td>36'601'317</td><td>36'579'173</td><td>36'578'953</td><td>35'065'645</td></tr>
<tr><td>Savings compared to level 0</td><td></td><td>8%</td><td>11%</td><td>14%</td><td>20%</td><td>22%</td><td>23%</td><td>23%</td><td>24%</td><td>24%</td><td>27%</td></tr>
</table>
