#include "laba4.h"

/* Упражнение 1. Коровы.
Для целого числа n введённого пользователем закончите фразу “На лугу пасется...”
одним из возможных продолжений: “n коров”, “n корова”, “n коровы”, правильно
склоняя слово “корова”. Напишите два варианта программы: с использованием
условного оператора if-else и оператора множественного выбора switch. */

void cows() {
  printf("\tВведите число коров: ");
  int_nstd n = scanInt();
  if (not n.status)
    return;
  printf("\tНа лугу пасётся ");
  switch (n.num % 10) {
  case 1: {
    printf("%i корова.\n", n.num);
    break;
  }
  case 2:
  case 3:
  case 4: {
    if (not((n.num > 10) and (n.num < 15)))
      printf("%i коровы.\n", n.num);
    else
      printf("%i коров.\n", n.num);
    break;
  }
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 0: {
    printf("%i коров.\n", n.num);
    break;
  }
  }
}

/* Упражнение 2. День в календаре.
Напишите программу, которая по дате определяет день недели, на который эта дата
приходится. Для вычисления дня недели, на который эта дата приходится. Для
вычисления дня недели воспользуйтесь формулой:

n = (d * ceil(1/5 * (13 * (d - 2) - 1)) + Y + ceil(Y/4) + ceil(c/4) - 2c + 777)
% 7,

где d – месяц, Y – номер года в столетии, c – количество столетий, ceil() –
целочисленный результат (отбрасывание дробной части). Результат соответствует
дням: 0 – воскресенье, 1 – понедельник, 2 – вторник, …, 6 – суббота.*/

/*
 * Для начала, формула не работает.
 * Поэтому мы переделаем всё тут.
 */
int Date(int D, int M, int Y) {
  int a, y, m, R;
  a = (14 - M) / 12;
  y = Y - a;
  m = M + 12 * a - 2;
  R = 7000 + (D + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12);
  return R % 7;
}

void lesJours() {
  printf("\tВведите число: ");
  int_nstd d = scanInt();
  if (not d.status)
    return;
  printf("\tВведите месяц: ");
  int_nstd m = scanInt();
  if (not m.status)
    return;
  printf("\tВведите год: ");
  int_nstd y = scanInt();
  if (not y.status)
    return;
  int n = Date(d.num, m.num, y.num);
  printf("\tСегодня ");
  switch (n) {
  case 0: {
    printf("воскресенье.\n");
    break;
  }
  case 1: {
    printf("понедельник.\n");
    break;
  }
  case 2: {
    printf("вторник.\n");
    break;
  }
  case 3: {
    printf("среда.\n");
    break;
  }
  case 4: {
    printf("четверг.\n");
    break;
  }
  case 5: {
    printf("пятница.\n");
    break;
  }
  case 6: {
    printf("суббота.\n");
    break;
  }
  }
}

/* Упражнение 3. Равнобедренный треугольник.
Нарисовать равнобедренный треугольник из символов ^. Высоту выбирает
пользователь. Например: высота = 2, на экране:
@@@      ^
@@@     ^^^
*/
void pyramid() {
  printf("\tВведите высоту пирамиды: ");
  int_nstd h = scanInt();
  if (not h.status)
    return;
  for (int n = 1; n <= h.num; n++) {
    printf("\t");
    for (int i = 1; i <= h.num - n; i++)
      printf(" ");
    for (int i = 1; i <= 1 + 2 * (n - 1); i++)
      printf("^");
    printf("\n");
  }
}

/* Упражнение 4. Счастливое число
Дано четырехзначное число. Определите, является ли его десятичная запись
симметричной. Если число симметричное, то выведите 1, иначе выведите любое
другое целое число. Число может иметь меньше четырех знаков, тогда нужно
считать, что его десятичная запись дополняется слева нулями. */
void fortunaNumber() {
  printf("\tВведите число: ");
  int_nstd num = scanInt();
  if (not num.status)
    return;
  num.num = num.num % 10000;
  char str[4];
  for (int i = 0; i < 4; i++) {
    str[3 - i] = num.num % 10 + '0';
    num.num = num.num / 10;
  }
  if ((str[0] == str[3]) and (str[1] == str[2]))
    printf("\tРезультат: 1\n");
  else
    printf("\tРезультат: 0\n");
}

