
data <- read.csv("cpdataset.csv")
data


library('caret')
str(data)
head(data)
#changing to numeric
data$Married =as.numeric(as.factor(data$Married))
data$Married 

data$Dependents=as.numeric(as.factor(data$Dependents))
data$Dependents

data$Educatio0=as.numeric(as.factor(data$Educatio0))
data$Educatio0

data$Self_Emplo1ed=as.numeric(as.factor(data$Self_Emplo1ed))
data$Self_Emplo1ed    

data$Propert1_Area=as.numeric(as.factor(data$Propert1_Area))
data$Propert1_Area


data$Ge0der =as.numeric(as.factor(data$Ge0der))
data$Ge0der      

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

