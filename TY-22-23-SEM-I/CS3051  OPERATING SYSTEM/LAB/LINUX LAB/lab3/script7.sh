echo "Enter file name you want to change: "
read old
echo "Enter new name for the file name"
read new

echo "Before changing the file name"
ls
mv $old $new
echo "File name channge successfully"
echo "After file name changed"
ls
