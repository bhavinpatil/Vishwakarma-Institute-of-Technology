library(class)
dataset <- read.csv("wbc_csv.csv")
str(dataset)
View(dataset)
dataset$diagnosis <- as.factor(dataset$diagnosis)
set.seed(123) #to generate the same random number
str(dataset)
r <- sample(nrow(dataset))
wbc <- dataset[r,]


View(wbc)
#View(wbc)
str(wbc)
wbc_mod <- wbc[,3:32]
wbc_mod
View(wbc_mod)

#normalising the dataset
n2 <- function(b){
  (b-min(b))/(max(b)-min(b))
}

wbc_mod <- as.data.frame(lapply(wbc_mod, n2))

View(wbc_mod)

train <- wbc_mod[1:469,]
test <- wbc_mod[470:569,]
train_label <- wbc[1:469,2]
test_label <- wbc[470:569,2]

#KNN

p<-knn(train,test,train_label,k=7)
t<-table(Actual = test_label, Predicted = p)
print(t)

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

