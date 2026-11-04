#include <stdio.h>
#include <string.h>

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void rc4(unsigned char *data, int dataLen,
         unsigned char *key, int keyLen) {

    unsigned char S[256];
    unsigned char K[256];

    int i, j = 0, k = 0;

    for(i = 0; i < 256; i++) {
        S[i] = i;
        K[i] = key[i % keyLen];
    }

    for(i = 0; i < 256; i++) {
        j = (j + S[i] + K[i]) % 256;
        swap(&S[i], &S[j]);
    }

    i = 0;
    j = 0;

    for(k = 0; k < dataLen; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        swap(&S[i], &S[j]);

        data[k] ^= S[(S[i] + S[j]) % 256];
    }
}

int main() {

    unsigned char plaintext[] =
        "GITAMUNIVERSITYISDEEMEDTOBEUNIVERSITY";

    unsigned char key[] = "SARAGADAMNEHA";

    unsigned char data[100];

    int len = strlen((char *)plaintext);
    int keyLen = strlen((char *)key);
    int i;

    strcpy((char *)data, (char *)plaintext);

    printf("Plaintext : %s\n", plaintext);
    printf("Key       : %s\n", key);

    rc4(data, len, key, keyLen);

    printf("Ciphertext: ");

    for(i = 0; i < len; i++)
        printf("%02X", data[i]);

    printf("\n");

    rc4(data, len, key, keyLen);

    printf("Decrypted : %s\n", data);

    return 0;
}
