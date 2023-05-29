echo "Enter the Number to print Fibonacci Series:"
read n

a=0
b=1

echo "The Fibonacci Series: "
for(( i=0;i<$n;i++ ))
do
	echo $a
	fn=$((a+b))
	a=$b
	b=$fn
done