/* Задание 1. "Угадай число"
Пользователь загадывает число от 1 до N. Программа запрашивает у пользователя N.
Требуется отгадать загаданное число, задав как можно меньше вопросов. (Обычно
подобные задачи решают с помощью цикла). */
int_nstd guesser(int current) {
  printf("\tЗагаданное число - это %d?\n", current);
  printf("\t1. Да\n");
  printf("\t2. Нет, мое число меньше\n");
  printf("\t3. Нет, мое число больше\n\n");
  printf("\tОтвет: ");
  return scanInt();
}

void guessNumber() {
  printf("\tВведите N: ");
  int_nstd N = scanInt();
  if (not N.status)
    return;
  int left = 1, right = N.num, current;
  int_nstd choice;
  current = (right + 1) / 2;
  choice = guesser(current);
  while (choice.num != 1) {
    if (left == right) {
      printf("\tЛожь!\n");
      return;
    }
    if (choice.num == 2)
      right = current - 1;
    else if (choice.num == 3)
      left = current + 1;
    current = (right + left) / 2;
    choice = guesser(current);
  }
  printf("\n");
}

/* Напишите программу, вычисляющую значение числа π по этим формулам первые
n-итераций. Выводите все итерации и текущее значение числа π с 10-ю знаками
после запятой в следующем формате:
|----------------|
| N | piML | piV |
|----------------|
*/
const long double piRes = 3.141592;

long double piML(int iters) {
  int down = 1;
  short int sign = 1;
  long double total = 0.0;
  for (int i = 0; i < iters; i++) {
    total += (long double)sign * ((long double)1 / down);
    sign *= -1;
    down += 2;
  }
  return total * 4;
}

long double piV(int iters) {
  int up = 2, down = 1;
  long double total = 1.0;
  for (int i = 0; i < iters; i++) {
    total *= (long double)up / down;
    if (i % 2 == 1)
      up += 2;
    if (i % 2 == 0)
      down += 2;
  }
  return total * 2;
}

void piNum() {
  printf("\tВведите число итераций: ");
  int_nstd iters = scanInt();
  if (not iters.status)
    return;
  int MLdown = 1, Vup = 2, Vdown = 1;
  short int MLsign = 1;
  long double MLtotal = 0.0, Vtotal = 1.0;
  printf("\t|--------------------------------------|\n");
  for (int i = 0; i < iters.num; i++) {
    // 1. piML (Мадхава-Лейбниц)
    MLtotal += (long double)MLsign * ((long double)1 / MLdown);
    MLsign *= -1;
    MLdown += 2;
    // 2. piV (Валлис)
    Vtotal *= (long double)Vup / Vdown;
    if (i % 2 == 1)
      Vup += 2;
    if (i % 2 == 0)
      Vdown += 2;
    // 3. Вывод
    printf("\t| %10d | %10.8Lf | %10.8Lf |\n", (i + 1), MLtotal * 4,
           Vtotal * 2);
    // Для большей точности:
    // printf("\t| %d | %Lf | %Lf |", (i + 1), MLtotal * 4, Vtotal * 2);
  }
  printf("\t|--------------------------------------|\n");
  printf("\t|     Ni     |    piML    |     piV    |\n");
  printf("\t|--------------------------------------|\n");
}

