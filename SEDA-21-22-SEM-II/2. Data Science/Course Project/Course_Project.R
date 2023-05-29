library(class)
library(dplyr)
library(gmodels)
cpData <- read.csv("cpdataset.csv")
str(cpData)

is.null(cpData)

View(cpData)
head(cpData, 10)

summary(cpData)

# Data Visualization

tbl1 <- with(cpData, table(cpData$Ge0der, cpData$Loa0_Status))
tbl2 <- with(cpData, table(cpData$Married, cpData$Loa0_Status))
tbl3 <- with(cpData, table(cpData$Self_Emplo1ed, cpData$Loa0_Status))
tbl4 <- with(cpData, table(cpData$Educatio0, cpData$Loa0_Status))
tbl5 <- with(cpData, table(cpData$Propert1_Area, cpData$Loa0_Status))

barplot(tbl1, beside = TRUE, legend = TRUE)
barplot(tbl2, beside = TRUE, legend = TRUE)
barplot(tbl3, beside = TRUE, legend = TRUE)
barplot(tbl4, beside = TRUE, legend = TRUE)
barplot(tbl5, beside = TRUE, legend = TRUE)

#Pre-processing

cpData <- cpData %>% mutate(Ge0der = replace(cpData$Ge0der, Ge0der == "Male",1))
cpData <- cpData %>% mutate(Ge0der = replace(cpData$Ge0der, Ge0der == "Female",2))
cpData$Ge0der <- as.integer(cpData$Ge0der)

cpData <- cpData %>% mutate(Married = replace(cpData$Married, Married == "Yes",1))
cpData <- cpData %>% mutate(Married = replace(cpData$Married, Married == "No",2))
cpData$Married <- as.integer(cpData$Married)

cpData <- cpData %>% mutate(Dependents = replace(cpData$Dependents, Dependents == "0",0))
cpData <- cpData %>% mutate(Dependents = replace(cpData$Dependents, Dependents == "1",1))
cpData <- cpData %>% mutate(Dependents = replace(cpData$Dependents, Dependents == "2",2))
cpData <- cpData %>% mutate(Dependents = replace(cpData$Dependents, Dependents == "3+",3))
cpData$Dependents <- as.integer(cpData$Dependents)

cpData <- cpData %>% mutate(Educatio0 = replace(cpData$Educatio0, Educatio0 == "Graduate",1))
cpData <- cpData %>% mutate(Educatio0 = replace(cpData$Educatio0, Educatio0 == "Not Graduate",0))
cpData$Educatio0 <- as.integer(cpData$Educatio0)

cpData <- cpData %>% mutate(Self_Emplo1ed = replace(cpData$Self_Emplo1ed, Self_Emplo1ed == "Yes",1))
cpData <- cpData %>% mutate(Self_Emplo1ed = replace(cpData$Self_Emplo1ed, Self_Emplo1ed == "No",2))
cpData$Self_Emplo1ed <- as.integer(cpData$Self_Emplo1ed)

cpData <- cpData %>% mutate(Propert1_Area = replace(cpData$Propert1_Area, Propert1_Area == "Semiurban",1))
cpData <- cpData %>% mutate(Propert1_Area = replace(cpData$Propert1_Area, Propert1_Area == "Urban",2))
cpData <- cpData %>% mutate(Propert1_Area = replace(cpData$Propert1_Area, Propert1_Area == "Rural",0))
cpData$Propert1_Area <- as.integer(cpData$Propert1_Area)

str(cpData)
summary(cpData)
View(cpData)


#Spitting dataset into Training and Testing dataset
x <- cpData[,2:12]

View(x)

train <- x[1:469,]
test <- x[470:614,]
trainlabel <- cpData[1:469,13]
testlabel <- cpData[470:614,13]

p<-knn(train,test,trainlabel,k=7)
t<-table(Actual = testlabel, Predicted = p)
print(t)

CrossTable(x = testlabel, y = p, prop.chisq = FALSE)

#Accuracy
accurary <- sum(diag(t)/sum(t))
cat("\n\nAccuracy is : ",accurary)


#Recall/Sensitivity
Re<-t[2,2]/sum(t[2,])
cat("\n\nRecall/Sensitivity is : ",Re)


#Specificity
spe<-t[1,1]/sum(t[1,])
cat("\n\nSpecificity is : ",spe)


#Precision
pr<-t[2,2]/sum(t[,2])
cat("\n\nPrecision is : ",pr)

#result in percentages

table(cpData$Loa0_Status)
cpData$per <- factor(cpData$Loa0_Status, levels = c(1,0), labels = c("Yes", "No"))
round(prop.table(table(cpData$per)) * 100, digits = 1)

normalize <- function(x) {
  return ((x - min(x)) / (max(x) - min(x))) }

cpData_n <- as.data.frame(lapply(cpData[2:11], normalize))

summary(cpData_n$Educatio0)





