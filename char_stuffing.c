#include <stdio.h>

#define DLE 16   // Data Link Escape
#define STX 2    // Start of Text
#define ETX 3    // End of Text

int main() {
    char ch, arr[50], rec[50];
    int len = 0, i, j;

    printf("Enter data stream (characters only):\n");

    // --------------------------------------------------------
    // ADD START FRAME: DLE STX
    // --------------------------------------------------------
    arr[len++] = DLE;
    arr[len++] = STX;

    // --------------------------------------------------------
    // BYTE STUFFING:
    // If the data contains DLE, insert an extra DLE
    // --------------------------------------------------------
    while ((ch = getchar()) != '\n') {

        if (ch == DLE) {
            // Stuffing: duplicate DLE to escape it
            arr[len++] = DLE;
        }

        arr[len++] = ch;   // Store actual data byte
    }

    // --------------------------------------------------------
    // ADD END FRAME: DLE ETX
    // --------------------------------------------------------
    arr[len++] = DLE;
    arr[len++] = ETX;

    // --------------------------------------------------------
    // PRINT STUFFED STREAM
    // (Human readable: print names instead of ASCII values)
    // --------------------------------------------------------
    printf("\nStuffed Stream:\n");
    for (i = 0; i < len; i++) {
        if (arr[i] == DLE)      printf("DLE ");
        else if (arr[i] == STX) printf("STX ");
        else if (arr[i] == ETX) printf("ETX ");
        else                    printf("%c ", arr[i]);
    }

    // --------------------------------------------------------
    // DESTUFFING:
    // If sequence is DLE DLE → remove one DLE
    // Output only actual data bytes
    // --------------------------------------------------------
    printf("\n\nDestuffed Data:\n");

    for (j = 2; j < len - 2; j++) {  // Skip outer DLE STX ... DLE ETX

        // If DLE is found, check if next byte is also DLE
        if (arr[j] == DLE && arr[j + 1] == DLE) {
            printf("DLE ");  // Output single real DLE
            j++;            // Skip stuffed DLE
        }
        else if (arr[j] == DLE && arr[j + 1] != DLE) {
            // This is control framing, should NOT print anything
            continue;
        }
        else {
            // Normal data
            printf("%c ", arr[j]);
        }
    }

    return 0;
}
