// BIT STUFFING PROGRAM (EASY VERSION)

#include <stdio.h>
#include <string.h>

int main() {

    // Start and end flag = 01111110 (HDLC)
    char stuffed[50] = "01111110";   
    char destuffed[50];

    char ch;
    int writePos = 8;   // next write index after the starting flag
    int readPos, outPos;
    int oneCount = 0;

    printf("\nEnter the data bits:\n");

    // ---------------------------------------------------------
    // BIT STUFFING:
    // Add '0' after every 5 consecutive '1's
    // ---------------------------------------------------------
    while ((ch = getchar()) != '\n') {

        // Count consecutive 1s
        if (ch == '1')
            oneCount++;
        else
            oneCount = 0;

        // Store the input character
        stuffed[writePos++] = ch;

        // If 5 consecutive ones → stuff '0'
        if (oneCount == 5) {
            stuffed[writePos++] = '0';
            oneCount = 0;
        }
    }

    // Append ending flag
    strcat(stuffed, "01111110");

    printf("\nBit Stuffed Stream:\n");
    for (int i = 0; i < writePos + 8; i++)
        printf("%c", stuffed[i]);


    // ---------------------------------------------------------
    // BIT DE-STUFFING:
    // Remove the stuffed '0' after every sequence of 5 '1's
    // ---------------------------------------------------------
    oneCount = 0;
    outPos = 0;

    printf("\n\nDe-stuffed Stream:\n");

    // Start reading after the first flag → index = 8
    for (readPos = 8; readPos < writePos; readPos++) {

        // Count ones
        if (stuffed[readPos] == '1')
            oneCount++;
        else
            oneCount = 0;

        // Output the bit
        destuffed[outPos++] = stuffed[readPos];

        // If 5 ones followed by a stuffed 0 → skip the 0
        if (oneCount == 5 && stuffed[readPos + 1] == '0') {
            readPos++;
            oneCount = 0;
        }
    }

    // Print destuffed output
    for (int i = 0; i < outPos; i++)
        printf("%c", destuffed[i]);

    return 0;
}
