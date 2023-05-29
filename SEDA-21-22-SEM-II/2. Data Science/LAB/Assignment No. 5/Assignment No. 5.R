
cat("Nearest Neighbour\n")

dataset <- read.csv("knn1_csv.csv")
eucld <- sqrt(((3-dataset$x)**2)+((2-dataset$y)**2))
dataset <- cbind(dataset,eucld)
sorted_data <- dataset[order(dataset$eucld),]
cat("Class of P for NN is", sorted_data[1,4])

cat("\n---------------------------\n")
cat("\n\nK-Nearest Neighbour\n")

#k=5

df <- sorted_data[1:5,]
l1<-length(which(df$class==1))
l2<-length(which(df$class==2))
l3<-length(which(df$class==3))
if(l1>l2 & l1>l3){
  cat("class of P for KNN where k = 5 is : ",1)
  }
if(l2>l1 & l2 > l3){
  cat("class of P for KNN where k = 5 is : ",2)
}else{
  cat("class of P for KNN where k = 5 is : ",3)
}

#k=7

df1 <- sorted_data[1:7,]
l1<-length(which(df1$class==1))
l2<-length(which(df1$class==2))
l3<-length(which(df1$class==3))
if(l1>l2 & l1>l3){
  cat("\nclass of P for KNN where k = 7 is : ",1)
}
if(l2>l1 & l2 > l3){
  cat("\nclass of P for KNN where k = 7 is : ",2)
}else{
  cat("\nclass of P for KNN where k = 7 is : ",3)
}


cat("\n---------------------------\n")
cat("\n\nR-Nearest Neighbour\n")

#R = 1.45

df2 <- sorted_data[sorted_data$eucld<1.45,]
l1<-length(which(df2$class==1))
l2<-length(which(df2$class==2))
l3<-length(which(df2$class==3))
if(l1>l2 & l1>l3){
  cat("\nclass of P for RNN where R = 1.45 is : ",1)
}
if(l2>l1 & l2 > l3){
  cat("\nclass of P for RNN where R = 1.45 is : ",2)
}else{
  cat("\nclass of P for RNN where R = 1.45 is : ",3)
}


cat("\n---------------------------\n")
cat("\n\nModified K-Nearest Neighbour\n")

#K = 5

df3 <- sorted_data[1:5,]
dk <- max(df3$eucld)
d1 <- min(df3$eucld)
w <- (dk - df3$eucld)/(dk-d1)
df3 <- cbind(df3,w)
sum1 <- sum(df3$w[df3$class==1])
sum2 <- sum(df3$w[df3$class==2])
sum3 <- sum(df3$w[df3$class==3])
if(sum1>sum2 & sum1>sum3){
  cat("\nClass of P for MKNN where K = 5 is : ",1)
}
if(sum2>sum1 & sum2>sum3){
  cat("\nClass of P for MKNN where K = 5 is : ",2)
}else{
    cat("\nClass of P for MKNN where K = 5 is : ",3)
}

