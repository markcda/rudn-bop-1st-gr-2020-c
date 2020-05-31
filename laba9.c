#include "laba9.h"

// Упражнение 1.
void arr_push(int *stack, int *last, int a) {
  stack[(*last)++] = a;
  stack = (int *)realloc(stack, (*last + 1) * sizeof(int));
}

int arr_pop(int *stack, int *last, bool *err) {
  if (*last == 0) {
    *err = true;
    return -1;
  }
  int k = stack[--(*last)];
  stack = (int *)realloc(stack, (*last + 1) * sizeof(int));
  return k;
}

int *arr_dfs(int **graph, int *sizes, int amount, int search) {
  int *levels = (int *)malloc(amount * sizeof(int));
  for (int i = 0; i < amount; i++)
    levels[i] = -1;
  levels[search] = 0;
  int *last = (int *)malloc(sizeof(int));
  *last = 0;
  int *queue = (int *)malloc((*last + 1) * sizeof(int));
  arr_push(queue, last, search);
  while (*last) {
    int v = arr_pop(queue, last, NULL);
    for (int w_index = 0; w_index < sizes[v]; w_index++) {
      int w = graph[v][w_index];
      if (levels[w] == -1) {
        arr_push(queue, last, w);
        levels[w] = levels[v] + 1;
      }
    }
  }
  free(last);
  free(queue);
  return levels;
}

void l9_e1dot1() {
  int *last = (int *)malloc(sizeof(int));
  *last = 0;
  int *stack = (int *)malloc((*last + 1) * sizeof(int));
  printf("\tВводите:\n");
  printf("\tа) \"1 <любое число, которое вы хотите поместить в стек>\" - "
         "добавление числа в стек\n");
  printf("\tб) \"2\" - получение последнего числа из стека\n");
  printf("\tИли оставьте строку пустой для выхода.\n");
  while (true) {
    printf("\t");
    int_nstd *options = scanInts();
    if (not options[1].status) {
      free(options);
      break;
    }
    if (options[1].num == 1) {
      if (not options[2].status) {
        free(options);
        break;
      }
      arr_push(stack, last, options[2].num);
    } else if (options[1].num == 2) {
      bool *err = (bool *)malloc(sizeof(bool));
      *err = false;
      int k = arr_pop(stack, last, err);
      if (not(*err))
        printf("\tЧисло в стеке: %d.\n", k);
      else
        printf("\tЧисел в стеке больше нет.\n");
      free(err);
    } else {
      free(options);
      break;
    }
    free(options);
  }
  free(stack);
  free(last);
}

// Упражнение 2.
stack_t *new_stack(int initial_size) {
  stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
  stack->data_size = initial_size;
  if (stack->data_size <= 0)
    stack->data_size = DEFAULT_STACK_SIZE;
  stack->last = 0;
  stack->data = (int *)malloc(stack->data_size * sizeof(int));
  return stack;
}

void delete_stack(stack_t *stack) {
  free(stack->data);
  free(stack);
}

void struct_push(stack_t *stack, int a) {
  if (++(stack->last) == stack->data_size) {
    stack->data_size++;
    stack->data = (int *)realloc(stack->data, stack->data_size * sizeof(int));
  }
  stack->data[stack->last - 1] = a;
}

bool struct_pop(stack_t *stack, int *a) {
  if (stack->last - 1 == -1) {
    return false;
  }
  *a = stack->data[--stack->last];
  return true;
}

int *struct_dfs(int **graph, int *sizes, int amount, int search) {
  int *levels = (int *)malloc(amount * sizeof(int));
  for (int i = 0; i < amount; i++)
    levels[i] = -1;
  levels[search] = 0;
  stack_t *queue = new_stack(amount + 1);
  struct_push(queue, search);
  while (queue->last) {
    int *v = (int *)malloc(sizeof(int));
    struct_pop(queue, v);
    for (int w_index = 0; w_index < sizes[*v]; w_index++) {
      int w = graph[*v][w_index];
      if (levels[w] == -1) {
        struct_push(queue, w);
        levels[w] = levels[*v] + 1;
      }
    }
    free(v);
  }
  delete_stack(queue);
  return levels;
}

