#include <stdio.h>
#include <string.h>

int isLetter(char c)
{
    return ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z'));
}

char upperChar(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';

    return c;
}

void createMatrix(char key[], char matrix[5][5])
{
    int used[26] = {0};
    int k = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        char c = upperChar(key[i]);

        if (!isLetter(c))
            continue;

        if (c == 'J')
            c = 'I';

        if (!used[c - 'A'])
        {
            used[c - 'A'] = 1;
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c == 'J')
            continue;

        if (!used[c - 'A'])
        {
            used[c - 'A'] = 1;
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
}

void displayMatrix(char matrix[5][5])
{
    printf("\nPlayfair Matrix:\n");

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void findPosition(char matrix[5][5], char c, int *row, int *col)
{
    if (c == 'J')
        c = 'I';

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == c)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

int preparePlaintext(char text[], char prepared[])
{
    char letters[500];
    int n = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isLetter(text[i]))
        {
            char c = upperChar(text[i]);

            if (c == 'J')
                c = 'I';

            letters[n++] = c;
        }
    }

    int i = 0;
    int k = 0;

    while (i < n)
    {
        char a = letters[i];

        if (i + 1 >= n)
        {
            prepared[k++] = a;

            if (a == 'X')
                prepared[k++] = 'Q';
            else
                prepared[k++] = 'X';

            i++;
        }
        else
        {
            char b = letters[i + 1];

            if (a == b)
            {
                prepared[k++] = a;

                if (a == 'X')
                    prepared[k++] = 'Q';
                else
                    prepared[k++] = 'X';

                i++;
            }
            else
            {
                prepared[k++] = a;
                prepared[k++] = b;
                i += 2;
            }
        }
    }

    prepared[k] = '\0';

    return k;
}

void playfairTransform(char input[], char output[],
                       char matrix[5][5], int encryption)
{
    char letters[500];
    int n = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (isLetter(input[i]))
        {
            char c = upperChar(input[i]);

            if (c == 'J')
                c = 'I';

            letters[n++] = c;
        }
    }

    if (n % 2 != 0)
    {
        printf("Invalid ciphertext: odd number of letters.\n");
        output[0] = '\0';
        return;
    }

    int k = 0;

    for(int i = 0; i < n; i += 2)
    {
        char a = letters[i];
        char b = letters[i + 1];

        int r1, c1, r2, c2;

        findPosition(matrix, a, &r1, &c1);
        findPosition(matrix, b, &r2, &c2);

        if (r1 == r2)
        {
            if (encryption)
            {
                c1 = (c1 + 1) % 5;
                c2 = (c2 + 1) % 5;
            }
            else
            {
                c1 = (c1 + 4) % 5;
                c2 = (c2 + 4) % 5;
            }

            output[k++] = matrix[r1][c1];
            output[k++] = matrix[r2][c2];
        }
        else if(c1 == c2)
        {
            if (encryption)
            {
                r1 = (r1 + 1) % 5;
                r2 = (r2 + 1) % 5;
            }
            else
            {
                r1 = (r1 + 4) % 5;
                r2 = (r2 + 4) % 5;
            }

            output[k++] = matrix[r1][c1];
            output[k++] = matrix[r2][c2];
        }
        else
        {
            output[k++] = matrix[r1][c2];
            output[k++] = matrix[r2][c1];
        }
    }

    output[k] = '\0';
}

void mergeOutput(char original[], char transformed[], char output[])
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

int main()
{
    char key[200];
    char text[500];
    char prepared[500];
    char transformed[500];
    char output[600];

    char matrix[5][5];

    int choice;

    printf("PLAYFAIR CIPHER\n");
    printf("----------------\n");

    printf("Enter key: ");
    scanf(" %199[^\n]", key);

    createMatrix(key, matrix);
    displayMatrix(matrix);

    getchar();

    printf("\n1. Encryption\n");
    printf("2. Decryption\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    getchar();

    printf("Enter text: ");
    scanf(" %499[^\n]", text);

    if(choice == 1)
    {
        preparePlaintext(text, prepared);

        playfairTransform(prepared, transformed, matrix, 1);

        mergeOutput(text, transformed, output);

        printf("\nCiphertext: %s\n", output);
    }
    else if(choice == 2)
    {
        playfairTransform(text, transformed, matrix, 0);

        if(transformed[0] != '\0')
        {
            mergeOutput(text, transformed, output);

            printf("\nDecrypted text: %s\n", output);
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
    return 0;
}
