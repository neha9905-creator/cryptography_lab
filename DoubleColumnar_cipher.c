#include <stdio.h>
#include <string.h>

void encrypt(char s[], char out[], int key[], int n)
{
    int i,j,k,r,len,rows;
    len=strlen(s);
    rows=len/n;
    k=0;

    for(j=1;j<=n;j++)
        for(i=0;i<n;i++)
            if(key[i]==j)
                for(r=0;r<rows;r++)
                    out[k++]=s[r*n+i];

    out[k]='\0';
}

void decrypt(char s[], char out[], int key[], int n)
{
    int i,j,k,r,len,rows;
    len=strlen(s);
    rows=len/n;
    k=0;

    for(j=1;j<=n;j++)
        for(i=0;i<n;i++)
            if(key[i]==j)
                for(r=0;r<rows;r++)
                    out[r*n+i]=s[k++];

    out[len]='\0';
}

int main()
{
    char text[100],a[100],b[100],c[100];
    int k1[20],k2[20],n,i;

    printf("Enter text: ");
    scanf("%s",text);

    printf("Enter key length: ");
    scanf("%d",&n);

    printf("Enter first key: ");
    for(i=0;i<n;i++)
        scanf("%d",&k1[i]);

    printf("Enter second key: ");
    for(i=0;i<n;i++)
        scanf("%d",&k2[i]);

    while(strlen(text)%n!=0)
        strcat(text,"X");

    encrypt(text,a,k1,n);
    encrypt(a,b,k2,n);

    decrypt(b,c,k2,n);
    decrypt(c,a,k1,n);

    printf("Encrypted: %s\n",b);
    printf("Decrypted: %s\n",a);

    return 0;
}
