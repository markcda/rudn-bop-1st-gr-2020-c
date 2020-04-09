#include <locale.h>

#include "laba3.h"
#include "laba4.h"
#include "laba5.h"
#include "laba6.h"
#include "nonstdio.h"

void starter(int variant) {
  switch (variant) {
    case 1: {
      average();
      break;
    }
    case 2: {
      numberAndNumeral();
      break;
    }
    case 3: {
      maxAndMin();
      break;
    }
    case 4: {
      cows();
      break;
    }
    case 5: {
      lesJours();
      break;
    }
    case 6: {
      pyramid();
      break;
    }
    case 7: {
      fortunaNumber();
      break;
    }
    case 8: {
      guessNumber();
      break;
    }
    case 9: {
      piNum();
      break;
    }
    case 10: {
      pifagoreanTable();
      break;
    }
    case 11: {
      pyramid2();
      break;
    }
    case 12: {
      adding();
      break;
    }
    case 13: {
      playingArithmetic();
      break;
    }
    case 14: {
      travelTime();
      break;
    }
    case 15: {
      array_l5_1();
      break;
    }
    case 16: {
      array_l5_2();
      break;
    }
    case 17: {
      array_l5_3();
      break;
    }
    case 18: {
      array_l5_4();
      break;
    }
    case 19: {
      array_l5_5();
      break;
    }
    case 20: {
      matrix_l6_1();
      break;
    }
    case 21: {
      matrix_l6_2();
      break;
    }
    case 22: {
      matrix_l6_3();
      break;
    }
    case 23: {
      matrix_l6_4();
      break;
    }
    case 24: {
      matrix_l6_5();
      break;
    }
  }
}

int main() {
  // Инициализируем оболочку.
  setlocale(LC_ALL, "Rus");
  printf("[Информация о выпуске] Максимальная длина строки: %d\n", DEFAULT_STR_LENGTH);
  srand(time(NULL));
  int_nstd fn;
  char l[DEFAULT_STR_LENGTH];
  sleep(3);

  // Запускаем оболочку.
  while (1) {
    // Выбор вариантов
    printf("-------------------------------------------------\n");
    printf("Привет! Выбери задание, которое хочешь проверить:\n");
    printf("0)  Выход\n");
    printf(
        "1)  [Лаба 3] Задание 1 - Среднее значение введённых "
        "чисел\n");
    printf("2)  [Лаба 3] Задание 2 - Число и цифра\n");
    printf("3)  [Лаба 3] Задание 3 - Максимум и минимум\n");
    printf("4)  [Лаба 4] Упражнение 1 - Коровы\n");
    printf("5)  [Лаба 4] Упражнение 2 - День в календаре\n");
    printf("6)  [Лаба 4] Упражнение 3 - Пирамида\n");
    printf("7)  [Лаба 4] Упражнение 4 - Счастливое число\n");
    printf("8)  [Лаба 4] Задание 1 - Угадай число\n");
    printf("9)  [Лаба 4] Задание 2 - Число π\n");
    printf("10) [Лаба 4] Задание 3 - Таблица Пифагора\n");
    printf("11) [Лаба 4] Задание 4 - Равнобедренный треугольник 2.0\n");
    printf("12) [Лаба 4] Задание 5* - Сложение\n");
    printf("13) [Лаба 4] Задание 6* - Игра в арифметику\n");
    printf("14) [Лаба 4] Задание 7* - Время в пути\n");
    printf("15) [Лаба 5] Задание 1 - Перезапись элементов массива\n");
    printf("16) [Лаба 5] Задание 2 - Массив сумм элементов\n");
    printf("17) [Лаба 5] Задание 3 - Уникальные элементы\n");
    printf("18) [Лаба 5] Задание 4 - Индексы чётных элементов\n");
    printf("19) [Лаба 5] Задание 5 - Самое кратное число\n");
    printf("20) [Лаба 6] Задание 1 - Строки и их суммы\n");
    printf("21) [Лаба 6] Задание 2 - min из max и наоборот\n");
    printf("22) [Лаба 6] Задание 3 - Меняем диагонали местами\n");
    printf("23) [Лаба 6] Задание 4 - Побитовые операции\n");
    printf("24) [Лаба 6] Задание 5 - Динамический массив дробных чисел\n");

    // Ввод варианта
    fn = scanInt();

    // Условия выхода
    if (not fn.status or not fn.num) break;

    // Исполнение варианта
    starter(fn.num);
    printf("Нажмите ВВОД для продолжения...");
    fgets(l, DEFAULT_STR_LENGTH, stdin);
  }
  return 0;
}
