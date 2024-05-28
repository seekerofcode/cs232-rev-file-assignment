These are bash scripts. Run each one from the main directory like this:

`bash tests/correct.sh`

or, to see debugging info as the script runs:

`bash -x tests/correct.sh`

The script returns 0 when it succeeds. It should issue an error message
and return -1 when it fails. You can see the return code of the script
in the shell by doing:

`echo $?`
