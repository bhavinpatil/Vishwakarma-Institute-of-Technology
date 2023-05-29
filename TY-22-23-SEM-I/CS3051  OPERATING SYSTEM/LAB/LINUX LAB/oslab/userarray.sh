echo "Enter number of Array: "
read n
echo "Enter Array Number: "
for((i=0; i<$n; i++))
do
	read b
	c[$i]=$b
done
echo "Entered Array is: "
# for((i=0; i<$n; i++))
# do
	# t=${c[$i]}
echo ${c[@]}
# done
