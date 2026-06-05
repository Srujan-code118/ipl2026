#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int n;
    char source, auxiliary, destination;
} Frame;

int main() {
    int n;
    printf("Enter number of disks: ");
    scanf("%d", &n);

    Frame stack[100];
    int top = -1;

    stack[++top] = (Frame){n, 'A', 'B', 'C'};

    while (top >= 0) {
        Frame current = stack[top--];

        if (current.n == 1) {
            printf("Move disk 1 from %c to %c\n",
                   current.source,
                   current.destination);
        } else {
            stack[++top] = (Frame){
                current.n - 1,
                current.auxiliary,
                current.source,
                current.destination
            };

            stack[++top] = (Frame){
                1,
                current.source,
                current.auxiliary,
                current.destination
            };

            stack[++top] = (Frame){
                current.n - 1,
                current.source,
                current.destination,
                current.auxiliary
            };
        }
    }
    return 0;
}