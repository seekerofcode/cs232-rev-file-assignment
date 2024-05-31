/* CS232 -- reversing the contents of a file
 *
 * rev
 * This program copies the contents of one file to another file, but in reverse.
 *
 * Used starter code from homework.
 *
 * Name: Emma Wang (ejw38)
 * Date: 1-25-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for access()
#include <sys/stat.h> // for stat()
#include <string.h>

// Prototypes
void check_num_args(int argc, char *argv[]);
void check_src_file_is_regular(char *path);
int copy_src_to_dest(char *sorc, char *destin);

// Main
int main(int argc, char *argv[])
{
    // These functions exit(-1) if there is a problem.
    check_num_args(argc, argv);
    check_src_file_is_regular(argv[1]);
    copy_src_to_dest(argv[1], argv[2]);
    return 0;   // no error
}

// This function exits if the number of arguments is wrong.
void check_num_args(int argc, char *argv[]) {

    // argc should equal 3; there should be 2 arguments
    if (argc != 3) {
        perror("Error: number of arguments is wrong.");
        exit(-1);
    }
}

// This function exits if src is a not a regular file.
void check_src_file_is_regular(char *path) {

    struct stat checker;

    // does src exist?
    if (access(path, F_OK) == -1) {
        perror("Error: src file doesn't exist.");
        exit(-1);
    }

    // exit if stat() can't get file properties
    if (stat(path, &checker) == -1) {
        perror("Error: unable to retrieve file properties.");
        exit(-1);
    }

    // is it a regular file?
    /* S_ISREG borrowed from
     * https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
     */
    else {
        if (S_ISREG(checker.st_mode) == 0) {
            perror("Error: src is not a regular file.");
            exit(-1);
        }
    }
}

// This function copies src to dest in reverse.
int copy_src_to_dest(char *sorc, char *destin) {

    FILE *src, *dest;
    char c;

    // open src
    src = fopen(sorc, "r");
    if (src == NULL) {
        perror("Error: can't open src file.");
        exit(-1);
    }

    // open dest
    dest = fopen(destin, "w");
    if (dest == NULL) {
        perror("Error: can't open dest file.");
        exit(-1);
    }

    // get src file size
    /* ftell borrowed from
     * https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
     */
    fseek(src, 0, SEEK_END);
    int size = ftell(src);

    // get last character
    fseek(src, -1, SEEK_END);
    c = fgetc(src);

    // loop through src and copy to dest in reverse
    int num = 0;
    while (num < size) {
        fputc(c, dest);
        fseek(src, -2, SEEK_CUR);
        c = fgetc(src);
        num++;
    }

    fclose(src);
    fclose(dest);

    return 0;
}