#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Number of columns to sum (supplied in command line)
int n;

// Used to store two ends of first pipe
int fd[2];

// Number of files supplied in command line
int numFiles;

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

// Total sum of all matrices
int totalSum;

// Function to open a file
FILE* openFile();

// Function to sum a matrix
int summatrix();

int main(int argc, char*argv[]) {
  // Check command line arguments validity (did user supply file name and # of columns?)
  if(argv[2] == NULL || argv[1] == NULL) {
    exit(0);
  }
  
  if(pipe(fd) == -1) {
    return -1;
  };
  numFiles = argc - 2;

  //Ensure the "first" child has something to read so no deadlock
  int initialNum = 0;
  if(write(fd[1], &initialNum, sizeof(initialNum)) == -1) {
    return -1;
  };

  for(int i = 0; i < numFiles; i++) {
    int pid = fork();
    if(pid == 0) {
      int thisSum = 0;
      n = atoi(argv[argc - 1]);
      fileName = argv[i + 1];
      fp = openFile(fileName);
      thisSum = summatrix(fp);
      int prevSum;
      if(read(fd[0], &prevSum, sizeof(prevSum)) == -1) {
        return -1;
      };
      int added = prevSum + thisSum;
      if(write(fd[1], &added, sizeof(added)) == -1) {
        return -1;
      };
      fclose(fp);
      return 0;
    }
  }
  
  while(wait(NULL) > 0);
  
  if(read(fd[0], &totalSum, sizeof(totalSum)) == -1) {
    return -1;
  };
  
  printf("Sum: %d\n", totalSum);
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
