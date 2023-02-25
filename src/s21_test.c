#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./s21_string.h"

START_TEST(test_s21_strlen) {
    char str[8][15] = {"HelloWorld", "Hello world", "Hello world\n",
                       "h\n",        " \n",         " ",
                       "",           "\n"};
    for (int i = 0; i < 8; i++)
        ck_assert_int_eq(s21_strlen(str[i]), strlen(str[i]));
}
END_TEST

START_TEST(test_s21_strcspn) {
    char s1[10][25] = {"1234567890", "Hello world", "Helloworld",
                       "wor ld",     "hello",       ""};
    char s2[10][25] = {"3546", "dfsfg", "lloe", " ", "oe", "dsf"};
    for (int i = 0; i < 10; i++)
        ck_assert_int_eq(s21_strcspn(s1[i], s2[i]), strcspn(s1[i], s2[i]));
}
END_TEST

START_TEST(test_s21_strspn) {
    char s1[10][25] = {"1234567890", "Hello world", "Helloworld",
                       "wor ld",     "hello",       ""};
    char s2[10][25] = {"3546", "dfsfg", "lloe", " ", "oe", "dsf"};
    for (int i = 0; i < 10; i++)
        ck_assert_int_eq(s21_strspn(s1[i], s2[i]), strspn(s1[i], s2[i]));
}
END_TEST

START_TEST(test_s21_strtok) {
    char strs21[][25] = {"hel/lowo/rld", "hello world", "1 hello\n 00w",
                         " Hello 12 world 23 yep", ""};
    char strstd[][25] = {"hel/lowo/rld", "hello world", "1 hello\n 00w",
                         " Hello 12 world 23 yep", ""};
    char sym[][10] = {"/", "ss", "1 \n", "12 23", "D"};
    char *s21 = s21_NULL;
    char *std = s21_NULL;
    for (int i = 0; i < 5; i++) {
        s21 = s21_strtok(strs21[i], sym[i]);
        std = strtok(strstd[i], sym[i]);
        if (std == s21_NULL) {
            ck_assert_ptr_null(s21);
        } else {
            ck_assert_str_eq(s21, std);
            while (std != s21_NULL) {
                s21 = s21_strtok(s21_NULL, sym[i]);
                std = strtok(s21_NULL, sym[i]);
                if (std == s21_NULL)
                    ck_assert_ptr_null(s21);
                else
                    ck_assert_str_eq(s21, std);
            }
        }
    }
}
END_TEST

START_TEST(test_s21_strpbrk) {
    const char s1[10][20] = {"1234567890", "Helloworld", "world", "qwerty",
                             "Hello"};
    const char s2[10][20] = {"321", "hel", "asd", "rtyq", "ello"};
    int i;
    for (i = 0; i < 5; i++)
        ck_assert_str_eq(s21_strpbrk(s1[i], s2[i]), strpbrk(s1[i], s2[i]));
    ck_assert_ptr_null(s21_strpbrk(s1[i], s2[i]));
}
END_TEST

START_TEST(test_s21_strstr) {
    char s1[10][20] = {"1234567890", "Helloworld", "world", "qw erty",
                       "pri\nvet"};
    char s2[10][20] = {"123", "Hel", "r", " ", "\n"};
    for (int i = 0; i < 5; i++)
        ck_assert_str_eq(s21_strstr(s1[i], s2[i]), strstr(s1[i], s2[i]));
}
END_TEST

START_TEST(test_s21_strcmp) {
    char s1[10][20] = {"Hello", "",  "hello", "worl\n", "asdf",
                       "123",   " ", "\0",    "000",    "fasf\tsadasd\nsd"};
    char s2[10][20] = {"Hello",  "worlp", "",    "he\tllo", "F",
                       "123457", "wr",    "sad", "\t",      "dfg\taa\0asd"};
    for (int i = 0; i < 2; i++)
        ck_assert_int_eq(s21_strcmp(s1[i], s2[i]), strcmp(s1[i], s2[i]));
}
END_TEST

START_TEST(test_s21_strncmp) {
    char s1[10][20] = {"Hello", "",  "hello", "worl\n", "asdf",
                       "123",   " ", "\0",    "000",    "fasf\tsadasd\nsd"};
    char s2[10][20] = {"Hello",  "worlp", "",    "he\tllo", "F",
                       "123457", "wr",    "sad", "\t",      "dfg\taa\0asd"};
    for (int n = -1000; n < 1000; n++) {
        for (int i = 0; i < 2; i++) {
            ck_assert_int_eq(s21_strncmp(s1[i], s2[i], n),
                             strncmp(s1[i], s2[i], n));
        }
    }
}
END_TEST

START_TEST(test_s21_memcmp) {
    char s1[10][20] = {"Hello", "",  "hello", "worl\n", "asdf",
                       "123",   " ", "\0",    "000",    "fasf\tsadasd\nsd"};
    char s2[10][20] = {"Hello",  "worlp", "",    "he\tllo", "F",
                       "123457", "wr",    "sad", "\t",      "dfg\taa\0asd"};
    for (int n = -1000; n < 1000; n++) {
        for (int i = 0; i < 10; i++) {
            ck_assert_int_eq(s21_memcmp(s1[i], s2[i], n),
                             memcmp(s1[i], s2[i], n));
        }
    }
}
END_TEST

START_TEST(test_s21_strcat) {
    char s1[9][20] = {"Hello", "",  "hello", "worl\n", "asdf",
                      "123",   " ", "\0",    "000"};
    char s2[9][20] = {"Hello",  "worlp", "",    "he\tllo", "F",
                      "123457", "wr",    "sad", "\t"};
    for (int i = 0; i < 9; i++)
        ck_assert_str_eq(s21_strcat(s1[i], s2[i]), strcat(s1[i], s2[i]));
}
END_TEST

START_TEST(test_s21_strncat) {
    char s1[12][20] = {"Hello", "",   "hello", "worl\n", "asdf",  "123",
                       " ",     "\0", "000",   "asd",    "privet"};
    char s2[12][20] = {"Hello", "worlp", "",   "he\tllo", "F",     "123457",
                       "wr",    "sad",   "\t", "ds",      "alloha"};
    for (int n = -1; n < 5; n++) {
        for (int i = 0; i < 11; i++) {
            ck_assert_str_eq(s21_strncat(s1[i], s2[i], n),
                             strncat(s1[i], s2[i], n));
        }
    }
}
END_TEST

START_TEST(test_s21_strcpy) {
    char s1[9][20] = {"Hello", "",  "hello", "worl\n", "asdf",
                      "123",   " ", "\0",    "000"};
    char s2[9][20] = {"Hello",  "worlp", "",    "he\tllo", "F",
                      "123457", "wr",    "sad", "\t"};
    for (int i = 0; i < 9; i++)
        ck_assert_str_eq(s21_strcpy(s1[i], s2[i]), strcpy(s1[i], s2[i]));
}
END_TEST

START_TEST(test_s21_strncpy) {
    char s1[12][20] = {"Hello", "",   "hello", "worl\n", "asdf",  "123",
                       " ",     "\0", "000",   "asd",    "privet"};
    char s2[12][20] = {"Hello", "worlp", "",   "he\tllo", "F",     "123457",
                       "wr",    "sad",   "\t", "ds",      "alloha"};
    for (int n = 0; n < 5; n++) {
        for (int i = 0; i < 9; i++) {
            ck_assert_str_eq(s21_strncpy(s1[i], s2[i], n),
                             strncpy(s1[i], s2[i], n));
        }
    }
}
END_TEST

START_TEST(test_s21_memcpy) {
    char s1[12][20] = {"Hello", "",   "hello", "worl\n", "asdf",  "123",
                       " ",     "\0", "000",   "asd",    "privet"};
    char s2[12][20] = {"Hello", "worlp", "",   "he\tllo", "F",     "123457",
                       "wr",    "sad",   "\t", "ds",      "alloha"};
    for (int n = 0; n < 5; n++) {
        for (int i = 0; i < 9; i++) {
            ck_assert_str_eq(s21_memcpy(s1[i], s2[i], n),
                             memcpy(s1[i], s2[i], n));
        }
    }
}
END_TEST

START_TEST(test_s21_strchr) {
    char s1[6][20] = {"Hello", "53423", "sdsdf", " 324fdg", "", "\0"};
    char sym[6] = {'e', '3', ' ', '\t', 'd', ' '};
    for (int i = 0; i < 7; i++)
        ck_assert_pstr_eq(s21_strchr(s1[i], sym[i]), strchr(s1[i], sym[i]));
}
END_TEST

START_TEST(test_s21_strrchr) {
    char s1[6][20] = {"Hello", "53423", "sdsdf", " 324fdg", "", "\0"};
    char sym[6] = {'e', '3', ' ', '\t', 'd', ' '};
    for (int i = 0; i < 7; i++)
        ck_assert_pstr_eq(s21_strrchr(s1[i], sym[i]), strrchr(s1[i], sym[i]));
}
END_TEST

START_TEST(test_s21_memchr) {
    char s1[6][20] = {"Hello", "53423", "sdsdf", " 324fdg", "", "\0"};
    char sym[6] = {'e', '3', ' ', '\t', 'd', ' '};
    for (int n = 0; n < 10; n++) {
        for (int i = 0; i < 7; i++)
            ck_assert_pstr_eq(s21_memchr(s1[i], sym[i], n),
                              memchr(s1[i], sym[i], n));
    }
}
END_TEST

START_TEST(test_s21_memmove) {
    char s1[10][20] = {"helloworld", "", "asd\tgge", "21344", "ssasdda\0"};
    for (int n = 0; n < 10; n++) {
        for (int i = 0; i < 10; i++) {
            ck_assert_pstr_eq(s21_memmove(s1[i], s1[i - 1], n),
                              memmove(s1[i], s1[i - 1], n));
            ck_assert_pstr_eq(s21_memmove(s1[i], s1[i + 1], n),
                              memmove(s1[i], s1[i + 1], n));
            ck_assert_pstr_eq(s21_memmove(s1[i], s1[i], n),
                              memmove(s1[i], s1[i], n));
        }
    }
}
END_TEST

START_TEST(test_s21_memset) {
    char s1[6][50] = {"Hello", "53423", "sdsdf", " 324fdg", "", "dsa"};
    char s2[6][50] = {"Hello", "53423", "sdsdf", " 324fdg", "", "dsa"};
    int sym[6] = {'e', '3', '1', '\t', 'd', ' '};
    for (int n = 0; n < 40; n++) {
        for (int i = 0; i < 6; i++) {
            ck_assert_pstr_eq(s21_memset(s1[i], sym[i], n),
                              memset(s2[i], sym[i], n));
        }
    }
}
END_TEST

START_TEST(test_s21_to_upper) {
    char s1[8][20] = {"Hello", "53423",        "sdSdf", "",
                      "dsa",   "SADAss\tddDD", " ",     "Dd\0dD"};
    char res[8][20] = {"HELLO", "53423",        "SDSDF", "",
                       "DSA",   "SADASS\tDDDD", " ",     "DD"};
    for (int i = 0; i < 8; i++) ck_assert_str_eq(s21_to_upper(s1[i]), res[i]);
}
END_TEST

START_TEST(test_s21_to_lower) {
    char s1[8][20] = {"Hello", "53423",        "sdSdf", "",
                      "dSa",   "SADAss\tddDD", " ",     "Dd\0dD"};
    char res[8][20] = {"hello", "53423",        "sdsdf", "",
                       "dsa",   "sadass\tdddd", " ",     "dd"};
    for (int i = 0; i < 8; i++) ck_assert_str_eq(s21_to_lower(s1[i]), res[i]);
}
END_TEST

START_TEST(test_s21_insert) {
    char s1[10][20] = {"Hello", "",  "hello", "worl\n", "asdf",
                       "123",   " ", "\0",    "000",    "fasf\tsadasd\nsd"};
    char s2[10][20] = {"Hello",  "worlp", "",    "he\tllo", "F",
                       "123457", "wr",    "sad", "\t",      "dfg\taa\0asd"};
    char res[10][25] = {"HellHelloo", "worlp",
                        "hello",      "he\tlloworl\n",
                        "asFdf",      "112345723",
                        " wr",        "sad",
                        "00\t0",      "fdfg\taaasf\tsadasd\nsd"};
    s21_size_t n[10] = {4, 0, 4, 0, 2, 1, 1, 0, 2, 1};
    for (int i = 0; i < 10; i++) {
        ck_assert_str_eq(s21_insert(s1[i], s2[i], n[i]), res[i]);
    }
}
END_TEST

START_TEST(test_s21_trim) {
    char s1[10][20] = {"Hello", "",  "hello", "worl\n", "asdf",
                       "123",   " ", "\0",    "000",    "fasf\tsadasd\nsd"};
    char s2[10][20] = {"Hello",  "worlp", "",    "he\tllo", "F",
                       "123457", "wr",    "sad", "\t",      "dfg\taa\0asd"};
    char res[10][20] = {"", "", "hello", "worl\n", "asdf",
                        "", "", "",      "000",    "sf\tsadasd\ns"};
    for (int i = 0; i < 10; i++) {
        ck_assert_str_eq(s21_trim(s1[i], s2[i]), res[i]);
    }
}
END_TEST

START_TEST(test_s21_strerror) {
    for (int err = 0; err < 100; err++)
        ck_assert_pstr_eq(s21_strerror(err), strerror(err));
    int err1 = 400;
    ck_assert_pstr_eq(s21_strerror(err1), strerror(err1));
}
END_TEST

