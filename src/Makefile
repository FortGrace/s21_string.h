CC=gcc
CFLAGS= -Wall -Werror -Wextra
PLATFORM := $(shell uname)

all: test gcov_report

ifeq ($(PLATFORM), Darwin)
test: s21_string.a
	$(CC) --coverage s21_string.c s21_test.c -o test s21_string.a -lcheck
	./test
else
test: s21_string.a
	$(CC) --coverage s21_string.c s21_test.c -o test s21_string.a -lcheck_pic -lpthread -lrt -lm -lsubunit
	./test
endif
gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

s21_string.o: s21_string.c s21_string.h
	$(CC) $(CFLAGS) -c s21_string.c

s21_string.a: s21_string.o
	ar rc s21_string.a s21_string.o
	ranlib s21_string.a

clean:
	rm -rf ./*.o ./*.gcda ./*.gcno ./*.info ./*.a test
	rm -rf report

rebuild: clean all
