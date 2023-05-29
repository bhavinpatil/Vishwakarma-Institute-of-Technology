echo "Enter String to Check Palindrome or not:"
read str

len=${#str}

for(( i=$len-1; i>=0; i-- ))
do
	rev="$rev${str:$i:1}"
done
if [ $str == $rev ]; 
then
	echo "String is Palindrom"
else
	echo "String is not Palindrome"
fi
