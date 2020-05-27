#include "laba8.h"

// Пример первый.
void comparison() {
  float x4 = 0.1;
  double x8 = 0.1;
  if (x4 == x8)
    printf("x4 == x8\n");
  else
    printf("x4 != x8\n");
}

void summation_sequence() {
  int j;
  float summ = 0;
  for (j = 1; j <= 1000; j++)
    summ += 1.0 / j;
  printf("Сумма равна %12.9f\n", summ);
  summ = 0;
  for (j = 1000; j >= 1; j--)
    summ += 1.0 / j;
  printf("Сумма равна %12.9f\n", summ);
}

void l8_e1() {
  printf("\tВывод функций:\n");
  comparison();
  summation_sequence();
  printf("\tВышеперечисленные строки показывают, что точность вычислений в Си "
         "хромает до невозможности.\n");
}

// Пример второй.
float Bakers_map(float x) {
  if (x < 0.5)
    return 2.0 * x;
  else
    return 2.0 * x - 1.0;
}

void l8_e2() {
  double a = 0.2;
  double b = 0.2;
  printf("\tНачальные значения переменных: %.5f %.5f\n", a, b);
  printf("\tВведите количество итераций для преобразования пекаря: ");
  int_nstd iters = scanInt(); // int iters = 0; scanf("%d", &iters);
  if (not iters.status)
    return;
  for (int i = 0; i < iters.num; i++) {
    a = Bakers_map(a);
    b = Bakers_map(b);
  }
  printf("\tРезультат совместных преобразований пекаря.\n");
  printf("\tЗначение первой переменной: %f\n", a);
  printf("\tЗначение второй переменной: %f\n", b);
  a = 0.2;
  b = 0.2;
  for (int i = 0; i < iters.num; i++)
    a = Bakers_map(a);
  for (int i = 0; i < iters.num; i++)
    b = Bakers_map(b);
  printf("\tРезультат преобразований пекаря по отдельности.\n");
  printf("\tЗначение первой переменной: %f\n", a);
  printf("\tЗначение второй переменной: %f\n", b);
  printf("\n\tПребывая в полной уверенности, что числа совпадают, давайте "
         "возьмём начальные значения a и b из первого примера: они отличаются "
         "совсем незначительно.\n");
  a = -7; // Для нормализации данных
  for (int i = 1; i <= 1000; i++)
    a += 1.0 / i;
  b = -7; // Для нормализации данных
  for (int i = 1000; i >= 1; i--)
    b += 1.0 / i;
  for (int i = 0; i < iters.num; i++)
    a = Bakers_map(a);
  for (int i = 0; i < iters.num; i++)
    b = Bakers_map(b);
  printf("\tРезультат преобразований пекаря по отдельности.\n");
  printf("\tЗначение первой переменной: %f\n", a);
  printf("\tЗначение второй переменной: %f\n", b);
  printf("\n\tНа больших итерациях функция Bakers_map проделывает обратную "
         "работу: не создаёт хаос, а сглаживает его, выступая в роли "
         "кугельблица для любых чисел.\n");
}

// Пример третий.
const double pi = 3.14159265358979323846264338327950288419716939937510;
double f(double x) { return x - 0.333f * cos(x) - 0.7f * pi; }
double g(double x) { return x * x - 16 * x + 49; }

bool isPositive(double x) {
  if (x - ((int)(x / 10)) > 0)
    return true;
  else
    return false;
}

double Bisection(double a, double b, double epsilon, double (*fun)(double x)) {
  if (fun(a) == 0)
    return a;
  if (fun(b) == 0)
    return b;
  float dx = 0, xi = 0;
  while (b - a > epsilon) {
    dx = (b - a) / 2;
    xi = a + dx;
    if (isPositive(fun(a)) != isPositive(fun(xi)))
      b = xi;
    else
      a = xi;
  }
  return xi;
}

