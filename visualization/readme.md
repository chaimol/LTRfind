#files list
### getLTRpeak.R
Analyze the peaks of 1 or more LTR_time.xls, the output files are All.LTR_peak.csv and All.LTR_time.density.png.
### visual_LTR.R
Visualize a plot of the insertion time distribution of LTRs in 1 LTR file.The output files are abbr.LTR.density.png and abbr.LTR_type.density.png
### visual_LAI.R
Visualize the distribution of LAI on chromosomes in 1 LAI file.Output file is abbr.LAI.png

#### Usage:
```
Rscript visual_LAI.R genome.*.out.LAI abbr pwd
Rscript visual_LTR.R abbr.LTR_time.xls abbr workpath
Rscript getLTRpeak.R configfile workpath
```

getLTRpeak.R
- configfile should be in workpath
- configfile should have 2 columns, and columns must be is `abbr_species	latin_species`
- config files must use tab separators
- The abbr.LTR_time.xls file in config must exist in the workpath. abbr.LTRtime.xls must use tab separators.

**Notes: All the input file header must be same with the example!**
#### Run example
```
Rscript visual_LAI.R Ath.genome.fa.out.LAI Ath $PWD/../example/LAI
Rscript visual_LTR.R Ath.LTR_time.xls Ath $PWD/../example/LTR
Rscript getLTRpeak.R config.tsv $PWD/../example/LTR_peak
```