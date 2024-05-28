mkdir d1

./rev d1 f2
# Check if the return value is 255
if [ $? -eq 255 ]; then
  rm -rf d1 f2
  echo "rev when src is directory did not return -1"
  exit 0
else
  rm -rf d1 f2
  exit 255
fi
