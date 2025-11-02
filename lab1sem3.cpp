#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

struct student {
    char famil[20];
    char name[20];
    char facult[20];
    char Nomzach[20];
};

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Ru");
    srand(time(NULL));

    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Ошибка: размер массива должен быть положительным!\n");
        return 1;
    }

    int minA, maxA;
    printf("Введите диапазон значений (min max): ");
    scanf("%d %d", &minA, &maxA);

    if (minA > maxA) {
        printf("Ошибка: минимальное значение не может быть больше максимального!\n");
        return 1;
    }

    int* array = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        array[i] = rand() % (maxA - minA + 1) + minA;
    }

    int min = array[0], max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] < min) min = array[i];
        if (array[i] > max) max = array[i];
    }

    printf("Массив: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Min = %d, Max = %d\n", min, max);
    printf("Разница = %d\n", max - min);

    free(array);

    int rows, cols;
    int minM, maxM;

    printf("Введите количество строк: ");
    scanf("%d", &rows);
    printf("Введите количество столбцов: ");
    scanf("%d", &cols);

    printf("Введите диапазон значений (min max): ");
    scanf("%d %d", &minM, &maxM);

    if (rows <= 0 || cols <= 0 || minM > maxM) {
        printf("Ошибка ввода данных!\n");
        return 1;
    }

    int** matrix = (int**)malloc(rows * sizeof(int*));
    int* row_sums = (int*)malloc(rows * sizeof(int));
    int* col_sums = (int*)malloc(cols * sizeof(int));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d!\n", i);
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            free(row_sums);
            free(col_sums);
            return 1;
        }
    }

    memset(row_sums, 0, rows * sizeof(int));
    memset(col_sums, 0, cols * sizeof(int));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (maxM - minM + 1) + minM;
            row_sums[i] += matrix[i][j];
            col_sums[j] += matrix[i][j];
        }
    }

    printf("\nСгенерированный массив %dx%d:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nСуммы по строкам:\n");
    for (int i = 0; i < rows; i++) {
        printf("Строка %d: %d\n", i + 1, row_sums[i]);
    }

    printf("\nСуммы по столбцам:\n");
    for (int j = 0; j < cols; j++) {
        printf("Столбец %d: %d\n", j + 1, col_sums[j]);
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(row_sums);
    free(col_sums);

    int numStudents;
    printf("Введите количество студентов: ");
    scanf("%d", &numStudents);

    struct student* students = (struct student*)malloc(numStudents * sizeof(struct student));

    for (int i = 0; i < numStudents; i++) {
        printf("\nСтудент %d:\n", i + 1);
        printf("Введите фамилию: ");
        scanf("%19s", students[i].famil);
        printf("Введите имя: ");
        scanf("%19s", students[i].name);
        printf("Введите факультет: ");
        scanf("%19s", students[i].facult);
        printf("Введите номер зачетной книжки: ");
        scanf("%19s", students[i].Nomzach);
    }

    int searchChoice;
    do {
        printf("\nВыберите параметр для поиска:\n");
        printf("1 - По фамилии\n");
        printf("2 - По имени\n");
        printf("3 - По факультету\n");
        printf("4 - По номеру зачетной книжки\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &searchChoice);

        if (searchChoice == 0) break;

        char searchStr[20];
        int found = 0;

        switch (searchChoice) {
        case 1:
            printf("Введите фамилию для поиска: ");
            scanf("%19s", searchStr);
            printf("\nРезультаты поиска по фамилии '%s':\n", searchStr);
            for (int i = 0; i < numStudents; i++) {
                if (strstr(students[i].famil, searchStr) != NULL) {
                    printf("Студент: %s %s, Факультет: %s, Номер зачетки: %s\n",
                        students[i].famil, students[i].name,
                        students[i].facult, students[i].Nomzach);
                    found = 1;
                }
            }
            break;
        case 2:
            printf("Введите имя для поиска: ");
            scanf("%19s", searchStr);
            printf("\nРезультаты поиска по имени '%s':\n", searchStr);
            for (int i = 0; i < numStudents; i++) {
                if (strstr(students[i].name, searchStr) != NULL) {
                    printf("Студент: %s %s, Факультет: %s, Номер зачетки: %s\n",
                        students[i].famil, students[i].name,
                        students[i].facult, students[i].Nomzach);
                    found = 1;
                }
            }
            break;
        case 3:
            printf("Введите факультет для поиска: ");
            scanf("%19s", searchStr);
            printf("\nРезультаты поиска по факультету '%s':\n", searchStr);
            for (int i = 0; i < numStudents; i++) {
                if (strstr(students[i].facult, searchStr) != NULL) {
                    printf("Студент: %s %s, Факультет: %s, Номер зачетки: %s\n",
                        students[i].famil, students[i].name,
                        students[i].facult, students[i].Nomzach);
                    found = 1;
                }
            }
            break;
        case 4:
            printf("Введите номер зачетной книжки для поиска: ");
            scanf("%19s", searchStr);
            printf("\nРезультаты поиска по номеру зачетной книжки '%s':\n", searchStr);
            for (int i = 0; i < numStudents; i++) {
                if (strstr(students[i].Nomzach, searchStr) != NULL) {
                    printf("Студент: %s %s, Факультет: %s, Номер зачетки: %s\n",
                        students[i].famil, students[i].name,
                        students[i].facult, students[i].Nomzach);
                    found = 1;
                }
            }
            break;
        default:
            printf("Неверный выбор!\n");
            continue;
        }

        if (!found) {
            printf("Студенты с указанными параметрами не найдены.\n");
        }
    } while (searchChoice != 0);

    free(students);

    return 0;
}