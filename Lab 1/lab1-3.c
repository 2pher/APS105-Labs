#include <stdio.h>

int main(void) {
    int number;
    int remainder;
    int remainder2;
    int remainder3;
    int remainder4; 

    printf("Enter number to convert to base 2: ");
    scanf("%d", &number);

    remainder = number % 2;
    number = number / 2;
    remainder2 = number % 2;
    number = number / 2;
    remainder3 = number % 2; 
    number = number / 2; 
    remainder4 = number % 2;
    number = number / 2;

    printf("The four digits of that number are as follows:\n");
    printf("Most siginificant digit: %d\n", remainder4);
    printf("Next digit: %d\n", remainder3);
    printf("Next digit: %d\n", remainder2);
    printf("Least siginificant digit: %d\n", remainder);

    return 0;

}