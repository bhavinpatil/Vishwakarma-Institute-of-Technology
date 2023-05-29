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
	if [ $((${c[$i]}%2)) == 0 ]; then
		pos[$i]=${c[$i]}
	elif [ $((${c[$i]}%2)) == 1 ]; then
		neg[$i]=${c[$i]}
	fi
done
echo "Even Number are: " ${pos[@]}
echo "Old Number are: " ${neg[@]}
