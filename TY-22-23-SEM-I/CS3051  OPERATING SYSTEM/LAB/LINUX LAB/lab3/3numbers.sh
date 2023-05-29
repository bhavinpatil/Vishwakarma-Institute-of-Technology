echo "Enter first Number"
read num1

echo "Enter second Number"
read num2

echo "Enter third Number"
read num3

if [ $num1 -eq $num2 ] && [ $num2 -eq $num3 ]
then
echo "Numbers are Equal"
elif [ $num1 -gt $num2 ] && [ $num1 -gt $num3 ]
then
echo $num1 "is greater than other two numbers"
elif [ $num2 -gt $num1 ] && [ $num2 -gt $num3 ]
then
echo $num2 "is greater than other two numbers"
else
echo $num3 "is greater than other two numbers"
fi

