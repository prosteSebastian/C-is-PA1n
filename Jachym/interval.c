#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    int weight;
    int from;
    int to;
} I;


typedef struct IntervalArray {
    I** ins;
    int size;
    int max;
} Ia;


typedef struct Timeline {
    int* array;
    int start;
    int end;
} T;


Ia* array_init() {
    Ia* array = (Ia *)malloc(sizeof(Ia));

    array -> ins = NULL;
    array -> size = 0;
    array -> max = 0;

    return array;
}


void array_realloc(Ia* array) {
    if (array -> size < array -> max) {
        return;
    }

    array -> max += 4;
    array -> max *= 2;
    array -> ins = (I **)realloc(array -> ins, array -> max * sizeof(I *));
}


void array_push(Ia* array, I* in) {
    array_realloc(array);

    array -> ins[array -> size] = in;
    array -> size++;
}


void array_free(Ia* array) {
    for (int i = 0; i < array -> size; i++) {
        free(array -> ins[i]);
    }

    free(array -> ins);
    free(array);
}


int find_end(Ia* array) {
    int max = array -> ins[0] -> to;

    for (int i = 1; i < array -> size; i++) {
        int current_start = array -> ins[i] -> to;

        if (current_start > max) {
            max = current_start;
        }
    }

    return max;
}


int find_start(Ia* array) {
    int min = array -> ins[0] -> from;

    for (int i = 1; i < array -> size; i++) {
        int current_start = array -> ins[i] -> from;

        if (current_start < min) {
            min = current_start;
        }
    }

    return min;
}


I* in_init(int weight, int from, int to) {
    I* in = (I *)malloc(sizeof(I));

    in -> weight = weight;
    in -> from = from;
    in -> to = to;

    return in;
}


int in_read(Ia* array) {
    int weight, from, to;

    int code = scanf("%d: %d..%d", &weight, &from, &to);

    if (code == EOF) return EOF;

    I* interval = in_init(weight, from, to);

    array_push(array, interval);

    return 1;
}


void set_timeline(T* timeline, I* in) {
    for (int i = in -> from; i < in -> to; i++) {
        timeline -> array[i - timeline -> start] += in -> weight;
    }
}


void timeline_occupy(T* timeline, Ia* array) {
    for (int i = 0; i < array -> size; i++) {
        set_timeline(timeline, array -> ins[i]);
    }
}


T* timmeline_init(Ia* array) {
    T* timeline = (T *)malloc(sizeof(T));
    int min = find_start(array);
    int max = find_end(array);

    timeline -> array = (int *)calloc((max - min), sizeof(int));
    timeline -> start = min;
    timeline -> end = max;

    timeline_occupy(timeline, array);

    return timeline;
}


void timeline_free(T* timeline) {
    free(timeline -> array);
    free(timeline);
}


int max_weight(T* timeline) {
    int min = timeline -> array[0];
    for (int i = 0; i < timeline -> end - timeline -> start; i++) {
        if (timeline -> array[i] > min) {
            min = timeline -> array[i];
        }
    }

    return min;
}


void make_intervals(T* timeline) {
    int weight = max_weight(timeline);
    int from;
    int to;
    printf("Nevyssi zates: %d\n", weight);
    for (int i = 0; i < timeline -> end - timeline -> start; i++) {
        int w = timeline -> array[i];
        int w_b = timeline -> array[i - 1];
        int w_a = timeline -> array[i + 1];

        if (w == weight && w_b != weight) {
            from = timeline -> start + i;
        }

        if (w == weight && w_a != weight) {
            to = timeline -> start + i;
            printf("%d..%d\n", from, to + 1);
        }

    }
}


int main() {
    Ia* array = array_init();

    printf("Zatez:\n");
    while (in_read(array) != EOF) {
    }

    T* timeline = timmeline_init(array);
    printf("\n");
    make_intervals(timeline);
    timeline_free(timeline);


    array_free(array);
    return 0;
}