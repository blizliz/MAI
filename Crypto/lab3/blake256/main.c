#include "blake256.h"

int main() {
    printf("Input message: ");
    uint8_t data[BUFFER_SIZE];

    uint32_t i = 0;
    uint8_t c = getchar();
    while (c != '\n') {
        data[i] = c;
        ++i;
        c = getchar();
    }

    uint8_t digest[33];
    Blake256Hash(digest, data, i);

    printf("Digest: ");
    for (int i = 0; i < 32; ++i) {
        printf("%02x", digest[i]);
    }

    return 0;
}