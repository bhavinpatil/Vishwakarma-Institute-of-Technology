
# factorial()
# {
#     product=$1
           
#     # Defining a function to calculate factorial using recursion
#     if((product <= 2)); then
#         echo $product
#     else
#         f=$((product -1))
        
# # Recursive call

# f=$(factorial $f)
# f=$((f*product))
# echo $f
# fi
# }

# # main program
# # reading the input from user
# echo "Enter the number:"   
# read num

# # defining a special case for 0! = 1
# if((num == 0)); then   
# echo 1
# else
# #calling the function
# factorial $num
# fi

echo "Enter a number"
read num

fact=1

while [ $num -gt 1 ]
do
  fact=$((fact * num))  #fact = fact * num
  num=$((num - 1))      #num = num - 1
done

echo $fact