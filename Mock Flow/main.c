/*
 * Name: Bryan Johnson
 * NetID: btj117
 * Compiler: GCC
 * Program Description:
 * This program will read a file of randomly generated values as bytes and converts them to a char array.
 * The program will check the values and print a low pressure alert if the value is <= to 550 or high pressure if it is
 * >= 1450. It also prints how many values have been read since the last pressure alert.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// union of bytes and integers
union ISTR
{
    int val;
    char bytes[4];
};


int main(int argc, char *argv[])
{
    char *filename = "flowData.dat"; // filename defaults to flowData.dat
    int val = 0;
    int count = 0;
    int fd;
    int inBytes = -1;
    union ISTR in;

    fd = open(filename, O_RDONLY); // file descriptor to open and read file

    // error catching if opening file fails
    if(fd == -1)
    {
        perror("Opening file for read");
        exit(EXIT_FAILURE);
    }
    // condition if user inputs too many arguments
    if (argc != 1 && argc != 2)
    {
        printf("syntax options:"  // prints syntax options
               "\nreadFile\n"
               "readFile <filename>\n");
        exit(EXIT_SUCCESS); // exits with exit success status
    }

    // condition if user inputs a different filename/path
    if (argc == 2)
    {
        filename = (char*)malloc ( 1024 * sizeof (char) + 1); // allocates memory for user inputted filename
        sscanf(argv[1], "%s", filename); // filename based on user input
        free(filename); // frees allocated memory
    }

    // main loop for reading bytes of file and outputting values as integers
    while (inBytes != 0)
    {
        in.val = val;
        inBytes = read(fd, in.bytes, 2); // reads 2 bytes of each value in file
        // error catching if reading bytes in file fails
        if (inBytes == -1) {
            perror("Reading file"); // error printed
            close(fd); // closes file
            exit(EXIT_FAILURE); // exits with exit failure status
        }
        // condition if read value is less than or equal to 550 & not EOF
        if (in.val <= 550 && inBytes != 0) {
            printf("WARNING! Low Pressure in line: %d psi\n", in.val); // low pressure warning printed
            printf("Values since last alert: %d\n", count); // count since last alert printed
            count = 0; // count since last alert reset to 0
        }
        // condition if read value is greater than or equal to 1450 & not EOF
        if (in.val >= 1450 && inBytes != 0) {
            printf("WARNING! High Pressure in line: %d psi\n", in.val); // high pressure warning printed
            printf("Values since last alert: %d\n", count); // count since last alert printed
            count = 0; // count since last alert reset to 0
        }

        count++; // count since last alert incremented by 1
    }
    close(fd); // closes file

    exit(EXIT_SUCCESS); // exits with exit success status
}