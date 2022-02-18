#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of columns to sum (supplied in command line)
int n;

// File pointer to the file to be summed
FILE* fp;

// The buffer reader that reads each line of input
char buffer[255];

// The file name (supplied in command line)
char* fileName;

// The delimiter to separate numbers in a line of text
char* delim;

// Holds the sum of the matrix
int sum;

// Keeps count of how many columns have been summed for each row
int j;

// Each number that is read from the file
int number;

// The size of the file
int size;

// Function to open a file
FILE* openFile();

// Function to sum a matrix
int summatrix();

int main(int argc, char*argv[]) {
  // Check command line arguments validity (did user supply file name and # of columns?)
  if(argv[2] == NULL || argv[1] == NULL) {
    exit(0);
  }
  n = atoi(argv[2]);
  fileName = argv[1];
  fp = openFile(fileName);
  sum = summatrix(fp);
  fclose(fp);
  printf("Sum: %d\n", sum);
  return 0;
}

FILE* openFile(char* fileName) {
  if(fileName == NULL) {
    fprintf(stderr, "No file name supplied\n");
    exit(0);
  }

  fp = fopen(fileName, "r");
  if(fp == NULL) {
    fprintf(stderr, "range: cannot open file\n");
    exit(1);
  }
  
  return fp;
}

int summatrix(FILE* file) {
  sum = 0;
  j = 0;
  while(fgets(buffer, 255, fp)) {
    delim = strtok(buffer, " ");
    j = 0;
    while(delim != NULL) {
      if(j == n) {
        break;
      }
      number = atoi(delim);
      if(number >= 0) {
        sum += number;
      } else {
        fprintf(stderr, "Warning - Value %d found.\n", number);
      }
      delim = strtok(NULL, " ");
      j++;
    }
  }
  return sum;
}