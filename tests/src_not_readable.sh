echo "helloworld" > f1
chmod 000 f1

# Run the command ./rev f1 f2
./rev f1 f2
# Check if the return value is 255
if [ $? -eq 255 ]; then
  rm -rf f1 f2
  exit 0
else
  echo "rev when src is not readable did not return -1"
  rm -rf f1 f2
  exit 255
fi
