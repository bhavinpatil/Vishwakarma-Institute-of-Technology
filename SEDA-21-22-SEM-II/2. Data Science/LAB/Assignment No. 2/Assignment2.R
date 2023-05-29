# Binomial distribution
f<-read.csv("travelled abroad_csv.csv")
p <- sum(f$Travelledabroad == "Y") / nrow(f)
per <- p * 100
d1 <- dbinom(0:10,10,p)


cat("\n\nProbability p : ", p)
cat("\n\nPercentage of ppl travelled abroad : ", per)
cat("\n\nProbability value from 0 to 10 :\n ",d1)

k <- 0:10
plot(k,d1, type ="l")

# to check success and failure satisfaction (success failure rule):
#np>=10
#n(1-p)>=10
#if it is satisfied then normal distribution can be applied
#n is number of samples

# Q.4
d2 <- dbinom(0:100,100,p)
pbd <- sum(dbinom(59:100,100,p))
cat("\n\nProbability for k>59 with Binomial Distribution: ",pbd)
k1<-0:100
plot(k1,d2,type="l")


# Normal Distribution     
# mu = np
# sigma = sqrt(np(1-p))
m<- 100*p
sd <- sqrt(100*p*(1-p))
cat("\n\nMean: ", m)
cat("\n\nStandard Deviation: ",sd)
p <- pnorm(59,m,sd,lower.tail = F)
cat("\n\nProbability for k> 59 by Normal Distribution: ",p)