void l8_e3() {
  printf("\tФункция f(x) = x - 0.333 * cos(x) - 0.7 * π\n");
  printf("\tФункция g(x) = x ** 2 - 16 * x + 49\n");
  printf("\tВведите левую границу для алгоритма бисекции: ");
  double_nstd a = scanDouble();
  if (not a.status)
    return;
  printf("\tВведите правую границу для алгоритма бисекции: ");
  double_nstd b = scanDouble();
  if (not b.status)
    return;
  if (a.num >= b.num)
    return;
  printf("\tВведите необходимую точность вычислений (по умолчанию - 0.001): ");
  double_nstd epsilon = scanDouble();
  if (not epsilon.status) {
    epsilon.status = true;
    epsilon.num = 0.001;
  }
  if (epsilon.num < 0)
    epsilon.num = 0.001;
  printf("\tРезультат работы алгоритма для f(x) - %.5f\n",
         Bisection(a.num, b.num, epsilon.num, f));
  printf("\tРезультат работы алгоритма для g(x) - %.5f\n",
         Bisection(a.num, b.num, epsilon.num, g));
}

// Пример четвёртый.
int sumOfDigits(int number) {
  int digit = 0;
  if (number < 0)
    number = -number;
  if (number < 0)
    return 2;
  while (number > 0) {
    digit = digit + (number % 10);
    number = number / 10;
  }
  if (digit > 9)
    digit = digit / 10 + digit % 10;
  if (digit > 9)
    digit = 1;
  return digit;
}

void l8_e4() {
  printf("\tСумматор цифр числа (учитывая ограничение на int в Си, работающий "
         "правильно и с одним циклом).\n"); // MAX_INT = 2147483647
  printf("\tВведите целое число: ");
  int_nstd number = scanInt();
  while (number.status) {
    printf("\tСумма цифр числа %d равна %d.\n", number.num,
           sumOfDigits(number.num));
    printf("\tВведите целое число: ");
    number = scanInt();
  }
}

/* Задание 1.
 * Реализуйте метод хорд, аналогично заданию в Exemple 8.3. (см.
 * Программирование и информатика Антонюк В.А., Иванов А.П., 2015). И
 * протестируйте его на функции из задания Exemple 8.3. */
double Secant(double a, double b, double epsilon, double (*fun)(double x)) {
  while (fabs(b - a) > epsilon) {
    a = b - (b - a) * fun(b) / (fun(b) - fun(a));
    b = a + (a - b) * fun(a) / (fun(a) - fun(b));
  }
  return b;
}

void l8_1() {
  printf("\tФункция f(x) = x - 0.333 * cos(x) - 0.7 * π\n");
  printf("\tФункция g(x) = x ** 2 - 16 * x + 49\n");
  printf("\tВведите левую границу для алгоритма хорд: ");
  double_nstd a = scanDouble();
  if (not a.status)
    return;
  printf("\tВведите правую границу для алгоритма хорд: ");
  double_nstd b = scanDouble();
  if (not b.status)
    return;
  if (a.num >= b.num)
    return;
  printf("\tВведите необходимую точность вычислений (по умолчанию - 0.001): ");
  double_nstd epsilon = scanDouble();
  if (not epsilon.status) {
    epsilon.status = true;
    epsilon.num = 0.001;
  }
  if (epsilon.num < 0)
    epsilon.num = 0.001;
  printf("\tРезультат работы алгоритма для f(x) - %.5f\n",
         Secant(a.num, b.num, epsilon.num, f));
  printf("\tРезультат работы алгоритма для g(x) - %.5f\n",
         Secant(a.num, b.num, epsilon.num, g));
}

/* Задание 2.
 * Реализуйте один из методов вычисления определённого интеграла из
 * главы 3. Вычисление определённых интегралов книги Программирование и
 * информатика Антонюк В.А., Иванов А.П., 2015. И протестируйте его. */
double leftRectIntegralMethod(double a, double b, double epsilon,
                              double (*fun)(double x)) {
  double s = 0;
  while (a < b) {
    s += fun(a) * epsilon;
    a += epsilon;
  }
  return s;
}

double rightRectIntegralMethod(double a, double b, double epsilon,
                               double (*fun)(double x)) {
  double s = 0;
  while (a + epsilon < b) {
    s += fun(a + epsilon) * epsilon;
    a += epsilon;
  }
  return s;
}

double centralRectIntegralMethod(double a, double b, double epsilon,
                                 double (*fun)(double x)) {
  double s = 0;
  while (a + epsilon / 2 < b) {
    s += fun(a + epsilon / 2) * epsilon;
    a += epsilon;
  }
  return s;
}

