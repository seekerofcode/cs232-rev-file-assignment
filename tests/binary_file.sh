./rev /bin/sleep rev_sleep
if [ $return_value -eq 255 ]; then
  exit 255
fi

# Get the size of the file /bin/sleep
size_bin_sleep=$(stat -c%s "/bin/sleep")

# Get the size of the file rev_sleep
size_rev_sleep=$(stat -c%s "rev_sleep")

# Check if the sizes are the same
if [ "$size_bin_sleep" -ne "$size_rev_sleep" ]; then
  echo "The size of /bin/sleep is different from the size of rev_sleep."
  rm rev_sleep
  exit 255
fi

rm rev_sleep
exit 0
