#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
    s21_size_t lenght = 0;
    for (; *(str + lenght); lenght++) {
    }
    return lenght;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    const char *p1, *p2;
    char c, sc;
    for (p1 = str1;;) {
        c = *p1++;
        p2 = str2;
        do {
            if ((sc = *p2++) == c) return (p1 - 1 - str1);
        } while (sc != 0);
    }
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t len = 0, str1I = 0, str2I = 0;
    if ((str1 != s21_NULL) || (str2 != s21_NULL)) {
        while (str2[str2I] != '\0') {
            if (str1[str1I] == str2[str2I]) {
                str1I++;
                str2I = -1;
                len++;
            }
            str2I++;
        }
    }
    return len;
}

char *s21_strtok(char *str, const char *delim) {
    static char *next;
    if (str) {
        next = str;
        while (*next && s21_strchr(delim, *next)) *next++ = '\0';
    }
    if (*next == '\0') {
        str = s21_NULL;
    } else {
        str = next;
        while (*next && !s21_strchr(delim, *next)) ++next;
        while (*next && s21_strchr(delim, *next)) *next++ = '\0';
    }
    return str;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    str1 += s21_strcspn(str1, str2);
    return *str1 ? (char *)str1 : s21_NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
    char *result = (char *)haystack;
    s21_size_t needle_len = s21_strlen(needle);
    s21_size_t haystack_len = s21_strlen(haystack);

    if (needle[0] != '\0') {
        char *haystack_cp = s21_strchr(haystack, needle[0]);
        if (haystack_cp == s21_NULL || needle[1] == '\0') {
            result = haystack_cp;
        } else if (haystack_len < needle_len) {
            result = s21_NULL;
        } else if (s21_memcmp(haystack_cp, needle, needle_len) == 0) {
            result = haystack_cp;
        } else {
            result = s21_NULL;
        }
    } else {
        result = (char *)haystack;
    }
    return result;
}

int s21_strcmp(const char *str1, const char *str2) {
    for (; *str1 && *str1 == *str2; str1++, str2++) {
    }
    return *str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int res = 0;
    if (n != 0) {
        while (n-- - 1 && *str1 && *str1 == *str2) {
            str1++, str2++;
        }
        res = *str1 - *str2;
    }
    return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int flag = 0;
    int save = 0;
    if (n != 0) {
        register const unsigned char *p1 = str1, *p2 = str2;
        do {
            if (*p1++ != *p2++) {
                save = (*--p1 - *--p2);
                flag = 1;
            }
        } while (--n != 0 && flag == 0);
    }
    return save;
}

char *s21_strcat(char *dest, const char *src) {
    int i, j;
    i = j = 0;
    while (dest[i] != '\0') i++;
    while ((dest[i++] = src[j++]) != '\0') {
    }
    return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    int f = 0;
    if (n != 0) {
        char *d = dest;
        const char *s = src;
        while (*d != 0) d++;
        do {
            if ((*d = *s++) == 0) f = 1;
            d++;
        } while (--n != 0 && f == 0);
        *d = 0;
    }
    return (dest);
}

char *s21_strcpy(char *dest, const char *src) {
    int i;
    i = 0;
    while ((dest[i] = src[i]) != '\0') i++;
    return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    long unsigned int i;
    i = 0;
    while (((dest[i] = src[i]) != '\0') && i < n - 1) i++;
    return dest;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    char *d = dest;
    const char *s = src;
    while (n--) *d++ = *s++;
    return dest;
}

char *s21_strchr(const char *str, int c) {
    int f = 0;
    char *save = s21_NULL;
    while (f == 0) {
        if (*str == c) {
            save = ((char *)str);
            f = 1;
        }
        if (*str == '\0') {
            f = 1;
        }
        str++;
    }
    return save;
}

