#include "laba7.h"
#include <string.h>

/* Задание 1.
 * В  программировании  можно  из  одной  функции  вызывать  другую.
 * Для  иллюстрации  этой возможности напишите программу по следующему
 * описанию. Основная ветка программы, не считая заголовков функций, состоит из
 * одной строки кода. Это вызов функции test(). В ней запрашивается на ввод
 * целое число. Если оно положительное, то вызывается функция positive(), тело
 * которой содержит команду вывода на экран слова "Положительное". Если число
 * отрицательное, то вызывается функция negative(), ее тело содержит выражение
 * вывода на экран слова "Отрицательное". */
void positive() { printf("\tПоложительное.\n"); }

void negative() { printf("\tОтрицательное.\n"); }

void test() {
  printf("\tВведите число: ");
  int_nstd num = scanInt();
  if (not num.status)
    return;
  if (num.num >= 0)
    positive();
  else
    negative();
}

void l7_1() { test(); }

/* Задание 2.
 * Напишите программу, в которой определены следующие четыре
 * функции:
 * 1. Функция getInput() не имеет параметров, запрашивает ввод с
 * клавиатуры и возвращает в основную программу полученную строку.
 * 2. Функция testInput() имеет один параметр. В теле она проверяет, можно ли
 * переданное ей значение преобразовать к целому числу. Если можно, возвращает
 * логическое True. Если нельзя – False.
 * 3. Функция strToInt() имеет один параметр. В теле преобразовывает переданное
 * значение к целочисленному типу. Возвращает полученное число.
 * 4. Функция printInt() имеет один параметр. Она выводит переданное значение на
 * экран и ничего не возвращает.
 * В основной ветке программы вызовите первую функцию. То, что она вернула,
 * передайте во вторую функцию. Если вторая функция вернула True, то те же
 * данные (из первой функции) передайте в третью функцию, а возвращенное третьей
 * функцией значение - в четвертую. */
char *getInput() {
  char *str = NULL;
  str = (char *)malloc(DEFAULT_STR_LENGTH * sizeof(char));
  fgets(str, DEFAULT_STR_LENGTH, stdin);
  return str;
}

bool testInput(char *str) {
  if (isPartOfInt(str[0]))
    return true;
  return false;
}

int strToInt(char *str) {
  int num = atoi(str);
  return num;
}

void printInt(int num) { printf("%d", num); }

void l7_2() {
  printf("\tВведите число: ");
  char *str = getInput();
  if (not testInput(str))
    return;
  int num = strToInt(str);
  printf("\t");
  printInt(num);
  printf("\n");
}

/* Задание 3.
 * Напишите функцию void stats(double* a, int size, double* min, double* max,
 * double* avg); которая  вычисляет  минимальное,  максимальное  и  среднее
 * значение  элементов  массива  a. Результат она должна разместить
 * соответственно по адресам min, max, avg. */
void stats(double *a, int size, double *min, double *max, double *avg) {
  if (not size)
    return;
  *min = a[0];
  *max = a[0];
  *avg = 0;
  for (int i = 0; i < size; i++) {
    if (*min > a[i])
      *min = a[i];
    if (*max < a[i])
      *max = a[i];
    *avg += a[i];
  }
  *avg = *avg / size;
}

void l7_3() {
  printf("\tВведите элементы массива через пробел: ");
  double_nstd *array = scanDoubles();
  if (not array[0].num)
    return;
  double *nums = NULL;
  int cntr = 0;
  for (int i = 0; i < array[0].num; i++) {
    if (not array[i + 1].status)
      break;
    cntr++;
    nums = (double *)realloc(nums, cntr * sizeof(double));
    nums[cntr - 1] = array[i + 1].num;
  }
  printf("\tВведённый массив:");
  for (int i = 0; i < cntr; i++)
    printf(" %f", nums[i]);
  printf("\n");
  double min = 0, max = 0, avg = 0;
  stats(nums, cntr, &min, &max, &avg);
  printf("\tМинимальный элемент в массиве: %f\n", min);
  printf("\tМаксимальный элемент в массиве: %f\n", max);
  printf("\tСреднее арифметическое элементов массива: %f\n", avg);
}

/* Задание 4.
 * Напишите функцию, которая удаляет из введённой пользователем строки все
 * повторяющиеся символы и пробелы, после чего выводит полученный результат на
 * экран. Например, если было введено "abc cde def", то должно быть выведено
 * "abcdef". */
