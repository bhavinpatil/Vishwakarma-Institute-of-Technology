#====================================================================
#Case Study No. 1
#====================================================================

cat("\n========================Solution for Case Study 1========================")

dataset1 <- read.csv("pollutant_csv.csv")
meanofTemp <- mean( dataset1$Temp [dataset1$Month == 6])
cat("\n\nQ. 1 Mean of Temp when Month = 6 : ", meanofTemp,"\n\n")

View(dataset1)

n <-nrow(dataset1)
cat("Q. 2 Number of observations in the given data : ", n,"\n\n")

cat("Q. 3 Last two rows: \n")
print(tail(dataset1,2))

cat("\n\nQ. 4 Value of Ozone in 47th row : ", dataset1$Ozone[47],"\n\n")

cat("Q. 5 Number of missing values in Ozone Column : ", sum(is.na(dataset1$Ozone)),"\n\n")

cat("Q. 6 Mean of Ozone column excluding missing values : ", mean(is.na(dataset1$Ozone)),"\n\n")

a <- dataset1[dataset1$Ozone > 31 & dataset1$Temp > 90,]
cat("Q. 7 Ozone above 31 and Temp above 90: ")
print(a)

a1 <- mean(dataset1$Solar.R, na.rm = T)
cat("Q. 8 Mean of Solar.R ",a1,"\n\n")

a2 <- max(dataset1$Ozone[dataset1$Month == 5], na.rm = T)
cat("Q. 9 Max Ozone Layer in the month of May: ", a2,"\n\n")

#====================================================================
#Case Study No. 2
#====================================================================

cat("\n\n\n*************Solution for Case Study 2****************")

dataset2 <- read.csv("hair_eye_color_csv.csv")

ans1 <- sum(dataset2$Eye.Color == "Brown")
cat("\n\nQ. 1) Number of people having Brown eyes: ",ans1,"\n\n")

ans2 <- sum(dataset2$Hair.Color == "Blonde")
cat("Q. 2) Number of people having Blonde Hairs: ",ans2,"\n\n")

ans3 <- sum(dataset2$Hair.Color == "Blonde" & dataset2$Eye.Color == "Black")
cat("Q. 3) Number of people having Blonde Hair and Black Eyes: ",ans3,"\n\n")

ans4 <- (sum(dataset2$Eye.Color == "Green") / length(dataset2) )* 100
cat("Q. 4) Percentage of the people with green eyes: ",ans4,"\n\n")

ans5 <- (sum(dataset2$Hair.Color == "Red" & dataset2$Eye.Color == "Blue") / length(dataset2) )* 100
cat("Q. 5) Percentage of the people with red hairs and blue eyes: ",ans5,"\n\n")

#====================================================================
#Case Study No. 3
#====================================================================

cat("\n\n\n*************Solution for Case Study 3****************")

dataset3 <- read.csv("germination_csv.csv");

answer1 <- mean(dataset3$Box == "Uncovered" & dataset3$water_amt == 4, rm.na = T) / length(dataset3)
answer1 <- mean(dataset3$germinated[dataset3$Box == "Uncovered" & dataset3$water_amt == 4])
cat("\n\nQ. 1) Average Number of seeds = ", answer1,"\n\n")

answer2 <- median(dataset3$Box == "Covered")
cat("Q. 2) Median: ", answer2)

library("dslabs")
library(dplyr)
t<-ggplot(iris,aes(Species,Sepal.Length,fill=Species))+geom_boxplot(outlier.color="red",outlier.shape=4,outlier.size = 4)+theme(legend.position = "none")+ggtitle("Boxplot")+xlab("species")+ylab("sepallength")
print(t)

View(iris)

View(murders)
y<-ggplot(murders,aes(population/10^6,total,col=region))+geom_point(size=3)+scale_x_log10()+scale_y_log10()+geom_text(aes(label=abb),size=3,nudge_x=0.050)+labs(title="SCATTERPLOT",x="Population",y="Total")
print(y)

