echo "Before files created"
ls
for((i=0;i<3;i++))
do
touch "F"$i
done
echo "Files F1, F2, F3 are created"

echo "After files created"
ls
