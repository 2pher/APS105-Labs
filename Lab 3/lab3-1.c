#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int convert2base(int base1, int num);
int convert2base10(int base2, int num);
int validate(char v_operator, int btest1, int btest2);
int number_checker(int btest, int ntest);

int main(void) {
    char operand;
    int input_base, output_base, num1, num2, answer, sum, difference, product, quotient;

    while (operand != '$') {
        printf("Give input ($ to stop): ");
        scanf("%s %d %d %d %d", &operand, &input_base, &num1, &num2, &output_base);

        int verify = validate(operand, input_base, output_base);
        int check_number1 = number_checker(input_base, num1);
        int check_number2 = number_checker(input_base, num2);

        if (verify == 1) {
            printf("Invalid operator\n");
        } else if (verify == 2) {
            printf("Invalid base\n");
        } else if (verify == 3) {
            break;
        } else {
            if ((check_number1 == 4) && (check_number2 == 4)) {
                int num1_base10 = convert2base10(input_base, num1);
                int num2_base10 = convert2base10(input_base, num2);

                switch(operand) {
                    case '+':
                        sum = num1_base10 + num2_base10;
                        answer = convert2base(output_base, sum);
                        printf("%d + %d (base %d) = %d + %d = %d (base %d)\n", num1, num2, input_base, num1_base10, num2_base10, answer, output_base);
                        break;
                    case '-':
                        difference = num1_base10 - num2_base10;
                        answer = convert2base(output_base, difference);
                        printf("%d - %d (base %d) = %d - %d = %d (base %d)\n", num1, num2, input_base, num1_base10, num2_base10, answer, output_base);
                        break;
                    case '*':
                        product = num1_base10 * num2_base10;
                        answer = convert2base(output_base, product);
                        printf("%d * %d (base %d) = %d * %d = %d (base %d)\n", num1, num2, input_base, num1_base10, num2_base10, answer, output_base);
                        break;
                    case '/':
                        quotient = num1_base10 / num2_base10;
                        answer = convert2base(output_base, quotient);
                        printf("%d / %d (base %d) = %d / %d = %d (base %d)\n", num1, num2, input_base, num1_base10, num2_base10, answer, output_base);
                        break;
                }
            } else {
                printf("Invalid digits in operand\n");
            }
        }
    }
    return 0;
}

int number_checker(int btest, int ntest) {
    int ncheck = ntest;
    while (ncheck > 0) {
        int checker = ncheck % 10;
        if (checker >= btest) {
            return 3;
        }
        ncheck /= 10;
    } 
    return 4;
}

int validate(char v_operator, int btest1, int btest2) {
    switch(v_operator) {
        case '+':
            if ((btest1 < 11) && (btest1 > 1) && (btest2 < 11) && (btest2 > 1)) {
                return 4;
            } else {
                return 2;
            }
        case '-':
            if ((btest1 < 11) && (btest1 > 1) && (btest2 < 11) && (btest2 > 1)) {
                return 4;
            } else {
                return 2;
            }
        case '*':
            if ((btest1 < 11) && (btest1 > 1) && (btest2 < 11) && (btest2 > 1)) {
                return 4;
            } else {
                return 2;
            }
        case '/':
            if ((btest1 < 11) && (btest1 > 1) && (btest2 < 11) && (btest2 > 1)) {
                return 4;
            } else {
                return 2;
            }
        case '$':
            return 3;
        default:
            return 1;
    }
}

int convert2base(int base1, int num) {
    int new_num_base_user = 0, remainder1 = 0, temp1 = num, i = 1;

    while (temp1 > 0) {
        remainder1 = temp1 % base1;
        new_num_base_user = new_num_base_user + (remainder1 * i);
        i = i * 10;
        temp1 /= base1;
    }
    return new_num_base_user;
}

int convert2base10(int base2, int num) {
    int new_num_base10 = 0, remainder2 = 0, temp2 = num, i = 0;
    while (temp2 > 0) {
        remainder2 = temp2 % 10;
        int new_base = (int) pow(base2, i);
        new_num_base10 = new_num_base10 + (remainder2 * new_base);
        i += 1;
        temp2 /= 10; 
    }
    return new_num_base10;
}