#include <stdio.h>

void bubbleSort(int* arr, int length) {
    int i, j, temp;

    for(i=0; i<length; i++) {
        for(j=0; j<length-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(void) {
    int i;
    int length = 3;
    int array[length];
    
    scanf("%d %d %d", &array[0], &array[1], &array[2]);
    bubbleSort(array, length);
    
    for(i=0; i<length; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
