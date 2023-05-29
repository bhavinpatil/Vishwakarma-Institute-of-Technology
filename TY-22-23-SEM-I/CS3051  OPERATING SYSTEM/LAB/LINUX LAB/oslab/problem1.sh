echo "Enter the Number of Array: "
read n
echo "Enter the Array: "
for((i=0; i<$n; i++))
do
	read a
	c[$i]=$a
done
for((i=0; i<$n; i++))
do
	if [ ${c[$i]} -gt 0 ]; then
		pos[$i]=${c[$i]}
	elif [ ${c[$i]} -lt 0 ]; then
		neg[$i]=${c[$i]}
	fi
done
echo "Positive Number are: " ${pos[@]}
echo "Negative Number are: " ${neg[@]}
