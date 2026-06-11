#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_SHAPES 100

/* Shape Types */
typedef enum {
    LINE = 1,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} ShapeType;

/* Shape Structure */
typedef struct {
    int id;
    ShapeType type;
    int x1, y1; /* Start/Top-Left/Center/V1 */
    int x2, y2; /* End/Bottom-Right/Radius/V2 */
    int x3, y3; /* V3 (used only for Triangle) */
    char ch;    /* Character to draw with (default '*') */
} Shape;

/* Canvas functions */
void clearCanvas(char grid[HEIGHT][WIDTH]) {
    int y, x;
    for (y = 0; y < HEIGHT; ++y) {
        for (x = 0; x < WIDTH; ++x) {
            grid[y][x] = '_';
        }
    }
}

void setPixel(char grid[HEIGHT][WIDTH], int x, int y, char ch) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        grid[y][x] = ch;
    }
}

void displayCanvas(char grid[HEIGHT][WIDTH]) {
    int x, y;
    /* Print tens digit of x axis for column numbering */
    printf("   ");
    for (x = 0; x < WIDTH; ++x) {
        if (x >= 10) {
            printf("%d", x / 10);
        } else {
            printf(" ");
        }
    }
    printf("\n");

    /* Print ones digit of x axis */
    printf("   ");
    for (x = 0; x < WIDTH; ++x) {
        printf("%d", x % 10);
    }
    printf("\n");

    /* Print top border */
    printf("  +");
    for (x = 0; x < WIDTH; ++x) printf("-");
    printf("+\n");

    /* Print grid content with y coordinates */
    for (y = 0; y < HEIGHT; ++y) {
        printf("%2d|", y);
        for (x = 0; x < WIDTH; ++x) {
            printf("%c", grid[y][x]);
        }
        printf("|\n");
    }

    /* Print bottom border */
    printf("  +");
    for (x = 0; x < WIDTH; ++x) printf("-");
    printf("+\n");
}

/* Drawing Algorithms */

/* 1. Line Drawing using Bresenham's Line Algorithm */
void drawLine(char grid[HEIGHT][WIDTH], int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1) {
        setPixel(grid, x1, y1, ch);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

/* 2. Rectangle Drawing */
void drawRectangle(char grid[HEIGHT][WIDTH], int x1, int y1, int x2, int y2, char ch) {
    drawLine(grid, x1, y1, x2, y1, ch); /* Top edge */
    drawLine(grid, x1, y2, x2, y2, ch); /* Bottom edge */
    drawLine(grid, x1, y1, x1, y2, ch); /* Left edge */
    drawLine(grid, x2, y1, x2, y2, ch); /* Right edge */
}

/* 3. Circle Drawing using Midpoint Circle Algorithm */
void drawCircle(char grid[HEIGHT][WIDTH], int cx, int cy, int r, char ch) {
    int x, y, d;
    if (r < 0) return;
    x = 0;
    y = r;
    d = 3 - 2 * r;

    while (y >= x) {
        setPixel(grid, cx + x, cy + y, ch);
        setPixel(grid, cx - x, cy + y, ch);
        setPixel(grid, cx + x, cy - y, ch);
        setPixel(grid, cx - x, cy - y, ch);
        setPixel(grid, cx + y, cy + x, ch);
        setPixel(grid, cx - y, cy + x, ch);
        setPixel(grid, cx + y, cy - x, ch);
        setPixel(grid, cx - y, cy - x, ch);

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

/* 4. Triangle Drawing */
void drawTriangle(char grid[HEIGHT][WIDTH], int x1, int y1, int x2, int y2, int x3, int y3, char ch) {
    drawLine(grid, x1, y1, x2, y2, ch);
    drawLine(grid, x2, y2, x3, y3, ch);
    drawLine(grid, x3, y3, x1, y1, ch);
}

/* Render a shape */
void drawShape(char grid[HEIGHT][WIDTH], const Shape* shape) {
    switch (shape->type) {
        case LINE:
            drawLine(grid, shape->x1, shape->y1, shape->x2, shape->y2, shape->ch);
            break;
        case RECTANGLE:
            drawRectangle(grid, shape->x1, shape->y1, shape->x2, shape->y2, shape->ch);
            break;
        case CIRCLE:
            drawCircle(grid, shape->x1, shape->y1, shape->x2, shape->ch); /* x2 stores radius */
            break;
        case TRIANGLE:
            drawTriangle(grid, shape->x1, shape->y1, shape->x2, shape->y2, shape->x3, shape->y3, shape->ch);
            break;
    }
}

/* Get Shape Details format */
void printShapeDetails(const Shape* shape) {
    switch (shape->type) {
        case LINE:
            printf("Line from (%d,%d) to (%d,%d)", shape->x1, shape->y1, shape->x2, shape->y2);
            break;
        case RECTANGLE:
            printf("Rectangle: Top-Left (%d,%d), Bottom-Right (%d,%d)", shape->x1, shape->y1, shape->x2, shape->y2);
            break;
        case CIRCLE:
            printf("Circle: Center (%d,%d), Radius %d", shape->x1, shape->y1, shape->x2);
            break;
        case TRIANGLE:
            printf("Triangle: Vertices (%d,%d), (%d,%d), (%d,%d)", shape->x1, shape->y1, shape->x2, shape->y2, shape->x3, shape->y3);
            break;
    }
}

/* Screen clearing */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* Helper to get integer input safely */
int getIntInput(const char* prompt, int minVal, int maxVal) {
    int val;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &val) == 1) {
            if (val >= minVal && val <= maxVal) {
                return val;
            }
            printf("Invalid range! Value must be between %d and %d.\n", minVal, maxVal);
        } else {
            printf("Invalid input! Please enter an integer.\n");
            /* Clear buffer */
            while (getchar() != '\n');
        }
    }
}

