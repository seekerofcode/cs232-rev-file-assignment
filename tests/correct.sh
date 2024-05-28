# Create or truncate the file named "numbers"
> numbers

# Write the first 1000 integers to the file
for i in {0..999}; do
  echo $i >> numbers
done

./rev numbers rev_numbers
if [ $? -eq 255 ]; then
  exit 255
fi
# Check if the file size is not 3890
filesize=$(stat -c%s "rev_numbers")
if [ "$filesize" -ne 3890 ]; then
  echo "File e2 is not empty."
  exit 255
fi

# Run md5sum on the file rev_numbers and capture the output
md5_output=$(md5sum rev_numbers)

# Extract the MD5 hash from the output
md5_hash=$(echo $md5_output | awk '{ print $1 }')

# Desired MD5 hash to compare against
desired_hash="3c3fc7e4f3eedf43db9ec4378a48ab0d"

# Compare the hashes
if [ "$md5_hash" != "$desired_hash" ]; then
  echo "MD5 hash does not match. Exiting script."
  exit 1
else
  echo "MD5 hash matches. Continuing script."
fi

rm numbers rev_numbers
exit 0
