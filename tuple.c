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

#include <stdio.h>
#include <stdlib.h>

void inputPoly(int *t, int **c, int **e, const char *name) {
    printf("Enter number of terms in %s polynomial: ", name);
    scanf("%d", t);
    *c = malloc(*t * sizeof(int));
    *e = malloc(*t * sizeof(int));
    if (!*c || !*e) exit(1);
    for (int i = 0; i < *t; i++) {
        printf("Term %d (coeff exponent): ", i + 1);
        scanf("%d %d", &(*c)[i], &(*e)[i]);
    }
}

void displayPoly(int *c, int *e, int t) {
    for (int i = 0; i < t; i++) {
        if (c[i] == 0) continue;
        printf("%dx^%d", c[i], e[i]);
        if (i < t - 1) printf(" + ");
    }
    printf("\n");
}

void addPoly(int *c1, int *e1, int t1, int *c2, int *e2, int t2) {
    int *c3 = malloc((t1 + t2) * sizeof(int));
    int *e3 = malloc((t1 + t2) * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < t1 && j < t2) {
        if (e1[i] > e2[j]) {
            c3[k] = c1[i]; e3[k++] = e1[i++];
        } else if (e1[i] < e2[j]) {
            c3[k] = c2[j]; e3[k++] = e2[j++];
        } else {
            c3[k] = c1[i] + c2[j]; e3[k++] = e1[i]; i++; j++;
        }
    }
    while (i < t1) { c3[k] = c1[i]; e3[k++] = e1[i++]; }
    while (j < t2) { c3[k] = c2[j]; e3[k++] = e2[j++]; }

    printf("\nSum of Polynomials:\n");
    displayPoly(c3, e3, k);
    free(c3); free(e3);
}

void multiplyPoly(int *c1, int *e1, int t1, int *c2, int *e2, int t2) {
    int max = t1 * t2;
    int *ct = malloc(max * sizeof(int));
    int *et = malloc(max * sizeof(int));
    int k = 0;

    for (int i = 0; i < t1; i++)
        for (int j = 0; j < t2; j++) {
            ct[k] = c1[i] * c2[j];
            et[k++] = e1[i] + e2[j];
        }

    int *cf = malloc(k * sizeof(int));
    int *ef = malloc(k * sizeof(int));
    int used[100] = {0}, n = 0;

    for (int i = 0; i < k; i++) {
        if (used[i]) continue;
        int sum = ct[i];
        for (int j = i + 1; j < k; j++)
            if (!used[j] && et[i] == et[j]) {
                sum += ct[j];
                used[j] = 1;
            }
        cf[n] = sum;
        ef[n++] = et[i];
    }

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (ef[j] < ef[j + 1]) {
                int tmp = ef[j]; ef[j] = ef[j + 1]; ef[j + 1] = tmp;
                tmp = cf[j]; cf[j] = cf[j + 1]; cf[j + 1] = tmp;
            }

    printf("\nProduct of Polynomials:\n");
    displayPoly(cf, ef, n);
    free(ct); free(et); free(cf); free(ef);
}

int main() {
    int *c1, *e1, t1, *c2, *e2, t2;
    inputPoly(&t1, &c1, &e1, "First");
    inputPoly(&t2, &c2, &e2, "Second");

    printf("\nFirst Polynomial:\n");
    displayPoly(c1, e1, t1);
    printf("Second Polynomial:\n");
    displayPoly(c2, e2, t2);

    addPoly(c1, e1, t1, c2, e2, t2);
    multiplyPoly(c1, e1, t1, c2, e2, t2);

    free(c1); free(e1); free(c2); free(e2);
    return 0;
}
 