void l7_4() {
  printf("\tВведите строку: ");
  char *str = (char *)malloc(DEFAULT_STR_LENGTH * sizeof(char));
  fgets(str, DEFAULT_STR_LENGTH, stdin);
  char *set = NULL;
  int cntr = 0;
  bool second = false;
  for (int i = 0; not isEndOfString(str[i]); i++) {
    bool toAdd = true;
    if ((int)str[i] < 0) {
      // Здесь нужно проверять теперь другие интересные вещи.
      // Нам нужно сравнивать символы по двойкам.
      if ((i != 0) and (cntr != 0)) {
        for (int j = 1; j < cntr; j++) {
          if (not second) {
            if (i + 1 < DEFAULT_STR_LENGTH) {
              if ((str[i] == set[j - 1]) and (str[i + 1] == set[j]) and
                  ((int)str[i + 1] < 0)) {
                toAdd = false;
                break;
              }
            }
          } else {
            if ((str[i] == set[j]) and (str[i - 1] == set[j - 1]) and
                ((int)str[i - 1] < 0)) {
              toAdd = false;
              break;
            }
          }
        }
        second = not second;
      }
    } else {
      second = false;
      for (int j = 0; j < cntr; j++) {
        if (str[i] == set[j]) {
          toAdd = false;
          break;
        }
      }
    }
    if ((not toAdd) or (str[i] == ' '))
      continue;
    cntr++;
    set = (char *)realloc(set, cntr * sizeof(char));
    set[cntr - 1] = str[i];
  }
  cntr++;
  set = (char *)realloc(set, cntr * sizeof(char));
  set[cntr - 1] = '\0';
  printf("\tПолучившийся набор символов: %s\n", set);
}

/* Задание 6*. «Авторассылка»
 * Найти в строке указанную подстроку и заменить ее на новую. Строку, ее
 * подстроку для замены иновую подстроку вводит пользователь. Пример работы
 * программы:
 *
 * Строка: Здравствуйте, Змей Горыныч. Сегодня совещание в 10.00
 * Ее заменяемая подстрока: Змей Горыныч
 * Новая подстрока: Арчибальт Аристархович
 * Здравствуйте, Арчибальт Аристархович. Сегодня совещание в 10.00 */
void l7_6() {
  printf("Введите строку: ");
  char *str = (char *)malloc(DEFAULT_STR_LENGTH * sizeof(char));
  fgets(str, DEFAULT_STR_LENGTH, stdin);
  printf("Введите подстроку поиска: ");
  char *search = (char *)malloc(DEFAULT_STR_LENGTH * sizeof(char));
  fgets(search, DEFAULT_STR_LENGTH, stdin);
  printf("Введите подстроку замены: ");
  char *replace = (char *)malloc(DEFAULT_STR_LENGTH * sizeof(char));
  fgets(replace, DEFAULT_STR_LENGTH, stdin);
  char *p;
  int index = -1;
  if ((p = strstr(str, search)) != NULL)
    index = p - str;
  else
    printf("В строке нет подстроки!");
}

/* Задание **. Магический квадрат
 * Подробнее про это: https://en.wikipedia.org/wiki/Magic_square */
void printMagicSquare(int **A, int n) {
  int r, c;
  printf("\tМагический квадрат:\n\t");
  for (r = 0; r < n; r++, printf("\n\t"))
    for (c = 0; c < n; c++)
      printf("%3d", A[r][c]);
  printf("\n");
}

void createMagicSquares(int **A, int sum, int p, int n, int *out) {
  int i, j, k, s;
  for (i = 1; i <= n * n; i++) {
    for (j = 0; j < p; j++)
      if (A[j / n][j % n] == i)
        break;
    if (j == p) {
      A[p / n][p % n] = i;
      if ((p + 1) % n == 0) {
        k = p / n * n;
        for (s = j = 0; j < n; j++)
          s += A[(k + j) / n][(k + j) % n];
        if (s < sum)
          continue;
        if (s > sum)
          return;
      } else if (p / n == n - 1) {
        k = p % n;
        for (s = j = 0; j < n * n; j += n)
          s += A[(k + j) / n][(k + j) % n];
        if (s < sum)
          continue;
        if (s > sum)
          return;
        if (!k) {
          for (s = 0, j = n - 1; j >= 0; j--, k += n)
            s += A[(k + j) / n][(k + j) % n];
          if (s < sum)
            continue;
          if (s > sum)
            return;
        }
      }
      if (p + 1 < n * n)
        createMagicSquares(A, sum, p + 1, n, out);
      else {
        for (s = j = 0; j < n; j++)
          s += A[j][j];
        if (s < sum)
          continue;
        if (s > sum)
          return;
        if (*out == 0) {
          printMagicSquare(A, n);
          *out -= 1;
        } else if (*out == 1)
          printMagicSquare(A, n);
      }
    }
  }
}

void its_a_kind_of_magic() {
  printf("\tВведите размерность магического квадрата: ");
  int_nstd n = scanInt();
  if (not n.status)
    return;
  printf("\tВведите 0, если хотите ограничить число результатов одним, и 1, "
         "если вывести все результаты: ");
  int_nstd times = scanInt();
  if (not times.status)
    return;
  int **A, sum = 0, *out;
  out = (int *)malloc(sizeof(int));
  *out = times.num;
  A = (int **)malloc(n.num * sizeof(int *));
  for (int i = 0; i < n.num; i++)
    A[i] = (int *)malloc(n.num * sizeof(int));
  for (int i = 1; i <= n.num * n.num; i++)
    sum += i;
  sum /= n.num;
  createMagicSquares(A, sum, 0, n.num, out);
  for (int i = 0; i < n.num; i++)
    free(A[i]);
  free(A);
}