char *s21_strrchr(const char *str, int c) {
    char *save;
    char ch;
    ch = c;
    for (save = s21_NULL;; ++str) {
        if (*str == ch) save = (char *)str;
        if (*str == '\0') return (save);
    }
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
    while (n && (*(unsigned char *)str != (unsigned char)c)) {
        str = (unsigned char *)str + 1;
        n--;
    }

    return (n ? (void *)str : s21_NULL);
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *d = dest;
    const char *s = src;
    if (d < s) {
        while (n--) *d++ = *s++;
    } else {
        const char *lasts = s + (n - 1);
        char *lastd = d + (n - 1);
        while (n--) *lastd-- = *lasts--;
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *STR = str;
    while (n-- > 0) *STR++ = c;
    return str;
}

void *s21_to_upper(const char *str) {
    char *result = s21_NULL;
    if (str) {
        int len = (s21_strlen(str));
        result = (char *)malloc((len + 1) * sizeof(char));
        if (result) {
            s21_strcpy(result, str);
            for (int i = 0; i < len; i++) {
                if (str[i] >= 97 && str[i] <= 122)
                    result[i] = (char)(str[i] - 32);
                else
                    result[i] = str[i];
            }
        }
    }
    return (void *)result;
}

void *s21_to_lower(const char *str) {
    char *result = s21_NULL;
    if (str) {
        int len = (s21_strlen(str));
        result = (char *)malloc((len + 1) * sizeof(char));
        if (result) {
            s21_strcpy(result, str);
            for (int i = 0; i < len; i++) {
                if (str[i] >= 65 && str[i] <= 90)
                    result[i] = (char)(str[i] + 32);
                else
                    result[i] = str[i];
            }
        }
    }
    return (void *)result;
}

void *s21_trim(const char *src, const char *trim_chars) {
    int len_src = 0, len_trim = 0, left = 0, right = 0;
    while (src[len_src] != '\0') len_src++;
    while (trim_chars[len_trim] != '\0') len_trim++;
    int flag_break = 0;
    for (int i = 0, count = 0; i < len_src && flag_break == 0; ++i) {
        for (int j = 0; j < len_trim; ++j)
            if (src[i] != trim_chars[j]) ++count;
        if (count == len_trim) {
            left = i;
            flag_break = 1;
        }
        count = 0;
    }
    flag_break = 0;
    for (int i = len_src - 1, count = 0; i >= 0 && flag_break == 0; --i) {
        for (int j = 0; j < len_trim; ++j)
            if (src[i] != trim_chars[j]) ++count;
        if (count == len_trim) {
            right = i;
            flag_break = 1;
        }
        count = 0;
    }
    char *buff = (char *)calloc((right - left + 200), sizeof(char));
    if (left < right) {
        for (int i = 0, j = left; i < right - left + 1; ++i, ++j)
            buff[i] = src[j];
        buff[right + 1] = '\0';
    }
    return buff;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    s21_size_t l1 = 0, l2 = 0;
    while (src[l1] != '\0') l1++;
    while (str[l2] != '\0') l2++;
    char *buffer;
    buffer = (char *)malloc((l1 + l2 + 10) * sizeof(char));
    s21_size_t i = 0, counter_for_buffer = 0;
    if (start_index < l1) {
        s21_insert_case(src, str, start_index, buffer, i, counter_for_buffer);
    } else if (start_index == l1) {
        while (src[i] != '\0') {
            buffer[counter_for_buffer] = src[i];
            counter_for_buffer++;
            i++;
        }
        if (counter_for_buffer == l1) {
            s21_size_t j = 0;
            while (str[j] != '\0') {
                buffer[counter_for_buffer] = str[j];
                counter_for_buffer++;
                j++;
            }
        }
        buffer[counter_for_buffer] = '\0';
    } else {
        free(buffer);
        buffer = s21_NULL;
    }
    char *p = buffer;
    return p;
}

char *s21_insert_case(const char *src, const char *str, s21_size_t start_index,
                      char *buffer, s21_size_t i,
                      s21_size_t counter_for_buffer) {
    while (src[i] != '\0') {
        if (i < start_index) {
            buffer[counter_for_buffer] = src[i];
        } else if (i == start_index) {
            buffer[i] = src[i];
            int j = 0;
            while (str[j] != '\0') {
                buffer[counter_for_buffer + j] = str[j];
                j++;
            }
            buffer[counter_for_buffer + j] = src[i];
            counter_for_buffer = counter_for_buffer + j + 1;
        } else {
            buffer[counter_for_buffer - 1] = src[i];
        }
        i++;
        counter_for_buffer++;
    }
    buffer[counter_for_buffer - 1] = '\0';
    return buffer;
}

#ifdef __APPLE__
char *s21_strerror(int errnum) {
    char *errors[] = errlist;
    char *buf = s21_NULL;
    buf = (char *)malloc(sizeof(char) * (1024));
    s21_memset((void *)buf, '\0', 1024);
    if (errnum < 0 || errnum > MAX_ERROR) {
        s21_sprintf(buf, "Unknown error: %d", errnum);
    } else {
        s21_strcat(buf, errors[errnum]);
    }
    return buf;
}
#elif __linux__
char *s21_strerror(int errnum) {
    char *errors[] = errlist;
    char *buf = s21_NULL;
    buf = (char *)malloc(sizeof(char) * (1024));
    s21_memset((void *)buf, '\0', 1024);
    if (errnum < 0 || errnum > MAX_ERROR) {
        s21_sprintf(buf, "Unknown error %d", errnum);
    } else {
        s21_strcat(buf, errors[errnum]);
    }
    return buf;
}
#endif

void full_with_zeroes_specifier(struct specifier *ex) {
    for (int i = 0; i < 5; i++) {
        ex->info[i] = 0;
    }
    ex->length = 0;
    ex->spec = 0;
}

float s21_round(double num) {
    double res;
    if ((int)num % 2 == 0 && (num - (int)num) == 0.5)
        res = floor(num);
    else
        res = round(num);
    return res;
}

void read_flag(struct specifier *ex, char **p, int *format_len) {
    // %[флаги][ширина][.точность][длина]спецификатор
    // c, d, i, f, s, u, %
    // Флаги: -, +, (пробел)
    // Ширина: (число)
    // Точность: .(число)
    // Длина: h, l

    while (**p == '-' || **p == '+' || **p == ' ') {
        if (**p == '-')
            ex->info[0] = 1;
        else if (**p == '+')
            ex->info[1] = 1;
        else if (**p == ' ')
            ex->info[2] = 1;
        (*p)++;
        (*format_len)--;
    }
    // считываем ширину
    while (**p >= '0' && **p <= '9') {
        ex->info[3] *= 10;
        ex->info[3] += **p - '0';
        (*p)++;
        (*format_len)--;
    }
    // считываем точность
    if (**p == '.') {
        if (*(*p + 1) <= '0' || *(*p + 1) > '9') ex->info[4] = -2;
        (*p)++;
        (*format_len)--;
        while (**p >= '0' && **p <= '9' && *p) {
            ex->info[4] *= 10;
            ex->info[4] += **p - '0';
            (*p)++;
            (*format_len)--;
        }
    } else {
        ex->info[4] = -1;
    }
    // считываем длину
    if (**p == 'h' || **p == 'l') {
        if (**p == 'h')
            ex->length = 'h';  // short int или unsigned short int
        else if (**p == 'l')
            ex->length = 'l';  // long int или unsigned long int
        (*p)++;
        (*format_len)--;
    }
    if (s21_strpbrk(*p, "cdifsu%")) {
        ex->spec = **p;
        (*p)++;
        (*format_len)--;
    }
}

char *s21_itoa(long long num, int base) {
    static char buf[21];
    for (int k = 0; k < 21; k++) buf[k] = '\0';
    int i = 19;
    if (num == 0) {
        buf[i] = '0';
        i--;
    }
    if (isfinite((double)num)) {
        num = (signbit((double)num)) ? -num : num;
        for (; num != 0 && i; i--, num /= base) {
            buf[i] = "0123456789abcdef"[num % base];
        }
    } else {
        s21_strcat(buf, "inf");
    }
    return &buf[i + 1];
}

char *s21_ftoa(double num, int accuracy) {
    static char res[1000];
    for (int k = 0; k < 1000; k++) res[k] = '\0';
    char zeroFlag[100] = {'\0'};
    int i = 0;
    long long intNum = 0;

    if (accuracy == -1) accuracy = 6;

    if (isfinite(num)) {
        num = (signbit(num)) ? -num : num;
        if (accuracy == -20 || accuracy == -2) {
            num = s21_round(num);
            intNum = num;
            char *temp = s21_itoa(intNum, 10);
            s21_strcat(res, temp);
        } else {
            intNum = num;
            char *temp = s21_itoa(intNum, 10);
            s21_strcat(res, temp);
            num -= intNum;
            if (num < 0) num++;
            int j = accuracy;
            while (j-- > 0) {
                zeroFlag[i++] = '0';
            }
            if (accuracy > 0) {
                int nulls;
                s21_strcat(res, ".");
                num *= pow(10, accuracy);
                num = round(num);
                temp = s21_itoa(num, 10);
                nulls = accuracy - s21_strlen(temp);
                s21_strcpy(zeroFlag + nulls, temp);
                s21_strcat(res, zeroFlag);
            }
            temp = s21_NULL;
        }
    } else {
        s21_strcat(res, "inf");
    }
    return &res[0];
}

void s21_write(char *str, int *j, struct specifier *ex, va_list *arg) {
    int neg = 0;
    long long num = 0;
    double numFloat = 0;
    int str_len = 0;
    char *s = s21_NULL;
    int len = 0;
    char *s_num = s21_NULL;
    int flag_spaces = 0;
    unsigned long long int u_num = 0;
    switch (ex->spec) {
        case ('c'):
            if (ex->info[0]) {
                str[*j] = va_arg(*arg, int);
                (*j)++;
                if (ex->info[3]) {
                    while ((ex->info[3] - 1) > 0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
            } else {
                if (ex->info[3]) {
                    while ((ex->info[3] - 1) > 0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
                str[*j] = va_arg(*arg, int);
                (*j)++;
            }
            break;
        case ('s'):
            s = va_arg(*arg, char *);
            str_len = s21_strlen(s);
            if (ex->info[4] == -1 || ex->info[4] > str_len)
                ex->info[4] = str_len;
            if (ex->info[4] == -2 || ex->info[4] == -20) ex->info[4] = 0;
            if (ex->info[0]) {
                s21_strncpy(str + *j, s, ex->info[4]);
                (*j) += ex->info[4];
                if (ex->info[3]) {
                    while ((ex->info[3] - ex->info[4]) > 0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
            } else {
                if (ex->info[3]) {
                    while ((ex->info[3] - ex->info[4]) > 0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
                s21_strncpy(str + *j, s, ex->info[4]);
                (*j) += ex->info[4];
                str[*j] = '\0';
            }
            break;
        case ('i'):
        case ('d'):
            switch (ex->length) {
                case ('h'):
                    num = (short int)va_arg(*arg, int);
                    break;
                case ('l'):
                    num = va_arg(*arg, long long);
                    break;
                default:
                    num = va_arg(*arg, int);
            }
            neg = signbit((double)num);
            s_num = s21_itoa(num, 10);
            len = s21_strlen(s_num);
            if (ex->info[4] < 0) ex->info[4] = 0;
            if (neg || (ex->info[1] && !neg && !ex->info[2]) ||
                (ex->info[2] && !neg))
                flag_spaces++;
            if (ex->info[0]) {
                if (neg) {
                    str[*j] = '-';
                    (*j)++;
                }
                if (ex->info[1] && !neg && !ex->info[2]) {
                    str[*j] = '+';
                    (*j)++;
                }
                if (ex->info[2] && !neg) {
                    str[*j] = ' ';
                    (*j)++;
                }
                int len_prec = ex->info[4];
                if (len_prec) {
                    while (len_prec - len > 0) {
                        str[*j] = '0';
                        (*j)++;
                        len_prec--;
                    }
                }
                s21_strcpy(str + *j, s_num);
                (*j) += len;
                if (ex->info[4] >= len) flag_spaces += -len;
                if (ex->info[3]) {
                    while ((ex->info[3] - flag_spaces - len - ex->info[4]) >
                           0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
            } else {
                if (ex->info[4] >= len) flag_spaces += -len;
                if (ex->info[3]) {
                    while ((ex->info[3] - flag_spaces - len - ex->info[4]) >
                           0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
                if (neg) {
                    str[*j] = '-';
                    (*j)++;
                }
                if (ex->info[1] && !neg && !ex->info[2]) {
                    str[*j] = '+';
                    (*j)++;
                }
                if (ex->info[2] && !neg) {
                    str[*j] = ' ';
                    (*j)++;
                }
                int len_prec = ex->info[4];
                if (len_prec) {
                    while (len_prec - len > 0) {
                        str[*j] = '0';
                        (*j)++;
                        len_prec--;
                    }
                }
                s21_strcpy(str + *j, s_num);
                (*j) += len;
            }
            break;
        case ('u'):
            switch (ex->length) {
                case ('h'):
                    u_num = (unsigned short int)va_arg(*arg, int);
                    break;
                case ('l'):
                    u_num = va_arg(*arg, unsigned long long);
                    break;
                default:
                    u_num = (unsigned int)va_arg(*arg, long long);
            }
            s_num = s21_itoa(u_num, 10);
            len = s21_strlen(s_num);
            if ((ex->info[1] && !ex->info[2]) || ex->info[2]) flag_spaces++;
            if (ex->info[4] < 0) ex->info[4] = 0;
            if (ex->info[0]) {
                if (ex->info[1] && !ex->info[2]) {
                    str[*j] = '+';
                    (*j)++;
                }
                if (ex->info[2]) {
                    str[*j] = ' ';
                    (*j)++;
                }
                int len_prec = ex->info[4];
                if (len_prec) {
                    while (len_prec - len > 0) {
                        str[*j] = '0';
                        (*j)++;
                        len_prec--;
                    }
                }
                s21_strcpy(str + *j, s_num);
                (*j) += len;
                if (ex->info[4] >= len) flag_spaces += -len;
                if (ex->info[3]) {
                    while ((ex->info[3] - len - flag_spaces - ex->info[4]) >
                           0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
            } else {
                if (ex->info[4] >= len) flag_spaces += -len;
                if (ex->info[3]) {
                    while ((ex->info[3] - len - flag_spaces - ex->info[4]) >
                           0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
                if (ex->info[1] && !ex->info[2]) {
                    str[*j] = '+';
                    (*j)++;
                }
                if (ex->info[2]) {
                    str[*j] = ' ';
                    (*j)++;
                }
                int len_prec = ex->info[4];
                if (len_prec) {
                    while (len_prec - len > 0) {
                        str[*j] = '0';
                        (*j)++;
                        len_prec--;
                    }
                }
                s21_strcpy(str + *j, s_num);
                (*j) += len;
            }
            break;
        case ('f'):
            numFloat = va_arg(*arg, double);
            neg = signbit(numFloat);
            s_num = s21_ftoa(numFloat, ex->info[4]);
            len = s21_strlen(s_num);
            if (neg || (ex->info[1] && !neg && !ex->info[2]) ||
                (ex->info[2] && !neg))
                flag_spaces++;
            if (ex->info[0]) {
                if (neg) {
                    str[*j] = '-';
                    (*j)++;
                }
                if (ex->info[1] && !neg && !ex->info[2]) {
                    str[*j] = '+';
                    (*j)++;
                }
                if (ex->info[2] && !neg) {
                    str[*j] = ' ';
                    (*j)++;
                }
                if (ex->info[4] < 0) ex->info[4] = 0;
                s21_strcpy(str + *j, s_num);
                (*j) += len;
                if (ex->info[3] > 0 && ex->info[4] == 0) {
                    while ((ex->info[3] - len - flag_spaces - ex->info[4]) >
                           0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
            } else {
                if (ex->info[4] == -2 || ex->info[4] == -20) ex->info[4] = 0;
                if (ex->info[3] > 0) {
                    while ((ex->info[3] - len - flag_spaces) > 0) {
                        str[*j] = ' ';
                        (*j)++;
                        ex->info[3]--;
                    }
                }
                if (neg) {
                    str[*j] = '-';
                    (*j)++;
                }
                if (ex->info[1] && !neg && !ex->info[2]) {
                    str[*j] = '+';
                    (*j)++;
                }
                if (ex->info[2] && !neg) {
                    str[*j] = ' ';
                    (*j)++;
                }
                s21_strcpy(str + *j, s_num);
                (*j) += len;
            }
            break;
        case ('%'):
            str[*j] = '%';
            (*j)++;
            break;
    }
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list arg;  // storing a variable-length argument list
    va_start(arg, format);

    int j = 0;  // counter for elements in str
    struct specifier ex;

    int format_len = s21_strlen(format);

    for (char *p = (char *)format; format_len > 0;) {
        if (*p == '%') {
            full_with_zeroes_specifier(&ex);
            p++;
            format_len--;
            read_flag(&ex, &p, &format_len);
            s21_write(str, &j, &ex, &arg);
        }
        if (*p != '\0' && *p != '%') {
            str[j] = *p;
            j++;
            p++;
            format_len--;
        }
    }
    str[j] = '\0';

    va_end(arg);
    return j;
}
