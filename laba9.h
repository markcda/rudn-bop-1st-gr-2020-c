#ifndef LABA9_H
#define LABA9_H

#include "nonstdio.h"
#include <string.h>

#define DEFAULT_STACK_SIZE 100

// Упражнение 1.
void arr_push(int *stack, int *last, int a);
int arr_pop(int *stack, int *last, bool *err);
int *arr_dfs(int **graph, int *sizes, int amount, int search);
void l9_e1dot1();

// Упражнение 2.
typedef struct stack {
  int *data;
  int last;
  int data_size;
} stack_t;

stack_t *new_stack(int initial_size);
void delete_stack(stack_t *stack);
void struct_push(stack_t *stack, int a);
bool struct_pop(stack_t *stack, int *a);
int *stack_dfs(int **graph, int *sizes, int amount, int search);
void l9_e2dot1();

void l9_e1X2dot2();

// Упражнение 3.
void l9_e3();

// Задание 1.
void l9_1();

// Задание 2.
void l9_2();

// Задание 3.
char hexGen(unsigned b1, unsigned b2, unsigned b3, unsigned b4);
void l9_3();

// Задание 4.
void str_swap(char *a, char *b);
void heapify(char *arr[], int rows, int i,
             bool (*cmp)(const char *, const char *));
void hsort(char *arr[DEFAULT_STR_LENGTH], int rows,
           bool (*cmp)(const char *, const char *));
bool compare(const char *a, const char *b);
void colossusAirlines();

#endif // LABA9_H
