# include <stdio.h>
# include <stdbool.h>
# include <math.h>

int reverseNumber(int number);
int getAscendingOrderedDigits(int number);
int getNumber(void);

int main(void) {
    int user_number = 0;
  
    while (user_number != -1) {
      int counter = 0;
      user_number = getNumber();
      
      if (user_number == -1) {
          break;
      } else {
          while (user_number != 6174) {
            counter += 1;
            printf("Number %d: %d\n", counter, user_number);
            int ordered_number = getAscendingOrderedDigits(user_number);
            int reversed_number = reverseNumber(ordered_number);
            user_number = reversed_number - ordered_number;
          }
      }
      printf("Number %d: %d\n", (counter+1), user_number);
      printf("Kaprekar's Constant was reached in %d iteration(s).\n", counter);
    } 
    return 0;
}

int reverseNumber(int number) {
  int new_number = 0, j = 0, remainder;
  for (int i = 3; i >= 0; i--) {
    j = pow(10, i);
    remainder = number % 10;
    new_number += remainder * j;
    number /= 10;
  }
  return new_number;
}

int getAscendingOrderedDigits(int number) {
  int value1, value2, value3, value4, emptyVar;
  
  for (int i = 1; i < 5; i++) {
    if (i == 1) {
      value1 = number % 10;
      number /= 10;
    } else if (i == 2) {
      value2 = number % 10;
      number /= 10;
    } else if (i == 3) {
      value3 = number % 10;
      number /= 10;
    } else {
      value4 = number % 10;
    }
  }

  for (int i = 1; i < 5; i++) {
    if (value1 > value2) {
      emptyVar = value1;
      value1 = value2;
      value2 = emptyVar;
    }
    if (value2 > value3) {
      emptyVar = value2;
      value2 = value3;
      value3 = emptyVar;
    }
    if (value3 > value4) {
      emptyVar = value3;
      value3 = value4;
      value4 = emptyVar;
    }    
  }
  int orderedNumber = (value4 + (value3 * 10) + (value2 * 100) + (value1 * 1000));
  return orderedNumber;
}

int getNumber(void) {
    int user_input;
    bool number = true;

    while (number) {
        printf("Enter a number (-1 to stop): ");
        scanf("%d", &user_input);
        
        if (user_input == -1) {
          user_input = -1;
          number = false;
        } else if ((10000 - user_input > 0) && (user_input - 999 > 0)) {
          number = false;
        } else {
          if (user_input - 999 <= 0) {
            printf("Error: The number is too small.\n");
          } else {
            printf("Error: The number is too large.\n");
          }
          number = true;
        }
    }
    return user_input;
}