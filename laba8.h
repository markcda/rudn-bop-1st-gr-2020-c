#ifndef LABA8_H
#define LABA8_H

#include "nonstdio.h"
#include <math.h>

// Пример первый.
void comparison();
void summation_sequence();
void l8_e1();

// Пример второй.
float Bakers_map(float x);
void l8_e2();

// Пример третий.
double f(double x);
double g(double x);
bool isPositive(double x);
double Bisection(double a, double b, double epsilon, double (*fun)(double x));
void l8_e3();

// Пример четвёртый.
int sumOfDigits(int number);
void l8_e4();

// Задание 1.
void l8_1();

// Задание 2.
double leftRectIntegralMethod(double a, double b, double epsilon,
                              double (*fun)(double x));
double rightRectIntegralMethod(double a, double b, double epsilon,
                               double (*fun)(double x));
double centralRectIntegralMethod(double a, double b, double epsilon,
                                 double (*fun)(double x));
double trapezoidIntegralMethod(double a, double b, double epsilon,
                               double (*fun)(double x));
double parabolaIntegralMethod(double a, double b, double epsilon,
                              double (*fun)(double x));
void l8_2();

// Задание 3.
bool isInCircle(double x, double y, double radius);
int degree(unsigned long long int number);
void l8_3();

// Задание 4.
double EilerODUmethod(double n, double h, double x0, bool printAllIters,
                      double (*fun)(double x), char *functionName);
void l8_4();

#endif // LABA8_H
