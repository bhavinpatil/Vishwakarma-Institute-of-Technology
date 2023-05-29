echo "Enter String to Reverse:"
read str

len=${#str}

for(( i=len-1;i>=0;i-- ))
do
	rev=$rev${str:i:1}
done
echo "$rev"

