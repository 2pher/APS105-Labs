#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int getInput(void);
void graphFunction(int, int, int, int);


int main(void) {
    int order = 0;

    while (order != -1) {
        int x0 = 0, x1 = 0, x2 = 0, x3 = 0;
        order = getInput();
        for (int i = 0; i < order + 1; i++) {
            if (i == 0) {
                printf("Enter coefficient of x^0: ");
                scanf("%d", &x0);
            }
            if (i == 1) {
                printf("Enter coefficient of x^1: ");
                scanf("%d", &x1);
            }
            if (i == 2) {
                printf("Enter coefficient of x^2: ");
                scanf("%d", &x2);
            }
            if (i == 3) {
                printf("Enter coefficient of x^3: ");
                scanf("%d", &x3);
            }            
        }
        if (order != -1) {
            graphFunction(x0, x1, x2, x3);
        }
    }
    return 0;
}

int getInput(void) {
    int input;
    bool invalid = true;

    while (invalid) {
        printf("Enter the order of the function: ");
        scanf("%d", &input);

        if (input == -1) {
            invalid = false;
        } else if (input >= 0 && input <= 3) {
            invalid = false;
        } else {
            printf("The order must be between [0, 3].\n");
        }
    }
    return input;
}

void graphFunction(int x0, int x1, int x2, int x3) {
    for (int i = 10; i > -11; i--) {
        for (int j = -10; j < 11; j++) {
            int y = (x0 + x1 * j + (int)(x2 * pow(j, 2)) + (int)(x3 * pow(j, 3)));
            if (y == i) {
                printf(" * ");
            } else if (j == 0) {
                printf(" | ");
            } else if (i == 0) {
                printf(" - ");
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
}