#ifndef LABA7_H
#define LABA7_H

#include "nonstdio.h"
#include "laba9.h"

// Задание 1.
void positive();
void negative();
void test();
void l7_1();

// Задание 2.
char *getInput();
bool testInput(char *str);
int strToInt(char *str);
void printInt(int num);
void l7_2();

// Задание 3.
void stats(double *a, int size, double *min, double *max, double *avg);
void l7_3();

// Задание 4.
void l7_4();

// Задание 6*.
void l7_6();

// Задание 7*.
void l7_7();

// Задание 8*.
int fact();
void l7_8();

// Задание **.
void printMagicSquare(int **A, int n);
void createMagicSquares(int **A, int sum, int p, int n, int *out);
void its_a_kind_of_magic();

#endif // LABA7_H