void l9_e2dot1() {
  stack_t *stack = new_stack(1);
  printf("\tВводите:\n");
  printf("\tа) \"1 <любое число, которое вы хотите поместить в стек>\" - "
         "добавление числа в стек\n");
  printf("\tб) \"2\" - получение последнего числа из стека\n");
  printf("\tИли оставьте строку пустой для выхода.\n");
  while (true) {
    printf("\t");
    int_nstd *options = scanInts();
    if (not options[1].status) {
      free(options);
      break;
    }
    if (options[1].num == 1) {
      if (not options[2].status) {
        free(options);
        break;
      }
      struct_push(stack, options[2].num);
    } else if (options[1].num == 2) {
      bool err = true;
      int *a = (int *)malloc(sizeof(int));
      err = struct_pop(stack, a);
      if (err)
        printf("\tЧисло в стеке: %d.\n", *a);
      else
        printf("\tЧисел в стеке больше нет.\n");
      free(a);
    } else {
      free(options);
      break;
    }
    free(options);
  }
  delete_stack(stack);
}

void l9_e1X2dot2() {
  printf("\tЗадайте список смежности следующим образом:\n");
  printf("\t1) пронумеруйте вершины от 0 до N\n");
  printf("\t2) в строке n = [0..N] вводите смежные с вершиной n вершины через "
         "пробел\n");
  printf("\t\t[если смежных вершин для вершины n нет, введите \"-1\"]\n");
  printf("\t3) когда закончите ввод, введите \"-2\"\n");
  int **A = (int **)malloc(sizeof(int *));
  A[0] = NULL;
  int *sizes = (int *)malloc(sizeof(int));
  sizes[0] = 0;
  int v = 0;
  printf("\t");
  int_nstd *vs = scanInts();
  while (vs[1].num != -2) {
    A[v] = (int *)malloc(vs[0].num * sizeof(int));
    for (int i = 0; i < vs[0].num; i++)
      A[v][i] = vs[i + 1].num;
    if (vs[1].num == -1)
      sizes[v++] = 0;
    else
      sizes[v++] = vs[0].num;
    A = (int **)realloc(A, (v + 1) * sizeof(int *));
    sizes = (int *)realloc(sizes, (v + 1) * sizeof(int));
    sizes[v] = 0;
    free(vs);
    printf("\t");
    vs = scanInts();
  }
  free(vs);
  printf("\tВведите теперь вершину поиска: ");
  int_nstd search = scanInt();
  if (not search.status or search.num < 0 or search.num > v - 1) {
    for (int i = 0; i <= v; i++)
      free(A[i]);
    free(A);
    free(sizes);
    return;
  }
  printf("\tВыберите функцию для поиска:\n");
  printf("\t1) arr_dfs (написана для мануального стека - динамического массива "
         "и счётчика)\n");
  printf("\t2) struct_dfs (написана для стека на основе структур): ");
  int_nstd option = scanInt();
  if (not option.status or (option.num != 1 and option.num != 2)) {
    for (int i = 0; i <= v; i++)
      free(A[i]);
    free(A);
    free(sizes);
    return;
  }
  int *levels = NULL;
  if (option.num == 1)
    levels = arr_dfs(A, sizes, v + 1, search.num);
  else
    levels = struct_dfs(A, sizes, v + 1, search.num);
  printf("\tРезультат поиска в глубину: {");
  for (int i = 0; i < v - 1; i++) {
    printf("%d: %d, ", i, levels[i]);
  }
  printf("%d: %d}.\n", v - 1, levels[v - 1]);
  for (int i = 0; i <= v; i++)
    free(A[i]);
  free(A);
  free(sizes);
}

