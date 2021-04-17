#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void merge(int array[], int begin, int middle, int end) {
  int firstSlice = begin;
  int secondSlice = middle + 1;
  int size = end - begin + 1;
  int auxIndex = 0;
  int *auxArray = (int*)malloc(size * sizeof(int));

  while(firstSlice <= middle && secondSlice <= end) {
    if(array[firstSlice] < array[secondSlice]) {
      // Adding values on aux array when first slice values is smaller than second slice 
      auxArray[auxIndex] = array[firstSlice];
      firstSlice++;
    } else {
      auxArray[auxIndex] = array[secondSlice];
      secondSlice++;
    }
    auxIndex++;
  }

  // If first slice yet have values
  while(firstSlice <= middle) {
    auxArray[auxIndex] = array[firstSlice];
    auxIndex++;
    firstSlice++;
  }

  // If second slice yet have values
  while (secondSlice <= end) {
    auxArray[auxIndex] = array[secondSlice];
    auxIndex++;
    secondSlice++;
  }
  
  // Move the elements to original array
  for(auxIndex = begin; auxIndex <= end; auxIndex++) {
    array[auxIndex] = auxArray[auxIndex - begin];
  }

  free(auxArray);
}

void mergeSort(int array[], int begin, int end) {
  if(begin < end) {
    int middle = (end + begin) / 2;

    mergeSort(array, begin, middle);
    mergeSort(array, middle + 1, end);
    merge(array, begin, middle, end);
  }
}

void addArrayValues(int array[], int size) {
  int value = SIZE;
  for(int i = 0; i < size; i++) {
    array[i] = (value--) * 10;
  }
}

void printArrayValues(int array[], int size, char* message) {
  printf("%s\n", message);
  for(int i = 0; i < size; i++) {
    printf("[%d]", array[i]);
  }
  printf("\n");
  printf("----------------\n");
}

int main() {
  int array[SIZE];

  addArrayValues(array, SIZE);

  printArrayValues(array, SIZE, "Inserting data on Array");

  mergeSort(array, 0, SIZE - 1);

  printArrayValues(array, SIZE, "Using merge sort");

  return 1;
}