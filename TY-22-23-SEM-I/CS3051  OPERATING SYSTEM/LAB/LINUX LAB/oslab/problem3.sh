echo "Enter the Number of Array: "
read n
echo "Enter the Array: "
for((i=0; i<$n; i++))
do
	read a
	c[$i]=$a
done

max=${c[0]}
min=${c[0]}

for i in "${c[@]}"
do
	if [[ "$i" -lt "$min" ]]; then
		min="$i"
	elif [[ "$i" -gt "$max" ]]; then
		max="$i"
	fi
done
echo "Smallest Number in the given array is : " $min
echo "Largest Number in the given array is : " $max
