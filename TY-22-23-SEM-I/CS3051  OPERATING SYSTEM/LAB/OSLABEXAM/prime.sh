echo "Enter Number: "
read n 

for ((i = 2; i<=n/2; i++))
do
    if [ $((n%i)) -eq 0 ]
    then
        echo "Number is not Prime"
        exit
    fi
done

echo "Number is prime"

num=0
while [ $n -gt 0 ]
do
    num=$(expr $num \* 10)
    k=$(expr $n % 10)
    num=$(expr $num + $k)
    n=$(expr $n / 10)
done
echo "number is $num"