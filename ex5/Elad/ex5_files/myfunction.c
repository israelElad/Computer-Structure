//313448888 Elad Israel

#define UPPER_BOUND 255
#define LOWER_BOUND 0
// Compute max and min of two integers, inline
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define DIV9(n) (((n) * 0xE38F) >> 19)

/**
 * Blur the image.
 * Doing it all in one function prevents jumps and stack manipulation of function calls
 */
void blur(Image *image) {

    //size of image(*3 for r,g,b)
    int imgSize = n * m;
    int imgCharSize = imgSize + (imgSize << 1);

    unsigned char *imgCpy = malloc(imgCharSize);
    unsigned char *imgDes = image->data;
    //copy image
    memcpy(imgCpy, imgDes, imgCharSize);

    int charsDimensions = m + (m << 1);
    int columnsLimit = charsDimensions - 3;
    int thisRow, previousRow, nextRow;
    int i, j;
    int sumRed, sumGreen, sumBlue;
    int previousRed, previousGreen, previousBlue, thisGreen, thisBlue, nextRed, nextGreen, nextBlue;
    //thisRed is j;

    for (i = 1; i < m - 1; ++i) {
        //calculate previous row index once instead of every iteration
        previousRow = (i - 1) * charsDimensions;
        thisRow = i * charsDimensions;
        nextRow = (i + 1) * charsDimensions;

        for (j = 3; j < columnsLimit; j += 3) {
            //calculate row's colors indices
            previousRed = j - 3;
            previousGreen = j - 2;
            previousBlue = j - 1;
            //thisRed=j
            thisGreen = j + 1;
            thisBlue = j + 2;
            nextRed = j + 3;
            nextGreen = j + 4;
            nextBlue = j + 5;

            //calculate the sum of each row.
            sumRed = imgCpy[previousRow + previousRed] +
                     imgCpy[previousRow + j] +
                     imgCpy[previousRow + nextRed] +
                     imgCpy[thisRow + previousRed] +
                     imgCpy[thisRow + j] +
                     imgCpy[thisRow + nextRed] +
                     imgCpy[nextRow + previousRed] +
                     imgCpy[nextRow + j] +
                     imgCpy[nextRow + nextRed];
            sumGreen = imgCpy[previousRow + previousGreen] +
                       imgCpy[previousRow + thisGreen] +
                       imgCpy[previousRow + nextGreen] +
                       imgCpy[thisRow + previousGreen] +
                       imgCpy[thisRow + thisGreen] +
                       imgCpy[thisRow + nextGreen] +
                       imgCpy[nextRow + previousGreen] +
                       imgCpy[nextRow + thisGreen] +
                       imgCpy[nextRow + nextGreen];
            sumBlue = imgCpy[previousRow + previousBlue] +
                      imgCpy[previousRow + thisBlue] +
                      imgCpy[previousRow + nextBlue] +
                      imgCpy[thisRow + previousBlue] +
                      imgCpy[thisRow + thisBlue] +
                      imgCpy[thisRow + nextBlue] +
                      imgCpy[nextRow + previousBlue] +
                      imgCpy[nextRow + thisBlue] +
                      imgCpy[nextRow + nextBlue];

            imgDes[thisRow + j] = (unsigned char) (DIV9(sumRed));
            imgDes[thisRow + thisGreen] = (unsigned char) (DIV9(sumGreen));
            imgDes[thisRow + thisBlue] = (unsigned char) (DIV9(sumBlue));
        }
    }
    //free image copy
    free(imgCpy);
}

/**
 * Sharpen the image.
 * Doing it all in one function prevents jumps and stack manipulation of function calls
 */
void sharpen(Image *image) {

    //size of image(*3 for r,g,b)
    int imgSize = n * m;
    int imgCharSize = imgSize + (imgSize << 1);

    unsigned char *imgCpy = malloc(imgCharSize);
    unsigned char *imgDes = image->data;
    //copy image
    memcpy(imgCpy, imgDes, imgCharSize);

    int charsDimensions = m + (m << 1);
    int columnsLimit = charsDimensions - 3;
    int thisRow, previousRow, nextRow;
    int i, j;
    int sumRed, sumGreen, sumBlue;
    int previousRed, previousGreen, previousBlue, thisGreen, thisBlue, nextRed, nextGreen, nextBlue;
    //thisRed is j;
    int thisRedMult, thisGreenMult, thisBlueMult;

    for (i = 1; i < m - 1; ++i) {
        //calculate previous row index once instead of every iteration
        previousRow = (i - 1) * charsDimensions;
        thisRow = i * charsDimensions;
        nextRow = (i + 1) * charsDimensions;

        for (j = 3; j < columnsLimit; j += 3) {
            //calculate row's colors indices
            previousRed = j - 3;
            previousGreen = j - 2;
            previousBlue = j - 1;
            //thisRed=j
            thisGreen = j + 1;
            thisBlue = j + 2;
            nextRed = j + 3;
            nextGreen = j + 4;
            nextBlue = j + 5;

            //calculate the sum of each row.
            sumRed = imgCpy[previousRow + previousRed] +
                     imgCpy[previousRow + j] +
                     imgCpy[previousRow + nextRed] +
                     imgCpy[thisRow + previousRed] +
                     imgCpy[thisRow + nextRed] +
                     imgCpy[nextRow + previousRed] +
                     imgCpy[nextRow + j] +
                     imgCpy[nextRow + nextRed];
            sumGreen = imgCpy[previousRow + previousGreen] +
                       imgCpy[previousRow + thisGreen] +
                       imgCpy[previousRow + nextGreen] +
                       imgCpy[thisRow + previousGreen] +
                       imgCpy[thisRow + nextGreen] +
                       imgCpy[nextRow + previousGreen] +
                       imgCpy[nextRow + thisGreen] +
                       imgCpy[nextRow + nextGreen];
            sumBlue = imgCpy[previousRow + previousBlue] +
                      imgCpy[previousRow + thisBlue] +
                      imgCpy[previousRow + nextBlue] +
                      imgCpy[thisRow + previousBlue] +
                      imgCpy[thisRow + nextBlue] +
                      imgCpy[nextRow + previousBlue] +
                      imgCpy[nextRow + thisBlue] +
                      imgCpy[nextRow + nextBlue];
            //calculates current value times 9
            thisRedMult = imgCpy[thisRow + j] + (imgCpy[thisRow + j] << 3);
            thisGreenMult = imgCpy[thisRow + thisGreen] + (imgCpy[thisRow + thisGreen] << 3);
            thisBlueMult = imgCpy[thisRow + thisBlue] + (imgCpy[thisRow + thisBlue] << 3);

            imgDes[thisRow + j] = (unsigned char) (MIN(MAX((thisRedMult - sumRed), LOWER_BOUND), UPPER_BOUND));
            imgDes[thisRow + thisGreen] = (unsigned char) (MIN(MAX((thisGreenMult - sumGreen), LOWER_BOUND), UPPER_BOUND));
            imgDes[thisRow + thisBlue] = (unsigned char) (MIN(MAX((thisBlueMult - sumBlue), LOWER_BOUND), UPPER_BOUND));
        }
    }
    //free image copy
    free(imgCpy);
}

/**
 * Blurs the image, then sharpen it.
 * writes both results to files.
 */
void myfunction(Image *image, char *srcImgpName, char *blurRsltImgName, char *sharpRsltImgName) {

    // blur the image
    blur(image);

    // save result image in file
    writeBMP(image, srcImgpName, blurRsltImgName);

    // sharpen the image
    sharpen(image);

    // save result image in file
    writeBMP(image, srcImgpName, sharpRsltImgName);
}

