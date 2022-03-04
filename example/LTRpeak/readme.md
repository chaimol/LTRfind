# this if example file for run getLTRpeak.R
## `getLTRpeak.R` usage:
`Rscript getLTRpeak.R configfile workpath`
- configfile should be in workpath
- configfile should have 2 columns, and columns must be is `abbr_species	latin_species`
- config files must use tab separators
- The abbr.LTRtime.xls file in config must exist in the workpath. abbr.LTRtime.xls must use tab separators.

## run getLTRpeak.R example
```
Rscript visualization/getLTRpeak.R config.tsv $PWD/visualization/example/LTR_peak
```