// Упражнение 3.
typedef struct BIT {
  unsigned b1 : 1;
  unsigned b2 : 1;
  unsigned b3 : 1;
  unsigned b4 : 1;
  unsigned b5 : 1;
  unsigned b6 : 1;
  unsigned b7 : 1;
  unsigned b8 : 1;
  unsigned b9 : 1;
  unsigned b10 : 1;
  unsigned b11 : 1;
  unsigned b12 : 1;
  unsigned b13 : 1;
  unsigned b14 : 1;
  unsigned b15 : 1;
  unsigned b16 : 1;
  unsigned b17 : 1;
  unsigned b18 : 1;
  unsigned b19 : 1;
  unsigned b20 : 1;
  unsigned b21 : 1;
  unsigned b22 : 1;
  unsigned b23 : 1;
  unsigned b24 : 1;
  unsigned b25 : 1;
  unsigned b26 : 1;
  unsigned b27 : 1;
  unsigned b28 : 1;
  unsigned b29 : 1;
  unsigned b30 : 1;
  unsigned b31 : 1;
  unsigned b32 : 1;
} BIT;

void l9_e3() {
  union common_field {
    BIT bits;
    unsigned char str[4];
    int i;
    float f;
    char *pch;
  } un;
  int sizBIT = sizeof(BIT);
  int sizun = sizeof(un);
  printf("\tРазмер переменной BIT: %2d байт или %2d бит\n", sizBIT, 8 * sizBIT);
  printf("\tРазмер переменной un: %2d байт или %2d бит\n", sizun, 8 * sizun);
  un.bits.b1 = 0;
  un.bits.b2 = 0;
  un.bits.b3 = 1;
  un.bits.b4 = 0;
  un.bits.b5 = 0;
  un.bits.b6 = 0;
  un.bits.b7 = 1;
  un.bits.b8 = 0;
  un.bits.b9 = 0;
  un.bits.b10 = 0;
  un.bits.b11 = 0;
  un.bits.b12 = 1;
  un.bits.b13 = 0;
  un.bits.b14 = 1;
  un.bits.b15 = 0;
  un.bits.b16 = 0;
  un.bits.b17 = 1;
  un.bits.b18 = 1;
  un.bits.b19 = 0;
  un.bits.b20 = 1;
  un.bits.b21 = 0;
  un.bits.b22 = 1;
  un.bits.b23 = 0;
  un.bits.b24 = 1;
  un.bits.b25 = 0;
  un.bits.b26 = 0;
  un.bits.b27 = 0;
  un.bits.b28 = 0;
  un.bits.b29 = 0;
  un.bits.b30 = 0;
  un.bits.b31 = 0;
  un.bits.b32 = 0;
  printf("\tun.str = %s\n", un.str);
  printf("\tun.i   = %i\n", un.i);
  printf("\tun.f   = %f\n", un.f);
  // предупреждение: cast from pointer to integer of different size
  // [-Wpointer-to-int-cast]
  //  printf("\tun.pch = %i\n", (int)un.pch);
}

/* Задание 1.
Задайте перечислимый тип для 16 основных цветов так, чтобы результатом сложения
двух значений этого типа был цвет, полученный от сложения соответствующих
цветов, по следующим правилам:
https://iskustvoblog.wordpress.com/цветовая-арифметика/ */
enum colors_s {
  // Первая попытка
  invisible = 0,
  red = 10,
  yellow = 31,
  blue = 70,
  orange = 41,
  green = 101,
  violet = 80,
  red_orange = 51,
  yellow_green = 132,
  blue_violet = 150,
  red_violet = 90,
  yellow_orange = 72,
  blue_green = 171,
  black = 120,
  white = 122,
  grey = 242
  // Вторая попытка
  //  invisible = 0,
  //  black = 1,
  //  white = 2,
  //  grey = 3,
  //  red = 4, // сначала думал, что всё работает... но black + grey != red.
  //  blue = 16,
  //  yellow = 64,
  //  violet = 20,
  //  orange = 68,
  //  green = 80,
  //  red_orange = 72,
  //  yellow_green = 144,
  //  blue_violet = 36,
  //  red_violet = 24,
  //  yellow_orange = 132,
  //  blue_green = 96
};

