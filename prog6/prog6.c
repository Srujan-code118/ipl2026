#include <stdio.h>
#include <math.h>

#define ROWS 25
#define COLS 50

typedef struct {
    int centerX;
    int centerY;
    int radius;
} Circle;

Circle inputCircle();
void initializeBuffer(char buffer[ROWS][COLS]);
void drawCircle(char buffer[ROWS][COLS], Circle c);
void displayBuffer(char buffer[ROWS][COLS]);

int main()
{
    char buffer[ROWS][COLS];
    Circle c;

    c = inputCircle();
    initializeBuffer(buffer);
    drawCircle(buffer, c);
    displayBuffer(buffer);
    return 0;
}

Circle inputCircle()
{
    Circle c;

    printf("Enter center X: ");
    scanf("%d", &c.centerX);

    printf("Enter center Y: ");
    scanf("%d", &c.centerY);

    printf("Enter radius: ");
    scanf("%d", &c.radius);

    return c;
}

void initializeBuffer(char buffer[ROWS][COLS])
{
    int i, j;
    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            buffer[i][j] = ' ';
        }
    }
}

void drawCircle(char buffer[ROWS][COLS], Circle c)
{
    int x, y;
    double distance;

    for(y = 0; y < ROWS; y++)
    {
        for(x = 0; x < COLS; x++)
        {
            distance = sqrt(
                (x - c.centerX) * (x - c.centerX) +
                (y - c.centerY) * (y - c.centerY)
            );

            if(fabs(distance - c.radius) < 0.5)
            {
                buffer[y][x] = '*';
            }
        }
    }
}

void displayBuffer(char buffer[ROWS][COLS])
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", buffer[i][j]);
        }
        printf("\n");
    }
}