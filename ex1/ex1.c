// 313448888 Elad Israel

#include <stdio.h>

/**
 * Fuction is_little_endian:
 * returns 1 if compiled and ran on a system which operates according to "Little Endian" format,
 * returns 0 if compiled and ran on a system which operates according to "Big Endian" format,
 *
 * It's done by storing integer "1" to memory.
 * if the system is using big endian first byte will be 0 and 0 will be returned.
 * if the system is using little endian first byte will be 1, and 1 will be returned.
 */
int is_little_endian() {
    long checker = 1;
    //points to the address of the number's first byte
    char *address = (char *) &checker;
    //returns the first byte
    return address[0];
}

/**
 * Fuction merge_bytes:
 * returns a word composed of least significant byte of y, and the rest of x's bytes.
 *
 * notice that the position of the least significant byte changes according to the way the system works:
 * if the system is using big endian first byte will be the msbyte.
 * if the system is using little endian first byte will be the lsbyte.
 */
unsigned long merge_bytes(unsigned long x, unsigned long int y) {
    unsigned long xCopy = x;
    //points to the address of the xCopy's first byte
    char *addressX = (char *) &xCopy;
    //points to the address of the y's first byte
    char *addressY = (char *) &y;

    //big endian- MSB first
    if (is_little_endian() == 0) {
        //reaches last byte of both numbers(their size minus 1 due to indices starting from 0) and insert y's to x's.
        addressX[sizeof(unsigned long) - 1] = addressY[sizeof(unsigned long) - 1];
    } else { //little endian- LSB first
        addressX[0] = addressY[0];
    }
    return xCopy;
}

/**
 * Fuction put_bytes:
 * returns the received number after replacing the i'th index with received char.
 *
 * notice that the order of indices changes according to the way the system works,
 * because index 0 is always the lsbyte, goint up towards the msbyte.
 * if the system is using big endian the indices will begin from the highest memory address of the word-
 * index 0 will contain the last byte of the word.
 * if the system is using little endian the indices will begin from the lowest memory address of the word-
 * index 0 will contain the first byte of the word.
 * */
unsigned long put_byte(unsigned long x, unsigned char b, int i) {
    if (i < 0 || i >= sizeof(unsigned long)) {
        printf("Error\n");
        return x;
    }

    //points to the address of the x's first byte
    char *addressX = (char *) &x;

    //big endian- MSB first
    if (is_little_endian() == 0) {
        /*
         * with big endian the indices are backwords- so firstly we reach the last byte of the number
         * (its size minus 1 due to indices starting from 0) and then going backwards i indices,
         * to get to required index. then inserts the char to its position.
         */
        addressX[sizeof(unsigned long) - i - 1] = b;
    } else {    //little endian- LSB first
        addressX[i] = b;
    }
    return x;
}