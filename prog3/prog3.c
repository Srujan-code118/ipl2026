#include <stdio.h>

void printBits(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        unsigned int mask = 1u << i;
        printf("%d", (n & mask) ? 1 : 0);

        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}

int countOnes(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int main() {
    unsigned int x;
    printf("Enter a number : ");
    scanf("%d",&x);

    printf("Binary of %u:\n", x);
    printBits(x);

    printf("Number of 1 bits = %d\n", countOnes(x));

    return 0;
}