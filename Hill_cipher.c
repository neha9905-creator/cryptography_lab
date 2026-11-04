#include <stdio.h>
#include <string.h>

int isLetter(char c)
{
    return ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z'));
}

char toUpperChar(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int modInverse(int a, int m)
{
    int x;

    a = (a % m + m) % m;

    for (x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
            return x;
    }

    return -1;
}

void mergeNonLetters(char original[], char transformed[], char output[])
{
    int i, j = 0, k = 0;

    for (i = 0; original[i] != '\0'; i++)
    {
        if (isLetter(original[i]))
        {
            output[k++] = transformed[j++];
        }
        else
        {
            output[k++] = original[i];
        }
    }

    while (transformed[j] != '\0')
        output[k++] = transformed[j++];

    output[k] = '\0';
}

void hillTransform(char text[], int key[2][2], char transformed[],
                   int encryption)
{
    char letters[500];
    int n = 0;
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isLetter(text[i]))
            letters[n++] = toUpperChar(text[i]);
    }

    if (encryption && n % 2 != 0)
        letters[n++] = 'X';

    letters[n] = '\0';

    int outIndex = 0;

    for (i = 0; i < n; i += 2)
    {
        int x = letters[i] - 'A';
        int y = letters[i + 1] - 'A';

        int a = (key[0][0] * x + key[0][1] * y) % 26;
        int b = (key[1][0] * x + key[1][1] * y) % 26;

        transformed[outIndex++] = a + 'A';
        transformed[outIndex++] = b + 'A';
    }

    transformed[outIndex] = '\0';
}

int main()
{
    int key[2][2];
    int inverseKey[2][2];
    int choice;
    int determinant, inverseDeterminant;

    char text[500];
    char transformed[500];
    char output[600];

    printf("HILL CIPHER\n");
    printf("------------\n");

    printf("Enter 2x2 key matrix:\n");

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            scanf("%d", &key[i][j]);
        }
    }

    determinant = key[0][0] * key[1][1]
                - key[0][1] * key[1][0];

    determinant = (determinant % 26 + 26) % 26;

    if (gcd(determinant, 26) != 1)
    {
        printf("Invalid key matrix.\n");
        printf("Determinant must be relatively prime to 26.\n");
        return 0;
    }

    printf("\n1. Encryption\n");
    printf("2. Decryption\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    getchar();

    printf("Enter text: ");
    scanf(" %499[^\n]", text);

    if (choice == 1)
    {
        hillTransform(text, key, transformed, 1);
        mergeNonLetters(text, transformed, output);

        printf("\nCiphertext: %s\n", output);
    }
    else if (choice == 2)
    {
        inverseDeterminant = modInverse(determinant, 26);

        inverseKey[0][0] = ( key[1][1] * inverseDeterminant) % 26;
        inverseKey[0][1] = (-key[0][1] * inverseDeterminant) % 26;
        inverseKey[1][0] = (-key[1][0] * inverseDeterminant) % 26;
        inverseKey[1][1] = ( key[0][0] * inverseDeterminant) % 26;

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                inverseKey[i][j] =
                    (inverseKey[i][j] % 26 + 26) % 26;
            }
        }

        int letterCount = 0;

        for (int i = 0; text[i] != '\0'; i++)
        {
            if (isLetter(text[i]))
                letterCount++;
        }

        if (letterCount % 2 != 0)
        {
            printf("Invalid ciphertext.\n");
            printf("Number of alphabetic characters must be even.\n");
            return 0;
        }

        hillTransform(text, inverseKey, transformed, 0);
        mergeNonLetters(text, transformed, output);

        printf("\nDecrypted text: %s\n", output);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}
