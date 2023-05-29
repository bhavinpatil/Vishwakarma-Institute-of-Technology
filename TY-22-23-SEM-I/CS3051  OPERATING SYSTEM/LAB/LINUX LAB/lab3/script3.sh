echo "Enter name for first file"
read file1
echo "Enter name for second file"
read file2

touch $file1 $file2
echo $file1 "and" $file2 "are created successfully"

ls
