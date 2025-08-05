#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct matrix {
    int row;
    int col;
    int** data;
} matrix;

void initialize_matrix(matrix* m, int row, int col) {
    int i;
    m->row = row;
    m->col = col;
    m->data = (int**) malloc(row * sizeof(int*));
    for (i = 0; i < row; i++) {
        m->data[i] = (int*) calloc(col, sizeof(int));  // safer: sets all to 0
    }
}

void populate_matrix(matrix* m, int percent, int ll, int ul) {
    int i, j;
    for (i = 0; i < m->row; i++) {
        for (j = 0; j < m->col; j++) {
            if ((rand() % 100) < (100 - percent)) {
                m->data[i][j] = (rand() % (ul - ll + 1)) + ll;
            } else {
                m->data[i][j] = 0;
            }
        }
    }
}

void print_matrix(matrix m) {
    int i, j;
    for (i = 0; i < m.row; i++) {
        for (j = 0; j < m.col; j++) {
            printf("%d ", m.data[i][j]);
        }
        printf("\n");
    }
}

int count_nnz(matrix m) {
    int i, j, count = 0;
    for (i = 0; i < m.row; i++) {
        for (j = 0; j < m.col; j++) {
            if (m.data[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}

void populate_tuple(matrix* t, matrix* m, int nnz) {
    t->data[0][0] = m->row;
    t->data[0][1] = m->col;
    t->data[0][2] = nnz;

    int i, j, k = 1;
    for (i = 0; i < m->row; i++) {
        for (j = 0; j < m->col; j++) {
            if (m->data[i][j] != 0) {
                t->data[k][0] = i;
                t->data[k][1] = j;
                t->data[k][2] = m->data[i][j];
                k++;
            }
        }
    }
}

matrix add_tuple(matrix t1, matrix t2) {
    if (t1.data[0][0] != t2.data[0][0] || t1.data[0][1] != t2.data[0][1]) {
        printf("The two matrices can't be added.\n");
        exit(1);
    }

    matrix result;
    int i = 1, j = 1, k = 1;
    int rows = t1.data[0][2] + t2.data[0][2] + 1;
    initialize_matrix(&result, rows, 3);

    while (i <= t1.data[0][2] && j <= t2.data[0][2]) {
        if ((t1.data[i][0] < t2.data[j][0]) ||
            (t1.data[i][0] == t2.data[j][0] && t1.data[i][1] < t2.data[j][1])) {
            result.data[k][0] = t1.data[i][0];
            result.data[k][1] = t1.data[i][1];
            result.data[k][2] = t1.data[i][2];
            i++;
        } else if ((t2.data[j][0] < t1.data[i][0]) ||
                   (t2.data[j][0] == t1.data[i][0] && t2.data[j][1] < t1.data[i][1])) {
            result.data[k][0] = t2.data[j][0];
            result.data[k][1] = t2.data[j][1];
            result.data[k][2] = t2.data[j][2];
            j++;
        } else {
            int sum = t1.data[i][2] + t2.data[j][2];
            if (sum != 0) {
                result.data[k][0] = t1.data[i][0];
                result.data[k][1] = t1.data[i][1];
                result.data[k][2] = sum;
                k++;
            }
            i++;
            j++;
            continue;
        }
        k++;
    }

    while (i <= t1.data[0][2]) {
        result.data[k][0] = t1.data[i][0];
        result.data[k][1] = t1.data[i][1];
        result.data[k][2] = t1.data[i][2];
        i++;
        k++;
    }

    while (j <= t2.data[0][2]) {
        result.data[k][0] = t2.data[j][0];
        result.data[k][1] = t2.data[j][1];
        result.data[k][2] = t2.data[j][2];
        j++;
        k++;
    }

    result.data[0][0] = t1.data[0][0];
    result.data[0][1] = t1.data[0][1];
    result.data[0][2] = k - 1;
    result.row = k;
    result.col = 3;

    return result;
}

void free_matrix(matrix* m) {
    for (int i = 0; i < m->row; i++) {
        free(m->data[i]);
    }
    free(m->data);  // don't forget this!
}

int main() {
    srand(time(0));

    matrix m1, m2, t1, t2, final_tuple;

    initialize_matrix(&m1, 3, 3);
    initialize_matrix(&m2, 3, 3);

    populate_matrix(&m1, 50, 1, 10);
    populate_matrix(&m2, 50, 1, 10);

    int nnz1 = count_nnz(m1);
    int nnz2 = count_nnz(m2);

    initialize_matrix(&t1, nnz1 + 1, 3);
    initialize_matrix(&t2, nnz2 + 1, 3);

    populate_tuple(&t1, &m1, nnz1);
    populate_tuple(&t2, &m2, nnz2);

    printf("Tuple 1:\n");
    print_matrix(t1);
    printf("\nTuple 2:\n");
    print_matrix(t2);
    printf("\nSum:\n");

    final_tuple = add_tuple(t1, t2);
    print_matrix(final_tuple);

    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&t1);
    free_matrix(&t2);
    free_matrix(&final_tuple);

    return 0;
}
