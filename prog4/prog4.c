#include<stdio.h>

typedef struct{
    unsigned int firstBit : 1;
    unsigned int secondBit : 2;
    unsigned int thirdBit : 5;
}Bitfield;

int main(){
    Bitfield a;

    a.firstBit = 1;
    a.secondBit = 3;
    a.thirdBit = 15;

    printf("First bit = %u\n",a.firstBit);
    printf("Second bit = %u\n",a.secondBit);
    printf("Third bit = %u\n",a.thirdBit);

    return 0;
}