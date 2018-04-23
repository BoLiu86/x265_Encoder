# x265 encoder
The x265 encoder is designed using the x265 open source project of the H.265/HEVC, which is the latest video coding standard.It achieves a reduction in memory capacity while maintaining the almost video quality. 

### Develop environment
Windows and vs2013

### How to use
a. Download x265 project from the website "https://bitbucket.org/multicoreware/x265/downloads/";     
b. Build the x265 project according to the personal develop tool;     
c. Copy files "x265.h", "x265_config.h", "libx265.lib", and "libx265.dll" to a new folder;     
d. Set the above folder as the develop folder, and include "x265.h".

### Encoding performance
In this experiment, in order to evaluate the performance of the x265 encoder, seven test sequences, which are suggested for the HEVC, from the dataset provided by MPEG are used. From the following table, it can be observed that the maximum compression ratio is reached 490 for "Traffic". And the compression result for other sequences is also high, which is more efficient. 
<table>
  <tr>
    <th width=9%>Class</th>
    <th width=20%>Sequences</th>
    <th width=21%>Original Size(Kb)</th>
    <th width=27%>Compressed Size(Kb)</th>
    <th width=23%>Compression Ratio</th>
  </tr>
  <tr>
  	<td>A</td>
    <td>PeopleOnStreet</td>
    <td>900000</td>
    <td>6718</td>
    <td>134</td>
  </tr>
  <tr>
    <td>A</td>
    <td>Traffic</td>
    <td>900000</td>
    <td>1835</td>
    <td bgcolor=#FFFF00>490</td>
  <tr>
    <td>B</td>
    <td>BasketballDrive</td>
    <td>1521888</td>
    <td>5297</td>
    <td>287</td>
  </tr>
  <tr>
    <td>B</td>
    <td>BQTerrace</td>
    <td>1825538</td>
    <td>3877</td>
    <td>471</td>
  </tr>
  <tr>
    <td>B</td>
    <td>Cactus</td>
    <td>1518750</td>
    <td>4577</td>
    <td>332</td>
  </tr>
  <tr>
    <td>B</td>
    <td>Kimono1</td>
    <td>729000</td>
    <td>2167</td>
    <td>336</td>
  </tr>
  <tr>
    <td>B</td>
    <td>ParkScene</td>
    <td>729000</td>
    <td>2529</td>
    <td>388</td>
  </tr>
</table>
