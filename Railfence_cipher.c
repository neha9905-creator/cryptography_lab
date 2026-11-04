#include <stdio.h>
#include <string.h>

void trans(char *s, char *out, int *key, int n)
{
    int i,j,r,k=0,len=strlen(s),rows=(len+n-1)/n;

    for(j=1;j<=n;j++)
        for(i=0;i<n;i++)
            if(key[i]==j)
                for(r=0;r<rows;r++)
                    if(r*n+i<len)
                        out[k++]=s[r*n+i];

    out[k]='\0';
}

void detrans(char *s, char *out, int *key, int n)
{
    int i,j,r,k=0,len=strlen(s),rows=(len+n-1)/n;

    for(j=1;j<=n;j++)
        for(i=0;i<n;i++)
            if(key[i]==j)
                for(r=0;r<rows;r++)
                    if(r*n+i<len)
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

    while(strlen(text)%n)
        strcat(text,"X");

    trans(text,a,k1,n);
    trans(a,b,k2,n);

    detrans(b,c,k2,n);
    detrans(c,a,k1,n);

    printf("Encrypted: %s\n",b);
    printf("Decrypted: %s\n",a);

    return 0;
}