/* Задание 3. Квадрат Пифагора.
Напишите программу, которая выводит на экран квадрат Пифагора – таблицу
умножения (https://ru.wikipedia.org/wiki/Таблица_умножения). */
void pifagoreanTable() {
  printf(
      "\t|---------------------------------------------------------------------"
      "--|\n");
  for (int i = 1; i <= 10; i++)
    printf("\t| %d * %2d = %2d | %d * %2d = %2d | %d * %2d = %2d | %d * %2d = "
           "%2d | %2d * %2d = %3d |\n",
           1, i, i, 2, i, 2 * i, 3, i, 3 * i, 4, i, 4 * i, 5, i, 5 * i);
  printf(
      "\t|---------------------------------------------------------------------"
      "--|\n");
  for (int i = 1; i <= 10; i++)
    printf("\t| %d * %2d = %2d | %d * %2d = %2d | %d * %2d = %2d | %d * %2d = "
           "%2d | %2d * %2d = %3d |\n",
           6, i, 6 * i, 7, i, 7 * i, 8, i, 8 * i, 9, i, 9 * i, 10, i, 10 * i);
  printf(
      "\t|---------------------------------------------------------------------"
      "--|\n");
}

/* Задание 4. Равнобедренный треугольник 2.0.
Нарисовать равнобедренный треугольник из символов ^, /, \, _. Высоту выбирает
пользователь. Например: высота = 3, на экране:
@@@    ^
@@@   / \
@@@   ___
*/
void pyramid2() {
  printf("\tВведите высоту пирамиды: ");
  int_nstd h = scanInt();
  if (not h.status)
    return;
  int l = h.num * 2 - 3;
  printf("\t");
  for (int j = 0; j < (l - 1) / 2; j++)
    printf(" ");
  printf("^\n\t");
  for (int i = 1; i < h.num - 1; i++) {
    for (int j = 0; j < (l - 1 - 2 * i) / 2; j++)
      printf(" ");
    printf("/");
    for (int j = 0; j < 1 + (i - 1) * 2; j++)
      printf(" ");
    printf("\\\n\t");
  }
  for (int j = 0; j < l; j++)
    printf("_");
  printf("\n");
}

/* Задание 5*. «Сложение»
Напишите программу, которая запрашивает ввод двух значений. Если хотя бы одно из
них не является числом, то должна выполняться конкатенация, т. е. соединение,
строк. В остальных случаях введенные числа суммируются. */
void adding() {
  char values[2][256];
  printf("\tВведите в двух последующих строчках необходимые символы:\n");
  for (unsigned int i = 0; i < 2; i++) {
    printf("\t");
    fgets(values[i], 256, stdin);
  }
  unsigned int lengths[2] = {0, 0};
  // Уточним их длины (то есть поймём, когда был введён нуль-терминатор или
  // перевод строки
  for (unsigned int i = 0; i < 2; i++)
    for (int j = 0; j < 255; j++)
      if (not isEndOfString(values[i][j]))
        lengths[i] += 1;
      else
        break;
  printf("\n\t[Отладка: длины строк] %d, %d\n\n", lengths[0], lengths[1]);
  bool nums[2] = {true, true};
  for (int i = 0; i < 2; i++)
    for (unsigned int j = 0; j < lengths[i]; j++)
      if (not isPartOfFloat(values[i][j])) {
        nums[i] = false;
        break;
      }
  if (nums[0] and nums[1]) {
    float sum = 0;
    float num1 = atof(values[0]);
    float num2 = atof(values[1]);
    sum = num1 + num2;
    printf("\tРезультат - число: %.5f\n", sum);
  } else {
    char ustr[lengths[0] + lengths[1] + 1];
    for (int i = 0; i < 2; i++)
      for (unsigned int j = 0; j < lengths[i]; j++)
        ustr[i * lengths[0] + j] = values[i][j];
    ustr[lengths[0] + lengths[1]] = '\0';
    printf("\tРезультат - строка: %s\n", ustr);
  }
}

