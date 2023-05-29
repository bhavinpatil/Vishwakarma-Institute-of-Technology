echo "Enter Number 1: "
read num1
echo "Enter Number 2:"
read num2

echo "Addition is: "
echo $((num1+num2))

echo "Substraction is: "
echo $((num1-num2))

echo "Product is: "
echo $((num1*num2))

echo "Quotient is: "
echo $((num1/num2))

echo "Remainder is: "
echo $((num1%num2))

echo $num1 "Raised to" $num2 "is: "
echo $((num1**num2))
