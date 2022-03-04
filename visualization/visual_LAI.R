#!/usr/bin/R
#可视化LAI在染色体上的分布的代码

###获取脚本的输入的参数
args<-commandArgs(T) #收集参数给args变量
#参数1  args[1] 

#Usage:Rscript visual_LAI.R genome.*.out.LAI abbr pwd
#第一个参数是输出的LAI文件，注意需要自己删除包含contig或scaffold的行。只能用于染色体
#第二个参数是用于输出的文件名的前缀
# 输入文件是 genome.str15.chr.fa.out.LAI abbr pwd
if ( length(args)==0 | args[1] == "-h" | args[1] == "--help" | length(args)<3){
  stop("Usage: visual_LAI.R genome.*.out.LAI abbr pathworkdir")
}

if(! require(ggplot2)){install.packages("ggplot2")}
library("ggplot2")

LAI_file <- args[1]
abbr <- args[2]
workdir <- args[3]
setwd(workdir)

#判断输入文件是否存在
if (! file.exists(LAI_file)){stop(paste0("the input file ",getwd(),"/",LAI_file," not exist!"))}

data2 <- read.delim(LAI_file,header = T)
data2 <- data2[!(data2$Chr %in% "whole_genome"),] #过滤第1行(是whole_genome)，pass.list的第一行是整体的LAI
data2$BP <- (data2$From + data2$To)/2 

#绘制散点图
chr_num <- length(unique(data2$Chr)) #获取染色体的数量
##控制绘图的行数，染色体数量>=20,则绘制2行
if (chr_num < 20){
  row_num <- 1
}else{
  row_num <- 2
}
##判断用户是否删除contig和scaffold
if (chr_num >50){
  warning("Notes:Please make sure your input LAI file have been delete  rows which contain the contig and scaffold!
      Your input chromosome numbers have been large then 50!!!")
}

ggplot(data2, aes(x=BP,y=LAI,color=Chr)) +
  geom_point()+
  facet_wrap(~Chr,scales = "free_x",shrink = FALSE,as.table = TRUE,strip.position="bottom",nrow=row_num)+
  theme_classic()+
  theme(legend.position = "none")+ #隐藏图例
  #scale_y_continuous(expand = c(0, 0)) + #设置y轴坐标从0开始
  #theme(axis.title = element_blank(),axis.line = element_blank())+
  theme(axis.title.x=element_blank(),axis.text.x=element_blank(),axis.ticks.x=element_blank())
ggsave(paste0(abbr,".LAI.pdf"),dpi = 300)
ggsave(paste0(abbr,".LAI.png"),dpi = 300)
print(paste0("Output LAI image in ",getwd(),"/",abbr,".LAI.png"))
dev.off()
# 
# head(data2) 
# CHR    From      To Intact  Total raw_LAI   LAI      BP
# 1   1       1 3000000 0.1917 0.7771   24.67 21.56 1500001
# 2   1  300001 3300000 0.1973 0.7971   24.76 21.65 1800001
# 3   1  600001 3600000 0.1976 0.8249   23.96 20.85 2100001
# 4   1  900001 3900000 0.2032 0.8621   23.57 20.46 2400001
# 5   1 1200001 4200000 0.1981 0.8769   22.59 19.48 2700001
# 6   1 1500001 4500000 0.1759 0.8843   19.89 16.78 3000001
#删除无法避免的Rplots.pdf
if (file.exists("Rplots.pdf")){
  file.remove("Rplots.pdf")
}