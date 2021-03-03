#include "blake256.h"

uint16_t SIZE = 101;
uint16_t IT_NUM = 10;

void str_to_bin(uint8_t in[], uint8_t bin[][9]) {

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 7; j >= 0; --j) {
            if (in[i] & (1 << j)) {
                bin[i][7 - j] = '1';
            } else {
                bin[i][7 - j] = '0';
            }
            bin[i][8] = '\0';
        }
    }
}

void rand_str(char *dest, size_t length) {
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

int main() {
    for (int i = 1; i <= 15; ++i) {
        printf("__________________________________\n");
        ROUNDS = i;
        printf("Number of rounds: %d\n", ROUNDS);

        uint32_t diff = 0;
        for (int j = 0; j < IT_NUM; ++j) {
            uint8_t data1[SIZE];
            rand_str(data1, SIZE - 1);

            char bin[SIZE][9];
            str_to_bin(data1, bin);
            if (bin[SIZE - 2][7] == '0') {
                bin[SIZE - 2][7] = '1';
            } else {
                bin[SIZE - 2][7] = '0';
            }

            uint8_t data2[SIZE];
            for (int l = 0; l < SIZE; ++l) {
                char c = strtol(bin[l], 0, 2);
                data2[l] = c;
            }

            uint8_t digest1[33];
            Blake256Hash(digest1, data1, SIZE);
            char binDigest1[33][9];
            str_to_bin(digest1, binDigest1);

            uint8_t digest2[33];
            Blake256Hash(digest2, data2, SIZE);
            char binDigest2[33][9];
            str_to_bin(digest2, binDigest2);

            for (int l = 0; l < 32; ++l) {
                for (int k = 0; k < 9; ++k) {
                    if (binDigest1[l][k] != binDigest2[l][k]) {
                        ++diff;
                    }
                }
            }
        }
        printf("Number of different bits: %d\n", diff / IT_NUM);
    }

    return 0;
}