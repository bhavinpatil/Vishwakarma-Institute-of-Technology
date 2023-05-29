cat("\n*Question 1*\n\n")
f <- read.csv("Hypothesis_csv1.csv")
head(f)
x1 <- mean(f$Life_Hrs)
x1
s <- sd(f$Life_Hrs)
s
se <- s/sqrt(50)

se

p1<- pnorm(x1,10000,se)

p1

prcomp(f, scale. = TRUE)

hist(f$Life_Hrs)

str(f)

cat("\n\nMean:",x1)
cat("\n\nStandard Error:",se)
cat("\n\nP Value for Ball bearing Example",p1)

if(p1 < 0.05){
  cat("\n\nReject null Hypothesis for 0.05")
}else{
  cat("\n\nDo not Reject null Hypothesis for 0.05")
}

if(p1 < 0.01){
  cat("\n\nReject null Hypothesis for 0.01")
}else{
  cat("\n\nDo not Reject null Hypothesis for 0.01")
}



cat("\n\n*Question 2*\n")

se2<-17/sqrt(35)
se2
pn <- 2*pnorm(134,130,se2,lower.tail = F)
pn
cat("\n\nP Value of potato chip case study: ",pn)
if(pn > 0.05){
  cat("\n\nReject null Hypothesis for 0.05")
}else{
  cat("\n\nDo not Reject null Hypothesis for 0.05")
}
if(pn < 0.01){
  cat("\n\nReject null Hypothesis for 0.01")
}else{
  cat("\n\nDo not Reject null Hypothesis for 0.01")
}