double trapezoidIntegralMethod(double a, double b, double epsilon,
                               double (*fun)(double x)) {
  double s = 0;
  while (a + epsilon < b) {
    s += 0.5f * (fun(a) + fun(a + epsilon)) * epsilon;
    a += epsilon;
  }
  return s;
}

double parabolaIntegralMethod(double a, double b, double epsilon,
                              double (*fun)(double x)) {
  double s = 0;
  while (a + epsilon < b) {
    s += epsilon / 6 * (fun(a) + 4 * fun(a + epsilon / 2) + fun(a + epsilon));
    a += epsilon;
  }
  return s;
}

void l8_2() {
  printf("\tФункция f(x) = x - 0.333 * cos(x) - 0.7 * π\n");
  printf("\tФункция g(x) = x ** 2 - 16 * x + 49\n");
  printf("\tВведите левую границу для вычисления интегралов: ");
  double_nstd a = scanDouble();
  if (not a.status)
    return;
  printf("\tВведите правую границу для вычисления интегралов: ");
  double_nstd b = scanDouble();
  if (not b.status)
    return;
  if (a.num >= b.num)
    return;
  printf("\tВведите разбиение отрезка (по умолчанию - 0.001): ");
  double_nstd epsilon = scanDouble();
  if (not epsilon.status) {
    epsilon.status = true;
    epsilon.num = 0.001;
  }
  if (epsilon.num < 0)
    epsilon.num = 0.001;
  printf("\n\tВыберите алгоритм/-ы (введите числа, соответствующие следующим "
         "алгоритмам):\n");
  printf("\t1) метод левых прямоугольников\n");
  printf("\t2) метод правых прямоугольников\n");
  printf("\t3) квадратичный метод центральных прямоугольников\n");
  printf("\t4) метод трапеций\n");
  printf("\t5) метод парабол: ");
  char *variants = (char *)malloc(DEFAULT_STR_LENGTH * sizeof(char));
  fgets(variants, DEFAULT_STR_LENGTH - 1, stdin);
  if (containsChar(variants, '1')) {
    printf("\tРезультат работы алгоритма 1 для f(x) - %.5f\n",
           leftRectIntegralMethod(a.num, b.num, epsilon.num, f));
    printf("\tРезультат работы алгоритма 1 для g(x) - %.5f\n",
           leftRectIntegralMethod(a.num, b.num, epsilon.num, g));
  }
  if (containsChar(variants, '2')) {
    printf("\tРезультат работы алгоритма 2 для f(x) - %.5f\n",
           rightRectIntegralMethod(a.num, b.num, epsilon.num, f));
    printf("\tРезультат работы алгоритма 2 для g(x) - %.5f\n",
           rightRectIntegralMethod(a.num, b.num, epsilon.num, g));
  }
  if (containsChar(variants, '3')) {
    printf("\tРезультат работы алгоритма 3 для f(x) - %.5f\n",
           centralRectIntegralMethod(a.num, b.num, epsilon.num, f));
    printf("\tРезультат работы алгоритма 3 для g(x) - %.5f\n",
           centralRectIntegralMethod(a.num, b.num, epsilon.num, g));
  }
  if (containsChar(variants, '4')) {
    printf("\tРезультат работы алгоритма 4 для f(x) - %.5f\n",
           trapezoidIntegralMethod(a.num, b.num, epsilon.num, f));
    printf("\tРезультат работы алгоритма 4 для g(x) - %.5f\n",
           trapezoidIntegralMethod(a.num, b.num, epsilon.num, g));
  }
  if (containsChar(variants, '5')) {
    printf("\tРезультат работы алгоритма 5 для f(x) - %.5f\n",
           parabolaIntegralMethod(a.num, b.num, epsilon.num, f));
    printf("\tРезультат работы алгоритма 5 для g(x) - %.5f\n",
           parabolaIntegralMethod(a.num, b.num, epsilon.num, g));
  }
}

/* Задание 3.
 * Реализуйте метод определения числа π с помощью метода Монте-Карло. (см.
 * Программирование и информатика Антонюк В.А., Иванов А.П., 2015). И
 * протестируйте его. */
bool isInCircle(double x, double y, double radius) {
  if (x * x + y * y <= radius * radius)
    return true;
  return false;
}

int degree(unsigned long long int number) {
  int _degree = 0;
  while (number > 0) {
    _degree++;
    number /= 10;
  }
  return _degree;
}

