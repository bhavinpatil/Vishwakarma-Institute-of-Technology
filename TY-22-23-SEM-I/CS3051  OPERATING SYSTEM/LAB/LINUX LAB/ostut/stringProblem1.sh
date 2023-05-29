echo "Enter String 1:" 
read str1
echo "Enter String 2:"
read str2

if [ ${#str1} = ${#str2} ]; then
	echo "Strings are Equal!"
elif [ ${#str1} > ${#str2} ]; then
	echo "String1 is greater than String2"
else
	echo "String2 is greater than String1"
fi
