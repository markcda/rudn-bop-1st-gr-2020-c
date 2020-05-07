#ifndef LABS_LABA4_H
#define LABS_LABA4_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <math.h>
#include <time.h>

#include "nonstdio.h"

// Упражнение 1
void cows();

// Упражнение 2
int Date(int D, int M, int Y);
void lesJours();

// Упражнение 3
void pyramid();

// Упражнение 4
void fortunaNumber();

// Задание 1
int_nstd guesser(int current);
void guessNumber();

// Задание 2
const long double piRes; // для следующих заданий (алгоритм ML, 3 млн
                         // итераций, округление в меньшую сторону)
long double piML(int iters);
long double piV(int iters);
void piNum();

// Задание 3
void pifagoreanTable();

// Задание 4
void pyramid2();

// Задание 5*
void adding();

// Задание 6*
void playingArithmetic();

// Задание 7*
void travelTime();

#endif // LABS_LABA4_H