void l9_1() {
  printf("\tПоскольку задание не может быть выполнено абсолютно корректно при "
         "помощи только лишь сложения в одной системе координат (по сути, "
         "необходимо две координаты минимум - чтобы изобразить плоскость "
         "цветов в полярных координатах), мы попытаемся избежать совпадений "
         "при суммировании цветов, которые объявлены в перечислении.\n\n");
  /* Это можно сделать при помощи бинарного представления: 2 бита отдаются под
   * бесцветный/чёрный/белый/серый, 2 бита - под бесцветный/красный/двойной
   * красный/пустое значение, таким же образом по 2 бита - для синего и
   * жёлтого.\n\n"); */
  // UPD: нет (см. выше)
  printf("\tПредопределённые цвета:\n");
  printf("\t\tinvisible = 0\n");
  printf("\t\tblack = 120\n");
  printf("\t\twhite = 122\n");
  printf("\t\tgrey = 242\n");
  printf("\t\tred = 10\n");
  printf("\t\tblue = 70\n");
  printf("\t\tyellow = 31\n");
  printf("\t\tviolet = 80\n");
  printf("\t\torange = 41\n");
  printf("\t\tgreen = 101\n");
  printf("\t\tred_orange = 51\n");
  printf("\t\tyellow_green = 132\n");
  printf("\t\tblue_violet = 150\n");
  printf("\t\tred_violet = 90\n");
  printf("\t\tyellow_orange = 72\n");
  printf("\t\tblue_green = 171\n");
  printf("\tВведите два цвета из перечисленных (или оставьте строку пустой для "
         "выхода): ");
  int_nstd *colors = scanInts();
  while (colors[0].num == 2) {
    char *color = (char *)malloc(40 * sizeof(char));
    int sum = colors[1].num + colors[2].num;
    switch (sum) {
    case invisible: {
      color = "invisible\0";
      break;
    }
    case black: {
      color = "black\0";
      break;
    }
    case white: {
      color = "white\0";
      break;
    }
    case grey: {
      color = "grey\0";
      break;
    }
    case red: {
      color = "red\0";
      break;
    }
    case blue: {
      color = "blue\0";
      break;
    }
    case yellow: {
      color = "yellow\0";
      break;
    }
    case violet: {
      color = "violet\0";
      break;
    }
    case orange: {
      color = "orange\0";
      break;
    }
    case green: {
      color = "green\0";
      break;
    }
    case red_orange: {
      color = "red_orange\0";
      break;
    }
    case yellow_green: {
      color = "yellow_green\0";
      break;
    }
    case blue_violet: {
      color = "blue_violet\0";
      break;
    }
    case red_violet: {
      color = "red_violet\0";
      break;
    }
    case yellow_orange: {
      color = "yellow_orange\0";
      break;
    }
    case blue_green: {
      color = "blue_green\0";
      break;
    }
    default: {
      color = "unknown\0";
      break;
    }
    }
    printf("\tРезультат - %d, %s.\n", sum, color);
    free(colors);
    printf(
        "\tВведите два цвета из перечисленных (или оставьте строку пустой для "
        "выхода): ");
    colors = scanInts();
  }
  free(colors);
}

/* Задание 2.
Определите структуру, описывающую вещи: название, вес, стоимость. Создайте
массив вещей. Напишите программу, которая помогает собрать чемодан: выводит
список доступных вещей и спрашивает размер чемодана (максимальный вес), после
чего предлагает собрать чемодан. Пользователь пишет названия вещей в строчку, а
программа проверяет могут ли они поместиться в чемодан и подсчитывает их
стоимость. Если вещи не помещаются в чемодан, программа предлагает повторить
попытку. */
struct thing {
  char *title;
  float weight;
  float cost;
};

