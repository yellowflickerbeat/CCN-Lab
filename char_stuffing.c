#include <stdio.h>

#define DLE 16   // Data Link Escape
#define STX 2    // Start of Text
#define ETX 3    // End of Text

int main() {
    char ch, arr[50], rec[50];
    int len = 0, i, j;

    printf("Enter data stream (characters only):\n");

    
    // DLE STX
    arr[len++] = DLE;
    arr[len++] = STX;
    
    while ((ch = getchar()) != '\n') {

        if (ch == DLE) {
            // Stuffing: duplicate DLE to escape it
            arr[len++] = DLE;
        }

        arr[len++] = ch;   // Store actual data byte
    }

    // END FRAME: DLE ETX

    arr[len++] = DLE;
    arr[len++] = ETX;

    
    printf("\nStuffed Stream:\n");
    for (i = 0; i < len; i++) {
        if (arr[i] == DLE)      printf("DLE ");
        else if (arr[i] == STX) printf("STX ");
        else if (arr[i] == ETX) printf("ETX ");
        else                    printf("%c ", arr[i]);
    }

   
    printf("\n\nDestuffed Data:\n");

    for (j = 2; j < len - 2; j++) {  // Skip outer DLE STX ... DLE ETX

        // If DLE is found, check if next byte is also DLE
        if (arr[j] == DLE && arr[j + 1] == DLE) {
            printf("DLE ");
            j++;            
        }
        else if (arr[j] == DLE && arr[j + 1] != DLE) {

            continue;
        }
        else {
            printf("%c ", arr[j]);
        }
    }

    return 0;
}
