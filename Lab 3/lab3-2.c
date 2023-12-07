# include <stdlib.h>
# include <stdio.h>
# include <math.h>

int main(void) {
    int radius;
  
    printf("Enter the radius of the circle: ");
    scanf("%d", &radius);
    int size_circle = 2 * radius + 1;
  
    for (int i = 0; i < size_circle; i++) {
        for (int j = 0; j < size_circle; j++) {
            if (pow(i - radius, 2) + pow(j - radius, 2) <= pow(radius, 2)) {
                printf("o");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    return 0;
}