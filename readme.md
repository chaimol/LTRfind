# LTRfind: a pipeline for get LTR and LAI ( base on [LTR_retriever](https://github.com/oushujun/LTR_retriever))

# 0.Require software (we provided version.only for Linux X86_64)
- [LTR_FINDER_parallel](https://github.com/oushujun/LTR_FINDER_parallel) 
- [gt](http://genometools.org/pub/binary_distributions/)
- [seqkit](https://bioinf.shenwei.me/seqkit/download/)
- [LTR_retriever](https://github.com/oushujun/LTR_retriever)
- R ggplot2 packages (for visualization only)

# 1. Install LTR_retriever by conda
```
conda create -n LTR_retriever
conda activate LTR_retriever
conda install -y -c conda-forge perl perl-text-soundex
conda install -y -c bioconda cd-hit repeatmasker
git clone https://github.com/oushujun/LTR_retriever.git
./LTR_retriever/LTR_retriever -h

chmod 757 gt-1.6.2/bin/gt
chmod 757 seqkit
chmod 757 LTRfind
chmod 757 LTR_FINDER_parallel-1.1/bin/LTR_FINDER.x86_64-1.0.7/ltr_finder


./LTRfind -h
```
you also can add  the path of `LTRfind` to the `~/.bashrc`.

# 2.how to use it
It is mainly used for the identification of diploid and polyploid LTR and the calculation of LAI value.
### Modify `config.ini` at first

### Purpose:
Get the LTR_RTs in the genome and calculate the LAI value of the genome at the same time. 
for Diploid use (`-D|Diploid`)
for Polyploid (up to octoploid) use (`-P|Polyploid`)

### Usage: 
```
	-h|--help 
	-D|Diploid Species genome.fa 
	-D|Diploid Species genome.fa ChrString 
	-P|Polyploid -abbr Species -g genome.fa -chr ChrString -p1 Ghir_A -p2 Ghir_D 
	-P|Polyploid -abbr Species -g genome.fa -p1 Ghir_A -p2 Ghir_D 
	-V | --version
```
### Example:
```
	LTRfind -D A.thaliana /path/A.thaliana.fa 
	LTRfind Diploid A.thaliana /path/A.thaliana.fa chr
	LTRfind -P -abbr Species -g genome.fa -chr ChrString -p1 Ghir_A -p2 Ghir_D 
	LTRfind -P -abbr Species -g genome.fa -chr ChrString -p1 Ghir_A -p2 Ghir_D -p3 Ghir_C 
	LTRfind -P -abbr Species -g genome.fa -chr ChrString -p1 Ghir_A -p2 Ghir_D -p3 Ghir_C -p4 Ghir_B
	LTRfind Polyploid -abbr Species -g genome.fa -p1 Ghir_A -p2 Ghir_D
	LTRfind -D A.thaliana ${PWD}/example/LTRfind/Ath.Chr4_5.fa chr
```
### Note:
In run `-D|Diploid` ，if you input the ChrString , will extract the Chromosome sequence for LTR and LAI (not analysis the scaffold sequence).
Input genome file must be `.fa`,not support `.fa.gz`.

**the genome.fa sequence ID should be less then 15 character. if your file is report over 15 character, can use `seqkit seq -i genome.fa >new.genome.fa` to extract the ID and delete the info after the ID**

if your input `genome.fa` `ChrID` may be like `>1`,in this case, you cannot use the `ChrStr` field to extract chromosome data and filter scaffold. 
It is recommended to use `LTRfind` after filtering by yourself. The ID length of genome.fa cannot exceed 15 characters. 
### Visualization
if you jsut want use the visualization module `visual_LAI` and `visual_LTR`.

**visual_LAI.R used only for chomosome, so if please delete the rows which is contain contigs and scaffolds in \*.out.LAI**
```
Rscript visual_LAI.R genome.out.LAI speciesname
Rscript visual_LAI.R genome.pass.list speciesname
```

# 3. Input
### Diploid: 
- speciesname 
- genome.fa 
- ChrStr (can be omitted)
### Polyploid:
- speciesname 
- genome.fa 
- ChrStr (If you do not provide this parameter, it is assumed that the genome file you provide only contains the sequence of the chromosome.)
- p1
- p2
- p3
- p4
## Example:
#### Polyploid:
for `Ghirsutum.fasta`
`head Ghirsutum.fasta`
```
>Ghir_A01
TAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAA
ACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACC
CTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTA
AACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAAC
CCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAAACCCTAAACCCTAAACCC
TAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAA
ACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACC
CTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTA
AACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAAC
...
>Ghir_D01
AAACCCTAAACCCTAAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAAACCCTAAACCCTAAACCCTAAACCCTA
AACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAAC
CCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCT
AAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAA
CCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCCTAAACCC
```
should be run like this:
`LTRfind -P -abbr G.hirsutum -g Ghirsutum.fasta -chr Ghir_ -p1 Ghir_A -p2 Ghir_D`
#### Diploid
`head Arabidopsis_thaliana.fa`
```
>chr01 dna:chromosome chromosome:TAIR10:1:1:30427671:1 REF
CCCTAAACCCTAAACCCTAAACCCTAAACCTCTGAATCCTTAATCCCTAAATCCCTAAAT
CTTTAAATCCTACATCCATGAATCCCTAAATACCTAATTCCCTAAACCCGAAACCGGTTT
CTCTGGTTGAAAATCATTGTGTATATAATGATAATTTTATCGTTTTTATGTAATTGCTTA
TTGTTGTGTGTAGATTTTTTAAAAATATCATTTGAGGTCAATACAAATCCTATTTCTTGT
GGTTTTCTTTCCTTCACTTAGCTATGGATGGTTTATCTTCATTTGTTATATTGGATACAA
```
`bash LTRfind -D A.thaliana Arabidopsis_thaliana.fa`or `bash LTRfind -D A.thaliana Arabidopsis_thaliana.fa chr`
# 4. Output
All the output is the same with [LTR_retriever](https://github.com/oushujun/LTR_retriever).
For Chinese, there are detail info [links](https://www.jianshu.com/p/ed289822c825) in Chinese.

# 5. Author & Version
- Build date:2021.06.17
- Last update: 2022.03.04
- Version: 0.3.1
- Author: Mol Chai
- Email: chaimol@163.com
# 6. Update info
### (2022/03/04) update to Version 0.3.1
+ Add visual module `getLTRpeak.R`.
+ Add example for test.
+ The test passed the module for diploid! Fixed some bugs!
 
### (2022/03/02) update to Version 0.3.0
+ Add `config.ini` file for user control the input software path .
+ Add the parameter `threads` to specify the number of cpus and the parameter `miu` to specify the differentiation speed. 
+ Add visual module `visul_LTR.R` and `visual_LAI.R`

### (2021/11/19)
Modify the value of `ltrharvest -similar 90` to `ltrharvest -similar 85`. In order to ensure that LTR_harvest and LTR_FINDER_parallel use the same similarity value (0.85). 

### (2021/11/05)
Using LTR_FINDER_parallel instead of LTR_FINDER, the running speed will be greatly improved. 