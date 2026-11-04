#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plaintext[200], ciphertext[200], decryptedtext[200];
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char key[] = "MNBVCXZLKJHGFDSAPOIUYTREWQ";
    int i, j;

    printf("Enter the message: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];

        if (isalpha(ch)) {
            char upper = toupper(ch);
            int index = upper - 'A';
            ciphertext[i] = key[index];

            if (islower(ch))
                ciphertext[i] = tolower(ciphertext[i]);
        } else {
            ciphertext[i] = ch;
        }
    }

    ciphertext[i] = '\0';

    printf("\nEncrypted Message: %s", ciphertext);

    for (i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];

        if (isalpha(ch)) {
            char upper = toupper(ch);

            for (j = 0; j < 26; j++) {
                if (key[j] == upper) {
                    decryptedtext[i] = alphabet[j];

                    if (islower(ch))
                        decryptedtext[i] = tolower(decryptedtext[i]);

                    break;
                }
            }
        } else {
            decryptedtext[i] = ch;
        }
    }

    decryptedtext[i] = '\0';

    printf("\nDecrypted Message: %s", decryptedtext);

    return 0;
}
