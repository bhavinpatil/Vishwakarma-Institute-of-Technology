str1="VIT"
echo "Firsr String is : " $str1

echo "Enter string: "
read str2
echo "Entered String is : " $str2


echo "Length of String 1 is :" ${#str1}

echo "Concatenation of String 1 and  String 2 is : " $str1$str2

echo "Lowercase of String 1" ${str1,,}

echo "Uppercase of String 2" ${str2^^}

echo "Slicing of String 1" ${str1:0:2}