void l8_3() {
  // Алгоритм таков: мы задаём первую четверть плоскости квадратом X на X, наш
  // круг будет иметь радиус X, и его центр будет находиться в начале отсчёта.
  // Таким образом, одна четверть круга расположится в первой четверти
  // плоскости. Посчитав вероятность случайных точек здесь, мы посчитаем
  // вероятность для всего круга.
  printf(
      "\tДля подсчёта значения числа π с помощью метода Монте-Карло нам "
      "понадобится координатная плоскость, чем больше - тем лучше и точнее; "
      "задайте длину этой плоскости целым числом X (максимум - 2147483647): ");
  int_nstd X = scanInt();
  if (not X.status)
    return;
  if (X.num < 1)
    return;
  printf("\tКруг точно так же будет иметь радиус X. Мы будем считать, что "
         "точка со случайными координатами (x, y) принадлежит кругу, если:\n");
  printf("\n\t\tx ** 2 + y ** 2 <= X ** 2\n\n");
  printf("\tТеперь нам понадобится выборка случайных чисел. Сколько чисел мы "
         "будем использовать для поиска числа π?\n");
  printf("\tВведите степень числа (максимум - 19, ввиду ограничения на "
         "переменные в Си): 1e+");
  int_nstd e = scanInt();
  if (not e.status)
    return;
  if ((e.num > 19) or (e.num < 1))
    return;
  long double pi = 0;
  double x = 0;
  double y = 0;
  printf("\tЕсли числа достаточно большие, а компьютер не очень мощный, "
         "придётся немного подождать. Начинаем вычисления.\n");
  unsigned long long int i;
  for (i = 0; degree(i) < e.num; i++) {
    x = dUniform(0, X.num);
    y = dUniform(0, X.num);
    if (isInCircle(x, y, X.num))
      pi++;
  }
  pi = 4 * pi / ((long double)i);
  printf("\tЧисло π в соответствии с введёнными данными равно %.5Lf.\n", pi);
}

/* Задание 4.
 * Реализуйте метод Эйлера для интегрирования ОДУ. (см. Программирование и
 * информатика Антонюк В.А., Иванов А.П., 2015). И протестируйте его. */
double EilerODUmethod(double n, double h, double x0, bool printAllIters,
                      double (*fun)(double x), char *functionName) {
  int step = 0;
  double y0 = fun(x0);
  for (int i = 0; i < n; i++) {
    x0 += h;
    y0 += h * fun(x0);
    if (printAllIters)
      printf("\t%s на шаге %d равна %.5f\n", functionName, ++step, y0);
  }
  return y0;
}

void l8_4() {
  printf("\tФункция f(x) = x - 0.333 * cos(x) - 0.7 * π\n");
  printf("\tФункция g(x) = x ** 2 - 16 * x + 49\n");
  printf("\tЗадайте сетку отрезка n (количество итераций): ");
  int_nstd n = scanInt();
  if (not n.status)
    return;
  if (n.num < 1)
    return;
  printf("\tЗадайте шаг сетки h: ");
  double_nstd h = scanDouble();
  if (not h.status)
    return;
  if (h.num <= 0.0)
    return;
  printf("\tТеперь введите x0 для f(x): ");
  double_nstd x0_1 = scanDouble();
  if (not x0_1.status)
    return;
  printf("\tИ введите x0 для g(x): ");
  double_nstd x0_2 = scanDouble();
  if (not x0_2.status)
    return;
  printf("\n");
  double yn_1 = EilerODUmethod(n.num, h.num, x0_1.num, true, f, "f\0");
  printf("\n");
  double yn_2 = EilerODUmethod(n.num, h.num, x0_2.num, true, g, "g\0");
  printf("\n");
  printf("\tИтоговые значения:\n");
  printf("\tДля функции f(x) как y<1>'(x): y<%d> = %.5f\n", n.num, yn_1);
  printf("\tДля функции g(x) как y<1>'(x): y<%d> = %.5f\n", n.num, yn_2);
}

/* Задание 5*. «Просто итерации»
 * Реализуйте метод итераций (метод простых итераций), аналогично заданию в
 * Exemple 8.3. (см. "Программирование и информатика Антонюк В.А., Иванов А.П.",
 * 2015). И протестируйте его на функции из задания Exemple 8.3. */
