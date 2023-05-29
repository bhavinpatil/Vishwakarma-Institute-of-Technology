df1 <- read.csv("datasetHA.csv")

# -------------------- Q. 3 Data Pre-processing ------------------

head(df1)

keeps <- c("Reference.Area", "Time.Period","Observation.Value")
df1 <- df1[keeps]
head(df1)
sum(is.null(df))

library(caret)

            #normalizing the observation values.

process <- preProcess(as.data.frame(df1$Observation.Value), method = c("range"))
scale <- predict(process, as.data.frame(df1$Observation.Value))
df1 <- cbind(df1, scale)
colnames(df1) <- c("ReferenceArea", "TimePeriod", "ObservationValue", "Scale")

head(df1)

library(dplyr)

df1 %>% filter(ReferenceArea == "India" ) -> a1
df1 %>% filter(ReferenceArea == "France" ) -> a2
df1 %>% filter(ReferenceArea == "Germany" ) -> a3
df1 %>% filter(ReferenceArea == "Pakistan" ) -> a4
df1 %>% filter(ReferenceArea == "United States of America" ) -> a5

train <- rbind(a1, a2, a3, a4, a5)

train %>% filter(TimePeriod > 2000 & TimePeriod < 2010) -> train

# ------------------- Q.1 Visualization ----------------- 

#---------Bar plot--------
ggplot(train, aes(fill=ReferenceArea, y=ObservationValue, x=TimePeriod))+geom_bar(position="dodge", stat="identity")+theme(axis.text.x =element_text(angle=0,vjust=2),plot.title=element_text(color="black",size=14,face="italic"))+labs(x="Time Period",y="Value",title="Primary Expenditure of 5 Countries")

#---------Box plot--------


# ------------------- Q.2 Meta Data ----------------- 

str(train)
summary(train)

# ------------------- Q.4 Hypothesis Testing for Year 2010 ----------------- 

df1 %>% filter(TimePeriod == 2010) -> Hypotrain
mean(Hypotrain$ObservationValue)

barplot(a1$ObservationValue)

#Population for the data is not normal 
#Using Central Limit theorem - if population is not normal and sample size if more than 30 than 
#we can assume distribution to be nearly normal  


meanObs <- mean(df$ObservationValue)
barplot(a5$ObservationValue)

stdDev <- sd(df$ObservationValue)
stdDev

Pval<- pnorm(893650,meanObs,stdDev)
Pval

if(Pval < 0.05){
  cat("\n\nReject null Hypothesis for 0.05")
}else{
  cat("\n\nDo not Reject null Hypothesis for 0.05")
}

if(Pval < 0.01){
  cat("\n\nReject null Hypothesis for 0.01")
}else{
  cat("\n\nDo not Reject null Hypothesis for 0.01")
}

# ------------------- Q.5 Principle Components ----------------- 

head(train)

prcomtrain <- train[, 2:3]

head(prcomtrain)

prcom <- prcomp(prcomtrain, scale. = TRUE)
summary(prcom)     # 2 PCs are required to pass the 90% of total varience.


# ------------------- Q.6 Cor-relation ----------------- 

head(train)


library(ggplot2)
ggplot(train,aes(TimePeriod,Scale,col=ReferenceArea))+geom_point(size=3)+geom_text(aes(label=""),size=3,nudge_x=0.050)+labs(title="SCATTERPLOT",x="Time Period",y="Values")

cor(train$TimePeriod, train$Scale)
Indi <- cor(a1$TimePeriod, a1$Scale) #Cor-relation Degree for India
Frn <- cor(a2$TimePeriod, a2$Scale) #Cor-relation Degree for France
Usa <- cor(a5$TimePeriod, a5$Scale) #Cor-relation Degree for USA
Ger <- cor(a3$TimePeriod, a3$Scale) #Cor-relation Degree for Germany
Pak <- cor(a4$TimePeriod, a4$Scale) #Cor-relation Degree for Pakistan

fdata <- data.frame(C_name = rep(c('India', 'France', 'Germany', 'Pakistan', 'USA')),
                    Cor_Val = rep(c(Indi, Frn, Ger, Pak, Usa)))

fdata

# ------------------- Q.7 Regression ----------------- 

l1 <- lm(Scale~TimePeriod, a1)
summary(l1)

#Predicted Values
prd <- predict(l1)
prd

#Confirming the Predicted Values
head(a1)

#Error Values
er <- a1$Scale - prd
er
 
#Scatter plot for India with Regression Line
ggplot(a1, aes(TimePeriod, Scale))+geom_point()+geom_smooth(method = "lm", formula = y~x, col="red", se=F)


