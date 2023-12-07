#include <stdio.h>
#include <math.h>

int main(void) {
    double x, y; 

    printf("Enter the x-coordinate in floating point: ");
    scanf("%lf", &x);
    printf("Enter the y-coordinate in floating point: ");
    scanf("%lf", &y);

    x = round(x*100)/100;
    y = round(y*100)/100;

    if (x == 0) {
        if (y == 0) {
            printf("(%.2lf, %.2lf) is at the origin.", x, y);
        } else {
            printf("(%.2lf, %.2lf) is on the y axis.", x, y);
        } 
    } else {
        if (y == 0) {
            printf("(%.2lf, %.2lf) is at the x axis.", x, y);
        } else {
            if (x > 0) {
                if (y > 0) {
                    printf("(%.2lf, %.2lf) is in quadrant I.", x, y);
                } else {
                    printf("(%.2lf, %.2lf) is in quadrant IV.", x, y);
                }
            } else {
                if (y > 0) {
                    printf("(%.2lf, %.2lf) is in quadrant II.", x, y);
                } else {
                    printf("(%.2lf, %.2lf) is in quarant III.", x, y);
                }
            }
        }
    }

    return 0;
    
}