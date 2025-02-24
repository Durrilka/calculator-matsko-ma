#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int expression();
int term();
int factor();

const char* input; // Указатель на текущую позицию во вводе

// Пропуск пробелов
void skip_spaces() {
    while (isspace(*input)) {
        input++;
    }
}

// Чтение числа
int number() {
    int result = 0;
    while (isdigit(*input)) {
        result = result * 10 + (*input - '0');
        input++;
    }
    return result;
}

// Обработка выражений: + и -
int expression() {
    int value = term();

    while (1) {
        skip_spaces();
        if (*input == '+') {
            input++;
            value += term();
        } else if (*input == '-') {
            input++;
            value -= term();
        } else {
            break;
        }
    }
    return value;
}

// Обработка терминов: * и /
int term() {
    int value = factor();

    while (1) {
        skip_spaces();
        if (*input == '*') {
            input++;
            value *= factor();
        } else if (*input == '/') {
            input++;
            int divisor = factor();
            if (divisor == 0) {
                printf("Ошибка: деление на ноль!\n");
                exit(EXIT_FAILURE);
            }
            value /= divisor;
        } else {
            break;
        }
    }
    return value;
}

// Обработка чисел и скобок
int factor() {
    skip_spaces();
    
    if (*input == '(') {
        input++;
        int value = expression();
        skip_spaces();
        if (*input == ')') {
            input++;
        } else {
            printf("Ошибка: пропущена закрывающая скобка!\n");
            exit(EXIT_FAILURE);
        }
        return value;
    }

    if (isdigit(*input)) {
        return number();
    }

    printf("Ошибка: недопустимый символ '%c'\n", *input);
    exit(EXIT_FAILURE);
}

int main() {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Ошибка: пустой ввод!\n");
        return 1;
    }
    
    input = buffer;
    int result = expression();
    printf("%d\n", result);
    return 0;
}
