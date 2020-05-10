#include "laba6.h"

/* Задание 1.
Напишите программу, создающую матрицу и заполняющую её случайными числами (или
пользователь заполняет её с клавиатуры) все элементы, кроме последних элементов
строк. Программа должна вычислить сумму элементов каждой строки и записать ее
в последнюю ячейку строки. В конце следует вывести полученную матрицу. */
void matrix_l6_1() {
  printf("\tВведите размеры матрицы через пробел (строки и столбцы): ");
  int_nstd *size = scanInts();
  if (size[0].num != 2)
    return;
  if (not size[1].status or not size[2].status)
    return;
  if ((size[1].num < 1) or (size[2].num < 2))
    return;
  int matrix[size[1].num][size[2].num];
  // Выбор варианта задания
  printf("\tКак вы хотите заполнить матрицу?\n");
  printf("\t1) Заполнить с клавиатуры\n");
  printf("\t2) Заполнить случайными числами\n\t");
  int_nstd variant = scanInt();
  if (not variant.status)
    return;
  // Исполнение варианта с заполнением с клавиатуры
  if (variant.num == 1) {
    printf("\n\tНачиная со следующей строки, вводите числа через пробел.\n");
    printf("\tДоступная длина строки: %d элемент(-а/-ов)\n", size[2].num - 1);
    for (int i = 0; i < size[1].num; i++) {
      printf("\tСтрока %d: ", i + 1);
      int_nstd *row = scanInts();
      if (row[0].num != size[2].num - 1)
        return;
      for (int j = 0; j < size[2].num - 1; j++)
        if (row[j + 1].status)
          matrix[i][j] = row[j + 1].num;
        else
          return;
      free(row);
    }
    // Исполнение варианта с генератором псевдослучайных чисел
  } else if (variant.num == 2) {
    printf(
        "\tВведите через пробел два числа, которые будут служить границами для "
        "генератора псевдослучайных чисел: ");
    int_nstd *limits = scanInts(); // LFPRNG
    if (limits[0].num != 2)
      return;
    if (not limits[1].status or not limits[2].status)
      return;
    int min = limits[1].num > limits[2].num ? limits[2].num : limits[1].num,
        max = limits[1].num > limits[2].num ? limits[1].num : limits[2].num;
    for (int i = 0; i < size[1].num; i++)
      for (int j = 0; j < size[2].num - 1; j++)
        matrix[i][j] = uniform(min, max);
  } else
    return;
  // Заполнение последнего столбца
  for (int i = 0; i < size[1].num; i++) {
    matrix[i][size[2].num - 1] = 0;
    for (int j = 0; j < size[2].num - 1; j++)
      matrix[i][size[2].num - 1] += matrix[i][j];
  }
  // Вывод матрицы
  printf("\tПолученная матрица:\n");
  for (int i = 0; i < size[1].num; i++) {
    printf("\t");
    for (int j = 0; j < size[2].num; j++)
      printf("%4d ", matrix[i][j]);
    printf("\n");
  }
}

/* Задание 2.
Создайте и заполните случайными числами от 1 до 100 матрицу. Определите в ней
максимальный элемент из минимальных в строках. И минимальный элемент из
максимальных в строках. */
void matrix_l6_2() {
  const int min = 1, max = 100;
  printf("\tВведите размеры матрицы через пробел (строки и столбцы): ");
  int_nstd *size = scanInts();
  if (size[0].num != 2)
    return;
  if (not size[1].status or not size[2].status)
    return;
  if ((size[1].num < 1) or (size[2].num < 1))
    return;
  int matrix[size[1].num][size[2].num];
  for (int i = 0; i < size[1].num; i++)
    for (int j = 0; j < size[2].num; j++)
      matrix[i][j] = uniform(min, max);
  printf("\tПолученная матрица:\n");
  for (int i = 0; i < size[1].num; i++) {
    printf("\t");
    for (int j = 0; j < size[2].num; j++)
      printf("%4d ", matrix[i][j]);
    printf("\n");
  }
  int mins[size[1].num], maxs[size[1].num], maxOfMins, minOfMaxs;
  for (int i = 0; i < size[1].num; i++) {
    mins[i] = matrix[i][0];
    maxs[i] = matrix[i][0];
    for (int j = 0; j < size[2].num; j++) {
      if (matrix[i][j] < mins[i])
        mins[i] = matrix[i][j];
      if (matrix[i][j] > maxs[i])
        maxs[i] = matrix[i][j];
    }
  }
  maxOfMins = mins[0];
  minOfMaxs = maxs[0];
  for (int i = 0; i < size[1].num; i++) {
    if (mins[i] > maxOfMins)
      maxOfMins = mins[i];
    if (maxs[i] < minOfMaxs)
      minOfMaxs = maxs[i];
  }
  printf("\tМаксимальный элемент из минимальных - %d.\n", maxOfMins);
  printf("\tА минимальный из максимальных - %d.\n", minOfMaxs);
}

