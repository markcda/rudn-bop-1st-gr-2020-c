#include "nonstdio.h"

bool isEqual(char *str1, char *str2) {
  unsigned short int len1 = DEFAULT_STR_LENGTH, len2 = DEFAULT_STR_LENGTH;
  for (int i = 0; i < DEFAULT_STR_LENGTH; i++)
    if (isEndOfString(str1[i])) {
      len1 = i;
      break;
    }
  for (int i = 0; i < DEFAULT_STR_LENGTH; i++)
    if (isEndOfString(str2[i])) {
      len2 = i;
      break;
    }
  if (len1 != len2)
    return false;
  bool isEqual = true;
  for (int i = 0; i < len1; i++)
    if (str1[i] != str2[i])
      isEqual = false;
  return isEqual;
}

bool containsChar(char *str, char sym) {
  int i = 0;
  bool contains = false;
  while (not isEndOfString(str[i])) {
    if (str[i++] == sym) {
      contains = true;
      break;
    }
  }
  return contains;
}

// Прикладные функции для определения типа символа
bool isPartOfFloat(char sym) {
  if ((((int)sym < 48) or ((int)sym > 57)) and (sym != '-') and (sym != '.'))
    return false;
  return true;
}

bool isPartOfInt(char sym) {
  if ((((int)sym < 48) or ((int)sym > 57)) and (sym != '-'))
    return false;
  return true;
}

bool isEndOfString(char sym) {
  if ((sym == '\0') or (sym == '\n'))
    return true;
  return false;
}

// Прикладные функции ввода чисел
int *countSplits(char in[]) {
  int numbersCounter = 0, stringLength = DEFAULT_STR_LENGTH;
  bool prevIsSpace = true;
  for (int i = 0; i < DEFAULT_STR_LENGTH; i++) {
    if (isEndOfString(in[i])) {
      stringLength = i;
      break;
    }
    if (in[i] == ' ') {
      if (not prevIsSpace)
        prevIsSpace = true;
    } else {
      if (prevIsSpace) {
        prevIsSpace = false;
        numbersCounter++;
      }
    }
  }
  int *res = malloc(2 * sizeof(int));
  res[0] = numbersCounter;
  res[1] = stringLength;
  return res;
}

float_nstd scanFloat() {
  float_nstd fns = {0, true};
  char number[31];
  fgets(number, 30, stdin);
  fns.num = strtof(number, 0);
  fns.status = isPartOfFloat(number[0]);
  return fns;
}

float_nstd *splitFloats(char in[], int numberCounter, int stringLength) {
  if (numberCounter == 0) {
    float_nstd *floats = (float_nstd *)malloc(sizeof(float_nstd));
    floats[0].num = 0;
    floats[0].status = true;
    return floats;
  }
  float_nstd *floats =
      (float_nstd *)malloc((numberCounter + 1) * sizeof(float_nstd));
  char temp[DEFAULT_STR_LENGTH];
  int i = 0, tI = 0, numeral = 0;
  bool prevIsSpace = true;
  for (int j = 0; j < DEFAULT_STR_LENGTH; j++)
    temp[j] = ' ';
  floats[numeral + 1].status = true;
  while (i < stringLength) {
    if (in[i] == ' ') {
      if (not prevIsSpace) {
        floats[numeral + 1].num = atof(temp);
        numeral++;
        floats[numeral + 1].status = true;
        for (int j = 0; j < DEFAULT_STR_LENGTH; j++)
          temp[j] = ' ';
        tI = 0;
      }
      prevIsSpace = true;
    } else if (isPartOfFloat(in[i])) {
      temp[tI] = in[i];
      tI++;
      prevIsSpace = false;
    } else {
      floats[numeral + 1].status = false;
      prevIsSpace = false;
    }
    i++;
  }
  floats[numeral + 1].num = atof(temp);
  floats[0].num = numeral + 1;
  floats[0].status = true;
  return floats;
}

float_nstd *scanFloats() {
  char in[DEFAULT_STR_LENGTH];
  fgets(in, DEFAULT_STR_LENGTH - 1, stdin);
  int *res = countSplits(in);
  float_nstd *floats = splitFloats(in, res[0], res[1]);
  free(res);
  return floats;
}

