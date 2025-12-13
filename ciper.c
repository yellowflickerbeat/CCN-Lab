#include <stdio.h>
#include <ctype.h>

#define MAX 1000

int main() {

    char plain[MAX], cipher[MAX];
    int shift, p, c;

    printf("Enter plaintext:\n");
    fgets(plain, MAX, stdin);
    do {
        printf("Enter key (1–25): ");
        scanf("%d", &shift);
    } while (shift < 1 || shift > 25);

    // ------------------------------
    // ENCRYPTION
    // ------------------------------
    c = 0;
    for (p = 0; plain[p] != '\0'; p++) {
        if (isalpha(plain[p])) {
            char up = toupper(plain[p]);
            cipher[c++] = ((up - 'A') + shift) % 26 + 'A';
        }
    }
    cipher[c] = '\0';

    printf("\nEncrypted text:\n%s\n", cipher);

    // ------------------------------
    // DECRYPTION KEY
    // ------------------------------
    do {
        printf("\nEnter key for decryption: ");
        scanf("%d", &shift);
    } while (shift < 1 || shift > 25);

    // ------------------------------
    // DECRYPTION
    // ------------------------------
    p = 0;
    for (c = 0; cipher[c] != '\0'; c++) {
        plain[p++] = ((cipher[c] - 'A') + (26 - shift)) % 26 + 'A';
    }
    plain[p] = '\0';

    printf("\nDecrypted text:\n%s\n", plain);

    return 0;
}