START_TEST(sprintf_pr_1) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %%");
    s21_sprintf(test_your, "Hello %%");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_pr_2) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello 2022 World");
    s21_sprintf(test_your, "Hello 2022 World");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_1) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %c", 'W');
    s21_sprintf(test_your, "Hello %c", 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_2) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %-5c", 'W');
    s21_sprintf(test_your, "Hello %-5c", 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_3) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %5c", 'W');
    s21_sprintf(test_your, "Hello %5c", 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_4) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %-c", 'W');
    s21_sprintf(test_your, "Hello %-c", 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_5) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %c", 'W');
    s21_sprintf(test_your, "Hello %c", 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_6) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "%cHello %c", 's', 'W');
    s21_sprintf(test_your, "%cHello %c", 's', 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_7) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "He%cllo %-5c", 's', 'W');
    s21_sprintf(test_your, "He%cllo %-5c", 's', 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_8) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "%5cHello %5c", 's', 'W');
    s21_sprintf(test_your, "%5cHello %5c", 's', 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_9) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "%-10cHello %-c", 's', 'W');
    s21_sprintf(test_your, "%-10cHello %-c", 's', 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_c_10) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "He%%llo %c", 'W');
    s21_sprintf(test_your, "He%%llo %c", 'W');
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_1) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %d", 23);
    s21_sprintf(test_your, "Hello %d", 23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_3) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %-6d", 23);
    s21_sprintf(test_your, "Hello %-6d", 23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_4) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %+d", 23);
    s21_sprintf(test_your, "Hello %+d", 23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_5) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello % d", 23);
    s21_sprintf(test_your, "Hello % d", 23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_6) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %hd", 23);
    s21_sprintf(test_your, "Hello %hd", 23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_8) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %10d", -23);
    s21_sprintf(test_your, "Hello %10d", -23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_9) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %+10d", 23);
    s21_sprintf(test_your, "Hello %+10d", 23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_10) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %+10d", -23);
    s21_sprintf(test_your, "Hello %+10d", -23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_d_11) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello % 10d", -23);
    s21_sprintf(test_your, "Hello % 10d", -23);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_1) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %d %f", 5, -23.0);
    s21_sprintf(test_your, "Hello %d %f", 5, -23.0);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_2) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %s %f", "abc", -23.0);
    s21_sprintf(test_your, "Hello %s %f", "abc", -23.0);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_3) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hel%ulo %s %f", 100, "abc", -23.0);
    s21_sprintf(test_your, "Hel%ulo %s %f", 100, "abc", -23.0);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_4) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %s %.3f", "abc", -23.0000001);
    s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.0000001);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_5) {
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "Hello %s %.7f", "abc", -23.999999);
    s21_sprintf(test_your, "Hello %s %.7f", "abc", -23.999999);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_30) {
#line 379
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%-.f dslkj", 20.235300);
    s21_sprintf(test_your, "saeflkahj%-.f dslkj", 20.235300);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_31) {
#line 386
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%f dslkj", 0.000000006);
    s21_sprintf(test_your, "saeflkahj%f dslkj", 0.000000006);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_32) {
#line 393
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%.f dslkj", 0.000000006);
    s21_sprintf(test_your, "saeflkahj%.f dslkj", 0.000000006);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_33) {
#line 400
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%12f dslkj", 0.000000006);
    s21_sprintf(test_your, "saeflkahj%12f dslkj", 0.000000006);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_34) {
#line 407
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%.12f dslkj", 0.000000006);
    s21_sprintf(test_your, "saeflkahj%.12f dslkj", 0.000000006);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_35) {
#line 414
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%-.12f dslkj", 0.000000006);
    s21_sprintf(test_your, "saeflkahj%-.12f dslkj", 0.000000006);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_36) {
#line 421
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%%%%%%%%%% dslkj");
    s21_sprintf(test_your, "saeflkahj%%%%%%%%%% dslkj");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_37) {
#line 428
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%%%%%%%%%%%-.12f dslkj", 0.000000006);
    s21_sprintf(test_your, "saeflkahj%%%%%%%%%%%-.12f dslkj", 0.000000006);
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_38) {
#line 435
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahj%s dslkj", "0.000000006");
    s21_sprintf(test_your, "saeflkahj%s dslkj", "0.000000006");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_39) {
#line 442
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "saeflkahjdslkj%s", "^&*(=...%");
    s21_sprintf(test_your, "saeflkahjdslkj%s", "^&*(=...%");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_40) {
#line 449
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "%ssaeflkahj dslkj", "^&*(=...%");
    s21_sprintf(test_your, "%ssaeflkahj dslkj", "^&*(=...%");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_41) {
#line 456
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "%ssaeflkahj%sdslkj%s", "^&*(=...%", "jk", "");
    s21_sprintf(test_your, "%ssaeflkahj%sdslkj%s", "^&*(=...%", "jk", "");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_42) {
#line 463
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "%ssaeflkahj%sdslkj%s", "", "", " ");
    s21_sprintf(test_your, "%ssaeflkahj%sdslkj%s", "", "", " ");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_43) {
#line 470
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "%-ssaeflkahj%1sdslkj%s", "^&*(=...%", "jk", "");
    s21_sprintf(test_your, "%-ssaeflkahj%1sdslkj%s", "^&*(=...%", "jk", "");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(sprintf_44) {
#line 477
    char test_original[1024];
    char test_your[1024];
    sprintf(test_original, "%3ssaeflkahj%1sdslkj%10s", "^&*(=...%", " ", "");
    s21_sprintf(test_your, "%3ssaeflkahj%1sdslkj%10s", "^&*(=...%", " ", "");
    ck_assert_str_eq(test_original, test_your);
}
END_TEST

START_TEST(int_sprintf_pr_1) {
#line 484
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %%"),
                     s21_sprintf(test_your, "Hello %%"));
}
END_TEST

START_TEST(int_sprintf_pr_2) {
#line 489
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello 2022 World"),
                     s21_sprintf(test_your, "Hello 2022 World"));
}
END_TEST

START_TEST(int_sprintf_c_1) {
#line 494
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %c", 'W'),
                     s21_sprintf(test_your, "Hello %c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_2) {
#line 499
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %-5c", 'W'),
                     s21_sprintf(test_your, "Hello %-5c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_3) {
#line 504
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %5c", 'W'),
                     s21_sprintf(test_your, "Hello %5c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_4) {
#line 509
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %-c", 'W'),
                     s21_sprintf(test_your, "Hello %-c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_5) {
#line 514
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %c", 'W'),
                     s21_sprintf(test_your, "Hello %c", 'W'));
}
END_TEST

START_TEST(int_sprintf_c_6) {
#line 519
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "%cHello %c", 's', 'W'),
                     s21_sprintf(test_your, "%cHello %c", 's', 'W'));
}
END_TEST

START_TEST(int_sprintf_c_7) {
#line 524
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "He%cllo %-5c", 's', 'W'),
                     s21_sprintf(test_your, "He%cllo %-5c", 's', 'W'));
}
END_TEST

START_TEST(int_sprintf_c_8) {
#line 529
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "%5cHello %5c", 's', 'W'),
                     s21_sprintf(test_your, "%5cHello %5c", 's', 'W'));
}
END_TEST

START_TEST(int_sprintf_c_9) {
#line 534
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "%-10cHello %-c", 's', 'W'),
                     s21_sprintf(test_your, "%-10cHello %-c", 's', 'W'));
}
END_TEST

START_TEST(int_sprintf_c_10) {
#line 539
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "He%%llo %c", 'W'),
                     s21_sprintf(test_your, "He%%llo %c", 'W'));
}
END_TEST

START_TEST(int_sprintf_d_1) {
#line 544
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %d", 23),
                     s21_sprintf(test_your, "Hello %d", 23));
}
END_TEST

START_TEST(int_sprintf_d_2) {
#line 549
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %05d", 23),
                     s21_sprintf(test_your, "Hello %05d", 23));
}
END_TEST

START_TEST(int_sprintf_d_3) {
#line 554
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %-6d", 23),
                     s21_sprintf(test_your, "Hello %-6d", 23));
}
END_TEST

START_TEST(int_sprintf_d_4) {
#line 559
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %+d", 23),
                     s21_sprintf(test_your, "Hello %+d", 23));
}
END_TEST

START_TEST(int_sprintf_d_5) {
#line 564
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello % d", 23),
                     s21_sprintf(test_your, "Hello % d", 23));
}
END_TEST

START_TEST(int_sprintf_d_6) {
#line 569
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %hd", 23),
                     s21_sprintf(test_your, "Hello %hd", 23));
}
END_TEST

START_TEST(int_sprintf_d_7) {
#line 574
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %ld", 238230000006325000),
                     s21_sprintf(test_your, "Hello %ld", 238230000006325000));
}
END_TEST

START_TEST(int_sprintf_d_8) {
#line 579
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello % 10d", 23),
                     s21_sprintf(test_your, "Hello % 10d", 23));
}
END_TEST

START_TEST(int_sprintf_d_9) {
#line 584
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %+10d", 23),
                     s21_sprintf(test_your, "Hello %+10d", 23));
}
END_TEST

START_TEST(int_sprintf_d_10) {
#line 589
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %+10d", -23),
                     s21_sprintf(test_your, "Hello %+10d", -23));
}
END_TEST

START_TEST(int_sprintf_d_11) {
#line 594
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello % 10d", -23),
                     s21_sprintf(test_your, "Hello % 10d", -23));
}
END_TEST

START_TEST(int_sprintf_d_and_c_1) {
#line 599
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %d %018d", 5, -23),
                     s21_sprintf(test_your, "Hello %d %018d", 5, -23));
}
END_TEST

START_TEST(int_sprintf_1) {
#line 604
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %d %f", 5, -23.0),
                     s21_sprintf(test_your, "Hello %d %f", 5, -23.0));
}
END_TEST

START_TEST(int_sprintf_2) {
#line 609
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "Hello %s %f", "abc", -23.0),
                     s21_sprintf(test_your, "Hello %s %f", "abc", -23.0));
}
END_TEST

START_TEST(int_sprintf_3) {
#line 614
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "Hel%ulo %s %f", 100, "abc", -23.0),
        s21_sprintf(test_your, "Hel%ulo %s %f", 100, "abc", -23.0));
}
END_TEST

START_TEST(int_sprintf_4) {
#line 619
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "Hello %s %.3f", "abc", -23.0000001),
        s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.0000001));
}
END_TEST

START_TEST(int_sprintf_5) {
#line 624
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "Hello %s %.7f", "abc", -23.999999),
        s21_sprintf(test_your, "Hello %s %.7f", "abc", -23.999999));
}
END_TEST

START_TEST(int_sprintf_6) {
#line 629
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "Hello %s %.3f", "abc", -23.999999),
        s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.999999));
}
END_TEST

START_TEST(int_sprintf_8) {
#line 639
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "H%uello %s", 123456789,
                "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"),
        s21_sprintf(test_your, "H%uello %s", 123456789,
                    "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"));
}
END_TEST

START_TEST(int_sprintf_9) {
#line 644
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "saeflkahj%lfdslkj", 1234.0),
                     s21_sprintf(test_your, "saeflkahj%lfdslkj", 1234.0));
}
END_TEST

START_TEST(int_sprintf_10) {
#line 649
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj%010.12f dslkj", -4353.235300),
        s21_sprintf(test_your, "saeflkahj%010.12f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_11) {
#line 654
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj%+010.12f dslkj", 4353.235300),
        s21_sprintf(test_your, "saeflkahj%+010.12f dslkj", 4353.235300));
}
END_TEST

START_TEST(int_sprintf_12) {
#line 659
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj% 10.12f dslkj", 0.235300),
        s21_sprintf(test_your, "saeflkahj% 10.12f dslkj", 0.235300));
}
END_TEST

START_TEST(int_sprintf_13) {
#line 664
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj% 10.12f dslkj", -4353.235300),
        s21_sprintf(test_your, "saeflkahj% 10.12f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_14) {
#line 669
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj%-.12f dslkj", 4353.235300),
        s21_sprintf(test_your, "saeflkahj%-.12f dslkj", 4353.235300));
}
END_TEST

START_TEST(int_sprintf_15) {
#line 674
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj%-.12f dslkj", -4353.235300),
        s21_sprintf(test_your, "saeflkahj%-.12f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_17) {
#line 684
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj%-.12f dslkj", -4353.235300),
        s21_sprintf(test_your, "saeflkahj%-.12f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_18) {
#line 689
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "saeflkahj%-f dslkj", 0.235300),
                     s21_sprintf(test_your, "saeflkahj%-f dslkj", 0.235300));
}
END_TEST

START_TEST(int_sprintf_19) {
#line 694
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(sprintf(test_original, "saeflkahj%+f dslkj", 0.235300),
                     s21_sprintf(test_your, "saeflkahj%+f dslkj", 0.235300));
}
END_TEST

START_TEST(int_sprintf_20) {
#line 699
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj% f dslkj", -4353.235300),
        s21_sprintf(test_your, "saeflkahj% f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_21) {
#line 704
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "saeflkahj% 8f dslkj", -4353.235300),
        s21_sprintf(test_your, "saeflkahj% 8f dslkj", -4353.235300));
}
END_TEST

START_TEST(int_sprintf_22) {
#line 709
    char test_original[1024];
    char test_your[1024];
    ck_assert_int_eq(
        sprintf(test_original, "%s%s%s%s%s%ssaeflkahj% 8f dslkj", "ds", " ",
                " ", "0", "+", "9999999", -4353.235300),
        s21_sprintf(test_your, "%s%s%s%s%s%ssaeflkahj% 8f dslkj", "ds", " ",
                    " ", "0", "+", "9999999", -4353.235300));
}
END_TEST

