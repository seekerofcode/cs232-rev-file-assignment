./rev nofile nofile2

# return 255 if the output is not 255
if [ $? -ne 255 ]; then
  echo "script did not return -1 when trying to reverse non-existent file"
  exit 255
fi
exit 0