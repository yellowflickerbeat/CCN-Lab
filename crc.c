#include <stdio.h>
#include <string.h>

char data[128], gen[32] = "10110";   // Generator polynomial
char temp[128], remainder[32];
int data_len, gen_len;

void xor_operation() {
    for (int i = 1; i < gen_len; i++)
        remainder[i] = (remainder[i] == gen[i]) ? '0' : '1';
}

void compute_crc() {
    // Copy first generator-length bits into remainder
    for (int i = 0; i < gen_len; i++)
        remainder[i] = temp[i];

    int pointer = gen_len;

    while (pointer <= data_len + gen_len - 2) {
        if (remainder[0] == '1')
            xor_operation();

        // Shift left by 1
        for (int i = 0; i < gen_len - 1; i++)
            remainder[i] = remainder[i + 1];

        remainder[gen_len - 1] = temp[pointer++];
    }
}

int main() {
    gen_len = strlen(gen);

    printf("Enter data bits: ");
    scanf("%s", data);

    data_len = strlen(data);

    // Append zeros for CRC calculation
    strcpy(temp, data);
    for (int i = data_len; i < data_len + gen_len - 1; i++)
        temp[i] = '0';
    temp[data_len + gen_len - 1] = '\0';

    printf("Modified data (after appending zeros): %s\n", temp);

    compute_crc();

    printf("CRC bits: ");
    for (int i = 0; i < gen_len - 1; i++)
        printf("%c", remainder[i]);

    // Create final codeword
    printf("\nFinal codeword: ");
    for (int i = 0; i < data_len; i++) printf("%c", data[i]);
    for (int i = 0; i < gen_len - 1; i++) printf("%c", remainder[i]);

    printf("\n");

    return 0;
}