void l9_2() {
  struct thing things[7] = {{"Чашка\0", 0.6, 500.0},
                            {"Ноутбук\0", 2.1, 69990.0},
                            {"Учебник по матану\0", 0.8, 749.0},
                            {"Пенал\0", 0.3, 2149.0},
                            {"Пауэрбанк\0", 0.7, 1990.0},
                            {"Коллекция крышек от банок\0", 0.8, 149000.0},
                            {"Портрет Авогадро\0", 2.4, 4680000.0}};
  printf("\tДоступные вещи:\n");
  for (int i = 0; i < 7; i++) {
    printf("\t\t%s, вес - %.3f кг, стоимость - %.2f рублей.\n", things[i].title,
           things[i].weight, things[i].cost);
  }
  float totalWeight, totalCost;
  float_nstd maxWeight;
  do {
    totalWeight = 0;
    totalCost = 0;
    printf("\tВведите максимальный вес: ");
    maxWeight = scanFloat();
    if (not maxWeight.status)
      return;
    printf("\tВведите названия вещей в одну строку (также учтите, что названия "
           "вещей нужно вводить без ошибок и с большой буквы): ");
    char *takedThings = (char *)malloc(DEFAULT_STR_LENGTH * sizeof(char));
    fgets(takedThings, DEFAULT_STR_LENGTH - 1, stdin);
    if (isEndOfString(takedThings[0]))
      return;

    for (int i = 0; i < 7; i++) {
      if (strstr(takedThings, things[i].title)) {
        totalWeight += things[i].weight;
        totalCost += things[i].cost;
      }
    }
    free(takedThings);
    if (totalWeight > maxWeight.num) {
      printf(
          "\tВес вещей превысил вес рюкзака. Хотите повторить попытку? (y/n) ");
      fgets(takedThings, DEFAULT_STR_LENGTH - 1, stdin);
      if (takedThings[0] != 'y')
        return;
    }
  } while (totalWeight > maxWeight.num);
  printf("\tРюкзак собран! Суммарный вес - %.3f кг, суммарная стоимость - %.2f "
         "рублей.\n",
         totalWeight, totalCost);
}

/* Задание 3.
С помощью объединения целого типа и массива символов выведите на экран
шестнадцатеричное представление целого числа. */
char hexGen(unsigned b1, unsigned b2, unsigned b3, unsigned b4) {
  int hexNumber = b1 + b2 * 2 + b3 * 4 + b4 * 8;
  char s = '0';
  switch (hexNumber) {
  case 0:
    s = '0';
    break;
  case 1:
    s = '1';
    break;
  case 2:
    s = '2';
    break;
  case 3:
    s = '3';
    break;
  case 4:
    s = '4';
    break;
  case 5:
    s = '5';
    break;
  case 6:
    s = '6';
    break;
  case 7:
    s = '7';
    break;
  case 8:
    s = '8';
    break;
  case 9:
    s = '9';
    break;
  case 10:
    s = 'a';
    break;
  case 11:
    s = 'b';
    break;
  case 12:
    s = 'c';
    break;
  case 13:
    s = 'd';
    break;
  case 14:
    s = 'e';
    break;
  case 15:
    s = 'f';
    break;
  }
  return s;
}

void l9_3() {
  union {
    int num;
    BIT bit;
  } hn;
  printf("\tВведите целое число: ");
  int_nstd num = scanInt();
  if (not num.status)
    return;
  /* Простой способ (без объединений) - вывести число при помощи printf("%x",
   * num.num);
   * Сложный - разделить число на четвёрки битов (16 значений), через
   * специальную функцию перевести 4 бита числа в 8 бит символа и вывести на
   * экран. */
  hn.num = num.num;
  char str[9];
  str[8] = '\0';
  str[7] = hexGen(hn.bit.b1, hn.bit.b2, hn.bit.b3, hn.bit.b4);
  str[6] = hexGen(hn.bit.b5, hn.bit.b6, hn.bit.b7, hn.bit.b8);
  str[5] = hexGen(hn.bit.b9, hn.bit.b10, hn.bit.b11, hn.bit.b12);
  str[4] = hexGen(hn.bit.b13, hn.bit.b14, hn.bit.b15, hn.bit.b16);
  str[3] = hexGen(hn.bit.b17, hn.bit.b18, hn.bit.b19, hn.bit.b20);
  str[2] = hexGen(hn.bit.b21, hn.bit.b22, hn.bit.b23, hn.bit.b24);
  str[1] = hexGen(hn.bit.b25, hn.bit.b26, hn.bit.b27, hn.bit.b28);
  str[0] = hexGen(hn.bit.b29, hn.bit.b30, hn.bit.b31, hn.bit.b32);
  printf("\tРезультат в 16-ричной системе счисления: 0x%s\n", str);
}

