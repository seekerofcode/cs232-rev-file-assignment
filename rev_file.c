
/*
 * The cp program, that just copies one file to another.
 * NOTE: only copies an existing file contents to a new file.  Does not
 * work recursively.  Fails if the new file exists already.
 * Needs to check *every* possible error and give a good descriptive error
 * message.
 * Usage: copy <srcfile> <destfile>
 *
 * Author: Victor Norman  (vtn2@calvin.edu)
 * Date: 2/18/2018
 * For: CS232, Homework02
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define DEBUG 1

void usage_and_exit(char *msg) {
    fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "Usage: copy <srcfile> <destfile>\n");
    exit(-1);
}

void print_message_and_exit(char *format_str, char *str) {
    char buffer[128];
    if (snprintf(buffer, 128, format_str, str) < 1) {
        perror("snprintf error");
        exit(-1);
    }
    perror(buffer);
    exit(-1);
}

FILE *open_file(char *fname, char *mode) {
    FILE *f = fopen(fname, mode);
    if (f == NULL) {
        print_message_and_exit("Error opening file \"%s\"", fname);
    }
    return f;
}

void check_num_args(int argc, char **argv) {
    if (argc != 3) {
        usage_and_exit("Wrong number of arguments.");
    }
}

void check_src_file_is_regular(char *src) {
    struct stat sb;
    /* Check if the src file is a file.  If not, exit out. */
    if (stat(src, &sb) != 0) {
        print_message_and_exit("Error: getting status of %s failed\n", src);
    }
    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "Error: %s is not a regular file.\n", src);
        exit(-1);
    }
}

void close_files(char *src, char *dest, FILE *fsrc, FILE *fdest) {
    if (fclose(fsrc) != 0) {
        print_message_and_exit("Error closing file \"%s\"", src);
    }
    if (fclose(fdest) != 0) {
        print_message_and_exit("Error closing file \"%s\"", dest);
    }
}

void copy_src_to_dest(char *src, char *dest) {
    FILE *fsrc = open_file(src, "r");
    FILE *fdest = open_file(dest, "w");
    int c;
    // move read pointer to the last byte in the file.
    fseek(fsrc, -1, SEEK_END);

    if (DEBUG) {
        printf("Copying %s to %s\n", src, dest);
    }
    while (1) {
        c = fgetc(fsrc);

        /* fgetc() returns EOF on end of file or error.  Only way to tell the
           difference is by calling ferror(). */
        if (c == EOF) {
            if (ferror(fsrc) != 0) {
                print_message_and_exit("Error reading from file \"%s\"", src);
            } else {
                break;  // done
            }
        }

        if (fputc(c, fdest) == EOF) {
            print_message_and_exit("Error writing to file \"%s\"", dest);
        }
        // go backward 2 since fgetc moves the read pointer forward 1.
        if (fseek(fsrc, -2, SEEK_CUR) == -1) {
            break;
        }
    }
    close_files(src, dest, fsrc, fdest);
}

int main(int argc, char *argv[]) {
    /* These functions exit(-1) if there is a problem. */
    check_num_args(argc, argv);
    check_src_file_is_regular(argv[1]);
    copy_src_to_dest(argv[1], argv[2]);
    return 0; /* no error */
}

/*
 * Grader: please look for these things:
 * o Name and login id at top of file.
 * o their code must check the number of arguments and fail with a good
message if
 *   the wrong number of args is given.
 * o all output (which should only be errors) must be sent to stderr.
 * o should use snprintf() not sprintf() so that there is no chance of
overrunning
 *   a buffer.
 * o ALL calls that return errors must have their return values checked and
an
 *   appropriate error printed.  (Easiest to do with perror.)
 * o main must return a value < 0 for any error condition and 0 when no
error.
 * o Code should be clean and neat with good consistent indenting, good
variable names,
 *   good function names, etc.
 *
 * Run these tests:
 * PASSING tests:
 * o a good test that copies a file.  Use a binary file (like a .jpg) to
make sure that works. Use md5 or md5sum to make sure the contents are
identical.  If copying a binary file fails, try a text file.
 * o destination file is in a directory that exists -- this test should
pass.
 * o src file path contains a directory that exists -- this test should
pass.  I.e., you should
 *   be able to copy from xyz/abc to somefile.   If this doesn't work for
students, no penalty.
 * FAILING tests:
   ALL error message you see should be descriptive of the error: no "error
   seen" messages.
 * o too few arguments.
 * o too many arguments.
 * o src file does not exist.
 * o src file exists but is not readable -- use chmod 222 to make a file
only writeable.
 * o destination file is in a directory that is not writeable.
 * o dest file is in a non-existent directory.
 * o src file is in a non-existent directory.
 * o src or dest file name is very long -- or just check code to see if they
use
 *   sprintf() or some such thing that can overrun the buffer.
 * o inspect the code to make sure the files are closed before the program
ends.
 * o src is a directory.  Make sure destination file is not created.
 */
