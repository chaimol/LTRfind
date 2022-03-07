#!/usr/bin/R
#Usage:Rscript visual_LTR.R abbr.LTR_time.xls abbr pwd
#

##获取脚本的输入的参数
args<-commandArgs(T) #收集参数给args变量
#判断是否正确输入参数
if (length(args)==0 | args[1] == "-h" | args[1] == "--help" | length(args)<3){
  stop("Usage: visual_LTR.R abbr.LTR_time.xls abbr pathworkdir")
}

if(!require("ggplot2"))install.packages("ggplot2")
library("ggplot2")
#参数1  args[1] 输入abbr.LTR_time.xls
#参数2  args[2] 输入abbr
#参数3  args[3] 输入工作路径
LTR_time_file <- args[1]
abbr <- args[2]
workdir <- args[3]
setwd(workdir)

#判断输入文件是否存在
if (! file.exists(LTR_time_file)){stop(paste0("the input file ",getwd(),"/",LTR_time_file," not exist!"))}
dat<-read.delim(LTR_time_file,header=TRUE)
#读取的abbr.LTR_time.xls格式如下：
# SuperFamily     TE_type Insertion_Time
# Copia   LTR     -0
# Gypsy   LTR     54679
# Copia   LTR     314204
# unknown NA      71121
# Copia   LTR     536727


#除以100万
dat$VAF <-dat$Insertion_Time / 1000000

#画图（出图结果中x轴是以mya（百万年）为单位的。）
ggplot(dat,aes(x=VAF))+geom_density(color = "red")+xlab('Mya')+ylab('Density')+
  scale_x_continuous(expand = c(0, 0)) + 
  #scale_y_continuous(expand = c(0, 0))+ #设置横纵坐标从0开始
  theme_classic()
ggsave(paste0(abbr,'.LTR.density.pdf'),dpi = 300)
ggsave(paste0(abbr,'.LTR.density.png'),dpi = 300)
print(paste0("output file in ",getwd(),"/",abbr,'.LTR.density.png'))
dev.off()

#求峰值
y_peak <- which.max(density(dat$VAF)$y)#找y值最大的
x_peak <- density(dat$VAF)$x[y_peak]#找出最大的y所对应的x   
print(paste0("the LTR peak is X:",x_peak," Y:",y_peak))

#画图
ggplot(dat,aes(x=VAF))+geom_density(aes(color = SuperFamily))+xlab('Mya')+ylab('Density')+
  scale_x_continuous(expand = c(0, 0)) + 
  #scale_y_continuous(expand = c(0, 0))+ #设置横纵坐标从0开始
  theme_classic()
ggsave(paste0(abbr,'.LTR_type.density.pdf'),dpi = 300)
ggsave(paste0(abbr,'.LTR_type.density.png'),dpi = 300)
print(paste0("output file in ",getwd(),"/",abbr,'.LTR_type.density.png'))
dev.off()
#删除无法避免的Rplots.pdf
if (file.exists("Rplots.pdf")){
  file.remove("Rplots.pdf")
}
save.image(file=paste0(abbr,".LTR.Rdata"))
print(paste0("save LAI data to ",workdir,"/",abbr,".LTR.Rdata"))