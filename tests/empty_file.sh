touch empty
./rev empty e2

# Get the size of the file e2
filesize=$(stat -c%s "e2")

rm -f empty e2
# Check if the file size is not 0
if [ "$filesize" -ne 0 ]; then
  echo "File e2 is not empty."
  exit 255
else
  echo "File e2 is empty."
  exit 0
fi