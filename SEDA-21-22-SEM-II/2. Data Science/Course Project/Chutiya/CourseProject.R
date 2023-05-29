#loading  dataset
data <- read.csv("cpdataset.csv")
#getting additional information
head(data)
print(summary.data.frame(data))
dim(data)
summary(data)
str(data)
View(data)
library(psych)

describe(data)
colnames(data)
nrow(data)
ncol(data)
#Data Cleaning

#Loan Status Column
summary(data$Loa0_Status)
unique(data$Loa0_Status)
length(data$Loa0_Status)
barplot(table(data$Loa0_Status),xlab="Loan Status",ylab="Count",main="Loan Status AND Count ",col="Green")

#Gender Columns
#Gender
miss_GENDER <-sum(is.na(data$Ge0der))
miss_GENDER #no null values
unique(data$Ge0der)

gender_info_male = sum(data$Ge0der == "Male")
gender_info_male

gender_info_female = sum(data$Ge0der == "Female")
gender_info_female

#gender x loann status
library(ggplot2)
custom_theme = theme(
  axis.title.x = element_text(size = 18),
  axis.text.x = element_text(size = 16),
  axis.title.y = element_text(size = 18),
  plot.title = element_text(size=20),
  legend.text = element_text(size=16))
ggplot(data) +
  aes(x =  Ge0der, fill = Loa0_Status) +
  geom_bar(fill = "#999999") +
  xlab("Gender") + ylab("Count") + custom_theme

dplyr::count(data, data$Ge0der, sort = TRUE)
encode_gender2 = table(data$Ge0der)
table(data$Ge0der)
prop.table(table(data$Ge0der))

#Married
unique(data$Married)

miss_married <- sum(is.na(data$Married))
miss_married #no null values

Married_info_yes = sum(data$Married  == "Yes")
Married_info_yes

Married_info_No = sum(data$Married  == "No")
Married_info_No

attach(data)
Married.count<-table(Married)
Married.count
barplot(Married.count, names.arg=c("Married","Unmarried"), main="Distribution of Married", xlab="Married", ylab="Count")

#Dependants

miss_dependants <- sum(is.na(data$Dependents))
miss_dependants

unique(data$Dependents)

ggplot(data) +
  aes(x =  Dependents , fill = Loa0_Status) +
  geom_bar(fill = "#999999") +
  xlab("Married") + ylab("Count") + custom_theme

zero_count = sum(data$Dependents  == 0)
zero_count

dependents.count <- table(data$Dependents)
dependents.count
barplot(dependents.count, names.arg=c("0","1","2","3+"), main="Distribution of dependants", xlab="Married", ylab="Count")


barplot(table(data$Educatio0),xlab="Education",ylab="Applicants",main="Graduated vs Not Graduated",col="Green")

#self employed
Self_employed=as.numeric(as.factor(data$Self_Emplo1ed ))
Self_employed

barplot(table(data$Self_Emplo1ed),xlab="Self Employed",ylab="Applicants",main="Self Employed vs Non-self Employed ",col="Green")

ggplot(data) +
  aes(x =  Self_Emplo1ed, fill = Loa0_Status) +
  geom_bar(fill = "#999999") +
  xlab("Self Employeed") + ylab("Count") + custom_theme






#property area
barplot(table(data$Propert1_Area),xlab="Area of property",ylab="Applicants",main="Urban vs Rural vs Sub-urban properties",col="Green")


#finding co relation
# getting the correlation between each variable
library(psych)
library(class)
library(caTools)
library(caret)
library(mltools)
library(data.table)

str(data)


real_data <- data
dataset <- data
str(real_data)
data <- data[,2:12]
str(data)

#changing to numeric

data$Ge0der =as.numeric(as.factor(data$Ge0der))
data$Married =as.numeric(as.factor(data$Married))
data$Dependents=as.numeric(as.factor(data$Dependents))
data$Educatio0=as.numeric(as.factor(data$Educatio0))
data$Self_Emplo1ed =as.numeric(as.factor(data$Self_Emplo1ed))
data$Propert1_Area=as.numeric(as.factor(data$Propert1_Area))


