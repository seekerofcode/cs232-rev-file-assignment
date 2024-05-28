echo "hello world" > f1
mkdir x

# should succeed
./rev f1 x/f2
if [ $? -ne 0 ]; then
  rm -rf f1 x
  echo "rev into a directory failed"
  exit 255
fi

# check the file is there
if [ ! -f x/f2 ]; then
  rm -rf f1 x
  echo "rev into a directory failed: file not found"
  exit 255
fi

rm -rf x

# Try reversing into root directory (should fail)
./rev f1 /f3
# should fail
if [ $? -ne 255 ]; then
  rm -f f1
  echo "rev into root directory succeeded (should fail)"
  exit 255
fi
rm -rf f1

exit 0
