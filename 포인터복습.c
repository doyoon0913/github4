#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int min(int *list, int start, int n) {
    int min_idx = start;
    
    for (int i = start + 1; i < n; i++) {
        if (list[i] < list[min_idx]) {
            min_idx = i; 
        }
    }
    return min_idx;
}
void select_sort(int *list, int n) {
    for (int i = 0; i < n - 1; i++) {

        int min_idx = min(list, i, n);
        swap(&list[i], &list[min_idx]);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int *list = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }
    select_sort(list, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    free(list);

    return 0;
}