str(data)
#finding correlation
cr <-cor(data)
cr
cor(data, method = "spearman")
cor.test(data$Applica0tI0come, data$Loa0_Amou0t_Term)
library(corrplot)
corrplot(cr)
corrplot(cr, method = "pie")

# Knn classifier
dataset<-data
str(dataset)
View(dataset)
data_scaled = as.data.frame(scale(data[,7:10]))
str(data_scaled)
data_scaled$Self_Emplo1ed = dataset$Self_Emplo1ed
data_scaled$Educatio0 = dataset$Educatio0
data_scaled$Dependents = dataset$Dependents
data_scaled$Married = dataset$Married
data_scaled$Ge0der = dataset$Ge0der
data_scaled$Loa0_Id = dataset$Loa0_Id
data_scaled$Credit_Histor1 = dataset$Credit_Histor1
data_scaled$Propert1_Area = dataset$Propert1_Area
data_scaled$Loa0_Status = dataset$Loa0_Status
View(data_scaled)

data=data_scaled[1:11]
data <- dummyVars(" ~ .", data=data)
newdata <- data.frame(predict(data, newdata = dataset)) 
head(dataset)
dataset<-cbind(newdata,dataset[13])
dataset$Loa0_Status<-as.factor(dataset$Loa0_Status)
table(dataset$Loa0_Status)
str(dataset)
#install.packages("ROSE")
library(ROSE)
over <- ovun.sample(Loa0_Status~., data=dataset, method= "over",N=800)$data
str(over)
table(over$Loa0_Status)
set.seed(240)
dataset<-over
samplesplit<-sample.split(dataset$Loa0_Status,SplitRatio = 0.75)
head(samplesplit)
length(samplesplit)

# Train-test splitting
df1_train<-subset(dataset,samplesplit==TRUE)
df1_test<-subset(dataset,samplesplit==FALSE)
str(df1_train)
length(df1_test)
length(df1_train)
## KNN classifier

# build the KNN classifier over dataset
knn_classifier<-knn(train=df1_train[,1:12],test=df1_test[,1:12],cl=df1_train$Loa0_Status,k=4)
knn_classifier

con_matrix<-table(Actual=df1_test$Loa0_Status,Predicted=knn_classifier)
con_matrix
accuracy<-sum(diag(con_matrix))/sum(con_matrix)
accuracy


#random forest
data <-real_data
library(party)
library(randomForest)
dataset<-data
View(dataset)
View(data)
data_scaled = as.data.frame(scale(data[,7:10]))
data_scaled$Self_Emplo1ed = dataset$Self_Emplo1ed
data_scaled$Educatio0 = dataset$Educatio0
data_scaled$Dependents = dataset$Dependents
data_scaled$Married = dataset$Married
data_scaled$Ge0der = dataset$Ge0der
data_scaled$Loa0_Id = dataset$Loa0_Id
data_scaled$Credit_Histor1 = dataset$Credit_Histor1
data_scaled$Propert1_Area = dataset$Propert1_Area
data_scaled$Loa0_Status = dataset$Loa0_Status
View(data_scaled)

data=data_scaled[1:11]
str(data)
data <- dummyVars(" ~ .", data=data)
newdata <- data.frame(predict(data, newdata = dataset)) 
dataset<-cbind(newdata,dataset[13])
dataset$Loa0_Status<-as.factor(dataset$Loa0_Status)
table(dataset$Loa0_Status)
library(ROSE)
over <- ovun.sample(Loa0_Status~., data=dataset, method= "over",N=800)$data
str(over)
table(over$Loa0_Status)
set.seed(240)
dataset<-over
samplesplit<-sample.split(dataset$Loa0_Status,SplitRatio = 0.75)
head(samplesplit)
length(samplesplit)

# Train-test splitting
df1_train<-subset(dataset,samplesplit==TRUE)
df1_test<-subset(dataset,samplesplit==FALSE)
length(df1_test)
length(df1_train)

str(df1_train)

output.forest <- randomForest(Loa0_Status ~ ., data = df1_train,ntree=700,mtry=6)
print(output.forest)

