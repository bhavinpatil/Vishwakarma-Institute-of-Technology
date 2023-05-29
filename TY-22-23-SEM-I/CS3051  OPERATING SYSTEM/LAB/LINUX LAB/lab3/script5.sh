echo "Enter name for first directory"
read dir1
echo "Enter name for second file"
read dir2

mkdir $dir1 $dir2
echo $dir1 "and" $dir2 "are created successfully"

ls
