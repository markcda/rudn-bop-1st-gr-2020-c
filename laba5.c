#include "laba5.h"

/* Задание 1.
Создать массив типа int на 30 элементов и заполнить его случайными числами от 5
до 15. После заполнения перезаписать все числа, которые больше десяти: от
хранимого значение отнять 10. */
void array_l5_1() {
  const int numberOfElements = 30;
  int array[numberOfElements];
  for (int i = 0; i < numberOfElements; i++) array[i] = uniform(5, 15);
  printf("\tМассив:");
  for (int i = 0; i < numberOfElements; i++) printf(" %d", array[i]);
  for (int i = 0; i < numberOfElements; i++)
    if (array[i] > 10) array[i] -= 10;
  printf("\n\tПреобразованный массив:");
  for (int i = 0; i < numberOfElements; i++) printf(" %d", array[i]);
  printf("\n");
}

/* Задание 2.
Объявить три массива одинакового размера. Первые два заполнить случайными
значениями от 10 до 30. В элементы третьего массива записать сумму
соответствующих элементов первых двух массивов. Затем найдите среднее
арифметическое элементов третьего массива, максимальное и минимальное значение,
которые он хранит. */
void array_l5_2() {
  printf("\tВведите длину массивов: ");
  int_nstd length = scanInt();
  if (not length.status or length.num < 1) return;
  int arrays[3][length.num];
  // Заполняем первые два массива
  for (int i = 0; i < length.num; i++) {
    arrays[0][i] = uniform(10, 30);
    arrays[1][i] = uniform(10, 30);
    arrays[2][i] = arrays[0][i] + arrays[1][i];
  }
  printf("\tПервый массив:");
  for (int i = 0; i < length.num; i++) printf(" %d", arrays[0][i]);
  printf("\n\tВторой массив:");
  for (int i = 0; i < length.num; i++) printf(" %d", arrays[1][i]);
  printf("\n\tТретий массив:");
  for (int i = 0; i < length.num; i++) printf(" %d", arrays[2][i]);
  // Ищем минимальные и максимальные элементы, а так же - среднее арифметическое
  int min = arrays[2][0], max = arrays[2][0];
  float middle = 0.0;
  for (int i = 0; i < length.num; i++) {
    middle += arrays[2][i];
    if (arrays[2][i] < min) min = arrays[2][i];
    if (arrays[2][i] > max) max = arrays[2][i];
  }
  middle /= length.num;
  printf(
      "\n\tМаксимальный элемент - %d, минимальный элемент - %d, а среднее "
      "арифметическое - %.3f\n",
      max, min, middle);
}

/* Задание 3.
Создайте и заполните случайными значениями массив. Найдите в массиве элементы,
которые в нем встречаются только один раз, и выведите их на экран. Отдельно
запоминать эти элементы не нужно (используйте маркер признака уникальности). */
void array_l5_3() {
  printf("\tВведите длину массива: ");
  int_nstd length = scanInt();
  if (not length.status or length.num < 1) return;
  int array[length.num];
  printf(
      "\tВведите через пробел два числа, которые будут служить границами для "
      "генератора псевдослучайных чисел: ");
  int_nstd *limits = scanInts();  // LFPRNG
  if (limits[0].num != 2) return;
  if (not limits[1].status or not limits[2].status) return;
  int min = limits[1].num > limits[2].num ? limits[2].num : limits[1].num,
      max = limits[1].num > limits[2].num ? limits[1].num : limits[2].num;
  for (int i = 0; i < length.num; i++) array[i] = uniform(min, max);
  printf("\tМассив:");
  for (int i = 0; i < length.num; i++) printf(" %d", array[i]);
  bool unique;  // маркер
  int cntr = 0;
  for (int i = 0; i < length.num; i++) {
    unique = true;
    for (int j = 0; j < length.num; j++)
      if (i != j and array[i] == array[j]) {
        unique = false;
        break;
      }
    if (unique) cntr++;
    if (cntr == 1) {
      printf("\n\tУникальные числа:");
      cntr++;
    }
    if (unique) printf(" %d", array[i]);
  }
  printf("\n");
}

/* Задание 4.
Создайте и заполните случайными значениями массив. Определите индексы четных
элементов массива, сохраните их в отдельном массиве. После этого выведите их на
экран. */
void array_l5_4() {
  printf("\tВведите длину массива: ");
  int_nstd length = scanInt();
  if (not length.status or length.num < 1) return;
  int array[length.num];
  printf(
      "\tВведите через пробел два числа, которые будут служить границами для "
      "генератора псевдослучайных чисел: ");
  int_nstd *limits = scanInts();  // LFPRNG
  if (limits[0].num != 2) return;
  if (not limits[1].status or not limits[2].status) return;
  int min = limits[1].num > limits[2].num ? limits[2].num : limits[1].num,
      max = limits[1].num > limits[2].num ? limits[1].num : limits[2].num;
  for (int i = 0; i < length.num; i++) array[i] = uniform(min, max);
  printf("\tМассив:");
  for (int i = 0; i < length.num; i++) printf(" %d", array[i]);
  // Посчитаем чётные элементы
  int cntr = 0;
  for (int i = 0; i < length.num; i++)
    if (array[i] % 2 == 0) cntr++;
  if (not cntr) return;
  int evenIndexes[cntr];
  cntr = 0;
  for (int i = 0; i < length.num; i++)
    if (array[i] % 2 == 0) {
      evenIndexes[cntr] = i;
      cntr++;
    }
  printf("\n\tИндексы чётных элементов:");
  for (int i = 0; i < cntr; i++) printf(" %d", evenIndexes[i]);
  printf("\n");
}

/* Задание 5.
Создать массив типа int на 30 элементов и заполнить его случайными числами от 2
до 99. Проверьте кратность каждого числа каждому числу от 2 до 9 включительно.
Введите массивы, которые будут хранить маркеры кратности. Определите «самое
кратное число» - число, кратное максимальному количеству чисел от 2 до 9
включительно. Напечатайте это число и числа, которым оно кратно. */
void array_l5_5() {
  const int numberOfElements = 30;
  const int min = 2, max = 99;
  int array[numberOfElements];
  bool markers[8][numberOfElements];
  for (int i = 0; i < numberOfElements; i++) array[i] = uniform(min, max);
  printf("\tМассив:");
  for (int i = 0; i < numberOfElements; i++) printf(" %d", array[i]);
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < numberOfElements; j++)
      if (array[j] % (i + 2) == 0)
        markers[i][j] = true;
      else
        markers[i][j] = false;
  int bestDivisibleNumberIndex = 0, bestDivisibleNumberCounter = 0, cntr;
  for (int i = 0; i < numberOfElements; i++) {
    cntr = 0;
    for (int j = 0; j < 8; j++)
      if (markers[j][i]) cntr++;
    if (cntr > bestDivisibleNumberCounter) {
      bestDivisibleNumberCounter = cntr;
      bestDivisibleNumberIndex = i;
    }
  }
  printf("\n");
  if ((bestDivisibleNumberIndex == 0) and (bestDivisibleNumberCounter == 0)) {
    printf("\tСреди чисел принципиально нет кратных.\n");
    return;
  }
  printf("\tСамое кратное число - %d. Оно кратно следующим числам:",
         array[bestDivisibleNumberIndex]);
  for (int i = 0; i < 8; i++)
    if (markers[i][bestDivisibleNumberIndex]) printf(" %d", i + 2);
  printf("\n");
}