predTrain <- predict(output.forest, df1_train, type = "class")
# Checking Training accuracy
con_matrix<-table(Actual= df1_train$Loa0_Status,predicted=predTrain) 
print(con_matrix)
accuracy<-sum(diag(con_matrix))/sum(con_matrix)
accuracy


pred_train <- predict(output.forest, df1_test, type = "class")
# Checking Testing accuracy 
con_matrix<-table(actual=df1_test$Loa0_Status,predicted=pred_train)  
print(con_matrix)
accuracy<-sum(diag(con_matrix))/sum(con_matrix)
accuracy


#svm 
data<-real_data
library('caret')
str(data)
head(data)

#changing to numeric
data$Ge0der =as.numeric(as.factor(data$Ge0der))
data$Married =as.numeric(as.factor(data$Married))
data$Dependents=as.numeric(as.factor(data$Dependents))
data$Educatio0=as.numeric(as.factor(data$Educatio0))
data$Self_Emplo1ed=as.numeric(as.factor(data$Self_Emplo1ed))
data$Propert1_Area=as.numeric(as.factor(data$Propert1_Area))

data <- data[c(-1)]
str(data)

set.seed(3033)
intrain <- createDataPartition(y= data$Loa0_Status , p=0.7,list = FALSE)
training <- data[intrain,]
testing <- data[-intrain,]

dim(training);
dim(testing);

anyNA(data)
summary(data)
str(training)

#factorizing
training[["Loa0_Status"]] = factor(training[["Loa0_Status"]])
trctrl <- trainControl(method = "repeatedcv" , number = 10, repeats = 3)

svm_linear <- train(Loa0_Status~.,data = training, method = "svmLinear"
                    ,trControl = trctrl, preProcess = c("center" , "scale"),
                    tuneLength = 10)


svm_linear

test_predict <- predict(svm_linear,newdata = testing)
test_predict

confusionMatrix(table(test_predict,testing$Loa0_Status))

length(data$Loa0_Status)
length(test_predict)
length(testing)

grid <- expand.grid(C= c(0.01,0.05,0.1,0.25,0.5,0.75,1,1.25,1.5,1.75,2.5))
set.seed(3233)
svm_linear_grid <-train(Loa0_Status~. , data = training,method="svmLinear"
                        , trControl = trctrl,
                        preProcess = c("center","scale"),
                        tuneGrid = grid,
                        tuneLength = 10)

svm_linear_grid

plot(svm_linear_grid)
test_pred_grid <- predict(svm_linear_grid,newdata = testing)
test_pred_grid

confusionMatrix(table(test_pred_grid,testing$Loa0_Status))


##############
#getting accuracy for user input
data <-real_data
dataset<-data
View(dataset)
View(data)
data=data[2:12]
data <- dummyVars(" ~ .", data=data)
newdata <- data.frame(predict(data, newdata = dataset)) 
dataset<-cbind(newdata,dataset[13])
dataset$Loa0_Status<-as.factor(dataset$Loa0_Status)
set.seed(240)
samplesplit<-sample.split(dataset$Loa0_Status,SplitRatio = 0.75)
head(samplesplit,n=25)
length(samplesplit)

# Train-test splitting
df1_train<-subset(dataset,samplesplit==TRUE)
df1_test<-subset(dataset,samplesplit==FALSE)
for (x in 1:801){
  #data <-real_data
  library(mltools)
  library(data.table)
  data=data[2:12]
  data <- dummyVars(" ~ .", data=data)
  newdata <- data.frame(predict(data, newdata = dataset)) 
  dataset<-cbind(newdata,dataset[13])
  dataset$Loa0_Status<-as.factor(dataset$Loa0_Status)
  set.seed(133)
  samplesplit<-sample.split(dataset$Loa0_Status,SplitRatio = 0.75)
  
  df1_train<-subset(dataset,samplesplit==TRUE)
  df1_test<-subset(dataset,samplesplit==FALSE)
  output.forest <- randomForest(Loa0_Status ~ ., data = df1_train,ntree=700,mtry=6)
  pred_train <- predict(output.forest, df1_test, type = "class")
  con_matrix<-table(predicted=pred_train, actual=df1_test$Loan_Status)  
  print(table(Actual= df1_test$Loan_Status,predicted=pred_train))
  accuracy<-sum(diag(con_matrix))/sum(con_matrix)*100
  print(accuracy)
  if(a<accuracy){
    a=accuracy
    i=x
  }
}



