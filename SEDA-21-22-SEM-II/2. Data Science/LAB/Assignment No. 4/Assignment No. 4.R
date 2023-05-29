
#Single Linear Regression
cat("Single Linear Regression\n")
dataset <- read.csv("Toy_sales_csv.csv")
head(dataset)
l1 <- lm(Unitsales~Price, dataset)
print(summary(l1))

View(dataset)

#Scatter Plot
library(ggplot2)
p <- ggplot(dataset, aes(Price, Unitsales))+geom_point()+geom_smooth(method = "lm", formula = y~x, col="red", se=F)
print(p)

#Predicted Values

cat("\n\nPredicted Values\n")
pred1 <- predict(l1)
print((pred1))

#Error Values

cat("\n\nError Values\n")
er <- dataset$Unitsales - pred1
print(er)


#Multiple Linear Regression
cat("\n------------------------------------------------------------\n")
cat("\n\n\nMultiple Linear Regression\n")
l2 <- lm(Unitsales ~ Price + Adexp + Promexp, dataset)
print(summary(l2))

#Predicted Values
cat("\n\nPredicted Values\n")
pred2 <- predict(l2)
print(pred2)

s <- data.frame(Price = c(9.1,8.1), Adexp = c(52,50), Promexp = c(61,60))
pred2 <- predict(l2, s)
print(pred2)
