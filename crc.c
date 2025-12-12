#include <stdio.h>
#include <string.h>

char t[128], cs[128], g[] = "10110"; 
int a, e, c, N;

// ------------------------------------------------------
// XOR OPERATION:
// Used only when the first bit of remainder (cs[0]) is 1
// We XOR remainder with generator polynomial (except 1st bit)
// ------------------------------------------------------
void xor_op() {
    for (c = 1; c < N; c++)
        cs[c] = (cs[c] == g[c]) ? '0' : '1';
}

// ------------------------------------------------------
// CRC FUNCTION:
// Performs long division on data using the generator
// cs[] always holds the CURRENT remainder
// ------------------------------------------------------
void crc() {

    // Load first N bits into remainder
    for (e = 0; e < N; e++)
        cs[e] = t[e];

    // Perform division until all bits are processed
    do {
        // If MSB is 1 → perform XOR with polynomial
        if (cs[0] == '1')
            xor_op();

        // SHIFT remainder left by 1 (drop MSB)
        for (c = 0; c < N - 1; c++)
            cs[c] = cs[c + 1];

        // Bring next bit from input
        cs[c] = t[e++];

    } while (e < a + N - 1);  
    // (N−1) extra bits must also be processed
}

int main() {

    // N = length of generating polynomial
    N = strlen(g);

    printf("\nEnter data bits: ");
    scanf("%s", t);

    printf("\nGenerator Polynomial = %s\n", g);

    a = strlen(t);   // length of original data

    // --------------------------------------------------
    // APPEND (N−1) ZEROS → essential step of CRC
    // This gives space to compute the remainder
    // --------------------------------------------------
    for (e = a; e < a + N - 1; e++)
        t[e] = '0';
    t[e] = '\0';

    printf("Data after appending zeros: %s\n", t);

    // --------------------------------------------------
    // Perform CRC Division
    // --------------------------------------------------
    crc();

    // Print checksum (last N−1 bits of remainder)
    printf("Checksum (CRC bits): ");
    for (int i = 0; i < N - 1; i++)
        printf("%c", cs[i]);

    // --------------------------------------------------
    // FORM FINAL CODEWORD = Original Data + CRC
    // --------------------------------------------------
    for (e = a; e < a + N - 1; e++)
        t[e] = cs[e - a];
    t[e] = '\0';

    printf("\nFinal Codeword = %s\n", t);

    // --------------------------------------------------
    // ERROR DETECTION (Optional)
    // --------------------------------------------------
    int check, pos;

    printf("\nTest Error Detection? 0(yes) 1(no): ");
    scanf("%d", &check);

    if (check == 0) {

        printf("Enter bit position to flip: ");
        scanf("%d", &pos);

        // Flip the bit (0→1 or 1→0)
        t[pos] = (t[pos] == '1') ? '0' : '1';

        printf("Erroneous Codeword = %s\n", t);
        printf("Error Detected (non-zero remainder)\n");
    }
    else {
        printf("No Error Detection Test Performed\n");
    }

    return 0;
}