int_nstd scanInt() {
  int_nstd fns = {0, true};
  char number[31];
  fgets(number, 30, stdin);
  fns.num = strtol(number, 0, 10);
  fns.status = isPartOfInt(number[0]);
  return fns;
}

int_nstd *splitInts(char in[], int numberCounter, int stringLength) {
  if (numberCounter == 0) {
    int_nstd *ints = (int_nstd *)malloc(sizeof(int_nstd));
    ints[0].num = 0;
    ints[0].status = true;
    return ints;
  }
  int_nstd *ints = (int_nstd *)malloc((numberCounter + 1) * sizeof(int_nstd));
  char temp[DEFAULT_STR_LENGTH];
  int i = 0, tI = 0, numeral = 0;
  bool prevIsSpace = true;
  for (int j = 0; j < DEFAULT_STR_LENGTH; j++)
    temp[j] = ' ';
  ints[numeral + 1].status = true;
  while (i < stringLength) {
    if (in[i] == ' ') {
      if (not prevIsSpace) {
        ints[numeral + 1].num = atoi(temp);
        numeral++;
        ints[numeral + 1].status = true;
        for (int j = 0; j < DEFAULT_STR_LENGTH; j++)
          temp[j] = ' ';
        tI = 0;
      }
      prevIsSpace = true;
    } else if (isPartOfInt(in[i])) {
      temp[tI] = in[i];
      tI++;
      prevIsSpace = false;
    } else {
      ints[numeral + 1].status = false;
      prevIsSpace = false;
    }
    i++;
  }
  ints[numeral + 1].num = atoi(temp);
  ints[0].num = numeral + 1;
  ints[0].status = true;
  return ints;
}

int_nstd *scanInts() {
  char in[DEFAULT_STR_LENGTH];
  fgets(in, DEFAULT_STR_LENGTH - 1, stdin);
  int *res = countSplits(in);
  int_nstd *ints = splitInts(in, res[0], res[1]);
  free(res);
  return ints;
}

double_nstd scanDouble() {
  double_nstd fns = {0, true};
  char number[46];
  fgets(number, 45, stdin);
  fns.num = strtod(number, 0);
  fns.status = isPartOfFloat(number[0]);
  return fns;
}

double_nstd *splitDoubles(char in[], int numberCounter, int stringLength) {
  if (numberCounter == 0) {
    double_nstd *doubles = (double_nstd *)malloc(sizeof(double_nstd));
    doubles[0].num = 0;
    doubles[0].status = true;
    return doubles;
  }
  double_nstd *doubles =
      (double_nstd *)malloc((numberCounter + 1) * sizeof(double_nstd));
  printf("%d\n", numberCounter);
  char temp[DEFAULT_STR_LENGTH];
  int i = 0, tI = 0, numeral = 0;
  bool prevIsSpace = true;
  for (int j = 0; j < DEFAULT_STR_LENGTH; j++)
    temp[j] = ' ';
  doubles[numeral + 1].status = true;
  while (i < stringLength) {
    if (in[i] == ' ') {
      if (not prevIsSpace) {
        doubles[numeral + 1].num = atof(temp);
        numeral++;
        doubles[numeral + 1].status = true;
        for (int j = 0; j < DEFAULT_STR_LENGTH; j++)
          temp[j] = ' ';
        tI = 0;
      }
      prevIsSpace = true;
    } else if (isPartOfFloat(in[i])) {
      temp[tI] = in[i];
      tI++;
      prevIsSpace = false;
    } else {
      doubles[numeral + 1].status = false;
      prevIsSpace = false;
    }
    i++;
  }
  doubles[numeral + 1].num = atof(temp);
  doubles[0].num = numeral + 1;
  doubles[0].status = true;
  return doubles;
}

double_nstd *scanDoubles() {
  char in[DEFAULT_STR_LENGTH];
  fgets(in, DEFAULT_STR_LENGTH - 1, stdin);
  int *res = countSplits(in);
  double_nstd *doubles = splitDoubles(in, res[0], res[1]);
  free(res);
  return doubles;
}

// Прикладные функции для получения псевдослучайных наборов чисел
int uniform(int min, int max) {
  // Функция имитирует поведение random.uniform для положительных min и max
  return rand() % (max - min + 1) + min;
}

double dUniform(double min, double max) {
  return min + (rand() / (RAND_MAX / (max - min)));
}
