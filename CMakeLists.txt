cmake_minimum_required(VERSION 3.15)
project(labs C)

set(CMAKE_C_STANDARD 11)

add_executable(labs main.c laba3.h laba3.c
  laba4.h laba4.c laba5.h laba5.c laba6.h
  laba6.c laba7.h laba7.c laba8.h laba8.c
  nonstdio.h nonstdio.c)
target_link_libraries(labs m)