set.seed(133)
samplesplit<-sample.split(dataset$Loa0_Status,SplitRatio = 0.8)
df1_train<-subset(dataset,samplesplit==TRUE)
df1_test<-subset(dataset,samplesplit==FALSE)
output.forest <- randomForest(Loa0_Status ~ ., data = df1_train,ntree=109,mtry=6)
pred_train <- predict(output.forest, df1_test, type = "class")
# Checking classification accuracy
con_matrix<-table(pred_train, df1_test$Loa0_Status)  
print(table(Actual= df1_test$Loa0_Status,predicted=pred_train))
accuracy<-sum(diag(con_matrix))/sum(con_matrix)*100
print(accuracy)

t<-table(pred_train, df1_test$Loa0_Status)  
ac1=sum(diag(t))/sum(t)
sensitivity<-t[2,2]/sum(t[2,])
specificity<-t[1,1]/sum(t[1,])
precision<-t[2,2]/sum(t[,2])


cat("1. The Accuracy of the  Model is:",ac1)
cat("\n2. The Sensitivity of the  Model is:",sensitivity)
cat("\n3. The Specifity of the  Model is:",specificity)
cat("\n4. The Precision of the  Model is:",precision)

cat("Enter 1 for yes OR 0 for no")
r=readline(prompt="Enter the gender:")
if(r=="Female"){
  df1_test[1,1]=1
  df1_test[1,2]=0
}else{
  df1_test[1,1]=0
  df1_test[1,2]=1
}

r=readline(prompt="Enter are you married:")
if(r=="1"){
  df1_test[1,3]=0
  df1_test[1,4]=1
}else{
  df1_test[1,3]=1
  df1_test[1,4]=0
}
r=readline(prompt="Enter the number of dependents:")
if(r=="0"){
  df1_test[1,5]=1
  df1_test[1,6]=0
  df1_test[1,7]=0
  df1_test[1,8]=0
}else if(r=="1"){
  df1_test[1,5]=0
  df1_test[1,6]=1
  df1_test[1,7]=0
  df1_test[1,8]=0
}else if(r=="2"){
  df1_test[1,5]=0
  df1_test[1,6]=0
  df1_test[1,7]=1
  df1_test[1,8]=0
}else{
  df1_test[1,5]=0
  df1_test[1,6]=0
  df1_test[1,7]=0
  df1_test[1,8]=1
}
r=readline(prompt="Enter are you graduate:")
if(r=="1"){
  df1_test[1,9]=1
  df1_test[1,10]=0
}else{
  df1_test[1,9]=0
  df1_test[1,10]=1
}
r=readline(prompt="Enter are you self-employed:")
if(r=="1"){
  df1_test[1,11]=0
  df1_test[1,12]=1
}else{
  df1_test[1,11]=1
  df1_test[1,12]=0
}
df1_test[1,13]=as.integer(readline(prompt="Enter ApplicantIncome:"))
df1_test[1,14]=as.integer(readline(prompt="Enter CoapplicantIncome:"))
df1_test[1,15]=as.integer(readline(prompt="Enter LoanAmount in thousands:"))
df1_test[1,16]=as.integer(readline(prompt="Enter Loan_Amount_Term in months:"))
df1_test[1,17]=as.integer(readline(prompt="Enter Credit_History:"))
cat("Menu\n1.)Enter 1 for Rural\n2.)Enter 2 for Semiurban\n3.)Enter 3 for Urban")
r=readline(prompt="Enter Property_Area:")
if(r=="1"){
  df1_test[1,18]=1
  df1_test[1,19]=0
  df1_test[1,20]=0
}else if(r=="2"){
  df1_test[1,18]=0
  df1_test[1,19]=1
  df1_test[1,20]=0
}else{
  df1_test[1,18]=0
  df1_test[1,19]=0
  df1_test[1,20]=1
}
pred_train <- predict(output.forest, df1_test[1,], type = "class")
pred_train
if(pred_train=="N"){
  cat("You will not get loan")
}else{
  cat("You will get loan")
}