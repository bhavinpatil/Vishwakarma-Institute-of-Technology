library(randomForest)
f <-read.csv("cpdataset.csv")
#View(f)
str(f)
f$Loan_Status = as.factor(f$Loa0_Status)
#set.seed(123)
str(f) 
index = sample(2,nrow(f), replace = TRUE, prob = c(0.7,0.3));
training <- f[index == 1,]
testing <- f[index ==2,]
RFM = randomForest(Loan_Status ~ ., data = training)
Loan_Status_Pred <- predict(RFM, testing)
testing$Loan_Status_Pred = Loan_Status_Pred 
#View(testing)
CFM <- table(testing$Loan_Status, testing$Loan_Status_Pred) #confusion matrix
cat("\n\n Confusion matrix: \n" )
print(CFM)
Accuracy <- sum(diag(CFM) / sum(CFM))
cat("\n\nclassification Accuracy" , Accuracy )
ac <- sum(diag(CFM))/sum(CFM)
cat("\nAccuracy =", ac)
re <- CFM[2,2]/sum(CFM[2,])
cat("\nRecall =", re)
mspe <- CFM[1,1]/sum(CFM[1,])
cat("\nSpecificity= ",mspe)
pr <- CFM[2,2]/sum(CFM[,2])
cat("\nPrecision= ",mspe)