double Iters(double x0, double epsilon, double iters, double (*fun)(double x)) {
  do {
    /* (1) [x<i+1> == F(x<i>)]  <==>  [f(x) == 0]. Отсюда:
     * (2) [f(x) + 1 == 1] ==> [(f(x) + 1) * x == x] */
    double x1 = (fun(x0) + 1) * x0;
    if (fabs(x1 - x0) < epsilon)
      return x1;
    x0 = x1;
    iters--;
  } while (iters);
  return x0;
}

void l8_5() {
  printf("\tФункция f(x) = x - 0.333 * cos(x) - 0.7 * π\n");
  printf("\tФункция g(x) = x ** 2 - 16 * x + 49\n");
  printf("\tВведите необходимую точность вычислений (по умолчанию - 0.001): ");
  double_nstd epsilon = scanDouble();
  if (not epsilon.status) {
    epsilon.status = true;
    epsilon.num = 0.001;
  }
  if (epsilon.num < 0)
    epsilon.num = 0.001;
  printf("\tВведите максимальное число итераций (по умолчанию - 20 тысяч): ");
  double_nstd iters = scanDouble();
  if (not iters.status) {
    iters.status = true;
    iters.num = 20000;
  }
  if (iters.num < 1)
    epsilon.num = 20000;
  printf("\tТеперь введите x0 для f(x): ");
  double_nstd x0_1 = scanDouble();
  if (not x0_1.status)
    return;
  printf("\tИ введите x0 для g(x): ");
  double_nstd x0_2 = scanDouble();
  if (not x0_2.status)
    return;
  printf("\tРезультат работы алгоритма для f(x) - %.5f\n",
         Iters(x0_1.num, epsilon.num, iters.num, f));
  printf("\tРезультат работы алгоритма для g(x) - %.5f\n",
         Iters(x0_2.num, epsilon.num, iters.num, g));
}

/* Задание 6*. «Правило Рунге»
 * Используйте правило Рунге (https://ru.wikipedia.org/wiki/Правило_Рунге) для
 * получения значения определённого интеграла из задания 2 с заданной точностью.
 */
double RungeKuttaRuleWithTrapezoidIntegralMethod(double a, double b,
                                                 double epsilon, int steps,
                                                 double (*fun)(double x)) {
  double In = 0, I2n = 0;
  do {
    In = I2n;
    I2n = 0;
    double h = (b - a) / steps;
    while (a + h < b) {
      I2n += 0.5f * (fun(a) + fun(a + h)) * h;
      a += h;
    }
    steps *= 2;
  } while (fabs(I2n - In) / 3 < epsilon);
  return I2n;
}

void l8_6() {
  printf("\tФункция f(x) = x - 0.333 * cos(x) - 0.7 * π\n");
  printf("\tФункция g(x) = x ** 2 - 16 * x + 49\n");
  printf("\tВведите левую границу для вычисления интегралов: ");
  double_nstd a = scanDouble();
  if (not a.status)
    return;
  printf("\tВведите правую границу для вычисления интегралов: ");
  double_nstd b = scanDouble();
  if (not b.status)
    return;
  if (a.num >= b.num)
    return;
  printf("\tВведите точность интегрирования (по умолчанию - 0.001): ");
  double_nstd epsilon = scanDouble();
  if (not epsilon.status) {
    epsilon.status = true;
    epsilon.num = 0.001;
  }
  if (epsilon.num < 0)
    epsilon.num = 0.001;
  printf("\tВведите начальное число шагов (по умолчанию - 16): ");
  int_nstd steps = scanInt();
  if (not steps.status) {
    steps.status = true;
    steps.num = 16;
  }
  if (steps.num < 0)
    steps.num = 16;
  printf("\tРезультат работы метода трапеций с правилом Рунге-Кутты для f(x) - "
         "%.5f\n",
         RungeKuttaRuleWithTrapezoidIntegralMethod(a.num, b.num, epsilon.num,
                                                   steps.num, f));
  printf("\tРезультат работы метода трапеций с правилом Рунге-Кутты для g(x) - "
         "%.5f\n",
         RungeKuttaRuleWithTrapezoidIntegralMethod(a.num, b.num, epsilon.num,
                                                   steps.num, g));
}
