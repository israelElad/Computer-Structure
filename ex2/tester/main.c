// 313448888 Elad Israel

#include <stdio.h>
#include <string.h>

#define BACKSLASH_R 0x000d
#define BACKSLASH_N 0x000a


void swapTwoBytes(unsigned char twoBytes[]);

int exactCopyOrEndianSwap(char **argv, int swapEndianness);

int createWithChangedLetter(FILE *oldFile, FILE *newFile, const unsigned char
oldLetter[], unsigned char newLetter[], int swapEndianness);

int convertOS(char **argv, int swapEndianness);

/************************************************************************
 * function name: main
 * The Input: -
 * The output: 0 if successful, -1 if an error occurred
 * The Function operation: receives details about the way the file
 * should be copied:
 * exact copy if only two parameters were received,
 * with conversion of new line characters to another OS,
 * and/or switching endianness from little endian to big endian.
 * then it executes that mission accordingly using the appropriate methods
*************************************************************************/
int main(int argc, char **argv) {
    switch (argc) {
        case 3:
            //exact copy
            if (exactCopyOrEndianSwap(argv, 0) == 0) {
                return 0;
            }
            //fail
            return -1;

        case 5:
            //convert OS, without change in endianness
            if (convertOS(argv, 0) == 0) {
                return 0;
            }
            //fail
            return -1;

        case 6:
            if (strcmp(argv[5], "-keep") == 0) {
                //convert OS, without change in endianness
                if (convertOS(argv, 0) == 0) {
                    return 0;
                }
            } else if (strcmp(argv[5], "-swap") == 0) {
                //convert OS, with change in endianness
                if (convertOS(argv, 1) == 0) {
                    return 0;
                }
            }
        default:
            //Invalid input
            return -1;
    }
}

/*******************************************************************************
 * function name: convertOS
 * The Input: argv array from user, swapEndianness
 *            containing 1 if swap is needed, and 0 otherwise.
 * The output: 0 if successful, -1 otherwise.
 * The Function operation: determines according to the arguments
 * inserted by user which characters should be replaced by which characters,
 * and calls the function that creates the file accordingly.
*******************************************************************************/
int convertOS(char **argv, int swapEndianness) {
    //if same OS
    if (strcmp(argv[3], argv[4]) == 0) {
        return exactCopyOrEndianSwap(argv, swapEndianness);
    }
    FILE *oldFile, *newFile;
    unsigned char oldLetter[3];
    oldLetter[1] = '\0';
    oldLetter[2] = '\0';
    unsigned char newLetter[3];
    newLetter[1] = '\0';
    newLetter[2] = '\0';
    //open file in read binary only mode
    oldFile = fopen(argv[1], "rb");
    if (oldFile == NULL) {
        //No file exists with that name- exit program.
        return -1;
    }
    //open file in write binary mode only. If already exists- overwrite.
    newFile = fopen(argv[2], "wb");
    if (newFile == NULL) {
        //Cannot create file.
        return -1;
    }

    if (strcmp(argv[3], "-unix") == 0) {
        oldLetter[0] = BACKSLASH_N;  //'\n'
    } else if (strcmp(argv[3], "-mac") == 0) {
        oldLetter[0] = BACKSLASH_R;  //'\r'
    } else if (strcmp(argv[3], "-win") == 0) {
        oldLetter[0] = BACKSLASH_R;  //'\r'
        oldLetter[1] = BACKSLASH_N;  //'\n'
    } else {
        //Invalid input
        return -1;
    }

    if (strcmp(argv[4], "-unix") == 0) {
        newLetter[0] = BACKSLASH_N;  //'\n'
    } else if (strcmp(argv[4], "-mac") == 0) {
        newLetter[0] = BACKSLASH_R;  //'\r'
    } else if (strcmp(argv[4], "-win") == 0) {
        newLetter[0] = BACKSLASH_R;  //'\r'
        newLetter[1] = BACKSLASH_N;  //'\n'
    } else {
        //Invalid input
        return -1;
    }
    //create the file
    if (createWithChangedLetter(oldFile, newFile, oldLetter, newLetter,
                                swapEndianness) != 0) {
        return -1;
    }
    if (ferror(oldFile) != 0) {
        return -1;
    }
    //closing the files
    fclose(oldFile);
    fclose(newFile);
    return 0;
}

/*******************************************************************************
 * function name: exactCopyOrEndianSwap
 * The Input: argv array from user, swapEndianness
 *            containing 1 if swap is needed, and 0 otherwise.
 * The output: 0 if successful, -1 otherwise.
 * The Function operation: reads and create a file according to the arguments
 * inserted by user.
 * then copies the first file to the next, two bytes at a time, as UTF-16 is
 * encoding each character as 2 bytes,
 * if there is a need to swap endianness it swaps the endianness of the 2 bytes
 * inside the buffer before writing it.
*******************************************************************************/
int exactCopyOrEndianSwap(char **argv, int swapEndianness) {
    FILE *oldFile, *newFile;
    unsigned char twoBytes[2];
    //open file in read binary only mode
    oldFile = fopen(argv[1], "rb");
    if (oldFile == NULL) {
        //No file exists with that name- exit program.
        return -1;
    }
    //open file in write binary mode only. If already exists- overwrite.
    newFile = fopen(argv[2], "wb");
    if (newFile == NULL) {
        //Cannot create file.
        return -1;
    }
    //read 1 element whose size is 2 bytes into twoBytes char array.
    while (fread(twoBytes, 2, 1, oldFile) == 1) {
        if (swapEndianness) {
            swapTwoBytes(twoBytes);
        }
        fwrite(twoBytes, 2, 1, newFile);
    }
    //error occurred, before reaching end of file
    if (ferror(oldFile) != 0) {
        return -1;
    }
    //close the files.
    fclose(oldFile);
    fclose(newFile);
    return 0;
}

