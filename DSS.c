#include <stdio.h>
#include <string.h>

#define P 23
#define Q 11
#define G 2

long long power(long long a, long long b, long long mod) {
    long long result = 1;
    a %= mod;

    while (b > 0) {
        if (b % 2)
            result = (result * a) % mod;

        a = (a * a) % mod;
        b /= 2;
    }

    return result;
}

long long modInverse(long long a, long long m) {
    for (long long i = 1; i < m; i++) {
        if ((a * i) % m == 1)
            return i;
    }
    return -1;
}

long long hashMessage(char message[]) {
    long long hash = 0;

    for (int i = 0; message[i] != '\0'; i++)
        hash = (hash + (unsigned char)message[i]) % Q;

    return hash;
}

int main() {
    char message[200];
    long long x = 3;
    long long k = 4;
    long long y, h, r, s, w, u1, u2, v;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    y = power(G, x, P);
    h = hashMessage(message);

    r = power(G, k, P) % Q;
    s = (modInverse(k, Q) * (h + x * r)) % Q;

    printf("\n--- DSS / DSA Digital Signature ---\n");
    printf("Message       : %s\n", message);
    printf("Prime p       : %d\n", P);
    printf("Prime q       : %d\n", Q);
    printf("Generator g   : %d\n", G);
    printf("Private key x : %lld\n", x);
    printf("Public key y  : %lld\n", y);
    printf("Hash h        : %lld\n", h);
    printf("Signature r   : %lld\n", r);
    printf("Signature s   : %lld\n", s);

    w = modInverse(s, Q);
    u1 = (h * w) % Q;
    u2 = (r * w) % Q;

    v = ((power(G, u1, P) * power(y, u2, P)) % P) % Q;

    printf("Verification v: %lld\n", v);

    if (r == v)
        printf("Digital signature is VALID.\n");
    else
        printf("Digital signature is INVALID.\n");

    return 0;
}
