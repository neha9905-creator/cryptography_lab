#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plaintext[200], key[100], encrypted[200], decrypted[200];
    int i, j = 0, keyLen;

    printf("Enter the message: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    key[strcspn(key, "\n")] = '\0';
    keyLen = strlen(key);

    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];

        if (isalpha(ch)) {
            if (islower(ch))
                encrypted[i] = ((ch - 'a' + tolower(key[j % keyLen]) - 'a') % 26) + 'a';
            else
                encrypted[i] = ((ch - 'A' + toupper(key[j % keyLen]) - 'A') % 26) + 'A';

            j++;
        } else {
            encrypted[i] = ch;
        }
    }

    encrypted[i] = '\0';

    printf("\nEncrypted Message: %s", encrypted);

    j = 0;

    for (i = 0; encrypted[i] != '\0'; i++) {
        char ch = encrypted[i];

        if (isalpha(ch)) {
            if (islower(ch))
                decrypted[i] = ((ch - 'a' - (tolower(key[j % keyLen]) - 'a') + 26) % 26) + 'a';
            else
                decrypted[i] = ((ch - 'A' - (toupper(key[j % keyLen]) - 'A') + 26) % 26) + 'A';

            j++;
        } else {
            decrypted[i] = ch;
        }
    }

    decrypted[i] = '\0';

    printf("Decrypted Message: %s", decrypted);

    return 0;
}
