#Ascending Order
echo "Enter the Number of Array:"
read n
echo "Enter the Array Numbers: "
for (( i=0 ; i<$n; i++ ))
do
	read t
	numbers[$i]=$t
done

for (( i=0 ; i < ${#numbers[@]}; i++ )) 
do
    for (( j=0 ; j < ${#numbers[@]}; j++ )) 
    do
      if [[ ${numbers[$j]} -gt  ${numbers[$i]} ]]
      then
        tmp=${numbers[$i]}
        numbers[$i]=${numbers[$j]}
        numbers[$j]=${tmp}
      fi
    done
done


echo "Sorted Array in Ascending Order: "

for n in "${numbers[@]}"
do
    echo "$n"
done

#Descending Order
for (( i=0 ; i < ${#numbers[@]}; i++ )) 
do
    for (( j=0 ; j < ${#numbers[@]}; j++ )) 
    do
      if [[ ${numbers[$j]} -lt  ${numbers[$i]} ]]
      then
        tmp=${numbers[$i]}
        numbers[$i]=${numbers[$j]}
        numbers[$j]=${tmp}
      fi
    done
done

echo "Sorted Array in Descending Order:"

for n in "${numbers[@]}"
do
    echo "$n"
done
