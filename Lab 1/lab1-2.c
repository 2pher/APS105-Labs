#include <stdio.h>

int main(void) {
    float conversion_rate;
    float money;
    float calculation;

    printf("Enter the conversion rate: ");
    scanf("%f", &conversion_rate);

    printf("Enter the amount to be converted (in foreign currency): ");
    scanf("%f", &money);

    calculation = conversion_rate * money;
    printf("\nThe amount in Canadian Dolars is: %.2f", calculation);
    
    return 0;
    
}