START_TEST(sprintf_222) {
#line 721
    char str1[1024];
    s21_sprintf(str1, "Hola %8d", 34);
    char str2[1024];
    sprintf(str2, "Hola %8d", 34);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_223) {
#line 728
    char str1[1024];
    s21_sprintf(str1, "Hola %-8d", 34);
    char str2[1024];
    sprintf(str2, "Hola %-8d", 34);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_225) {
#line 742
    char str1[1024];
    s21_sprintf(str1, "Hola %18d", 34);
    char str2[1024];
    sprintf(str2, "Hola %18d", 34);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_226) {
#line 749
    char str1[1024];
    s21_sprintf(str1, "Hola %-18d", 34);
    char str2[1024];
    sprintf(str2, "Hola %-18d", 34);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_227) {
#line 756
    char str1[1024];
    s21_sprintf(str1, "Hola %02d", 343432);
    char str2[1024];
    sprintf(str2, "Hola %02d", 343432);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_228) {
#line 763
    char str1[1024];
    s21_sprintf(str1, "Hola %-2d", 34423342);
    char str2[1024];
    sprintf(str2, "Hola %-2d", 34423342);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_229) {
#line 770
    char str1[1024];
    s21_sprintf(str1, "Hola %9s", "Mundo");
    char str2[1024];
    sprintf(str2, "Hola %9s", "Mundo");
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2210) {
#line 777
    char str1[1024];
    s21_sprintf(str1, "Hola %-9s", "Mundo");
    char str2[1024];
    sprintf(str2, "Hola %-9s", "Mundo");
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2211) {
#line 784
    char str1[1024];
    s21_sprintf(str1, "Hola %2s", "Mundo");
    char str2[1024];
    sprintf(str2, "Hola %2s", "Mundo");
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2212) {
#line 791
    char str1[1024];
    s21_sprintf(str1, "Hola %-2s", "Mundo");
    char str2[1024];
    sprintf(str2, "Hola %-2s", "Mundo");
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2213) {
#line 798
    char str1[1024];
    s21_sprintf(str1, "Hola %12s", "Mundo");
    char str2[1024];
    sprintf(str2, "Hola %12s", "Mundo");
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssprintf_2214) {
#line 805
    char str1[1024];
    s21_sprintf(str1, "Hola %-12s", "Mundo");
    char str2[1024];
    sprintf(str2, "Hola %-12s", "Mundo");
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_231) {
#line 812
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "Hola %d", 7);
    sprintf(str1, "Hola %d", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_232) {
#line 819
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%d:%d:%d", 7, 4, 0);
    sprintf(str1, "%d:%d:%d", 7, 4, 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_233) {
#line 826
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "MAX %d", INT_MAX);
    sprintf(str1, "MAX %d", INT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_234) {
#line 833
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "MIN %d", INT_MIN);
    sprintf(str1, "MIN %d", INT_MIN);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_235) {
#line 840
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "Hola %i", 3534555);
    sprintf(str1, "Hola %i", 3534555);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_236) {
#line 847
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "Hola %+d", 3534555);
    sprintf(str1, "Hola %+d", 3534555);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_237) {
#line 854
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5d'", 7);
    sprintf(str1, "padding '%5d'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_238) {
#line 861
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5d'", INT_MAX);
    sprintf(str1, "padding '%5d'", INT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_239) {
#line 868
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5d'", INT_MIN);
    sprintf(str1, "padding '%5d'", INT_MIN);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2311) {
#line 882
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%05d'", INT_MAX);
    sprintf(str1, "padding '%05d'", INT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2312) {
#line 889
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%05d'", INT_MIN);
    sprintf(str1, "padding '%05d'", INT_MIN);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2313) {
#line 896
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%-5d'", 7);
    sprintf(str1, "padding '%-5d'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2314) {
#line 903
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%-5d'", INT_MAX);
    sprintf(str1, "padding '%-5d'", INT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2315) {
#line 910
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%-5d'", INT_MIN);
    sprintf(str1, "padding '%-5d'", INT_MIN);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2316) {
#line 917
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%.5d'", 7);
    sprintf(str1, "precision '%.5d'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2317) {
#line 924
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%.5d'", INT_MAX);
    sprintf(str1, "precision '%.5d'", INT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2318) {
#line 931
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%.5d'", INT_MIN);
    sprintf(str1, "precision '%.5d'", INT_MIN);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2319) {
#line 938
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%3.5d'", 7);
    sprintf(str1, "precision '%3.5d'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2320) {
#line 945
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%3.5d'", INT_MAX);
    sprintf(str1, "precision '%3.5d'", INT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2321) {
#line 952
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%3.5d'", INT_MIN);
    sprintf(str1, "precision '%3.5d'", INT_MIN);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2322) {
#line 959
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%-3.5d'", 7);
    sprintf(str1, "precision '%-3.5d'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2323) {
#line 966
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%-3.5d'", INT_MAX);
    sprintf(str1, "precision '%-3.5d'", INT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2324) {
#line 973
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%-3.5d'", INT_MIN);
    sprintf(str1, "precision '%-3.5d'", INT_MIN);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2325) {
#line 980
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "Hola %u", 7);
    sprintf(str1, "Hola %u", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2326) {
#line 987
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%u:%u:%u", 7, 4, 0);
    sprintf(str1, "%u:%u:%u", 7, 4, 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2327) {
#line 994
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "MAX %u", UINT_MAX);
    sprintf(str1, "MAX %u", UINT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2328) {
#line 1001
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "MIN %u", 0);
    sprintf(str1, "MIN %u", 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2329) {
#line 1008
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5u'", 7);
    sprintf(str1, "padding '%5u'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2330) {
#line 1015
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5u'", UINT_MAX);
    sprintf(str1, "padding '%5u'", UINT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2331) {
#line 1022
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5u'", 0);
    sprintf(str1, "padding '%5u'", 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2332) {
#line 1029
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%-5u'", 7);
    sprintf(str1, "padding '%-5u'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2333) {
#line 1036
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%-5u'", UINT_MAX);
    sprintf(str1, "padding '%-5u'", UINT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2334) {
#line 1043
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%-5u'", 0);
    sprintf(str1, "padding '%-5u'", 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2335) {
#line 1050
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%.5u'", 7);
    sprintf(str1, "precision '%.5u'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2336) {
#line 1057
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%.5u'", UINT_MAX);
    sprintf(str1, "precision '%.5u'", UINT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2337) {
#line 1064
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%.5u'", 0);
    sprintf(str1, "precision '%.5u'", 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2338) {
#line 1071
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%3.5u'", 7);
    sprintf(str1, "precision '%3.5u'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2339) {
#line 1078
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%3.5u'", UINT_MAX);
    sprintf(str1, "precision '%3.5u'", UINT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2340) {
#line 1085
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%3.5u'", 0);
    sprintf(str1, "precision '%3.5u'", 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2341) {
#line 1092
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%-3.5u'", 7);
    sprintf(str1, "precision '%-3.5u'", 7);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2342) {
#line 1099
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%-3.5u'", UINT_MAX);
    sprintf(str1, "precision '%-3.5u'", UINT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2343) {
#line 1106
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%-3.5u'", 0);
    sprintf(str1, "precision '%-3.5u'", 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2344) {
#line 1113
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "Hola %ld", 3534535547l);
    sprintf(str1, "Hola %ld", 3534535547l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2345) {
#line 1120
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%ld:%ld:%ld", 7l, 34543245324l, 0l);
    sprintf(str1, "%ld:%ld:%ld", 7l, 34543245324l, 0l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2346) {
#line 1127
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%ld", -5435432542l);
    sprintf(str1, "%ld", -5435432542l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2349) {
#line 1148
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "Hola %li", 3534535547l);
    sprintf(str1, "Hola %li", 3534535547l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2350) {
#line 1155
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5ld'", 72342l);
    sprintf(str1, "padding '%5ld'", 72342l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2802_i) {
#line 4935
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.20i] - l.%i\n, [% 15.20i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.20i] - l.%i\n, [% 15.20i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_3018) {
#line 3213
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3019) {
#line 3220
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3020) {
#line 3227
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3021) {
#line 3234
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.0d] - l.%d\n, [%-+3.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3021_2) {
#line 3241
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3022) {
#line 3248
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3023) {
#line 3255
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.2d] - l.%d\n, [%-+3.2d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3024) {
#line 3262
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3025) {
#line 3269
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3026) {
#line 3276
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.5d] - l.%d\n, [%-+3.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3027) {
#line 3283
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3028) {
#line 3290
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3029) {
#line 3297
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.15d] - l.%d\n, [%-+3.15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3030) {
#line 3304
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3031) {
#line 3311
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3032) {
#line 3318
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15d] - l.%d\n, [%-+15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3033) {
#line 3325
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3034) {
#line 3332
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3035) {
#line 3339
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.0d] - l.%d\n, [%-+15.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3036) {
#line 3346
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3037) {
#line 3353
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3038) {
#line 3360
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.5d] - l.%d\n, [%-+15.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3039) {
#line 3367
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3040) {
#line 3374
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3041) {
#line 3381
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.20d] - l.%d\n, [%-+15.20d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3072) {
#line 3388
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- d] - l.%d\n, [%- d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- d] - l.%d\n, [%- d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3073) {
#line 3395
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- d] - l.%d\n, [%- d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%- d] - l.%d\n, [%- d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3074) {
#line 3402
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- d] - l.%d\n, [%- d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%- d] - l.%d\n, [%- d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3075) {
#line 3409
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3076) {
#line 3416
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3077) {
#line 3423
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3d] - l.%d\n, [%- 3d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3078) {
#line 3430
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3079) {
#line 3437
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3080) {
#line 3444
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.0d] - l.%d\n, [%- 3.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3081) {
#line 3451
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3082) {
#line 3458
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3083) {
#line 3465
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.2d] - l.%d\n, [%- 3.2d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3084) {
#line 3472
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3085) {
#line 3479
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3086) {
#line 3486
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.5d] - l.%d\n, [%- 3.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3087) {
#line 3493
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3088) {
#line 3500
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3089) {
#line 3507
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.15d] - l.%d\n, [%- 3.15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3090) {
#line 3514
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3091) {
#line 3521
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3092) {
#line 3528
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15d] - l.%d\n, [%- 15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3093) {
#line 3535
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3094) {
#line 3542
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3095) {
#line 3549
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.0d] - l.%d\n, [%- 15.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3096) {
#line 3556
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3097) {
#line 3563
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3098) {
#line 3570
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.5d] - l.%d\n, [%- 15.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3099) {
#line 3577
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3100) {
#line 3584
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3101) {
#line 3591
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.20d] - l.%d\n, [%- 15.20d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3132) {
#line 3598
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3133) {
#line 3605
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3134) {
#line 3612
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+hd] - l.%d\n, [%-+hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3135) {
#line 3619
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3136) {
#line 3626
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3137) {
#line 3633
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3hd] - l.%d\n, [%-+3hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3138) {
#line 3640
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3139) {
#line 3647
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3140) {
#line 3654
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.0hd] - l.%d\n, [%-+3.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3141) {
#line 3661
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3142) {
#line 3668
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3143) {
#line 3675
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.2hd] - l.%d\n, [%-+3.2hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3144) {
#line 3682
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3145) {
#line 3689
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3146) {
#line 3696
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.5hd] - l.%d\n, [%-+3.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3147) {
#line 3703
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3148) {
#line 3710
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3149) {
#line 3717
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3.15hd] - l.%d\n, [%-+3.15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3150) {
#line 3724
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3151) {
#line 3731
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3152) {
#line 3738
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15hd] - l.%d\n, [%-+15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3153) {
#line 3745
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3154) {
#line 3752
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3155) {
#line 3759
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.0hd] - l.%d\n, [%-+15.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3156) {
#line 3766
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3157) {
#line 3773
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3158) {
#line 3780
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.5hd] - l.%d\n, [%-+15.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3159) {
#line 3787
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3160) {
#line 3794
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", SHRT_MIN,
                -2, __LINE__);
    sprintf(str1, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3161) {
#line 3801
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", SHRT_MAX,
                -2, __LINE__);
    sprintf(str1, "- %d - [%%-+15.20hd] - l.%d\n, [%-+15.20hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3192) {
#line 3808
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- hd] - l.%d\n, [%- hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- hd] - l.%d\n, [%- hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3193) {
#line 3815
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- hd] - l.%d\n, [%- hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- hd] - l.%d\n, [%- hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3194) {
#line 3822
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- hd] - l.%d\n, [%- hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- hd] - l.%d\n, [%- hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3195) {
#line 3829
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3196) {
#line 3836
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3197) {
#line 3843
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3hd] - l.%d\n, [%- 3hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3198) {
#line 3850
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3199) {
#line 3857
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3200) {
#line 3864
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.0hd] - l.%d\n, [%- 3.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3201) {
#line 3871
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3202) {
#line 3878
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3203) {
#line 3885
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.2hd] - l.%d\n, [%- 3.2hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3204) {
#line 3892
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3205) {
#line 3899
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3206) {
#line 3906
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.5hd] - l.%d\n, [%- 3.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3207) {
#line 3913
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3208) {
#line 3920
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3209) {
#line 3927
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 3.15hd] - l.%d\n, [%- 3.15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3210) {
#line 3934
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3211) {
#line 3941
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3212) {
#line 3948
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15hd] - l.%d\n, [%- 15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3213) {
#line 3955
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3214) {
#line 3962
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3215) {
#line 3969
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.0hd] - l.%d\n, [%- 15.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3216) {
#line 3976
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3217) {
#line 3983
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3218) {
#line 3990
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.5hd] - l.%d\n, [%- 15.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3219) {
#line 3997
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3220) {
#line 4004
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", SHRT_MIN,
                -2, __LINE__);
    sprintf(str1, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3221) {
#line 4011
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", SHRT_MAX,
                -2, __LINE__);
    sprintf(str1, "- %d - [%%- 15.20hd] - l.%d\n, [%- 15.20hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3373) {
#line 4018
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%s] - l.%d\n, [%s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%s] - l.%d\n, [%s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3375) {
#line 4034
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%3s] - l.%d\n, [%3s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3s] - l.%d\n, [%3s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3383) {
#line 4098
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3385) {
#line 4114
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%25s] - l.%d\n, [%25s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%25s] - l.%d\n, [%25s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3391) {
#line 4162
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-s] - l.%d\n, [%-s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-s] - l.%d\n, [%-s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3393) {
#line 4178
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3401) {
#line 4242
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-3.25s] - l.%d\n, [%-3.25s]", -2, __LINE__,
                str);
    sprintf(str1, "- %d - [%%-3.25s] - l.%d\n, [%-3.25s]", -2, __LINE__ - 2,
            str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3523) {
#line 4258
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%c] - l.%d\n, [%c]", -2, __LINE__, *str);
    sprintf(str1, "- %d - [%%c] - l.%d\n, [%c]", -2, __LINE__ - 1, *str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3525) {
#line 4266
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%3c] - l.%d\n, [%3c]", -2, __LINE__, *str);
    sprintf(str1, "- %d - [%%3c] - l.%d\n, [%3c]", -2, __LINE__ - 1, *str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3535) {
#line 4274
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%25c] - l.%d\n, [%25c]", -2, __LINE__, *str);
    sprintf(str1, "- %d - [%%25c] - l.%d\n, [%25c]", -2, __LINE__ - 1, *str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3554) {
#line 4282
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-c] - l.%d\n, [%-c]", -2, __LINE__, *str);
    sprintf(str1, "- %d - [%%-c] - l.%d\n, [%-c]", -2, __LINE__ - 1, *str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3555) {
#line 4290
    char str1[1024];
    char str2[1024];
    char *str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-3c] - l.%d\n, [%-3c]", -2, __LINE__, *str);
    sprintf(str1, "- %d - [%%-3c] - l.%d\n, [%-3c]", -2, __LINE__ - 1, *str);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2708_i) {
#line 4298
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%i] - l.%d\n, [%i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%i] - l.%d\n, [%i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2709_i) {
#line 4305
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%i] - l.%d\n, [%i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%i] - l.%d\n, [%i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2710_i) {
#line 4312
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%i] - l.%d\n, [%i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%i] - l.%d\n, [%i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2711i) {
#line 4319
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3d] - l.%d\n, [%3d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3d] - l.%d\n, [%3d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2712i) {
#line 4326
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3i] - l.%d\n, [%3i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%3i] - l.%d\n, [%3i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2713i) {
#line 4333
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3i] - l.%d\n, [%3i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%3i] - l.%d\n, [%3i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2714i) {
#line 4340
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0i] - l.%d\n, [%3.0i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.0i] - l.%d\n, [%3.0i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2715i) {
#line 4347
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0i] - l.%d\n, [%3.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.0i] - l.%d\n, [%3.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2716i) {
#line 4354
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2717i) {
#line 4361
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2718i) {
#line 4368
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2719i) {
#line 4375
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.2i] - l.%d\n, [%3.2i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2720i) {
#line 4382
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2721i) {
#line 4389
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2722i) {
#line 4396
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.5i] - l.%d\n, [%3.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2723i) {
#line 4403
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2724i) {
#line 4410
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2725i) {
#line 4417
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.15i] - l.%d\n, [%3.15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2726i) {
#line 4424
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15i] - l.%d\n, [%15i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15i] - l.%d\n, [%15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2727i) {
#line 4431
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15i] - l.%d\n, [%15i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%15i] - l.%d\n, [%15i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2728i) {
#line 4438
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15i] - l.%d\n, [%15i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%15i] - l.%d\n, [%15i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2729i) {
#line 4445
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2730i) {
#line 4452
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2731i) {
#line 4459
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.0i] - l.%d\n, [%15.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2732i) {
#line 4466
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2733i) {
#line 4473
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2734i) {
#line 4480
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.5i] - l.%d\n, [%15.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2735i) {
#line 4487
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2736i) {
#line 4494
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2737i) {
#line 4501
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.20i] - l.%d\n, [%15.20i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2738i) {
#line 4508
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-i] - l.%d\n, [%-i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-i] - l.%d\n, [%-i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2739i) {
#line 4515
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3i] - l.%d\n, [%-3i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3i] - l.%d\n, [%-3i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2740i) {
#line 4522
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.0i] - l.%d\n, [%-3.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.0i] - l.%d\n, [%-3.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2741i) {
#line 4529
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.2i] - l.%d\n, [%-3.2i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3.2i] - l.%d\n, [%-3.2i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2742i) {
#line 4536
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.5i] - l.%d\n, [%-3.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.5i] - l.%d\n, [%-3.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2743i) {
#line 4543
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.5i] - l.%d\n, [%-3.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.5i] - l.%d\n, [%-3.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2744i) {
#line 4550
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2745i) {
#line 4557
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2746i) {
#line 4564
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.15i] - l.%d\n, [%-3.15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2747i) {
#line 4571
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+i] - l.%d\n, [%+i]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+i] - l.%d\n, [%+i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2748i) {
#line 4578
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+i] - l.%d\n, [%+i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%+i] - l.%d\n, [%+i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2749i) {
#line 4585
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+i] - l.%d\n, [%+i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%+i] - l.%d\n, [%+i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2750_i) {
#line 4592
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2751_i) {
#line 4599
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2752_i) {
#line 4606
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2753_i) {
#line 4613
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2754_i) {
#line 4620
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2755_i) {
#line 4627
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3i] - l.%i\n, [%+3i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2756_i) {
#line 4634
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2757_i) {
#line 4641
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2758_i) {
#line 4648
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.5i] - l.%i\n, [%+3.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2759_i) {
#line 4655
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2760_i) {
#line 4662
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2761_i) {
#line 4669
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.15i] - l.%i\n, [%+3.15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2762_i) {
#line 4676
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15i] - l.%i\n, [%+15i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+15i] - l.%i\n, [%+15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2763_i) {
#line 4683
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15i] - l.%i\n, [%+15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15i] - l.%i\n, [%+15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2764_i) {
#line 4690
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15i] - l.%i\n, [%+15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15i] - l.%i\n, [%+15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2765_i) {
#line 4697
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2766_i) {
#line 4704
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2767_i) {
#line 4711
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.0i] - l.%i\n, [%+15.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2768_i) {
#line 4718
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2769_i) {
#line 4725
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2770_i) {
#line 4732
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.5i] - l.%i\n, [%+15.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2771_i) {
#line 4739
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2772_i) {
#line 4746
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2773_i) {
#line 4753
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.20i] - l.%i\n, [%+15.20i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2774_i) {
#line 4760
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% i] - l.%i\n, [% i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%% i] - l.%i\n, [% i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2775_i) {
#line 4767
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% i] - l.%i\n, [% i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %i - [%% i] - l.%i\n, [% i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2776_i) {
#line 4774
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% i] - l.%i\n, [% i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %i - [%% i] - l.%i\n, [% i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2777_i) {
#line 4781
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3i] - l.%i\n, [% 3i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%% 3i] - l.%i\n, [% 3i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_2405x) {
#line 1596
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [] - l.%d\n", -2, 2802);
    sprintf(str1, " - %d - [] - l.%d\n", -2, 2802);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2406x) {
#line 1603
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%3.15h%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%3.15h%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2408) {
#line 1610
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%03.15h%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%03.15h%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2409) {
#line 1617
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#0%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#0%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2410) {
#line 1624
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#015.20%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#015.20%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2411) {
#line 1631
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#0- 15.5%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#0- 15.5%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2412) {
#line 1638
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#0-+ 3.2%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#0-+ 3.2%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2413) {
#line 1645
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#0+ 3.2%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#0+ 3.2%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2414) {
#line 1652
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#0 15.5%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#0 15.5%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2415) {
#line 1659
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#-3%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#-3%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2416) {
#line 1666
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#-15.0%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#-15.0%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2417) {
#line 1673
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#-+15.0%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#-+15.0%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2418) {
#line 1680
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#- 15.0%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#- 15.0%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2419) {
#line 1687
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#-+ 15.0%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#-+ 15.0%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2420) {
#line 1694
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#-+ 15.20%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#-+ 15.20%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2421) {
#line 1701
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#+%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#+%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2423) {
#line 1708
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%#+15%%] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%#+15%%] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2427) {
#line 1715
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%d] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%d] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2428) {
#line 1722
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "[%d]", 0);
    sprintf(str1, "[%d]", 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2429) {
#line 1729
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%15.20d] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%15.20d] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2430) {
#line 1736
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "[%15.20d]", 0);
    sprintf(str1, "[%15.20d]", 0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2431) {
#line 1743
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%015.20d] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%015.20d] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2433) {
#line 1750
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%f'", 6.1);
    sprintf(str1, "precision '%f'", 6.1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2434) {
#line 1757
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%f] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%f] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2436) {
#line 1764
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%%3.15f] - l.%d\n", -2, __LINE__);
    sprintf(str1, " - %d - [%%3.15f] - l.%d\n", -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2708) {
#line 1771
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%d] - l.%d\n, [%d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%d] - l.%d\n, [%d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2709) {
#line 1778
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%d] - l.%d\n, [%d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%d] - l.%d\n, [%d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2710) {
#line 1785
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%d] - l.%d\n, [%d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%d] - l.%d\n, [%d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2711) {
#line 1792
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3d] - l.%d\n, [%3d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3d] - l.%d\n, [%3d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2712) {
#line 1799
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3d] - l.%d\n, [%3d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%3d] - l.%d\n, [%3d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2713) {
#line 1806
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3d] - l.%d\n, [%3d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%3d] - l.%d\n, [%3d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2714) {
#line 1813
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2715) {
#line 1820
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2716) {
#line 1827
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.0d] - l.%d\n, [%3.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2717) {
#line 1834
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2718) {
#line 1841
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2719) {
#line 1848
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.2d] - l.%d\n, [%3.2d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2720) {
#line 1855
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2721) {
#line 1862
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2722) {
#line 1869
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.5d] - l.%d\n, [%3.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2723) {
#line 1876
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2724) {
#line 1883
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2725) {
#line 1890
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.15d] - l.%d\n, [%3.15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2726) {
#line 1897
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15d] - l.%d\n, [%15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15d] - l.%d\n, [%15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2727) {
#line 1904
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15d] - l.%d\n, [%15d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%15d] - l.%d\n, [%15d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2728) {
#line 1911
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15d] - l.%d\n, [%15d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%15d] - l.%d\n, [%15d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2729) {
#line 1918
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2730) {
#line 1925
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2731) {
#line 1932
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.0d] - l.%d\n, [%15.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2732) {
#line 1939
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2733) {
#line 1946
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2734) {
#line 1953
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.5d] - l.%d\n, [%15.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2735) {
#line 1960
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2736) {
#line 1967
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2737) {
#line 1974
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.20d] - l.%d\n, [%15.20d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2738) {
#line 1981
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-d] - l.%d\n, [%-d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-d] - l.%d\n, [%-d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2739) {
#line 1988
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3d] - l.%d\n, [%-3d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3d] - l.%d\n, [%-3d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2740) {
#line 1995
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.0d] - l.%d\n, [%-3.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.0d] - l.%d\n, [%-3.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2741) {
#line 2002
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.2d] - l.%d\n, [%-3.2d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3.2d] - l.%d\n, [%-3.2d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2742) {
#line 2009
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.5d] - l.%d\n, [%-3.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.5d] - l.%d\n, [%-3.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2743) {
#line 2016
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.5d] - l.%d\n, [%-3.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.5d] - l.%d\n, [%-3.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2744) {
#line 2023
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2745) {
#line 2030
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2746) {
#line 2037
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.15d] - l.%d\n, [%-3.15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2747) {
#line 2044
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+d] - l.%d\n, [%+d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+d] - l.%d\n, [%+d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2748) {
#line 2051
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+d] - l.%d\n, [%+d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%+d] - l.%d\n, [%+d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2749) {
#line 2058
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+d] - l.%d\n, [%+d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%+d] - l.%d\n, [%+d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2750) {
#line 2065
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2751) {
#line 2072
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2752) {
#line 2079
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2753) {
#line 2086
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2754) {
#line 2093
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2755) {
#line 2100
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3d] - l.%d\n, [%+3d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2756) {
#line 2107
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2757) {
#line 2114
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2758) {
#line 2121
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.5d] - l.%d\n, [%+3.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2759) {
#line 2128
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2760) {
#line 2135
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2761) {
#line 2142
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.15d] - l.%d\n, [%+3.15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2762) {
#line 2149
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15d] - l.%d\n, [%+15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+15d] - l.%d\n, [%+15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2763) {
#line 2156
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15d] - l.%d\n, [%+15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15d] - l.%d\n, [%+15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2764) {
#line 2163
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15d] - l.%d\n, [%+15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15d] - l.%d\n, [%+15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2765) {
#line 2170
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2766) {
#line 2177
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2767) {
#line 2184
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.0d] - l.%d\n, [%+15.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2768) {
#line 2191
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2769) {
#line 2198
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2770) {
#line 2205
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.5d] - l.%d\n, [%+15.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2771) {
#line 2212
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2772) {
#line 2219
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2773) {
#line 2226
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.20d] - l.%d\n, [%+15.20d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2774) {
#line 2233
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% d] - l.%d\n, [% d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% d] - l.%d\n, [% d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2775) {
#line 2240
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% d] - l.%d\n, [% d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%% d] - l.%d\n, [% d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2776) {
#line 2247
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% d] - l.%d\n, [% d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%% d] - l.%d\n, [% d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2777) {
#line 2254
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3d] - l.%d\n, [% 3d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3d] - l.%d\n, [% 3d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2778) {
#line 2261
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3d] - l.%d\n, [% 3d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3d] - l.%d\n, [% 3d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2779) {
#line 2268
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3d] - l.%d\n, [% 3d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3d] - l.%d\n, [% 3d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2780) {
#line 2275
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", 0, -2, __LINE__);
    sprintf(str1, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2781) {
#line 2282
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2782) {
#line 2289
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, " - %d - [%% 3.0d] - l.%d\n, [% 3.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2783) {
#line 2296
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2784) {
#line 2303
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2785) {
#line 2310
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.2d] - l.%d\n, [% 3.2d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2786) {
#line 2317
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2786_2) {
#line 2324
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2787) {
#line 2331
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.5d] - l.%d\n, [% 3.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2788) {
#line 2338
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2789) {
#line 2345
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2790) {
#line 2352
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.15d] - l.%d\n, [% 3.15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2899_i) {
#line 5621
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2900_i) {
#line 5628
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.0hi] - l.%i\n, [% 15.0hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2904_i) {
#line 5635
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2905_i) {
#line 5642
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2906_i) {
#line 5649
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.20hi] - l.%i\n, [% 15.20hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3013) {
#line 5656
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+i] - l.%i\n, [%-+i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+i] - l.%i\n, [%-+i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3014) {
#line 5663
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+i] - l.%i\n, [%-+i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+i] - l.%i\n, [%-+i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3015) {
#line 5670
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+i] - l.%i\n, [%-+i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+i] - l.%i\n, [%-+i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3016) {
#line 5677
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3017) {
#line 5684
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3018) {
#line 5691
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3i] - l.%i\n, [%-+3i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3019) {
#line 5698
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3020) {
#line 5705
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3021) {
#line 5712
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.0i] - l.%i\n, [%-+3.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3021_2) {
#line 5719
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3022) {
#line 5726
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3023) {
#line 5733
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.2i] - l.%i\n, [%-+3.2i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3024) {
#line 5740
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3025) {
#line 5747
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3026) {
#line 5754
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.5i] - l.%i\n, [%-+3.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3027) {
#line 5761
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3028) {
#line 5768
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3029) {
#line 5775
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.15i] - l.%i\n, [%-+3.15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3030) {
#line 5782
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3031) {
#line 5789
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3032) {
#line 5796
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15i] - l.%i\n, [%-+15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3033) {
#line 5803
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3034) {
#line 5810
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3035) {
#line 5817
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.0i] - l.%i\n, [%-+15.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3036) {
#line 5824
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3037) {
#line 5831
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3038) {
#line 5838
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.5i] - l.%i\n, [%-+15.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3039) {
#line 5845
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3040) {
#line 5852
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3041) {
#line 5859
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15.20i] - l.%i\n, [%-+15.20i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3072) {
#line 5866
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- i] - l.%i\n, [%- i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%- i] - l.%i\n, [%- i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3073) {
#line 5873
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- i] - l.%i\n, [%- i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %i - [%%- i] - l.%i\n, [%- i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3074) {
#line 5880
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- i] - l.%i\n, [%- i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %i - [%%- i] - l.%i\n, [%- i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3075) {
#line 5887
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3076) {
#line 5894
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3077) {
#line 5901
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3i] - l.%i\n, [%- 3i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3078) {
#line 5908
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3079) {
#line 5915
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3080) {
#line 5922
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.0i] - l.%i\n, [%- 3.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3081) {
#line 5929
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3082) {
#line 5936
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3083) {
#line 5943
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.2i] - l.%i\n, [%- 3.2i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3084) {
#line 5950
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3085) {
#line 5957
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3086) {
#line 5964
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.5i] - l.%i\n, [%- 3.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3087) {
#line 5971
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3088) {
#line 5978
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3089) {
#line 5985
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 3.15i] - l.%i\n, [%- 3.15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3090) {
#line 5992
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3091) {
#line 5999
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3092) {
#line 6006
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15i] - l.%i\n, [%- 15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3093) {
#line 6013
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3094) {
#line 6020
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3095) {
#line 6027
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.0i] - l.%i\n, [%- 15.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3096) {
#line 6034
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3097) {
#line 6041
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3098) {
#line 6048
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.5i] - l.%i\n, [%- 15.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3099) {
#line 6055
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3100) {
#line 6062
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3101) {
#line 6069
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%- 15.20i] - l.%i\n, [%- 15.20i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3132) {
#line 6076
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3133) {
#line 6083
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3134) {
#line 6090
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+hi] - l.%i\n, [%-+hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3135) {
#line 6097
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3136) {
#line 6104
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3137) {
#line 6111
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3hi] - l.%i\n, [%-+3hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3138) {
#line 6118
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3139) {
#line 6125
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3140) {
#line 6132
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.0hi] - l.%i\n, [%-+3.0hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3141) {
#line 6139
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3142) {
#line 6146
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3143) {
#line 6153
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.2hi] - l.%i\n, [%-+3.2hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3144) {
#line 6160
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3145) {
#line 6167
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3146) {
#line 6174
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.5hi] - l.%i\n, [%-+3.5hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3147) {
#line 6181
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3148) {
#line 6188
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3149) {
#line 6195
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+3.15hi] - l.%i\n, [%-+3.15hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3150) {
#line 6202
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_3151) {
#line 6209
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-+15hi] - l.%i\n, [%-+15hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_2799) {
#line 2415
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2800) {
#line 2422
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2801) {
#line 2429
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2802) {
#line 2436
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.20d] - l.%d\n, [% 15.20d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2803) {
#line 2443
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%hd] - l.%d\n, [%hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%hd] - l.%d\n, [%hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2804) {
#line 2450
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%hd] - l.%d\n, [%hd]", SHRT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%hd] - l.%d\n, [%hd]", SHRT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2805) {
#line 2457
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%hd] - l.%d\n, [%hd]", SHRT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%hd] - l.%d\n, [%hd]", SHRT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2806) {
#line 2464
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3hd] - l.%d\n, [%3hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3hd] - l.%d\n, [%3hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2807) {
#line 2471
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3hd] - l.%d\n, [%3hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3hd] - l.%d\n, [%3hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2807_2) {
#line 2478
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3hd] - l.%d\n, [%3hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3hd] - l.%d\n, [%3hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2808) {
#line 2485
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2809) {
#line 2492
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2810) {
#line 2499
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.0hd] - l.%d\n, [%3.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2811) {
#line 2506
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2812) {
#line 2513
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2813) {
#line 2520
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.2hd] - l.%d\n, [%3.2hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2814) {
#line 2527
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2815) {
#line 2534
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2816) {
#line 2541
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.5hd] - l.%d\n, [%3.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2817) {
#line 2548
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2818) {
#line 2555
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2819) {
#line 2562
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%3.15hd] - l.%d\n, [%3.15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2820) {
#line 2569
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15hd] - l.%d\n, [%15hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15hd] - l.%d\n, [%15hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2821) {
#line 2576
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15hd] - l.%d\n, [%15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15hd] - l.%d\n, [%15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2822) {
#line 2583
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15hd] - l.%d\n, [%15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15hd] - l.%d\n, [%15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2823) {
#line 2590
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2824) {
#line 2597
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2825) {
#line 2604
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.0hd] - l.%d\n, [%15.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2826) {
#line 2611
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2827) {
#line 2618
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2828) {
#line 2625
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.5hd] - l.%d\n, [%15.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2829) {
#line 2632
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2830) {
#line 2639
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2831) {
#line 2646
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%15.20hd] - l.%d\n, [%15.20hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2832) {
#line 2653
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-hd] - l.%d\n, [%-hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-hd] - l.%d\n, [%-hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2833) {
#line 2660
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-hd] - l.%d\n, [%-hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-hd] - l.%d\n, [%-hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2834) {
#line 2667
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-hd] - l.%d\n, [%-hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-hd] - l.%d\n, [%-hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2835) {
#line 2674
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2836) {
#line 2681
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2837) {
#line 2688
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3hd] - l.%d\n, [%-3hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2838) {
#line 2695
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2839) {
#line 2702
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2840) {
#line 2709
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.0hd] - l.%d\n, [%-3.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2841) {
#line 2716
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2842) {
#line 2723
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2843) {
#line 2730
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.2hd] - l.%d\n, [%-3.2hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2844) {
#line 2737
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2845) {
#line 2744
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2846) {
#line 2751
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.5hd] - l.%d\n, [%-3.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2847) {
#line 2758
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2848) {
#line 2765
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2849) {
#line 2772
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-3.15hd] - l.%d\n, [%-3.15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2850) {
#line 2779
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+hd] - l.%d\n, [%+hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+hd] - l.%d\n, [%+hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2851) {
#line 2786
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+hd] - l.%d\n, [%+hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+hd] - l.%d\n, [%+hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2852) {
#line 2793
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+hd] - l.%d\n, [%+hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+hd] - l.%d\n, [%+hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2853) {
#line 2800
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2854) {
#line 2807
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2855) {
#line 2814
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3hd] - l.%d\n, [%+3hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2856) {
#line 2821
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2857) {
#line 2828
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2858) {
#line 2835
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.0hd] - l.%d\n, [%+3.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2859) {
#line 2842
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2860) {
#line 2849
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2861) {
#line 2856
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.5hd] - l.%d\n, [%+3.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2862) {
#line 2863
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2863) {
#line 2870
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2864) {
#line 2877
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+3.15hd] - l.%d\n, [%+3.15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2865) {
#line 2884
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2866) {
#line 2891
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2867) {
#line 2898
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15hd] - l.%d\n, [%+15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2868) {
#line 2905
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2869) {
#line 2912
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2870) {
#line 2919
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.0hd] - l.%d\n, [%+15.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2871) {
#line 2926
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2872) {
#line 2933
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2873) {
#line 2940
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.5hd] - l.%d\n, [%+15.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2368) {
#line 1281
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "Hola %lu", 7l);
    sprintf(str1, "Hola %lu", 7l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2369) {
#line 1288
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%lu:%lu:%lu", 7l, 4l, 0l);
    sprintf(str1, "%lu:%lu:%lu", 7l, 4l, 0l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2371) {
#line 1302
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "MIN %lu", 0l);
    sprintf(str1, "MIN %lu", 0l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2372) {
#line 1309
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5lu'", 7l);
    sprintf(str1, "padding '%5lu'", 7l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2374) {
#line 1323
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%5lu'", 0l);
    sprintf(str1, "padding '%5lu'", 0l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2375) {
#line 1330
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%-5lu'", 7l);
    sprintf(str1, "padding '%-5lu'", 7l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2377) {
#line 1344
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "padding '%-5lu'", 0l);
    sprintf(str1, "padding '%-5lu'", 0l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2378) {
#line 1351
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%.5lu'", 7l);
    sprintf(str1, "precision '%.5lu'", 7l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2380) {
#line 1365
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%.5lu'", 0l);
    sprintf(str1, "precision '%.5lu'", 0l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2381) {
#line 1372
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%3.5lu'", 7l);
    sprintf(str1, "precision '%3.5lu'", 7l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2383) {
#line 1386
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%3.5lu'", 0l);
    sprintf(str1, "precision '%3.5lu'", 0l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2384) {
#line 1393
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%-3.5lu'", 7l);
    sprintf(str1, "precision '%-3.5lu'", 7l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2386) {
#line 1407
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "precision '%-3.5lu'", 0l);
    sprintf(str1, "precision '%-3.5lu'", 0l);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2387) {
#line 1414
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%.5f", 3.5);
    sprintf(str1, "%.5f", 3.5);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2388) {
#line 1421
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%.5f", -3.5);
    sprintf(str1, "%.5f", -3.5);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2391) {
#line 1428
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%.5f", 0.0);
    sprintf(str1, "%.5f", 0.0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2392) {
#line 1435
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%.5f", 3.5458730589043);
    sprintf(str1, "%.5f", 3.5458730589043);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2393) {
#line 1442
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%.5f", -3.5458730589043);
    sprintf(str1, "%.5f", -3.5458730589043);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2394) {
#line 1449
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%10.4f", 3.5458730589043);
    sprintf(str1, "%10.4f", 3.5458730589043);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2395) {
#line 1456
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%10.4f", -3.5458730589043);
    sprintf(str1, "%10.4f", -3.5458730589043);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2396) {
#line 1463
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%07.5f", 334243.5458730589043);
    sprintf(str1, "%07.5f", 334243.5458730589043);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2401) {
#line 1470
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%10.5d", INT_MIN);
    sprintf(str1, "%10.5d", INT_MIN);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2402) {
#line 1477
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%10.5d", INT_MAX);
    sprintf(str1, "%10.5d", INT_MAX);
    ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_070510) {
#line 1568
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%.9f", 1000000000.00);
    sprintf(str1, "%.9f", 1000000000.00);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_070513) {
#line 1589
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "%3.f", 0.0);
    sprintf(str1, "%3.f", 0.0);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2791) {
#line 2359
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15d] - l.%d\n, [% 15d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 15d] - l.%d\n, [% 15d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2792) {
#line 2366
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15d] - l.%d\n, [% 15d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15d] - l.%d\n, [% 15d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2793) {
#line 2373
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15d] - l.%d\n, [% 15d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15d] - l.%d\n, [% 15d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2794) {
#line 2380
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2795) {
#line 2387
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2796) {
#line 2394
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.0d] - l.%d\n, [% 15.0d]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2797) {
#line 2401
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2798) {
#line 2408
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.5d] - l.%d\n, [% 15.5d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2874) {
#line 2947
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2875) {
#line 2954
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2876) {
#line 2961
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%+15.20hd] - l.%d\n, [%+15.20hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2877) {
#line 2968
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% hd] - l.%d\n, [% hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% hd] - l.%d\n, [% hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2878) {
#line 2975
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% hd] - l.%d\n, [% hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% hd] - l.%d\n, [% hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2879) {
#line 2982
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% hd] - l.%d\n, [% hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% hd] - l.%d\n, [% hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2880) {
#line 2989
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2881) {
#line 2996
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2882) {
#line 3003
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3hd] - l.%d\n, [% 3hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2883) {
#line 3010
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2884) {
#line 3017
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2885) {
#line 3024
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.0hd] - l.%d\n, [% 3.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2886) {
#line 3031
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2887) {
#line 3038
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2888) {
#line 3045
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.2hd] - l.%d\n, [% 3.2hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2889) {
#line 3052
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2890) {
#line 3059
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2891) {
#line 3066
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.5hd] - l.%d\n, [% 3.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2892) {
#line 3073
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2893) {
#line 3080
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2894) {
#line 3087
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 3.15hd] - l.%d\n, [% 3.15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2895) {
#line 3094
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2896) {
#line 3101
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2897) {
#line 3108
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15hd] - l.%d\n, [% 15hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2898) {
#line 3115
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2899) {
#line 3122
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2900) {
#line 3129
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.0hd] - l.%d\n, [% 15.0hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2901) {
#line 3136
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2902) {
#line 3143
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2903) {
#line 3150
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.5hd] - l.%d\n, [% 15.5hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2904) {
#line 3157
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", 0, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2905) {
#line 3164
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2906) {
#line 3171
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %d - [%% 15.20hd] - l.%d\n, [% 15.20hd]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3013) {
#line 3178
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+d] - l.%d\n, [%-+d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+d] - l.%d\n, [%-+d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3014) {
#line 3185
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+d] - l.%d\n, [%-+d]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+d] - l.%d\n, [%-+d]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3015) {
#line 3192
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+d] - l.%d\n, [%-+d]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+d] - l.%d\n, [%-+d]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3016) {
#line 3199
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", 0, -2, __LINE__);
    sprintf(str1, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3017) {
#line 3206
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %d - [%%-+3d] - l.%d\n, [%-+3d]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2778_i) {
#line 4788
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3i] - l.%i\n, [% 3i]", INT_MIN, -2, __LINE__);
    sprintf(str1, "- %i - [%% 3i] - l.%i\n, [% 3i]", INT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2779_i) {
#line 4795
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3i] - l.%i\n, [% 3i]", INT_MAX, -2, __LINE__);
    sprintf(str1, "- %i - [%% 3i] - l.%i\n, [% 3i]", INT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2780_i) {
#line 4802
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", 0, -2, __LINE__);
    sprintf(str1, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2781_i) {
#line 4809
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2782_i) {
#line 4816
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, " - %i - [%% 3.0i] - l.%i\n, [% 3.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2783_i) {
#line 4823
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2784_i) {
#line 4830
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2785_i) {
#line 4837
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 3.2i] - l.%i\n, [% 3.2i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2786_i) {
#line 4844
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2786_2_i) {
#line 4851
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2787_i) {
#line 4858
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 3.5i] - l.%i\n, [% 3.5i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2788_i) {
#line 4865
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2789_i) {
#line 4872
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2790_i) {
#line 4879
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 3.15i] - l.%i\n, [% 3.15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2791_i) {
#line 4886
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15i] - l.%i\n, [% 15i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%% 15i] - l.%i\n, [% 15i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2792_i) {
#line 4893
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15i] - l.%i\n, [% 15i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15i] - l.%i\n, [% 15i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2793_i) {
#line 4900
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15i] - l.%i\n, [% 15i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15i] - l.%i\n, [% 15i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2794_i) {
#line 4907
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2795_i) {
#line 4914
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", INT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", INT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2796_i) {
#line 4921
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", INT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.0i] - l.%i\n, [% 15.0i]", INT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2800_i) {
#line 4928
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%% 15.20i] - l.%i\n, [% 15.20i]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%% 15.20i] - l.%i\n, [% 15.20i]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2803_i) {
#line 4942
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%hi] - l.%i\n, [%hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%hi] - l.%i\n, [%hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2804_i) {
#line 4949
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%hi] - l.%i\n, [%hi]", SHRT_MIN, -2, __LINE__);
    sprintf(str1, "- %i - [%%hi] - l.%i\n, [%hi]", SHRT_MIN, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2805_i) {
#line 4956
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%hi] - l.%i\n, [%hi]", SHRT_MAX, -2, __LINE__);
    sprintf(str1, "- %i - [%%hi] - l.%i\n, [%hi]", SHRT_MAX, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2806_i) {
#line 4963
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3hi] - l.%i\n, [%3hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%3hi] - l.%i\n, [%3hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2807_i) {
#line 4970
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3hi] - l.%i\n, [%3hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3hi] - l.%i\n, [%3hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2807_2_i) {
#line 4977
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3hi] - l.%i\n, [%3hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3hi] - l.%i\n, [%3hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2808_i) {
#line 4984
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2809_i) {
#line 4991
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2810_i) {
#line 4998
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3.0hi] - l.%i\n, [%3.0hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2811_i) {
#line 5005
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2812_i) {
#line 5012
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2813_i) {
#line 5019
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3.2hi] - l.%i\n, [%3.2hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2814_i) {
#line 5026
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2815_i) {
#line 5033
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2816_i) {
#line 5040
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3.5hi] - l.%i\n, [%3.5hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2817_i) {
#line 5047
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2818_i) {
#line 5054
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2819_i) {
#line 5061
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%3.15hi] - l.%i\n, [%3.15hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2820_i) {
#line 5068
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15hi] - l.%i\n, [%15hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%15hi] - l.%i\n, [%15hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2821_i) {
#line 5075
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15hi] - l.%i\n, [%15hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15hi] - l.%i\n, [%15hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2822_i) {
#line 5082
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15hi] - l.%i\n, [%15hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15hi] - l.%i\n, [%15hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2823_i) {
#line 5089
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2824_i) {
#line 5096
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2825_i) {
#line 5103
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15.0hi] - l.%i\n, [%15.0hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2826_i) {
#line 5110
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2827_i) {
#line 5117
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2828_i) {
#line 5124
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15.5hi] - l.%i\n, [%15.5hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2829_i) {
#line 5131
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2830_i) {
#line 5138
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2831_i) {
#line 5145
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%15.20hi] - l.%i\n, [%15.20hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2832_i) {
#line 5152
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-hi] - l.%i\n, [%-hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-hi] - l.%i\n, [%-hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2833_i) {
#line 5159
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-hi] - l.%i\n, [%-hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-hi] - l.%i\n, [%-hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2834_i) {
#line 5166
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-hi] - l.%i\n, [%-hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-hi] - l.%i\n, [%-hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2835_i) {
#line 5173
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2836_i) {
#line 5180
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2837_i) {
#line 5187
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3hi] - l.%i\n, [%-3hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2838_i) {
#line 5194
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2839_i) {
#line 5201
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2840_i) {
#line 5208
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.0hi] - l.%i\n, [%-3.0hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2841_i) {
#line 5215
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2842_i) {
#line 5222
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2843_i) {
#line 5229
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.2hi] - l.%i\n, [%-3.2hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2844_i) {
#line 5236
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2845_i) {
#line 5243
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2846_i) {
#line 5250
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.5hi] - l.%i\n, [%-3.5hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2847_i) {
#line 5257
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2848_i) {
#line 5264
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2849_i) {
#line 5271
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%-3.15hi] - l.%i\n, [%-3.15hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2850_i) {
#line 5278
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+hi] - l.%i\n, [%+hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+hi] - l.%i\n, [%+hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2851_i) {
#line 5285
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+hi] - l.%i\n, [%+hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+hi] - l.%i\n, [%+hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2852_i) {
#line 5292
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+hi] - l.%i\n, [%+hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+hi] - l.%i\n, [%+hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2853_i) {
#line 5299
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2854_i) {
#line 5306
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2855_i) {
#line 5313
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3hi] - l.%i\n, [%+3hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2856_i) {
#line 5320
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2857_i) {
#line 5327
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2858_i) {
#line 5334
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.0hi] - l.%i\n, [%+3.0hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2859_i) {
#line 5341
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2860_i) {
#line 5348
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2861_i) {
#line 5355
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.5hi] - l.%i\n, [%+3.5hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2862_i) {
#line 5362
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2863_i) {
#line 5369
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2864_i) {
#line 5376
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+3.15hi] - l.%i\n, [%+3.15hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2865_i) {
#line 5383
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", 0, -2, __LINE__);
    sprintf(str1, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", 0, -2, __LINE__ - 1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2866_i) {
#line 5390
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2867_i) {
#line 5397
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15hi] - l.%i\n, [%+15hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2868_i) {
#line 5404
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2869_i) {
#line 5411
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2870_i) {
#line 5418
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.0hi] - l.%i\n, [%+15.0hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2871_i) {
#line 5425
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2872_i) {
#line 5432
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2873_i) {
#line 5439
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", SHRT_MAX, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.5hi] - l.%i\n, [%+15.5hi]", SHRT_MAX, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2874_i) {
#line 5446
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", 0, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", 0, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_i_2875_i) {
#line 5453
    char str1[1024];
    char str2[1024];
    s21_sprintf(str2, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", SHRT_MIN, -2,
                __LINE__);
    sprintf(str1, "- %i - [%%+15.20hi] - l.%i\n, [%+15.20hi]", SHRT_MIN, -2,
            __LINE__ - 2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

void s21_stringh_part1(TCase *tc1_1) {
    tcase_add_test(tc1_1, sprintf_pr_1);
    tcase_add_test(tc1_1, sprintf_pr_2);
    tcase_add_test(tc1_1, sprintf_c_1);
    tcase_add_test(tc1_1, sprintf_c_2);
    tcase_add_test(tc1_1, sprintf_c_3);
    tcase_add_test(tc1_1, sprintf_c_4);
    tcase_add_test(tc1_1, sprintf_c_5);
    tcase_add_test(tc1_1, sprintf_c_6);
    tcase_add_test(tc1_1, sprintf_c_7);
    tcase_add_test(tc1_1, sprintf_c_8);
    tcase_add_test(tc1_1, sprintf_c_9);
    tcase_add_test(tc1_1, sprintf_c_10);
    tcase_add_test(tc1_1, sprintf_d_1);
    tcase_add_test(tc1_1, sprintf_d_3);
    tcase_add_test(tc1_1, sprintf_d_4);
    tcase_add_test(tc1_1, sprintf_d_5);
    tcase_add_test(tc1_1, sprintf_d_6);
    tcase_add_test(tc1_1, sprintf_d_8);
    tcase_add_test(tc1_1, sprintf_d_9);
    tcase_add_test(tc1_1, sprintf_d_10);
    tcase_add_test(tc1_1, sprintf_d_11);
    tcase_add_test(tc1_1, sprintf_1);
    tcase_add_test(tc1_1, sprintf_2);
    tcase_add_test(tc1_1, sprintf_3);
    tcase_add_test(tc1_1, sprintf_4);
    tcase_add_test(tc1_1, sprintf_5);
    tcase_add_test(tc1_1, sprintf_30);
    tcase_add_test(tc1_1, sprintf_31);
    tcase_add_test(tc1_1, sprintf_32);
    tcase_add_test(tc1_1, sprintf_33);
    tcase_add_test(tc1_1, sprintf_34);
    tcase_add_test(tc1_1, sprintf_35);
    tcase_add_test(tc1_1, sprintf_36);
    tcase_add_test(tc1_1, sprintf_37);
    tcase_add_test(tc1_1, sprintf_38);
    tcase_add_test(tc1_1, sprintf_39);
    tcase_add_test(tc1_1, sprintf_40);
    tcase_add_test(tc1_1, sprintf_41);
    tcase_add_test(tc1_1, sprintf_42);
    tcase_add_test(tc1_1, sprintf_43);
    tcase_add_test(tc1_1, sprintf_44);
    tcase_add_test(tc1_1, int_sprintf_pr_1);
    tcase_add_test(tc1_1, int_sprintf_pr_2);
    tcase_add_test(tc1_1, int_sprintf_c_1);
    tcase_add_test(tc1_1, int_sprintf_c_2);
    tcase_add_test(tc1_1, int_sprintf_c_3);
    tcase_add_test(tc1_1, int_sprintf_c_4);
    tcase_add_test(tc1_1, int_sprintf_c_5);
    tcase_add_test(tc1_1, int_sprintf_c_6);
    tcase_add_test(tc1_1, int_sprintf_c_7);
    tcase_add_test(tc1_1, int_sprintf_c_8);
    tcase_add_test(tc1_1, int_sprintf_c_9);
    tcase_add_test(tc1_1, int_sprintf_c_10);
    tcase_add_test(tc1_1, int_sprintf_d_1);
    tcase_add_test(tc1_1, int_sprintf_d_2);
    tcase_add_test(tc1_1, int_sprintf_d_3);
    tcase_add_test(tc1_1, int_sprintf_d_4);
    tcase_add_test(tc1_1, int_sprintf_d_5);
    tcase_add_test(tc1_1, int_sprintf_d_6);
    tcase_add_test(tc1_1, int_sprintf_d_7);
    tcase_add_test(tc1_1, int_sprintf_d_8);
    tcase_add_test(tc1_1, int_sprintf_d_9);
    tcase_add_test(tc1_1, int_sprintf_d_10);
    tcase_add_test(tc1_1, int_sprintf_d_11);
    tcase_add_test(tc1_1, int_sprintf_d_and_c_1);
    tcase_add_test(tc1_1, int_sprintf_1);
    tcase_add_test(tc1_1, int_sprintf_2);
    tcase_add_test(tc1_1, int_sprintf_3);
    tcase_add_test(tc1_1, int_sprintf_4);
    tcase_add_test(tc1_1, int_sprintf_5);
    tcase_add_test(tc1_1, int_sprintf_6);
    tcase_add_test(tc1_1, int_sprintf_8);
    tcase_add_test(tc1_1, int_sprintf_9);
    tcase_add_test(tc1_1, int_sprintf_10);
    tcase_add_test(tc1_1, int_sprintf_11);
    tcase_add_test(tc1_1, int_sprintf_12);
    tcase_add_test(tc1_1, int_sprintf_13);
    tcase_add_test(tc1_1, int_sprintf_14);
    tcase_add_test(tc1_1, int_sprintf_15);
    tcase_add_test(tc1_1, int_sprintf_17);
    tcase_add_test(tc1_1, int_sprintf_18);
    tcase_add_test(tc1_1, int_sprintf_19);
    tcase_add_test(tc1_1, int_sprintf_20);
    tcase_add_test(tc1_1, int_sprintf_21);
    tcase_add_test(tc1_1, int_sprintf_22);
    tcase_add_test(tc1_1, sprintf_222);
    tcase_add_test(tc1_1, ssprintf_223);
    tcase_add_test(tc1_1, sprintf_225);
    tcase_add_test(tc1_1, ssprintf_226);
    tcase_add_test(tc1_1, ssprintf_227);
    tcase_add_test(tc1_1, ssprintf_228);
    tcase_add_test(tc1_1, ssprintf_229);
    tcase_add_test(tc1_1, ssprintf_2210);
    tcase_add_test(tc1_1, ssprintf_2211);
    tcase_add_test(tc1_1, ssprintf_2212);
    tcase_add_test(tc1_1, ssprintf_2213);
    tcase_add_test(tc1_1, ssprintf_2214);
    tcase_add_test(tc1_1, sprintf_231);
    tcase_add_test(tc1_1, sprintf_232);
    tcase_add_test(tc1_1, sprintf_233);
    tcase_add_test(tc1_1, sprintf_234);
    tcase_add_test(tc1_1, sprintf_235);
    tcase_add_test(tc1_1, sprintf_236);
    tcase_add_test(tc1_1, sprintf_237);
    tcase_add_test(tc1_1, sprintf_238);
    tcase_add_test(tc1_1, sprintf_239);
    tcase_add_test(tc1_1, sprintf_2311);
    tcase_add_test(tc1_1, sprintf_2312);
    tcase_add_test(tc1_1, sprintf_2313);
    tcase_add_test(tc1_1, sprintf_2314);
    tcase_add_test(tc1_1, sprintf_2315);
    tcase_add_test(tc1_1, sprintf_2316);
    tcase_add_test(tc1_1, sprintf_2317);
    tcase_add_test(tc1_1, sprintf_2318);
    tcase_add_test(tc1_1, sprintf_2319);
    tcase_add_test(tc1_1, sprintf_2320);
    tcase_add_test(tc1_1, sprintf_2321);
    tcase_add_test(tc1_1, sprintf_2322);
    tcase_add_test(tc1_1, sprintf_2323);
    tcase_add_test(tc1_1, sprintf_2324);
    tcase_add_test(tc1_1, sprintf_2325);
    tcase_add_test(tc1_1, sprintf_2326);
    tcase_add_test(tc1_1, sprintf_2327);
    tcase_add_test(tc1_1, sprintf_2328);
    tcase_add_test(tc1_1, sprintf_2329);
    tcase_add_test(tc1_1, sprintf_2330);
    tcase_add_test(tc1_1, sprintf_2331);
    tcase_add_test(tc1_1, sprintf_2332);
    tcase_add_test(tc1_1, sprintf_2333);
    tcase_add_test(tc1_1, sprintf_2334);
    tcase_add_test(tc1_1, sprintf_2335);
    tcase_add_test(tc1_1, sprintf_2336);
    tcase_add_test(tc1_1, sprintf_2337);
    tcase_add_test(tc1_1, sprintf_2338);
    tcase_add_test(tc1_1, sprintf_2339);
    tcase_add_test(tc1_1, sprintf_2340);
    tcase_add_test(tc1_1, sprintf_2341);
    tcase_add_test(tc1_1, sprintf_2342);
    tcase_add_test(tc1_1, sprintf_2343);
    tcase_add_test(tc1_1, sprintf_2344);
    tcase_add_test(tc1_1, sprintf_2345);
    tcase_add_test(tc1_1, sprintf_2346);
    tcase_add_test(tc1_1, sprintf_2349);
    tcase_add_test(tc1_1, sprintf_2350);
    tcase_add_test(tc1_1, sprintf_i_2802_i);
    tcase_add_test(tc1_1, sprintf_3018);
    tcase_add_test(tc1_1, sprintf_3019);
    tcase_add_test(tc1_1, sprintf_3020);
    tcase_add_test(tc1_1, sprintf_3021);
    tcase_add_test(tc1_1, sprintf_3021_2);
    tcase_add_test(tc1_1, sprintf_3022);
    tcase_add_test(tc1_1, sprintf_3023);
    tcase_add_test(tc1_1, sprintf_3024);
    tcase_add_test(tc1_1, sprintf_3025);
    tcase_add_test(tc1_1, sprintf_3026);
    tcase_add_test(tc1_1, sprintf_3027);
    tcase_add_test(tc1_1, sprintf_3028);
    tcase_add_test(tc1_1, sprintf_3029);
    tcase_add_test(tc1_1, sprintf_3030);
    tcase_add_test(tc1_1, sprintf_3031);
    tcase_add_test(tc1_1, sprintf_3032);
    tcase_add_test(tc1_1, sprintf_3033);
    tcase_add_test(tc1_1, sprintf_3034);
    tcase_add_test(tc1_1, sprintf_3035);
    tcase_add_test(tc1_1, sprintf_3036);
    tcase_add_test(tc1_1, sprintf_3037);
    tcase_add_test(tc1_1, sprintf_3038);
    tcase_add_test(tc1_1, sprintf_3039);
    tcase_add_test(tc1_1, sprintf_3040);
    tcase_add_test(tc1_1, sprintf_3041);
    tcase_add_test(tc1_1, sprintf_3072);
    tcase_add_test(tc1_1, sprintf_3073);
    tcase_add_test(tc1_1, sprintf_3074);
    tcase_add_test(tc1_1, sprintf_3075);
    tcase_add_test(tc1_1, sprintf_3076);
    tcase_add_test(tc1_1, sprintf_3077);
    tcase_add_test(tc1_1, sprintf_3078);
    tcase_add_test(tc1_1, sprintf_3079);
    tcase_add_test(tc1_1, sprintf_3080);
    tcase_add_test(tc1_1, sprintf_3081);
    tcase_add_test(tc1_1, sprintf_3082);
    tcase_add_test(tc1_1, sprintf_3083);
    tcase_add_test(tc1_1, sprintf_3084);
    tcase_add_test(tc1_1, sprintf_3085);
    tcase_add_test(tc1_1, sprintf_3086);
    tcase_add_test(tc1_1, sprintf_3087);
    tcase_add_test(tc1_1, sprintf_3088);
    tcase_add_test(tc1_1, sprintf_3089);
    tcase_add_test(tc1_1, sprintf_3090);
    tcase_add_test(tc1_1, sprintf_3091);
    tcase_add_test(tc1_1, sprintf_3092);
    tcase_add_test(tc1_1, sprintf_3093);
    tcase_add_test(tc1_1, sprintf_3094);
    tcase_add_test(tc1_1, sprintf_3095);
    tcase_add_test(tc1_1, sprintf_3096);
    tcase_add_test(tc1_1, sprintf_3097);
    tcase_add_test(tc1_1, sprintf_3098);
    tcase_add_test(tc1_1, sprintf_3099);
    tcase_add_test(tc1_1, sprintf_3100);
    tcase_add_test(tc1_1, sprintf_3101);
    tcase_add_test(tc1_1, sprintf_3132);
    tcase_add_test(tc1_1, sprintf_3133);
    tcase_add_test(tc1_1, sprintf_3134);
    tcase_add_test(tc1_1, sprintf_3135);
    tcase_add_test(tc1_1, sprintf_3136);
    tcase_add_test(tc1_1, sprintf_3137);
    tcase_add_test(tc1_1, sprintf_3138);
    tcase_add_test(tc1_1, sprintf_3139);
    tcase_add_test(tc1_1, sprintf_3140);
    tcase_add_test(tc1_1, sprintf_3141);
    tcase_add_test(tc1_1, sprintf_3142);
    tcase_add_test(tc1_1, sprintf_3143);
    tcase_add_test(tc1_1, sprintf_3144);
    tcase_add_test(tc1_1, sprintf_3145);
    tcase_add_test(tc1_1, sprintf_3146);
    tcase_add_test(tc1_1, sprintf_3147);
    tcase_add_test(tc1_1, sprintf_3148);
    tcase_add_test(tc1_1, sprintf_3149);
    tcase_add_test(tc1_1, sprintf_3150);
    tcase_add_test(tc1_1, sprintf_3151);
    tcase_add_test(tc1_1, sprintf_3152);
    tcase_add_test(tc1_1, sprintf_3153);
    tcase_add_test(tc1_1, sprintf_3154);
    tcase_add_test(tc1_1, sprintf_3155);
    tcase_add_test(tc1_1, sprintf_3156);
    tcase_add_test(tc1_1, sprintf_3157);
    tcase_add_test(tc1_1, sprintf_3158);
    tcase_add_test(tc1_1, sprintf_3159);
    tcase_add_test(tc1_1, sprintf_3160);
    tcase_add_test(tc1_1, sprintf_3161);
    tcase_add_test(tc1_1, sprintf_3192);
    tcase_add_test(tc1_1, sprintf_3193);
    tcase_add_test(tc1_1, sprintf_3194);
    tcase_add_test(tc1_1, sprintf_3195);
    tcase_add_test(tc1_1, sprintf_3196);
    tcase_add_test(tc1_1, sprintf_3197);
    tcase_add_test(tc1_1, sprintf_3198);
    tcase_add_test(tc1_1, sprintf_3199);
    tcase_add_test(tc1_1, sprintf_3200);
    tcase_add_test(tc1_1, sprintf_3201);
    tcase_add_test(tc1_1, sprintf_3202);
    tcase_add_test(tc1_1, sprintf_3203);
    tcase_add_test(tc1_1, sprintf_3204);
    tcase_add_test(tc1_1, sprintf_3205);
    tcase_add_test(tc1_1, sprintf_3206);
    tcase_add_test(tc1_1, sprintf_3207);
    tcase_add_test(tc1_1, sprintf_3208);
    tcase_add_test(tc1_1, sprintf_3209);
    tcase_add_test(tc1_1, sprintf_3210);
    tcase_add_test(tc1_1, sprintf_3211);
    tcase_add_test(tc1_1, sprintf_3212);
    tcase_add_test(tc1_1, sprintf_3213);
    tcase_add_test(tc1_1, sprintf_3214);
    tcase_add_test(tc1_1, sprintf_3215);
    tcase_add_test(tc1_1, sprintf_3216);
    tcase_add_test(tc1_1, sprintf_3217);
    tcase_add_test(tc1_1, sprintf_3218);
    tcase_add_test(tc1_1, sprintf_3219);
    tcase_add_test(tc1_1, sprintf_3220);
    tcase_add_test(tc1_1, sprintf_3221);
    tcase_add_test(tc1_1, sprintf_3373);
    tcase_add_test(tc1_1, sprintf_3375);
    tcase_add_test(tc1_1, sprintf_3383);
    tcase_add_test(tc1_1, sprintf_3385);
    tcase_add_test(tc1_1, sprintf_3391);
    tcase_add_test(tc1_1, sprintf_3393);
    tcase_add_test(tc1_1, sprintf_3401);
    tcase_add_test(tc1_1, sprintf_3523);
    tcase_add_test(tc1_1, sprintf_3525);
    tcase_add_test(tc1_1, sprintf_3535);
    tcase_add_test(tc1_1, sprintf_3554);
    tcase_add_test(tc1_1, sprintf_3555);
    tcase_add_test(tc1_1, sprintf_2708_i);
    tcase_add_test(tc1_1, sprintf_2709_i);
    tcase_add_test(tc1_1, sprintf_2710_i);
    tcase_add_test(tc1_1, sprintf_2711i);
    tcase_add_test(tc1_1, sprintf_2712i);
    tcase_add_test(tc1_1, sprintf_2713i);
    tcase_add_test(tc1_1, sprintf_2714i);
    tcase_add_test(tc1_1, sprintf_2715i);
    tcase_add_test(tc1_1, sprintf_2716i);
    tcase_add_test(tc1_1, sprintf_2717i);
    tcase_add_test(tc1_1, sprintf_2718i);
    tcase_add_test(tc1_1, sprintf_2719i);
    tcase_add_test(tc1_1, sprintf_2720i);
    tcase_add_test(tc1_1, sprintf_2721i);
    tcase_add_test(tc1_1, sprintf_2722i);
    tcase_add_test(tc1_1, sprintf_2723i);
    tcase_add_test(tc1_1, sprintf_2724i);
    tcase_add_test(tc1_1, sprintf_2725i);
    tcase_add_test(tc1_1, sprintf_2726i);
    tcase_add_test(tc1_1, sprintf_2727i);
    tcase_add_test(tc1_1, sprintf_2728i);
    tcase_add_test(tc1_1, sprintf_2729i);
    tcase_add_test(tc1_1, sprintf_2730i);
    tcase_add_test(tc1_1, sprintf_2731i);
    tcase_add_test(tc1_1, sprintf_2732i);
    tcase_add_test(tc1_1, sprintf_2733i);
    tcase_add_test(tc1_1, sprintf_2734i);
    tcase_add_test(tc1_1, sprintf_2735i);
    tcase_add_test(tc1_1, sprintf_2736i);
    tcase_add_test(tc1_1, sprintf_2737i);
    tcase_add_test(tc1_1, sprintf_2738i);
    tcase_add_test(tc1_1, sprintf_2739i);
    tcase_add_test(tc1_1, sprintf_2740i);
    tcase_add_test(tc1_1, sprintf_2741i);
    tcase_add_test(tc1_1, sprintf_2742i);
    tcase_add_test(tc1_1, sprintf_2743i);
    tcase_add_test(tc1_1, sprintf_2744i);
    tcase_add_test(tc1_1, sprintf_2745i);
    tcase_add_test(tc1_1, sprintf_2746i);
    tcase_add_test(tc1_1, sprintf_2747i);
    tcase_add_test(tc1_1, sprintf_2748i);
    tcase_add_test(tc1_1, sprintf_2749i);
    tcase_add_test(tc1_1, sprintf_i_2750_i);
    tcase_add_test(tc1_1, sprintf_i_2751_i);
    tcase_add_test(tc1_1, sprintf_i_2752_i);
    tcase_add_test(tc1_1, sprintf_i_2753_i);
    tcase_add_test(tc1_1, sprintf_i_2754_i);
    tcase_add_test(tc1_1, sprintf_i_2755_i);
    tcase_add_test(tc1_1, sprintf_i_2756_i);
    tcase_add_test(tc1_1, sprintf_i_2757_i);
    tcase_add_test(tc1_1, sprintf_i_2758_i);
    tcase_add_test(tc1_1, sprintf_i_2759_i);
    tcase_add_test(tc1_1, sprintf_i_2760_i);
    tcase_add_test(tc1_1, sprintf_i_2761_i);
    tcase_add_test(tc1_1, sprintf_i_2762_i);
    tcase_add_test(tc1_1, sprintf_i_2763_i);
    tcase_add_test(tc1_1, sprintf_i_2764_i);
    tcase_add_test(tc1_1, sprintf_i_2765_i);
    tcase_add_test(tc1_1, sprintf_i_2766_i);
    tcase_add_test(tc1_1, sprintf_i_2767_i);
    tcase_add_test(tc1_1, sprintf_i_2768_i);
    tcase_add_test(tc1_1, sprintf_i_2769_i);
    tcase_add_test(tc1_1, sprintf_i_2770_i);
    tcase_add_test(tc1_1, sprintf_i_2771_i);
    tcase_add_test(tc1_1, sprintf_i_2772_i);
    tcase_add_test(tc1_1, sprintf_i_2773_i);
    tcase_add_test(tc1_1, sprintf_i_2774_i);
    tcase_add_test(tc1_1, sprintf_i_2775_i);
    tcase_add_test(tc1_1, sprintf_i_2776_i);
    tcase_add_test(tc1_1, sprintf_i_2777_i);
    tcase_add_test(tc1_1, sprintf_2405x);
    tcase_add_test(tc1_1, sprintf_2406x);
    tcase_add_test(tc1_1, sprintf_2408);
    tcase_add_test(tc1_1, sprintf_2409);
    tcase_add_test(tc1_1, sprintf_2410);
    tcase_add_test(tc1_1, sprintf_2411);
    tcase_add_test(tc1_1, sprintf_2412);
    tcase_add_test(tc1_1, sprintf_2413);
    tcase_add_test(tc1_1, sprintf_2414);
    tcase_add_test(tc1_1, sprintf_2415);
    tcase_add_test(tc1_1, sprintf_2416);
    tcase_add_test(tc1_1, sprintf_2417);
    tcase_add_test(tc1_1, sprintf_2418);
    tcase_add_test(tc1_1, sprintf_2419);
    tcase_add_test(tc1_1, sprintf_2420);
    tcase_add_test(tc1_1, sprintf_2421);
    tcase_add_test(tc1_1, sprintf_2423);
    tcase_add_test(tc1_1, sprintf_2427);
    tcase_add_test(tc1_1, sprintf_2428);
    tcase_add_test(tc1_1, sprintf_2429);
    tcase_add_test(tc1_1, sprintf_2430);
    tcase_add_test(tc1_1, sprintf_2431);
    tcase_add_test(tc1_1, sprintf_2433);
    tcase_add_test(tc1_1, sprintf_2434);
    tcase_add_test(tc1_1, sprintf_2436);
    tcase_add_test(tc1_1, sprintf_2708);
    tcase_add_test(tc1_1, sprintf_2709);
    tcase_add_test(tc1_1, sprintf_2710);
    tcase_add_test(tc1_1, sprintf_2711);
    tcase_add_test(tc1_1, sprintf_2712);
    tcase_add_test(tc1_1, sprintf_2713);
    tcase_add_test(tc1_1, sprintf_2714);
    tcase_add_test(tc1_1, sprintf_2715);
    tcase_add_test(tc1_1, sprintf_2716);
    tcase_add_test(tc1_1, sprintf_2717);
    tcase_add_test(tc1_1, sprintf_2718);
    tcase_add_test(tc1_1, sprintf_2719);
    tcase_add_test(tc1_1, sprintf_2720);
    tcase_add_test(tc1_1, sprintf_2721);
    tcase_add_test(tc1_1, sprintf_2722);
    tcase_add_test(tc1_1, sprintf_2723);
    tcase_add_test(tc1_1, sprintf_2724);
    tcase_add_test(tc1_1, sprintf_2725);
    tcase_add_test(tc1_1, sprintf_2726);
    tcase_add_test(tc1_1, sprintf_2727);
    tcase_add_test(tc1_1, sprintf_2728);
    tcase_add_test(tc1_1, sprintf_2729);
    tcase_add_test(tc1_1, sprintf_2730);
    tcase_add_test(tc1_1, sprintf_2731);
    tcase_add_test(tc1_1, sprintf_2732);
    tcase_add_test(tc1_1, sprintf_2733);
    tcase_add_test(tc1_1, sprintf_2734);
    tcase_add_test(tc1_1, sprintf_2735);
    tcase_add_test(tc1_1, sprintf_2736);
    tcase_add_test(tc1_1, sprintf_2737);
    tcase_add_test(tc1_1, sprintf_2738);
    tcase_add_test(tc1_1, sprintf_2739);
    tcase_add_test(tc1_1, sprintf_2740);
    tcase_add_test(tc1_1, sprintf_2741);
    tcase_add_test(tc1_1, sprintf_2742);
    tcase_add_test(tc1_1, sprintf_2743);
    tcase_add_test(tc1_1, sprintf_2744);
    tcase_add_test(tc1_1, sprintf_2745);
    tcase_add_test(tc1_1, sprintf_2746);
    tcase_add_test(tc1_1, sprintf_2747);
    tcase_add_test(tc1_1, sprintf_2748);
    tcase_add_test(tc1_1, sprintf_2749);
    tcase_add_test(tc1_1, sprintf_2750);
    tcase_add_test(tc1_1, sprintf_2751);
    tcase_add_test(tc1_1, sprintf_2752);
    tcase_add_test(tc1_1, sprintf_2753);
    tcase_add_test(tc1_1, sprintf_2754);
    tcase_add_test(tc1_1, sprintf_2755);
    tcase_add_test(tc1_1, sprintf_2756);
}
void s21_stringh_part2(TCase *tc1_1) {
    tcase_add_test(tc1_1, sprintf_2757);
    tcase_add_test(tc1_1, sprintf_2758);
    tcase_add_test(tc1_1, sprintf_2759);
    tcase_add_test(tc1_1, sprintf_2760);
    tcase_add_test(tc1_1, sprintf_2761);
    tcase_add_test(tc1_1, sprintf_2762);
    tcase_add_test(tc1_1, sprintf_2763);
    tcase_add_test(tc1_1, sprintf_2764);
    tcase_add_test(tc1_1, sprintf_2765);
    tcase_add_test(tc1_1, sprintf_2766);
    tcase_add_test(tc1_1, sprintf_2767);
    tcase_add_test(tc1_1, sprintf_2768);
    tcase_add_test(tc1_1, sprintf_2769);
    tcase_add_test(tc1_1, sprintf_2770);
    tcase_add_test(tc1_1, sprintf_2771);
    tcase_add_test(tc1_1, sprintf_2772);
    tcase_add_test(tc1_1, sprintf_2773);
    tcase_add_test(tc1_1, sprintf_2774);
    tcase_add_test(tc1_1, sprintf_2775);
    tcase_add_test(tc1_1, sprintf_2776);
    tcase_add_test(tc1_1, sprintf_2777);
    tcase_add_test(tc1_1, sprintf_2778);
    tcase_add_test(tc1_1, sprintf_2779);
    tcase_add_test(tc1_1, sprintf_2780);
    tcase_add_test(tc1_1, sprintf_2781);
    tcase_add_test(tc1_1, sprintf_2782);
    tcase_add_test(tc1_1, sprintf_2783);
    tcase_add_test(tc1_1, sprintf_2784);
    tcase_add_test(tc1_1, sprintf_2785);
    tcase_add_test(tc1_1, sprintf_2786);
    tcase_add_test(tc1_1, sprintf_2786_2);
    tcase_add_test(tc1_1, sprintf_2787);
    tcase_add_test(tc1_1, sprintf_2788);
    tcase_add_test(tc1_1, sprintf_2789);
    tcase_add_test(tc1_1, sprintf_2790);
    tcase_add_test(tc1_1, sprintf_i_2899_i);
    tcase_add_test(tc1_1, sprintf_i_2900_i);
    tcase_add_test(tc1_1, sprintf_i_2904_i);
    tcase_add_test(tc1_1, sprintf_i_2905_i);
    tcase_add_test(tc1_1, sprintf_i_2906_i);
    tcase_add_test(tc1_1, sprintf_i_3013);
    tcase_add_test(tc1_1, sprintf_i_3014);
    tcase_add_test(tc1_1, sprintf_i_3015);
    tcase_add_test(tc1_1, sprintf_i_3016);
    tcase_add_test(tc1_1, sprintf_i_3017);
    tcase_add_test(tc1_1, sprintf_i_3018);
    tcase_add_test(tc1_1, sprintf_i_3019);
    tcase_add_test(tc1_1, sprintf_i_3020);
    tcase_add_test(tc1_1, sprintf_i_3021);
    tcase_add_test(tc1_1, sprintf_i_3021_2);
    tcase_add_test(tc1_1, sprintf_i_3022);
    tcase_add_test(tc1_1, sprintf_i_3023);
    tcase_add_test(tc1_1, sprintf_i_3024);
    tcase_add_test(tc1_1, sprintf_i_3025);
    tcase_add_test(tc1_1, sprintf_i_3026);
    tcase_add_test(tc1_1, sprintf_i_3027);
    tcase_add_test(tc1_1, sprintf_i_3028);
    tcase_add_test(tc1_1, sprintf_i_3029);
    tcase_add_test(tc1_1, sprintf_i_3030);
    tcase_add_test(tc1_1, sprintf_i_3031);
    tcase_add_test(tc1_1, sprintf_i_3032);
    tcase_add_test(tc1_1, sprintf_i_3033);
    tcase_add_test(tc1_1, sprintf_i_3034);
    tcase_add_test(tc1_1, sprintf_i_3035);
    tcase_add_test(tc1_1, sprintf_i_3036);
    tcase_add_test(tc1_1, sprintf_i_3037);
    tcase_add_test(tc1_1, sprintf_i_3038);
    tcase_add_test(tc1_1, sprintf_i_3039);
    tcase_add_test(tc1_1, sprintf_i_3040);
    tcase_add_test(tc1_1, sprintf_i_3041);
    tcase_add_test(tc1_1, sprintf_i_3072);
    tcase_add_test(tc1_1, sprintf_i_3073);
    tcase_add_test(tc1_1, sprintf_i_3074);
    tcase_add_test(tc1_1, sprintf_i_3075);
    tcase_add_test(tc1_1, sprintf_i_3076);
    tcase_add_test(tc1_1, sprintf_i_3077);
    tcase_add_test(tc1_1, sprintf_i_3078);
    tcase_add_test(tc1_1, sprintf_i_3079);
    tcase_add_test(tc1_1, sprintf_i_3080);
    tcase_add_test(tc1_1, sprintf_i_3081);
    tcase_add_test(tc1_1, sprintf_i_3082);
    tcase_add_test(tc1_1, sprintf_i_3083);
    tcase_add_test(tc1_1, sprintf_i_3084);
    tcase_add_test(tc1_1, sprintf_i_3085);
    tcase_add_test(tc1_1, sprintf_i_3086);
    tcase_add_test(tc1_1, sprintf_i_3087);
    tcase_add_test(tc1_1, sprintf_i_3088);
    tcase_add_test(tc1_1, sprintf_i_3089);
    tcase_add_test(tc1_1, sprintf_i_3090);
    tcase_add_test(tc1_1, sprintf_i_3091);
    tcase_add_test(tc1_1, sprintf_i_3092);
    tcase_add_test(tc1_1, sprintf_i_3093);
    tcase_add_test(tc1_1, sprintf_i_3094);
    tcase_add_test(tc1_1, sprintf_i_3095);
    tcase_add_test(tc1_1, sprintf_i_3096);
    tcase_add_test(tc1_1, sprintf_i_3097);
    tcase_add_test(tc1_1, sprintf_i_3098);
    tcase_add_test(tc1_1, sprintf_i_3099);
    tcase_add_test(tc1_1, sprintf_i_3100);
    tcase_add_test(tc1_1, sprintf_i_3101);
    tcase_add_test(tc1_1, sprintf_i_3132);
    tcase_add_test(tc1_1, sprintf_i_3133);
    tcase_add_test(tc1_1, sprintf_i_3134);
    tcase_add_test(tc1_1, sprintf_i_3135);
    tcase_add_test(tc1_1, sprintf_i_3136);
    tcase_add_test(tc1_1, sprintf_i_3137);
    tcase_add_test(tc1_1, sprintf_i_3138);
    tcase_add_test(tc1_1, sprintf_i_3139);
    tcase_add_test(tc1_1, sprintf_i_3140);
    tcase_add_test(tc1_1, sprintf_i_3141);
    tcase_add_test(tc1_1, sprintf_i_3142);
    tcase_add_test(tc1_1, sprintf_i_3143);
    tcase_add_test(tc1_1, sprintf_i_3144);
    tcase_add_test(tc1_1, sprintf_i_3145);
    tcase_add_test(tc1_1, sprintf_i_3146);
    tcase_add_test(tc1_1, sprintf_i_3147);
    tcase_add_test(tc1_1, sprintf_i_3148);
    tcase_add_test(tc1_1, sprintf_i_3149);
    tcase_add_test(tc1_1, sprintf_i_3150);
    tcase_add_test(tc1_1, sprintf_i_3151);
    tcase_add_test(tc1_1, sprintf_2799);
    tcase_add_test(tc1_1, sprintf_2800);
    tcase_add_test(tc1_1, sprintf_2801);
    tcase_add_test(tc1_1, sprintf_2802);
    tcase_add_test(tc1_1, sprintf_2803);
    tcase_add_test(tc1_1, sprintf_2804);
    tcase_add_test(tc1_1, sprintf_2805);
    tcase_add_test(tc1_1, sprintf_2806);
    tcase_add_test(tc1_1, sprintf_2807);
    tcase_add_test(tc1_1, sprintf_2807_2);
    tcase_add_test(tc1_1, sprintf_2808);
    tcase_add_test(tc1_1, sprintf_2809);
    tcase_add_test(tc1_1, sprintf_2810);
    tcase_add_test(tc1_1, sprintf_2811);
    tcase_add_test(tc1_1, sprintf_2812);
    tcase_add_test(tc1_1, sprintf_2813);
    tcase_add_test(tc1_1, sprintf_2814);
    tcase_add_test(tc1_1, sprintf_2815);
    tcase_add_test(tc1_1, sprintf_2816);
    tcase_add_test(tc1_1, sprintf_2817);
    tcase_add_test(tc1_1, sprintf_2818);
    tcase_add_test(tc1_1, sprintf_2819);
    tcase_add_test(tc1_1, sprintf_2820);
    tcase_add_test(tc1_1, sprintf_2821);
    tcase_add_test(tc1_1, sprintf_2822);
    tcase_add_test(tc1_1, sprintf_2823);
    tcase_add_test(tc1_1, sprintf_2824);
    tcase_add_test(tc1_1, sprintf_2825);
    tcase_add_test(tc1_1, sprintf_2826);
    tcase_add_test(tc1_1, sprintf_2827);
    tcase_add_test(tc1_1, sprintf_2828);
    tcase_add_test(tc1_1, sprintf_2829);
    tcase_add_test(tc1_1, sprintf_2830);
    tcase_add_test(tc1_1, sprintf_2831);
    tcase_add_test(tc1_1, sprintf_2832);
    tcase_add_test(tc1_1, sprintf_2833);
    tcase_add_test(tc1_1, sprintf_2834);
    tcase_add_test(tc1_1, sprintf_2835);
    tcase_add_test(tc1_1, sprintf_2836);
    tcase_add_test(tc1_1, sprintf_2837);
    tcase_add_test(tc1_1, sprintf_2838);
    tcase_add_test(tc1_1, sprintf_2839);
    tcase_add_test(tc1_1, sprintf_2840);
    tcase_add_test(tc1_1, sprintf_2841);
    tcase_add_test(tc1_1, sprintf_2842);
    tcase_add_test(tc1_1, sprintf_2843);
    tcase_add_test(tc1_1, sprintf_2844);
    tcase_add_test(tc1_1, sprintf_2845);
    tcase_add_test(tc1_1, sprintf_2846);
    tcase_add_test(tc1_1, sprintf_2847);
    tcase_add_test(tc1_1, sprintf_2848);
    tcase_add_test(tc1_1, sprintf_2849);
    tcase_add_test(tc1_1, sprintf_2850);
    tcase_add_test(tc1_1, sprintf_2851);
    tcase_add_test(tc1_1, sprintf_2852);
    tcase_add_test(tc1_1, sprintf_2853);
    tcase_add_test(tc1_1, sprintf_2854);
    tcase_add_test(tc1_1, sprintf_2855);
    tcase_add_test(tc1_1, sprintf_2856);
    tcase_add_test(tc1_1, sprintf_2857);
    tcase_add_test(tc1_1, sprintf_2858);
    tcase_add_test(tc1_1, sprintf_2859);
    tcase_add_test(tc1_1, sprintf_2860);
    tcase_add_test(tc1_1, sprintf_2861);
    tcase_add_test(tc1_1, sprintf_2862);
    tcase_add_test(tc1_1, sprintf_2863);
    tcase_add_test(tc1_1, sprintf_2864);
    tcase_add_test(tc1_1, sprintf_2865);
    tcase_add_test(tc1_1, sprintf_2866);
    tcase_add_test(tc1_1, sprintf_2867);
    tcase_add_test(tc1_1, sprintf_2868);
    tcase_add_test(tc1_1, sprintf_2869);
    tcase_add_test(tc1_1, sprintf_2870);
    tcase_add_test(tc1_1, sprintf_2871);
    tcase_add_test(tc1_1, sprintf_2872);
    tcase_add_test(tc1_1, sprintf_2873);
    tcase_add_test(tc1_1, sprintf_2368);
    tcase_add_test(tc1_1, sprintf_2369);
    tcase_add_test(tc1_1, sprintf_2371);
    tcase_add_test(tc1_1, sprintf_2372);
    tcase_add_test(tc1_1, sprintf_2374);
    tcase_add_test(tc1_1, sprintf_2375);
    tcase_add_test(tc1_1, sprintf_2377);
    tcase_add_test(tc1_1, sprintf_2378);
    tcase_add_test(tc1_1, sprintf_2380);
    tcase_add_test(tc1_1, sprintf_2381);
    tcase_add_test(tc1_1, sprintf_2383);
    tcase_add_test(tc1_1, sprintf_2384);
    tcase_add_test(tc1_1, sprintf_2386);
    tcase_add_test(tc1_1, sprintf_2387);
    tcase_add_test(tc1_1, sprintf_2388);
    tcase_add_test(tc1_1, sprintf_2391);
    tcase_add_test(tc1_1, sprintf_2392);
    tcase_add_test(tc1_1, sprintf_2393);
    tcase_add_test(tc1_1, sprintf_2394);
    tcase_add_test(tc1_1, sprintf_2395);
    tcase_add_test(tc1_1, sprintf_2396);
    tcase_add_test(tc1_1, sprintf_2401);
    tcase_add_test(tc1_1, sprintf_2402);
    tcase_add_test(tc1_1, sprintf_070510);
    tcase_add_test(tc1_1, sprintf_070513);
    tcase_add_test(tc1_1, sprintf_2791);
    tcase_add_test(tc1_1, sprintf_2792);
    tcase_add_test(tc1_1, sprintf_2793);
    tcase_add_test(tc1_1, sprintf_2794);
    tcase_add_test(tc1_1, sprintf_2795);
    tcase_add_test(tc1_1, sprintf_2796);
    tcase_add_test(tc1_1, sprintf_2797);
    tcase_add_test(tc1_1, sprintf_2798);
    tcase_add_test(tc1_1, sprintf_2874);
    tcase_add_test(tc1_1, sprintf_2875);
    tcase_add_test(tc1_1, sprintf_2876);
    tcase_add_test(tc1_1, sprintf_2877);
    tcase_add_test(tc1_1, sprintf_2878);
    tcase_add_test(tc1_1, sprintf_2879);
    tcase_add_test(tc1_1, sprintf_2880);
    tcase_add_test(tc1_1, sprintf_2881);
    tcase_add_test(tc1_1, sprintf_2882);
    tcase_add_test(tc1_1, sprintf_2883);
    tcase_add_test(tc1_1, sprintf_2884);
    tcase_add_test(tc1_1, sprintf_2885);
    tcase_add_test(tc1_1, sprintf_2886);
    tcase_add_test(tc1_1, sprintf_2887);
    tcase_add_test(tc1_1, sprintf_2888);
    tcase_add_test(tc1_1, sprintf_2889);
    tcase_add_test(tc1_1, sprintf_2890);
    tcase_add_test(tc1_1, sprintf_2891);
    tcase_add_test(tc1_1, sprintf_2892);
    tcase_add_test(tc1_1, sprintf_2893);
    tcase_add_test(tc1_1, sprintf_2894);
    tcase_add_test(tc1_1, sprintf_2895);
    tcase_add_test(tc1_1, sprintf_2896);
    tcase_add_test(tc1_1, sprintf_2897);
    tcase_add_test(tc1_1, sprintf_2898);
    tcase_add_test(tc1_1, sprintf_2899);
    tcase_add_test(tc1_1, sprintf_2900);
    tcase_add_test(tc1_1, sprintf_2901);
    tcase_add_test(tc1_1, sprintf_2902);
    tcase_add_test(tc1_1, sprintf_2903);
    tcase_add_test(tc1_1, sprintf_2904);
    tcase_add_test(tc1_1, sprintf_i_2778_i);
    tcase_add_test(tc1_1, sprintf_i_2779_i);
    tcase_add_test(tc1_1, sprintf_i_2780_i);
    tcase_add_test(tc1_1, sprintf_i_2781_i);
    tcase_add_test(tc1_1, sprintf_i_2782_i);
    tcase_add_test(tc1_1, sprintf_i_2783_i);
    tcase_add_test(tc1_1, sprintf_i_2784_i);
    tcase_add_test(tc1_1, sprintf_i_2785_i);
    tcase_add_test(tc1_1, sprintf_i_2786_i);
    tcase_add_test(tc1_1, sprintf_i_2786_2_i);
    tcase_add_test(tc1_1, sprintf_i_2787_i);
    tcase_add_test(tc1_1, sprintf_i_2788_i);
    tcase_add_test(tc1_1, sprintf_i_2789_i);
    tcase_add_test(tc1_1, sprintf_i_2790_i);
    tcase_add_test(tc1_1, sprintf_i_2791_i);
    tcase_add_test(tc1_1, sprintf_i_2792_i);
    tcase_add_test(tc1_1, sprintf_i_2793_i);
    tcase_add_test(tc1_1, sprintf_i_2794_i);
    tcase_add_test(tc1_1, sprintf_i_2795_i);
    tcase_add_test(tc1_1, sprintf_i_2796_i);
    tcase_add_test(tc1_1, sprintf_i_2800_i);
    tcase_add_test(tc1_1, sprintf_i_2803_i);
    tcase_add_test(tc1_1, sprintf_i_2804_i);
    tcase_add_test(tc1_1, sprintf_i_2805_i);
    tcase_add_test(tc1_1, sprintf_i_2806_i);
    tcase_add_test(tc1_1, sprintf_i_2807_i);
    tcase_add_test(tc1_1, sprintf_i_2807_2_i);
    tcase_add_test(tc1_1, sprintf_i_2808_i);
    tcase_add_test(tc1_1, sprintf_i_2809_i);
    tcase_add_test(tc1_1, sprintf_i_2810_i);
    tcase_add_test(tc1_1, sprintf_i_2811_i);
    tcase_add_test(tc1_1, sprintf_i_2812_i);
    tcase_add_test(tc1_1, sprintf_i_2813_i);
    tcase_add_test(tc1_1, sprintf_i_2814_i);
    tcase_add_test(tc1_1, sprintf_i_2815_i);
    tcase_add_test(tc1_1, sprintf_i_2816_i);
    tcase_add_test(tc1_1, sprintf_i_2817_i);
    tcase_add_test(tc1_1, sprintf_i_2818_i);
    tcase_add_test(tc1_1, sprintf_i_2819_i);
    tcase_add_test(tc1_1, sprintf_i_2820_i);
    tcase_add_test(tc1_1, sprintf_i_2821_i);
    tcase_add_test(tc1_1, sprintf_i_2822_i);
    tcase_add_test(tc1_1, sprintf_i_2823_i);
    tcase_add_test(tc1_1, sprintf_i_2824_i);
    tcase_add_test(tc1_1, sprintf_i_2825_i);
    tcase_add_test(tc1_1, sprintf_i_2826_i);
    tcase_add_test(tc1_1, sprintf_i_2827_i);
    tcase_add_test(tc1_1, sprintf_i_2828_i);
    tcase_add_test(tc1_1, sprintf_i_2829_i);
    tcase_add_test(tc1_1, sprintf_i_2830_i);
    tcase_add_test(tc1_1, sprintf_i_2831_i);
    tcase_add_test(tc1_1, sprintf_i_2832_i);
    tcase_add_test(tc1_1, sprintf_i_2833_i);
    tcase_add_test(tc1_1, sprintf_i_2834_i);
    tcase_add_test(tc1_1, sprintf_i_2835_i);
    tcase_add_test(tc1_1, sprintf_i_2836_i);
    tcase_add_test(tc1_1, sprintf_i_2837_i);
    tcase_add_test(tc1_1, sprintf_i_2838_i);
    tcase_add_test(tc1_1, sprintf_i_2839_i);
    tcase_add_test(tc1_1, sprintf_i_2840_i);
    tcase_add_test(tc1_1, sprintf_i_2841_i);
    tcase_add_test(tc1_1, sprintf_i_2842_i);
    tcase_add_test(tc1_1, sprintf_i_2843_i);
    tcase_add_test(tc1_1, sprintf_i_2844_i);
    tcase_add_test(tc1_1, sprintf_i_2845_i);
    tcase_add_test(tc1_1, sprintf_i_2846_i);
    tcase_add_test(tc1_1, sprintf_i_2847_i);
    tcase_add_test(tc1_1, sprintf_i_2848_i);
    tcase_add_test(tc1_1, sprintf_i_2849_i);
    tcase_add_test(tc1_1, sprintf_i_2850_i);
    tcase_add_test(tc1_1, sprintf_i_2851_i);
    tcase_add_test(tc1_1, sprintf_i_2852_i);
    tcase_add_test(tc1_1, sprintf_i_2853_i);
    tcase_add_test(tc1_1, sprintf_i_2854_i);
    tcase_add_test(tc1_1, sprintf_i_2855_i);
    tcase_add_test(tc1_1, sprintf_i_2856_i);
    tcase_add_test(tc1_1, sprintf_i_2857_i);
    tcase_add_test(tc1_1, sprintf_i_2858_i);
    tcase_add_test(tc1_1, sprintf_i_2859_i);
    tcase_add_test(tc1_1, sprintf_i_2860_i);
    tcase_add_test(tc1_1, sprintf_i_2861_i);
    tcase_add_test(tc1_1, sprintf_i_2862_i);
    tcase_add_test(tc1_1, sprintf_i_2863_i);
    tcase_add_test(tc1_1, sprintf_i_2864_i);
    tcase_add_test(tc1_1, sprintf_i_2865_i);
    tcase_add_test(tc1_1, sprintf_i_2866_i);
    tcase_add_test(tc1_1, sprintf_i_2867_i);
    tcase_add_test(tc1_1, sprintf_i_2868_i);
}
void s21_stringh_part3(TCase *tc1_1) {
    tcase_add_test(tc1_1, sprintf_i_2869_i);
    tcase_add_test(tc1_1, sprintf_i_2870_i);
    tcase_add_test(tc1_1, sprintf_i_2871_i);
    tcase_add_test(tc1_1, sprintf_i_2872_i);
    tcase_add_test(tc1_1, sprintf_i_2873_i);
    tcase_add_test(tc1_1, sprintf_i_2874_i);
    tcase_add_test(tc1_1, sprintf_i_2875_i);
    tcase_add_test(tc1_1, sprintf_2905);
    tcase_add_test(tc1_1, sprintf_2906);
    tcase_add_test(tc1_1, sprintf_3013);
    tcase_add_test(tc1_1, sprintf_3014);
    tcase_add_test(tc1_1, sprintf_3015);
    tcase_add_test(tc1_1, sprintf_3016);
    tcase_add_test(tc1_1, sprintf_3017);
    tcase_add_test(tc1_1, test_s21_strlen);
    tcase_add_test(tc1_1, test_s21_strcspn);
    tcase_add_test(tc1_1, test_s21_strspn);
    tcase_add_test(tc1_1, test_s21_strtok);
    tcase_add_test(tc1_1, test_s21_strpbrk);
    tcase_add_test(tc1_1, test_s21_strstr);
    tcase_add_test(tc1_1, test_s21_strcmp);
    tcase_add_test(tc1_1, test_s21_strncmp);
    tcase_add_test(tc1_1, test_s21_memcmp);
    tcase_add_test(tc1_1, test_s21_strcat);
    tcase_add_test(tc1_1, test_s21_strncat);
    tcase_add_test(tc1_1, test_s21_strcpy);
    tcase_add_test(tc1_1, test_s21_strncpy);
    tcase_add_test(tc1_1, test_s21_memcpy);
    tcase_add_test(tc1_1, test_s21_strchr);
    tcase_add_test(tc1_1, test_s21_strrchr);
    tcase_add_test(tc1_1, test_s21_memchr);
    tcase_add_test(tc1_1, test_s21_memmove);
    tcase_add_test(tc1_1, test_s21_memset);
    tcase_add_test(tc1_1, test_s21_to_upper);
    tcase_add_test(tc1_1, test_s21_to_lower);
    tcase_add_test(tc1_1, test_s21_insert);
    tcase_add_test(tc1_1, test_s21_trim);
    tcase_add_test(tc1_1, test_s21_strerror);
}

int main(void) {
    int failed;
    Suite *s = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s);

    suite_add_tcase(s, tc1_1);
    s21_stringh_part1(tc1_1);
    s21_stringh_part2(tc1_1);
    s21_stringh_part3(tc1_1);

    srunner_run_all(sr, CK_ENV);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
