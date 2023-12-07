#include <stdio.h>
#include <math.h>

int main(void) {
    double x, y, hypotenuse, angle, new_x, new_y;
    
    printf("Enter X: ");
    scanf("%lf", &x);
    printf("Enter Y: ");
    scanf("%lf", &y);

    new_x = x*x;
    new_y = y*y;

    hypotenuse = sqrt(new_x + new_y);
    angle = asin(y/hypotenuse);
    angle = angle * (180/M_PI);

    printf("\nThe Hypotenuse Length is: %.1lf\nThe Angle Theta is %.1lf degrees", hypotenuse, angle);

    return 0;

}