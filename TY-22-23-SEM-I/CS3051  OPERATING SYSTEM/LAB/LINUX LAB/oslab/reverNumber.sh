echo "Enter Number to Reverse:"
read num

len=${#num}

for(( i=$len-1; i>=0; i-- ))
do
	rev="$rev${num:$i:1}"
done

echo "Reverse of Given Number is $rev"
