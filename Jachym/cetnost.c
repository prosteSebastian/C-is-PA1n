#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Name {
    char* str;
    int count;
} N;

typedef struct NameArray {
    N** names;
    int size;
    int max;
} Na;


N* name_init(char* name) {
    N* new_name = (N *)malloc(sizeof(N));

    new_name -> str = name;
    new_name -> count = 1;

    return new_name;
}


void name_free(N* name) {
    free(name -> str);
    free(name);
}


Na* array_init() {
    Na* array = (Na *)malloc(sizeof(Na));

    array -> names = NULL;
    array -> size = 0;
    array -> max = 0;

    return array;
}


void array_realloc(Na* array) {
    if (array -> size < array -> max) {
        return;
    }

    array -> max += 4;
    array -> max *= 2;
    array -> names = (N **)realloc(array -> names, array -> max * sizeof(N *));
}


int array_has_name(Na* array, char* name) {
    for (int i = 0; i < array -> size; i++) {
        N* element = array -> names[i];
        if (strcmp(element -> str, name) == 0) {
            element -> count++;
            return 1;
        }
    }

    return 0;
}


void array_push(Na* array, char* name) {
    array_realloc(array);

    if (array_has_name(array, name)) {
        return;
    }

    N* new_name = name_init(strdup(name));
    array -> names[array -> size] = new_name;
    array -> size++;
}


void array_free(Na* array) {
    for (int i = 0; i < array -> size; i++) {
        name_free(array -> names[i]);
    }

    free(array -> names);
    free(array);
}


int count_max(Na* array) {
    int count = 0;
    int max = array -> names[0] -> count;
    for (int i = 0; i < array -> size; i++) {
        if (array -> names[i] -> count == max) {
            count++;
        }
    }

    return count;
}


int compare(const void* a, const void* b) {
    N* ptr_a = *(N**)a;
    N* ptr_b = *(N**)b;

    return ptr_b -> count >+ ptr_a -> count;
}


void array_sort(Na* array) {
    qsort(array -> names, array -> size, sizeof(array -> names[0]), compare);
}



void array_print(Na* array) {
    array_sort(array);
    int count = count_max(array);
    printf("Nejcastejsi jmeno: %d x\n", array -> names[0] -> count);
    for (int i = 0; i < count; i++) {
        printf("%s\n", array -> names[i] -> str);
    }
}


void read_name(char* line, Na* array) {
    char* token = strtok(line, " ");
    char* last = NULL;

    while (token) {
        char* name = token;
        token = strtok(NULL, " ");

        if (token) {
            array_push(array, name);
        }
    }
    
    free(last);
    free(token);
}


int main() {
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;
    Na* array = array_init();

    while ((nread = getline(&line, &len, stdin)) != -1) {
        read_name(line, array);
    }

    array_print(array);
    free(line);
    array_free(array);

    return 0;
}