/* Задание 6*. «Игра в арифметику»
Напишите программу, которая проверяет пользователя на знание таблицы умножения.
Пользователь сам вводит два целых однозначных числа. Программа задаёт вопрос:
результат умножения первого числа на второе. Пользователь должен ввести ответ и
увидеть на экране, правильно он ответил или нет. Если нет – показать ещё и
правильный результат. Повторять процедуру, пока пользователь не даст 5
правильных ответов. После трёх правильных ответов подряд программа должна
выводить поощрительное, ободряющее сообщение (на ваш вкус), после трёх
неправильных ответов подряд – «грязно выругаться» (на ваш вкус). */
void playingArithmetic() {
  short int wins = 0, fails = 0, total = 0;
  while (total < 5) {
    printf("\tВведите два числа через пробел: ");
    int_nstd *nums = scanInts();
    if (nums[0].num != 2)
      return;
    if (not nums[1].status or not nums[2].status)
      return;
    printf("\tЧему равно их произведение? ");
    int_nstd result = scanInt();
    if (not result.status)
      return;
    if (result.num == nums[1].num * nums[2].num) {
      total += 1;
      wins += 1;
    } else
      fails += 1;
    if (wins == 3) {
      printf("\tЕдрить-кадрить, ты красавчик! Три раза подряд правильно "
             "посчитал!\n");
      wins = 0;
    }
    if (fails == 3) {
      printf("\tЛя, ты ошибся три раза подряд. Негоже так!\n");
      fails = 0;
    }
  }
  printf("\tА вот и победа! Ты справился, красавец))\n");
}

/* Задание 7*. «Время в пути».
У пользователя есть список любимых мест, например: «дом», «универ», «кафешка»,
«парк», «тосамоеместо» и т.д. (придумайте что-нибудь на ваш вкус). Между всеми
возможными пунктами известно время перемещения в минутах. Необходимо написать
код, в котором будет реализован диалог с пользователем, начинающийся фразой:
«Доброе утро, куда отправимся сегодня?». После этого пользователь вводит
название места. Если же пункта с таким названием нет, надо сообщить об этом и
предложить ввести название снова. Считается, что в начале пользователь находится
дома. После ввода надо показать на экране время в пути в минутах. На это же
число секунд, что занимает путь в минутах, программа засыпает. По истечению
этого времени выводится сообщение: «Вот мы и на месте!». В каждом месте
пользователь может провести только 1 час, и программа соответственно ждёт 1
минуту. После этого программа предлагает пользователю отправиться ещё
куда-нибудь. Общее время, затраченное на перемещения и пребывания, суммируется,
программа заканчивает свою работу и желает «Спокойной ночи!» после того как
общее время составит 12 часов. */
struct place {
  char title[DEFAULT_STR_LENGTH];
  unsigned short int travelTime;
};

void travelTime() {
  struct place places[6] = {{"РУДН", 12},
                            {"L'école", 5},
                            {"Киноклуб", 10},
                            {"Совиное гнездо", 28},
                            {"Клуб программистов", 4},
                            {"CCLC", 92}};
  unsigned short int allTime = 0;
  while (allTime < 12 * 60) {
    printf("\tВведите место, в которое вы сегодня собрались: ");
    char curr[DEFAULT_STR_LENGTH];
    fgets(curr, DEFAULT_STR_LENGTH, stdin);
    if (isEndOfString(curr[0]))
      return;
    short int timeTo = -1;
    for (int i = 0; i < 6; i++)
      if (isEqual(places[i].title, curr))
        timeTo = places[i].travelTime;
    if (timeTo == -1) {
      printf("\tЭм... к сожалению, среди ваших любимых мест (точнее, "
             "предустановленных) нет такого. Зато вот что там есть:\n");
      for (int i = 0; i < 6; i++)
        printf("\t\t%d) %s - %d мин\n", i, places[i].title,
               places[i].travelTime);
      continue;
    }
    allTime += timeTo;
    sleep(timeTo);
    printf("\tВот мы и на месте!\n");
  }
  printf("\tКстати, время вышло. Спокойной ночи!\n");
}