/* Задание 4.
Самолетный парк авиакомпании Colossus Airlines включает один самолет с
количеством сидячих мест, равным 12. Он выполняет один рейс ежедневно. Напишите
программу резервирования авиабилетов, обладающую следующими возможностями.
Программа использует массив из 12 структур. Каждая структура содержит номер
места в самолете, специальный маркер, который показывает, зарезервировано ли
данное место, фамилию и имя пассажира, для которого это место выделено.
Программа отображает следующее меню:

Для выбора функции введите ее буквенное обозначение:
a) Показать количество свободных мест
b) Показать список пустых свободных мест
c) Показать алфавитный список занятых мест
d) Назначить пассажиру место
e) Удалить назначение места
f) Выйти из программы

Программа выполняет действия, соответствующие пунктам меню. Позиции меню d и e
требуют ввода дополнительных данных, каждая позиция меню должна обеспечить
пользователю возможность отказаться от выбранного варианта. По завершении
выполнения конкретной функции программа воспроизводит меню на экране, исключение
составляет позиция f. */
struct airplanePlace {
  int num;
  bool isReserved;
  char *passengerName;
};

void str_swap(char **a, char **b) {
  char **t = (char **)malloc(sizeof(char *));
  *t = *a;
  *a = *b;
  *b = *t;
}

void heapify(char **arr, int rows, int i, bool (*cmp)(char *, char *)) {
  int li, ri, big;
  while (1) {
    li = i * 2 + 1;
    ri = li + 1;
    if ((li < rows) && (*cmp)(arr[li], arr[i]))
      big = li;
    else
      big = i;
    if ((ri < rows) && (*cmp)(arr[ri], arr[big]))
      big = ri;
    if (big != i) {
      // printf("%s%s", arr[big], arr[i]);
      str_swap(&arr[big], &arr[i]);
      // printf("%s%s", arr[big], arr[i]);
      i = big;
    } else
      break;
  }
}

void hsort(char **arr, int rows, bool (*cmp)(char *, char *)) {
  for (int i = rows / 2; i >= 0; --i)
    heapify(arr, rows, i, cmp);
  for (int j = rows - 1; j >= 0; --j) {
    // printf("%s%s", arr[0], arr[j]);
    str_swap(&arr[0], &arr[j]);
    // printf("%s%s", arr[0], arr[j]);
    heapify(arr, j, 0, cmp);
  }
}

bool compare(char *a, char *b) {
  // printf("%s", a);
  // printf("%d ", (strcmp(a, b) > 0));
  return (strcmp(a, b) > 0);
}

