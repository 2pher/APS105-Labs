#include <stdio.h>

void appendStatistics(int userChoice[], const int ChoicesNum, int histogram[]);
int frequentBox(int histogram[], const int BoxesNum);

int main(void) {
  const int BoxesNum = 20;
  const int ChoicesNum = 5;

  int userOne[ChoicesNum], userOneHisto[BoxesNum];

  for (int i = 0; i < BoxesNum; i++) {
    userOneHisto[i] = 0;
  }

  int numOfTimes = 0;
  while (numOfTimes <= 5) {
    printf("Enter choices: ");
    for (int i = 0; i < 5; i++) {
      scanf("%d", &userOne[i]);
    }
    appendStatistics(userOne, ChoicesNum, userOneHisto);
    numOfTimes++;
  }
  printf("The smallest and most frequently used box is: %d\n",
         frequentBox(userOneHisto, BoxesNum));
  return 0;
}

void appendStatistics(int userChoice[], const int ChoicesNum, int histogram[]) {
  for (int i = 0; i < ChoicesNum; i++) {
    int number = userChoice[i];
    histogram[number]++;
    printf("%d ", histogram[i]);
  }
  printf("\n");
}

int frequentBox(int histogram[], const int BoxesNum) {
  int max, max_value = 0;
  for (int i = 0; i < BoxesNum; i++) {
    if (histogram[i] > max_value) {
      max_value = histogram[i];
      max = i;
    }
  }
  return max;
}