/* Helper to get character input safely */
char getCharInput(const char* prompt) {
    char ch;
    printf("%s", prompt);
    /* consume leading whitespaces */
    scanf(" %c", &ch);
    return ch;
}

/* Redraw canvas */
void redrawCanvas(char grid[HEIGHT][WIDTH], Shape shapes[], int shapeCount) {
    int i;
    clearCanvas(grid);
    for (i = 0; i < shapeCount; ++i) {
        drawShape(grid, &shapes[i]);
    }
}

int main() {
    char grid[HEIGHT][WIDTH];
    Shape shapes[MAX_SHAPES];
    int shapeCount = 0;
    int nextId = 1;
    int choice;

    while (1) {
        clearScreen();
        printf("=======================================\n");
        printf("     2D CHARACTER GRAPHICS EDITOR (C)\n");
        printf("=======================================\n\n");

        redrawCanvas(grid, shapes, shapeCount);
        displayCanvas(grid);

        printf("\nActive Shapes:\n");
        if (shapeCount == 0) {
            printf("  (none)\n");
        } else {
            int i;
            for (i = 0; i < shapeCount; ++i) {
                printf("  [%d] ", shapes[i].id);
                printShapeDetails(&shapes[i]);
                printf(" (drawn with '%c')\n", shapes[i].ch);
            }
        }

        printf("\nMenu Options:\n");
        printf("1. Add Shape\n");
        printf("2. Delete Shape\n");
        printf("3. Modify Shape\n");
        printf("4. Clear Canvas\n");
        printf("5. Exit\n");

        choice = getIntInput("Select option (1-5): ", 1, 5);

        if (choice == 1) { /* Add */
            int typeChoice;
            Shape newShape;
            int charChoice;

            if (shapeCount >= MAX_SHAPES) {
                printf("Maximum shape limit reached!\n");
                printf("Press Enter to continue...");
                while (getchar() != '\n');
                getchar();
                continue;
            }

            printf("\nChoose Shape Type:\n");
            printf("1. Line\n");
            printf("2. Rectangle\n");
            printf("3. Circle\n");
            printf("4. Triangle\n");
            typeChoice = getIntInput("Select type (1-4): ", 1, 4);

            newShape.id = nextId++;
            newShape.type = (ShapeType)typeChoice;
            newShape.ch = '*';

            if (typeChoice == 1) { /* Line */
                printf("\nEnter Start point:\n");
                newShape.x1 = getIntInput("  x1 (0-59): ", 0, WIDTH - 1);
                newShape.y1 = getIntInput("  y1 (0-19): ", 0, HEIGHT - 1);
                printf("Enter End point:\n");
                newShape.x2 = getIntInput("  x2 (0-59): ", 0, WIDTH - 1);
                newShape.y2 = getIntInput("  y2 (0-19): ", 0, HEIGHT - 1);
            }
            else if (typeChoice == 2) { /* Rectangle */
                printf("\nEnter Top-Left corner:\n");
                newShape.x1 = getIntInput("  x1 (0-59): ", 0, WIDTH - 1);
                newShape.y1 = getIntInput("  y1 (0-19): ", 0, HEIGHT - 1);
                printf("Enter Bottom-Right corner:\n");
                newShape.x2 = getIntInput("  x2 (0-59): ", 0, WIDTH - 1);
                newShape.y2 = getIntInput("  y2 (0-19): ", 0, HEIGHT - 1);
            }
            else if (typeChoice == 3) { /* Circle */
                printf("\nEnter Center point:\n");
                newShape.x1 = getIntInput("  cx (0-59): ", 0, WIDTH - 1);
                newShape.y1 = getIntInput("  cy (0-19): ", 0, HEIGHT - 1);
                newShape.x2 = getIntInput("  Radius r (0-40): ", 0, 40);
            }
            else if (typeChoice == 4) { /* Triangle */
                printf("\nEnter Vertex 1:\n");
                newShape.x1 = getIntInput("  x1 (0-59): ", 0, WIDTH - 1);
                newShape.y1 = getIntInput("  y1 (0-19): ", 0, HEIGHT - 1);
                printf("Enter Vertex 2:\n");
                newShape.x2 = getIntInput("  x2 (0-59): ", 0, WIDTH - 1);
                newShape.y2 = getIntInput("  y2 (0-19): ", 0, HEIGHT - 1);
                printf("Enter Vertex 3:\n");
                newShape.x3 = getIntInput("  x3 (0-59): ", 0, WIDTH - 1);
                newShape.y3 = getIntInput("  y3 (0-19): ", 0, HEIGHT - 1);
            }

            charChoice = getIntInput("Draw shape with standard '*' character? (1: Yes, 0: No/Custom): ", 0, 1);
            if (charChoice == 0) {
                newShape.ch = getCharInput("Enter single character to draw with: ");
            }

            shapes[shapeCount++] = newShape;
        }
        else if (choice == 2) { /* Delete */
            int deleteId;
            int foundIdx;
            int i;

            if (shapeCount == 0) {
                printf("No shapes to delete. Press Enter to continue...");
                while (getchar() != '\n');
                getchar();
                continue;
            }
            deleteId = getIntInput("Enter ID of shape to delete: ", 1, nextId);
            foundIdx = -1;
            for (i = 0; i < shapeCount; ++i) {
                if (shapes[i].id == deleteId) {
                    foundIdx = i;
                    break;
                }
            }
            if (foundIdx != -1) {
                for (i = foundIdx; i < shapeCount - 1; ++i) {
                    shapes[i] = shapes[i + 1];
                }
                shapeCount--;
                printf("Shape %d deleted successfully.\n", deleteId);
            } else {
                printf("Shape ID %d not found.\n", deleteId);
            }
            printf("Press Enter to continue...");
            while (getchar() != '\n');
            getchar();
        }
        else if (choice == 3) { /* Modify */
            int modifyId;
            int foundIdx;
            int i;

            if (shapeCount == 0) {
                printf("No shapes to modify. Press Enter to continue...");
                while (getchar() != '\n');
                getchar();
                continue;
            }
            modifyId = getIntInput("Enter ID of shape to modify: ", 1, nextId);
            foundIdx = -1;
            for (i = 0; i < shapeCount; ++i) {
                if (shapes[i].id == modifyId) {
                    foundIdx = i;
                    break;
                }
            }
            if (foundIdx != -1) {
                Shape* s = &shapes[foundIdx];
                int changeCh;

                printf("Modifying Shape %d: ", modifyId);
                printShapeDetails(s);
                printf("\n");

                if (s->type == LINE) {
                    printf("Enter new Start point:\n");
                    s->x1 = getIntInput("  x1 (0-59): ", 0, WIDTH - 1);
                    s->y1 = getIntInput("  y1 (0-19): ", 0, HEIGHT - 1);
                    printf("Enter new End point:\n");
                    s->x2 = getIntInput("  x2 (0-59): ", 0, WIDTH - 1);
                    s->y2 = getIntInput("  y2 (0-19): ", 0, HEIGHT - 1);
                }
                else if (s->type == RECTANGLE) {
                    printf("Enter new Top-Left corner:\n");
                    s->x1 = getIntInput("  x1 (0-59): ", 0, WIDTH - 1);
                    s->y1 = getIntInput("  y1 (0-19): ", 0, HEIGHT - 1);
                    printf("Enter new Bottom-Right corner:\n");
                    s->x2 = getIntInput("  x2 (0-59): ", 0, WIDTH - 1);
                    s->y2 = getIntInput("  y2 (0-19): ", 0, HEIGHT - 1);
                }
                else if (s->type == CIRCLE) {
                    printf("Enter new Center point:\n");
                    s->x1 = getIntInput("  cx (0-59): ", 0, WIDTH - 1);
                    s->y1 = getIntInput("  cy (0-19): ", 0, HEIGHT - 1);
                    s->x2 = getIntInput("  new Radius r (0-40): ", 0, 40);
                }
                else if (s->type == TRIANGLE) {
                    printf("Enter new Vertex 1:\n");
                    s->x1 = getIntInput("  x1 (0-59): ", 0, WIDTH - 1);
                    s->y1 = getIntInput("  y1 (0-19): ", 0, HEIGHT - 1);
                    printf("Enter new Vertex 2:\n");
                    s->x2 = getIntInput("  x2 (0-59): ", 0, WIDTH - 1);
                    s->y2 = getIntInput("  y2 (0-19): ", 0, HEIGHT - 1);
                    printf("Enter new Vertex 3:\n");
                    s->x3 = getIntInput("  x3 (0-59): ", 0, WIDTH - 1);
                    s->y3 = getIntInput("  y3 (0-19): ", 0, HEIGHT - 1);
                }

                changeCh = getIntInput("Change drawing character? (1: Yes, 0: No): ", 0, 1);
                if (changeCh == 1) {
                    s->ch = getCharInput("Enter new character: ");
                }
                printf("Shape modified successfully.\n");
            } else {
                printf("Shape ID %d not found.\n", modifyId);
            }
            printf("Press Enter to continue...");
            while (getchar() != '\n');
            getchar();
        }
        else if (choice == 4) { /* Clear all */
            shapeCount = 0;
            printf("Canvas cleared. Press Enter to continue...");
            while (getchar() != '\n');
            getchar();
        }
        else if (choice == 5) { /* Exit */
            printf("Exiting graphics editor. Goodbye!\n");
            break;
        }
    }
    return 0;
}