void colossusAirlines() {
  char l[DEFAULT_STR_LENGTH];
  struct airplanePlace places[12] = {
      {115, false, NULL}, {128, false, NULL}, {92, false, NULL},
      {9, false, NULL},   {51, false, NULL},  {49, false, NULL},
      {12, false, NULL},  {90, false, NULL},  {82, false, NULL},
      {83, false, NULL},  {84, false, NULL},  {111, false, NULL}};
  while (true) {
    printf("\tДля выбора функции введите ее буквенное обозначение:\n");
    printf("\ta) Показать количество свободных мест\n");
    printf("\tb) Показать список пустых свободных мест\n");
    printf("\tc) Показать алфавитный список занятых мест\n");
    printf("\td) Назначить пассажиру место\n");
    printf("\te) Удалить назначение места\n");
    printf("\tf) Выйти из программы\n");
    printf("\t");
    fgets(l, DEFAULT_STR_LENGTH - 1, stdin);
    if (l[0] == 'a') {
      int cntr = 12;
      for (int i = 0; i < 12; i++)
        if (places[i].isReserved)
          cntr--;
      printf("\t\tСвободных мест - %d\n", cntr);
    } else if (l[0] == 'b') {
      printf("\t\tСвободные места:");
      int cntr = 12;
      for (int i = 0; i < 12; i++) {
        if (places[i].isReserved)
          cntr--;
        else
          printf(" %d", places[i].num);
      }
      if (not cntr)
        printf(" отсутствуют.\n");
      else
        printf(".\n");
    } else if (l[0] == 'c') {
      char *reservedPlaces[12];
      int cntr = 0;
      for (int i = 0; i < 12; i++)
        if (places[i].isReserved)
          reservedPlaces[cntr++] = places[i].passengerName;
      if (cntr)
        hsort(reservedPlaces, cntr, compare);
      else {
        printf("\t\tЗанятых мест нет.\n");
        continue;
      }
      printf("\t\tАлфавитный список пассажиров:\n");
      for (int i = 0; i < cntr; i++) {
        printf("\t\t%s - ", reservedPlaces[i]);
        for (int j = 0; j < 12; j++) {
          if (not places[j].passengerName)
            continue;
          if (not strcmp(reservedPlaces[i], places[j].passengerName)) {
            printf("%d\n", places[j].num);
            break;
          }
        }
      }
    } else if (l[0] == 'd') {
      printf(
          "\t\tВведите ФИ пассажира (или оставьте строку пустой для отмены): ");
      char *passengerName = (char *)malloc(DEFAULT_STR_LENGTH * sizeof(char));
      fgets(passengerName, DEFAULT_STR_LENGTH - 1, stdin);
      if (isEndOfString(passengerName[0])) {
        free(passengerName);
        continue;
      }
      for (int i = 0; i < DEFAULT_STR_LENGTH; i++)
        if (passengerName[i] == '\n') {
          passengerName[i] = '\0';
          break;
        }
      printf("\t\tСвободные места:");
      int cntr = 12;
      for (int i = 0; i < 12; i++) {
        if (places[i].isReserved)
          cntr--;
        else
          printf(" %d", places[i].num);
      }
      if (not cntr) {
        printf(" отсутствуют.\n");
        free(passengerName);
        continue;
      } else
        printf(".\n");
      printf(
          "\t\tВведите номер места (или оставьте строку пустой для отмены): ");
      int_nstd seatNumber = scanInt();
      if (not seatNumber.status) {
        free(passengerName);
        continue;
      }
      int index = -1;
      for (int i = 0; i < 12; i++)
        if (places[i].num == seatNumber.num)
          index = i;
      if (index == -1) {
        free(passengerName);
        continue;
      }
      if (places[index].isReserved) {
        printf("\t\tМесто уже зарезервировано.\n");
        free(passengerName);
        continue;
      }
      places[index].isReserved = true;
      places[index].passengerName = passengerName;
    } else if (l[0] == 'e') {
      printf("\t\tЗанятые места:");
      int cntr = 0;
      for (int i = 0; i < 12; i++)
        if (places[i].isReserved) {
          printf(" %d", places[i].num);
          cntr++;
        }
      if (not cntr) {
        printf(" отсутствуют.\n");
        continue;
      } else
        printf(".\n");
      printf("\t\tВведите номер места, чтобы его освободить (или оставьте "
             "строку пустой для отмены): ");
      int_nstd seatNumber = scanInt();
      if (not seatNumber.status)
        continue;
      int index = -1;
      for (int i = 0; i < 12; i++)
        if (places[i].num == seatNumber.num)
          index = i;
      if (index == -1)
        continue;
      places[index].isReserved = false;
      free(places[index].passengerName);
    } else
      break;
  }
}
