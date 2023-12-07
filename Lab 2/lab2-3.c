#include <stdio.h>
#include <string.h>

int main(void) {
    double weight, height, BMI;
    char unit1[4], unit2[3];

    printf("Enter the body weight: ");
    scanf("%lf %s", &weight, &unit1);
    printf("Enter the height: ");
    scanf("%lf %s", &height, &unit2);

    if (strcmp(unit1, "lbs") == 0) {
        weight = weight * 0.453592;
        if (strcmp(unit2, "ft") == 0) {
            height = height * 0.3048;
            BMI = weight / (height*height);
        } else if (strcmp(unit2, "in") == 0) {
            height = height * 0.0254;
            BMI = weight / (height*height);
        } else {
            BMI = weight / (height*height);
        }
    } else {
        if (strcmp(unit2, "ft") == 0) {
            height = height * 0.3048;
            BMI = weight / (height*height);
        } else if (strcmp(unit2, "in") == 0) {
            height = height * 0.0254;
            BMI = weight / (height*height);
        } else {
            BMI = weight / (height*height);
        }
    }

    printf("\nThe Body Mass Index (BMI) is: %.1lf\n", BMI);

    if (BMI >= 30) {
        printf("Category: Obesity");
    } else if (BMI >= 25.0) {
        printf("Category: Overweight");
    } else if (BMI >= 18.5) {
        printf("Category: Healthy Weight");
    } else {
        printf("Category: Underweight");
    }

    return 0;

}