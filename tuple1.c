#include <stdio.h>
#include <stdlib.h>

int** allocMatrix(int r, int c) {
    int **mat = malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) mat[i] = malloc(c * sizeof(int));
    return mat;
}

void inputMatrix(int **mat, int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            scanf("%d", &mat[i][j]);
}

void writeToFile(const char *f, int **mat, int r, int c) {
    FILE *fp = fopen(f, "w");
    fprintf(fp, "%d %d\n", r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            fprintf(fp, "%d ", mat[i][j]);
    fclose(fp);
}

int** readFromFile(const char *f, int *r, int *c) {
    FILE *fp = fopen(f, "r");
    fscanf(fp, "%d %d", r, c);
    int **mat = allocMatrix(*r, *c);
    for (int i = 0; i < *r; i++)
        for (int j = 0; j < *c; j++)
            fscanf(fp, "%d", &mat[i][j]);
    fclose(fp);
    return mat;
}

void printTriplet(int **mat, int r, int c) {
    printf("\nTriplet Form (row col value):\n");
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (mat[i][j])
                printf("%d %d %d\n", i, j, mat[i][j]);
}

int main() {
    int r, c;
    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);

    int **mat = allocMatrix(r, c);
    printf("Enter matrix elements:\n");
    inputMatrix(mat, r, c);
    writeToFile("matrix.txt", mat, r, c);

    int r2, c2;
    int **mat2 = readFromFile("matrix.txt", &r2, &c2);
    printTriplet(mat2, r2, c2);

    for (int i = 0; i < r; i++) free(mat[i]);
    for (int i = 0; i < r2; i++) free(mat2[i]);
    free(mat); free(mat2);
    return 0;
}
