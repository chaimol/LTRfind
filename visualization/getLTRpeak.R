#!/usr/bin/R
#Usage:Rscript getLTRpeak.R config.tsv pwd
#purpose:for get LTR peak
#Input:config.tsv pathworkdir
#output:All_LTR_time.density.pdf All_LTR_time.density.png AllLTR_peak.csv
#输入的config.tsv文件格式如下：(分隔符是tab)
#abbr_species	latin_species
#Ath	A.thaliana
#Tca	T.cacao
#Tha	T.hassleriana
#Vvi	V.vinifera
#Sly	S.lycopersicum

#该脚本会读取当前目录下的Ath.LTR_time.xls,……Sly.LTR_time.xls，如果存在的话，会报错。


###获取脚本的输入的参数
args<-commandArgs(T) #收集参数给args变量
#参数1  args[1] 输入config

#判断是否正确输入参数
if ( length(args)==0 | args[1] == "-h" | args[1] == "--help" | length(args)<2 ){
  stop("Usage: visual_LTR.R config.tsv pathworkdir")
}

#运行前需要修改config.tsv里的参数
configfile <- args[1]
workdir <- args[2]
setwd(workdir)

config <- read.delim(configfile,header = TRUE)
all_abbr_species <- config$abbr_species #3字符缩写
all_latin_species <- config$latin_species #完整拉丁学名

#定义读取LTR的函数
get_LTRdata <- function(abbr){
  filename <- paste0(abbr,".LTR_time.xls")
  if (file.exists(filename)){
    data1 <- read.delim(filename,header = TRUE)
    data1$Insertion_Time <- data1$Insertion_Time / 1000000 #除以100万，画出的是百万
    return(data1)
  }else{
    #判断如果不存在abbr.LTR_time.xls的时候,告知不存在该文件，并报错。
    stop(paste0("Please make sure the file exist in",getwd(),"/",filename))
  }
} 

all_LTRdata <- data.frame()
for (i in 1:length(all_abbr_species)){
  mid_data <- get_LTRdata(all_abbr_species[i])
  mid_data$Species <- all_latin_species[i]
  assign(paste0(all_abbr_species[i],"_LTR"),mid_data) #给动态变量赋值
  all_LTRdata <- rbind(all_LTRdata,get(paste0(all_abbr_species[i],"_LTR"))) #逐次合并新生成的变量的值到all_data
}

if(!require("ggplot2")){install.packages("ggplot2")}
library("ggplot2")
if(! require("ggprism")){install.packages("ggprism")}
library("ggprism") #可以完善ggplot2的图使之达到发表级别
P_LTR <- ggplot(all_LTRdata,aes(x=Insertion_Time,group=Species))+geom_density(alpha=0.4,aes(color=Species))+theme_classic()+
  scale_x_continuous(expand = c(0,0),breaks = seq(0,10,1)) + xlab('Mya')+ylab('Density')+
  scale_y_continuous(expand = c(0, 0))+ #设置横纵坐标从0开始
  theme_prism(base_size = 12)+
  scale_y_continuous(guide = "prism_offset_minor")+scale_x_continuous(guide = "prism_offset_minor")
print(P_LTR)
ggsave('All.LTR_time.density.pdf',dpi = 400)
ggsave('All.LTR_time.density.png',dpi = 300)
print(paste0("output all the LTR distribute image is ",getwd(),"/All.LTR_time.density.png"))
dev.off()
#获取LTR的每一个峰值
get_peak <- function(dat,latin_name){
  VAF <- dat$Insertion_Time
  d <- density(VAF)
  modes <- function(d,s){
    i <- which(diff(sign(diff(d$y))) < 0) + 1
    data.frame(species=s,x = d$x[i], y = d$y[i])
  }
  return(modes(d,latin_name))
}

all_LTRpeak <- data.frame()
for (i in 1:length(all_abbr_species)){
  species_peak <- paste0(all_abbr_species[i],"_peak")
  assign(species_peak,get_peak(get(paste0(all_abbr_species[i],"_LTR")),all_latin_species[i])) #给动态变量赋值
  all_LTRpeak <- rbind(all_LTRpeak,get(species_peak)) #逐次合并新生成的变量的值到all_data
}
colnames(all_LTRpeak) <- c("Species","Peak_x","Peak_y")
print(all_LTRpeak)
write.csv(all_LTRpeak,"All.LTR_peak.csv",quote = F,row.names = F)
print(paste0("output all the peak to ",getwd(),"/All.LTR_peak.csv"))
#删除无法避免的Rplots.pdf
if (file.exists("Rplots.pdf")){
  file.remove("Rplots.pdf")
}
save.image(file=paste0(abbr,".LTRpeak.Rdata"))
print(paste0("save LAI data to ",workdir,"/",abbr,".LTRpeak.Rdata"))