/*******************************************************************************
 * function name: createWithChangedLetter
 * The Input: pointer to the old and new file, arrays containing the letters of
 * the previous OS and the letters of the new OS. swapEndianness
 *            containing 1 if swap is needed, and 0 otherwise.
 * The output: 0 if successful, -1 otherwise.
 * The Function operation: reading from the old file to the new one.
 * if it copies from windows OS, it reads twice, as windows new lines are
 * encoded as "\r\n".
 * if it copies to windows it inserts 2 characters for every 1 in the source
 * file, for the same reason.
 * otherwise, it copies all the content of the file, and switches \n with \r
 * in mac/unix.
 * if there is a need to swap endianness it swaps the endianness of the 2 bytes
 * inside the buffer before writing it.
*******************************************************************************/
int createWithChangedLetter(FILE *oldFile, FILE *newFile, const unsigned char
oldLetter[], unsigned char newLetter[], int swapEndianness) {
    unsigned char twoBytes[2];
    if (oldLetter[1] == '\0' && newLetter[1] == '\0') {//not from or to windows
        if (swapEndianness) {
            //swap only once since it should be inserted the same way every time
            swapTwoBytes(newLetter);
        }
        //read a 2 bytes element into twoBytes char array, from old file.
        while (fread(twoBytes, 2, 1, oldFile) == 1) {
            if (twoBytes[0] == oldLetter[0]) { //found a letter to switch
                fwrite(newLetter, 2, 1, newFile);
            } else { //hasn't found a letter to switch
                if (swapEndianness) {
                    swapTwoBytes(twoBytes);
                }
                fwrite(twoBytes, 2, 1, newFile);
            }
        }
    } else if (oldLetter[1] != '\0') {//from windows, to unix or mac
        if (swapEndianness) {
            //swap only once since it should be inserted the same way every time
            swapTwoBytes(newLetter);
        }
        //read a 2 bytes element into twoBytes char array, from old file.
        while (fread(twoBytes, 2, 1, oldFile) == 1) {
            if (twoBytes[0] == oldLetter[0]) { //'\r' was read
                unsigned char backslashR[2];
                backslashR[0] = twoBytes[0];
                backslashR[1] = twoBytes[1];
                //read another 2 bytes element into twoBytes char array.
                if (fread(twoBytes, 2, 1, oldFile) == 1) {
                    if (twoBytes[0] == oldLetter[1]) { //read '\r' and then '\n'
                        //write the 2 bytes element into twoBytes char array.
                        fwrite(newLetter, 2, 1, newFile);
                    } else { //'\r' was read and then not '\n'
                        if (swapEndianness) {
                            swapTwoBytes(backslashR);
                        }
                        //write '\r'
                        fwrite(backslashR, 2, 1, newFile);
                        if (swapEndianness) {
                            swapTwoBytes(twoBytes);
                        }
                        //write second character
                        fwrite(twoBytes, 2, 1, newFile);
                    }
                }
            } else {// something other than '\r' was read
                if (swapEndianness) {
                    swapTwoBytes(twoBytes);
                }
                fwrite(twoBytes, 2, 1, newFile);
            }
        }
    } else {//to windows, from unix or mac
        //read a 2 bytes element into twoBytes char array, from old file.
        while (fread(twoBytes, 2, 1, oldFile) == 1) {
            if (twoBytes[0] == oldLetter[0]) {//found a letter to switch
                //write '\r'
                twoBytes[0] = BACKSLASH_R;
                twoBytes[1] = 0x0000;
                if (swapEndianness) {
                    swapTwoBytes(twoBytes);
                }
                fwrite(twoBytes, 2, 1, newFile);
                //write '\n'
                twoBytes[0] = BACKSLASH_N;
                twoBytes[1] = 0x0000;
                if (swapEndianness) {
                    swapTwoBytes(twoBytes);
                }
                fwrite(twoBytes, 2, 1, newFile);
            } else { // hasn't found a letter to switch
                if (swapEndianness) {
                    swapTwoBytes(twoBytes);
                }
                fwrite(twoBytes, 2, 1, newFile);
            }
        }
    }
    //the possibility of from win and to win is dealt with in the calling method
    return 0;
}

/*******************************************************************************
 * function name: swapTwoBytes
 * The Input: a char array containing two bytes
 * The output: 0 if successful
 * The Function operation: swaps the first and second byte using
 * a temporary char.
*******************************************************************************/
void swapTwoBytes(unsigned char twoBytes[]) {
    unsigned char temp = twoBytes[0];
    twoBytes[0] = twoBytes[1];
    twoBytes[1] = temp;
}