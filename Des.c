#include <stdio.h>
#include <string.h>

int IP[] = {
58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
};

int FP[] = {
40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25,
};

int E[] = {
32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,
12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,
24,25,24,25,26,27,28,29,28,29,30,31,32,1
};

int P[] = {
16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
};

int PC1[] = {
57,49,41,33,25,17,9,1,58,50,42,34,26,18,
10,2,59,51,43,35,27,19,11,3,60,52,44,36,
63,55,47,39,31,23,15,7,62,54,46,38,30,22,
14,6,61,53,45,37,29,21,13,5,28,20,12,4
};

int PC2[] = {
14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,
26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,
51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
};

int SHIFTS[] = {
1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

int S_BOX[8][4][16] = {
{
{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
},
{
{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
},
{
{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
},
{
{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
},
{
{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
},
{
{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
},
{
{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
},
{
{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
}
};

void permute(char *in, char *out, int *table, int n) {
    int i;
    for (i = 0; i < n; i++)
        out[i] = in[table[i] - 1];
    out[n] = '\0';
}

void xor_bits(char *a, char *b, char *out, int n) {
    int i;
    for (i = 0; i < n; i++)
        out[i] = (a[i] == b[i]) ? '0' : '1';
    out[n] = '\0';
}

void left_shift(char *s, int n) {
    char temp[29];
    int i;
    strcpy(temp, s);
    for (i = 0; i < 28; i++)
        s[i] = temp[(i + n) % 28];
    s[28] = '\0';
}

void generate_keys(char *key, char keys[16][49]) {
    char perm[57], C[29], D[29], CD[57];
    int i;

    permute(key, perm, PC1, 56);

    strncpy(C, perm, 28);
    C[28] = '\0';
    strcpy(D, perm + 28);

    for (i = 0; i < 16; i++) {
        left_shift(C, SHIFTS[i]);
        left_shift(D, SHIFTS[i]);

        strcpy(CD, C);
        strcat(CD, D);

        permute(CD, keys[i], PC2, 48);
    }
}

void sbox_substitution(char *in, char *out) {
    int i, row, col, value;
    char block[7];

    for (i = 0; i < 8; i++) {
        strncpy(block, in + i * 6, 6);
        block[6] = '\0';

        row = (block[0] - '0') * 2 + (block[5] - '0');
        col = (block[1] - '0') * 8 +
              (block[2] - '0') * 4 +
              (block[3] - '0') * 2 +
              (block[4] - '0');

        value = S_BOX[i][row][col];

        out[i * 4]     = (value & 8) ? '1' : '0';
        out[i * 4 + 1] = (value & 4) ? '1' : '0';
        out[i * 4 + 2] = (value & 2) ? '1' : '0';
        out[i * 4 + 3] = (value & 1) ? '1' : '0';
    }

    out[32] = '\0';
}

void feistel(char *right, char *key, char *out) {
    char expanded[49], xored[49], substituted[33];

    permute(right, expanded, E, 48);
    xor_bits(expanded, key, xored, 48);
    sbox_substitution(xored, substituted);
    permute(substituted, out, P, 32);
}

void des(char *block, char *key, char *result, int decrypt) {
    char keys[16][49];
    char perm[65], L[33], R[33], newR[33];
    char f_result[33], combined[65];
    int i, round;

    generate_keys(key, keys);

    permute(block, perm, IP, 64);

    strncpy(L, perm, 32);
    L[32] = '\0';
    strcpy(R, perm + 32);

    for (i = 0; i < 16; i++) {
        round = decrypt ? 15 - i : i;

        feistel(R, keys[round], f_result);
        xor_bits(L, f_result, newR, 32);

        strcpy(L, R);
        strcpy(R, newR);
    }

    strcpy(combined, R);
    strcat(combined, L);

    permute(combined, result, FP, 64);
}

void text_to_bits(char *text, char *bits) {
    int i, j, value;

    for (i = 0; i < 8; i++) {
        value = (unsigned char)text[i];

        for (j = 7; j >= 0; j--)
            bits[i * 8 + (7 - j)] =
                (value & (1 << j)) ? '1' : '0';
    }

    bits[64] = '\0';
}

void bits_to_text(char *bits, char *text) {
    int i, j, value;

    for (i = 0; i < 8; i++) {
        value = 0;

        for (j = 0; j < 8; j++)
            value = value * 2 + (bits[i * 8 + j] - '0');

        text[i] = (char)value;
    }

    text[8] = '\0';
}

int main() {
    char plaintext[] = "welcometogitamuniversityvisakhapatnam";
    char key_text[] = "saragadamneha";
    char key[9], key_bits[65];
    char padded[256], ciphertext[2048] = "";
    char decrypted[256] = "";
    char block[9], block_bits[65], encrypted[65];
    char decrypted_bits[65], decrypted_block[9];
    int len, i, j;

    strncpy(key, key_text, 8);
    key[8] = '\0';

    strcpy(padded, plaintext);
    len = strlen(padded);

    while (len % 8 != 0)
        padded[len++] = ' ';

    padded[len] = '\0';

    text_to_bits(key, key_bits);

    for (i = 0; i < len; i += 8) {
        strncpy(block, padded + i, 8);
        block[8] = '\0';

        text_to_bits(block, block_bits);
        des(block_bits, key_bits, encrypted, 0);

        strcat(ciphertext, encrypted);
    }

    printf("Plaintext : %s\n", plaintext);
    printf("Key       : %s\n", key_text);
    printf("DES Key   : %s\n", key);
    printf("Ciphertext: %s\n", ciphertext);

    for (i = 0; i < len; i += 8) {
        strncpy(block_bits, ciphertext + i * 8, 64);
        block_bits[64] = '\0';

        des(block_bits, key_bits, decrypted_bits, 1);
        bits_to_text(decrypted_bits, decrypted_block);

        for (j = 0; j < 8; j++)
            decrypted[i + j] = decrypted_block[j];
    }

    decrypted[len] = '\0';

    while (len > 0 && decrypted[len - 1] == ' ')
        decrypted[--len] = '\0';

    printf("Decrypted : %s\n", decrypted);

    return 0;
}