/* Задание 3.
Создайте и заполните квадратную матрицу. Обменяйте значения главной и побочной
диагонали этой матрицы. */
void matrix_l6_3() {
  printf("\tВведите размер квадратной матрицы: ");
  int_nstd size = scanInt();
  if (not size.status)
    return;
  if (size.num < 1)
    return;
  int matrix[size.num][size.num];
  // Выбор варианта задания
  printf("\tКак вы хотите заполнить матрицу?\n");
  printf("\t1) Заполнить с клавиатуры\n");
  printf("\t2) Заполнить случайными числами\n\t");
  int_nstd variant = scanInt();
  if (not variant.status)
    return;
  // Исполнение варианта с заполнением с клавиатуры
  if (variant.num == 1) {
    printf("\n\tНачиная со следующей строки, вводите числа через пробел.\n");
    printf("\tДоступная длина строки: %d элемент(-а/-ов)\n", size.num);
    for (int i = 0; i < size.num; i++) {
      printf("\tСтрока %d: ", i + 1);
      int_nstd *row = scanInts();
      if (row[0].num != size.num)
        return;
      for (int j = 0; j < size.num; j++)
        if (row[j + 1].status)
          matrix[i][j] = row[j + 1].num;
        else
          return;
      free(row);
    }
    // Исполнение варианта с генератором псевдослучайных чисел
  } else if (variant.num == 2) {
    printf(
        "\tВведите через пробел два числа, которые будут служить границами для "
        "генератора псевдослучайных чисел: ");
    int_nstd *limits = scanInts(); // LFPRNG
    if (limits[0].num != 2)
      return;
    if (not limits[1].status or not limits[2].status)
      return;
    int min = limits[1].num > limits[2].num ? limits[2].num : limits[1].num,
        max = limits[1].num > limits[2].num ? limits[1].num : limits[2].num;
    for (int i = 0; i < size.num; i++)
      for (int j = 0; j < size.num; j++)
        matrix[i][j] = uniform(min, max);
  } else
    return;
  // Вывод матрицы
  printf("\tПолученная матрица:\n");
  for (int i = 0; i < size.num; i++) {
    printf("\t");
    for (int j = 0; j < size.num; j++)
      printf("%4d ", matrix[i][j]);
    printf("\n");
  }
  // Меняем местами главную и побочную диагонали матрицы
  int swap;
  for (int i = 0; i < size.num; i++) {
    swap = matrix[i][i];
    matrix[i][i] = matrix[i][size.num - 1 - i];
    matrix[i][size.num - 1 - i] = swap;
  }
  // Вывод изменённой матрицы
  printf("\tИтоговая матрица:\n");
  for (int i = 0; i < size.num; i++) {
    printf("\t");
    for (int j = 0; j < size.num; j++)
      printf("%4d ", matrix[i][j]);
    printf("\n");
  }
}

/* Задание 4.
Создайте матрицу 4Х8. Заполните две первые строки матрицы случайными нулями и
единицами. В третью строку записать результат побитовой операции «И» над числами
в соответствующих столбцах первых двух строк, в четвертую - результат побитовой
операции «ИЛИ». Вывести на экран полученный массив. */
void matrix_l6_4() {
  const int rows = 4, columns = 8;
  int matrix[rows][columns];
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < columns; j++)
      matrix[i][j] = uniform(1, 2) - 1;
  for (int i = 0; i < columns; i++)
    matrix[2][i] = matrix[0][i] & matrix[1][i];
  for (int i = 0; i < columns; i++)
    matrix[3][i] = matrix[0][i] | matrix[1][i];
  printf("\tИтоговая матрица:\n");
  for (int i = 0; i < rows; i++) {
    printf("\t");
    for (int j = 0; j < columns; j++)
      printf("%4d ", matrix[i][j]);
    printf("\n");
  }
}

/* Задание 5.
Создайте динамический массив для отдельного хранения знака числа, его целой и
дробной части в трёх отдельных столбцах. Пользователь вводит с клавиатуры
вещественные числа. А программа записывает в первый столбец матрицы знак числа
(0 для положительных чисел и 1 - для отрицательных), во второй - целую часть
чисел, в третий столбец - дробную часть. Для хранения целой и дробной части
привести к пятизначному целому. Для записи каждого нового вещественного числа
производить перевыделение памяти, аналогично Example (realloc).
Например, если вводится число 3.234093, то второй ячейке строки присваивается
3, третьей - 23409, а первой - число 0. */
typedef struct {
  bool sign;
  int integer;
  int fraction5;
} l6_5_float;

void matrix_l6_5() {
  l6_5_float *array = NULL;
  int length = 0;
  while (1) {
    printf("\tВведите число: ");
    char number[DEFAULT_STR_LENGTH];
    fgets(number, DEFAULT_STR_LENGTH - 1, stdin);
    if ((not isPartOfInt(number[0])) and
        (not isPartOfInt(number[1] and not isPartOfFloat(number[0]))))
      break;
    length++;
    array = (l6_5_float *)realloc(array, length * sizeof(l6_5_float));
    array[length - 1].sign = false;
    array[length - 1].integer = 0;
    array[length - 1].fraction5 = 0;
    bool afterPoint = false, exitFlag = false;
    int cntr = 0;
    for (int i = 0; i < DEFAULT_STR_LENGTH; i++) {
      if (not isPartOfFloat(number[i])) {
        break;
      }
      if (number[i] == '-')
        array[length - 1].sign = true;
      else if (number[i] == '.') {
        if (not afterPoint)
          afterPoint = true;
        else {
          exitFlag = true;
          break;
        }
      } else {
        char curr[2] = " \0";
        curr[0] = number[i];
        if (afterPoint) {
          if (cntr == 5)
            break;
          array[length - 1].fraction5 =
              array[length - 1].fraction5 * 10 + atoi(curr);
          cntr++;
        } else
          array[length - 1].integer =
              array[length - 1].integer * 10 + atoi(curr);
      }
    }
    if (exitFlag)
      break;
  }
  printf("\tИтоговая матрица:\n");
  printf("\t|-------|------------|-------|\n");
  for (int i = 0; i < length; i++)
    printf("\t| %5s | %10d | %5d |\n", array[i].sign ? "minus" : "plus",
           array[i].integer, array[i].fraction5);
  printf("\t|-------|------------|-------|\n");
  printf("\t|  sign |   integer  |  frac |\n");
  printf("\t|-------|------------|-------|\n");
}
