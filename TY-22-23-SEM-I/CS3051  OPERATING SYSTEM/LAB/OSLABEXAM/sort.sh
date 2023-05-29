arr=(10 30 40 20 5)

echo "Array Before Sorting:"
echo ${arr[@]}

for ((i = 0; i < 5; i++))
do
	for((j = 0; j < 5-i-1; j++))
	do
		if [ ${arr[j]} -gt ${arr[$((j+1))]} ]
		then
			temp=${arr[j]}
			arr[$j]=${arr[$((j+1))]}
			arr[$((j+1))]=$temp
		fi
	done
done

echo "Array after sorting:"
echo ${arr[@]}
