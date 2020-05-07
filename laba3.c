#include "laba3.h"

/* Задание 1. Среднее значение введённых чисел
Написать программу, запрашивующую у пользователя в бесконечном цикле число и
выводящую среднее значение всех введённых ранее чисел. Вывод в формате: "Среднее
значение этих ... чисел равно ...". Среднее значение выводить с точностью до 5
десятичных знаков (т.е. до 1/100000).
Программа перестаёт работать или при вводе символа вместо числа, или при
истечении 1 минуты с момента ввода первого числа. */
void average() {
  time_t start, end;
  float_nstd nextNumber;
  float avr = 0;
  int ctr = 0;
  start = time(NULL);
  for (end = time(NULL); difftime(end, start) < 60; end = time(NULL)) {
    printf("\tВведите следующее число (или символ, чтобы выйти): ");
    nextNumber = scanFloat();
    if (not nextNumber.status) break;
    avr = (avr * ctr + nextNumber.num) / (ctr + 1); // эта операция является
                                                    // причиной неточностей.
    ctr++;
  }
  printf("\tСреднее значение введённых чисел равно %.5f\n", avr);
}

/* Задание 2. "Число и цифра"
Запросите у пользователя целое число и сложите цифры этого числа.
Повторяйте последнее действие столько раз, сколько сможете, и выводите каждый
раз полученную сумму. */
void numberAndNumeral() {
  printf("\tВведите число, сумму цифр которого хотите получить: ");
  char number[DEFAULT_STR_LENGTH];
  fgets(number, DEFAULT_STR_LENGTH, stdin);
  int sum;
  do {
    sum = 0;
    int i = 0;
    char curr[2] = " \0";
    while (not isEndOfString(number[i]) and isPartOfInt(number[i])) {
      curr[0] = number[i];
      sum += atoi(curr);
      i++;
    }
    printf("\tПромежуточная сумма равна %i\n", sum);
    sprintf(number, "%i", sum);
  } while (sum >= 10);
}

/* Задание 3. "Максимум и минимум"
Запрашивайте у пользователя числа, определяйте максимальное и минимальное из
всех полученных чисел и сообщайте их ему. */
void maxAndMin() {
  float min = 0, max = 0;
  float_nstd curr;
  bool first = true;
  do {
    printf("\tВведите следующее число: ");
    curr = scanFloat();
    if (not curr.status) break;
    if (first) {
      min = curr.num;
      max = curr.num;
      first = false;
    }
    if (curr.num > max) max = curr.num;
    if (curr.num < min) min = curr.num;
    printf("\tМинимальное число на данном этапе: %f\n", min);
    printf("\tМаксимальное число на данном этапе: %f\n", max);
  } while (curr.status);
}
