#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    // + dist height
    int dist;
    int height;
} P;

typedef struct PointArray {
    Point** ps;
    int size;
    int max;
} Pa;


Pa* arr_init() {
    Pa* arr = (Pa *)malloc(sizeof(Pa));

    arr -> ps = NULL;
    arr -> size = 0;
    arr -> max = 0;

    return arr;
}


void arr_push(Pa* arr, P* p) {
    if (arr -> size >= arr -> max) {
        arr -> max = arr -> max * 2 + 4;
        arr -> ps = (P **)realloc(arr -> ps, arr -> max * sizeof(P *));
    }

    arr -> ps[arr -> size] = p;
    arr -> size++;
}


P* p_init(int dist, int height) {
    P* p = (P *)malloc(sizeof(P));

    p -> dist = dist;
    p -> height = height;

    return p;
}


void arr_free(Pa* arr) {
    for (int i = 0; i < arr -> size; i++) {

        printf("Here 1\n");
        free(arr -> ps[i]);
    }

    free(arr -> ps);
    free(arr);
}


void read_start(Pa* arr) {
    // start is always 0km -> is speacial case
    P* start = p_init(0, 0);
    scanf("%d", &start -> height);
    arr_push(arr, start);
}


int read_point(Pa* arr) {
    // save input to struct
    // don't have to sanitize
    int d, h;

    if (scanf(" + %d %d", &d, &h) == EOF) return 0;

    P* p = p_init(d, h);

    arr_push(arr, p);

    return 1;
}


void p_print(P* p) {
    printf("%d (%d)", p -> dist, p -> height);
}


void path_print(P* a, P* b) {
    printf("+ ");
    p_print(a);
    printf(" -> ");
    printf("+ ");
    p_print(b);
    printf("\n");
}


void arr_print(Pa* arr) {
    // out array is pairs (a -> b)
    for (int i = 0; i < arr -> size - 1; i += 2) {
        path_print(arr -> ps[i], arr -> ps[i + 1]);
    }
}


int is_ok(Pa* arr) {
    // actually has some descent
    P* max = arr -> ps[0];

    for (int i = 1; i < arr -> size; i++) {
        P* p = arr -> ps[i];

        if (p -> height <= max -> height) {
            // found descent
            return 1;
        }

        max = p;
    }

    return 0;
}


int is_better_path(P* a, P* b, P* max, P* min) {
    // has bigger descent
    // has to be longer since we're only looping forward
    // from the current element
    int descent = max -> height - min -> height;
    int temp_desc = a -> height - b -> height;

    // climb
    if (temp_desc < 0) return 0;

    // finding first viable point
    if (descent < 0) {
        return 1;
    }

    // found one
    if (temp_desc >= descent) {
        return 1;
    }

    return 0;
}



P* max_diff(Pa* arr) {
    // points with the biggest descent and longest path
    // first 2 don't have to be valid
    P* max = arr -> ps[0];
    P* min = arr -> ps[1];

    for (int i = 0; i < arr -> size - 1; i++) {
        P* a = arr -> ps[i];

        for (int j = i + 1; j < arr -> size; j++) {
            P* b = arr -> ps[j];

            if (is_better_path(a, b, max, min)) {
                max = a;
                min = b;
            }
        }
    }

    // encapsulating to make it easier to work with
    return p_init(min -> dist - max -> dist, max -> height - min -> height);
}


int is_variant(P* a, P* b, P* diffs) {
    int dist = b -> dist - a -> dist;
    int height = a -> height - b -> height;

    return dist == diffs -> dist && height == diffs -> height;
}


P* find_diffs(Pa* arr, Pa* arr_out) {
    P* diffs = max_diff(arr);

    for (int i = 0; i < arr -> size - 1; i++) {
        P* a = arr -> ps[i];

        for (int j = i + 1; j < arr -> size; j++) {
            P* b = arr -> ps[j];

            if (is_variant(a, b, diffs)) {
                arr_push(arr_out, a);
                arr_push(arr_out, b);
            }
        }
    }

    return diffs;
}



int main() {
    Pa* arr = arr_init();
    Pa* arr_out = arr_init();

    printf("Cyklotrasa:\n");
    read_start(arr);

    while (read_point(arr))  {
    }

    if (!is_ok(arr)) {
        printf("Nenalezeno\n");
    } else {
        P* diffs = find_diffs(arr, arr_out);
        printf("\n%d km, klesani: %d m, varianty: %d\n", diffs -> dist, diffs -> height, arr_out -> size / 2);
        arr_print(arr_out);
        free(diffs);
    }

    printf("Regular free\n");
    arr_free(arr);
    // points were freed
    free(arr_out -> ps);
    free(arr_out);;
    return 0;
}