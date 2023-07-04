#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

typedef struct {
    size_t w, h;
    size_t **cols;
} matrix_t;

matrix_t *matrix_create(const size_t width, const size_t height) {
    matrix_t *object = malloc(sizeof(matrix_t));
    object->w = width;
    object->h = height;

    size_t latest_n = 1;
    size_t **cols = malloc(sizeof(size_t*) * height);
    for (size_t col_index = 0; col_index < height; ++col_index) {
        cols[col_index] = malloc(sizeof(size_t) * width);

        size_t *const row = cols[col_index];
        for (size_t row_index = 0; row_index < width; ++row_index)
            row[row_index] = latest_n++;
    }
    object->cols = cols;

    return object;
}

void matrix_destroy(matrix_t **const pobject) {
    matrix_t* const object = *pobject;
    size_t **const cols = object->cols;
    
    const size_t height = object->h;
    for (size_t col_index = 0; col_index < height; ++col_index)
        free(cols[col_index]);
    free(cols);
    free(object);
    (*pobject) = NULL;
}

void matrix_print(const matrix_t *const object) {
    const size_t height = object->h;
    const size_t width = object->w;

    size_t **const cols = object->cols;
    for (size_t col_index = 0; col_index < height; ++col_index) {
        const size_t *row = cols[col_index];

        for (size_t row_index = 0; row_index < width; ++row_index)
            printf("(%zu, %zu): %zu\n", col_index, row_index, row[row_index]);
    }
}

size_t zufromstr(const char *str) {
    size_t number = 0;
    for (char ch = *str; ch != '\0'; ch = *(++str)) {
        number = number * 10 + (ch - '0');
    }
    return number;
}

int main(const int argc, const char *const *const argv) {
    if (argc != 3) {
        puts("2 Arguments needed\nUsage:\n\tgenerate_matrix <width> <height>");
        return 0;
    }

    const size_t width = zufromstr(argv[1]);
    const size_t height = zufromstr(argv[2]);
    
    matrix_t *matrix = matrix_create(width, height);
    matrix_print(matrix);
    matrix_destroy(&matrix);

    assert(matrix == NULL);
    return 0;
}