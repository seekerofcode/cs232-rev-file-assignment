# 3 args
./rev a b c
# Return the return value from ./rev: it should be 255
if [ $? -ne 255 ]; then
  echo "rev did not return -1 when given 3 arguments"
  exit 255
fi

# 1 arg
./rev a
if [ $? -ne 255 ]; then
  echo "rev did not return -1 when given 1 argument"
  exit 255
fi
exit 0
