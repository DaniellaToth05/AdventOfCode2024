#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_REPORTS 1001
#define MAX_LEVELS 1000

/*
    This is my code for the second day of the Advent of Code 2024

    ** PUZZLE ONE **
    The goal is determine how many reports in a list of numerical sequences
    are considered "safe". Each report is a sequence of numbers, and the criteria 
    for a report being safe are as follows:
        1. The sequence must be strictly increasing or strictly decreasing throughout
        2. The difference between any two consecutive numbers in the sequence must be
           at least 1 and at most 3
    The task is to count how many of these sequences in the provided data are safe based 
    on the above rules.

    ** PUZZLE TWO **


*/

// function prototypes to check if a report is safe
bool isSafe(int report[], int size);
bool isSafeWithDampener(int report[], int size);

int main(){

    int reports[MAX_REPORTS][MAX_LEVELS]; // 2D array to store the reports
    int reportSizes[MAX_REPORTS]; // array to store the sizes of the reports
    int numReports = 0; // variable to store the number of reports
    int safeCount = 0; // variable to store the number of safe reports

    FILE *file = fopen("AOC_Day2.txt", "r");
    if(file == NULL){
        printf("Sorry, there was an error opening the file!\n");
        return 1;
    }

    // while there are still reports to read
    while(!feof(file)){
        int size = 0;
        int level;

        // read the levels of the report while there are still levels to read
        while(fscanf(file, "%d", &level) == 1){
            reports[numReports][size] = level;
            size++;
        

        // if we hit a newline or the end of the file, we know we've reached the end of the report
        if(fgetc(file) == '\n' || feof(file)){
            break;
        }
        fseek(file, -1, SEEK_CUR); // move the file pointer back one character
    }

    reportSizes[numReports] = size; // store the size of the report
    numReports++; // increment the number of reports

    if(numReports >= MAX_REPORTS){
        printf("Sorry, the maximum number of reports has been reached!\n");
        break;
    }

    }
    fclose(file); // close the file

    // check each report to see if it is safe
    for(int i = 0; i < numReports; i++){
        if(isSafeWithDampener(reports[i], reportSizes[i])){
            safeCount++;
        }
    }

    printf("The number of safe reports is: %d\n", safeCount);

    return 0;
}

// function definition to check if a report is safe
bool isSafe(int report[], int size){
    bool isIncreasing = true; // variable to store whether the report is increasing or not
    bool isDecreasing = true; // variable to store whether the report is decreasing or not
    int difference; // variable to store the difference between two consecutive numbers

    for(int i = 0; i < size - 1; i++){
        difference = abs(report[i] - report[i + 1]); // calculate the difference between two consecutive numbers

        if(difference < 1 || difference > 3){ // if the difference is not within the range of 1 to 3, the report is not safe
            return false;
        }

        if(report[i] >= report[i+1]){
            isIncreasing = false; // if the report is not increasing, set the isIncreasing variable to false
        }
        if(report[i] <= report[i+1]){
            isDecreasing = false; // if the report is not decreasing, set the isDecreasing variable to false
        }
    }
    return isIncreasing || isDecreasing; // return true if the report is either increasing or decreasing
}

// function definition to check if a report is safe with a dampener
bool isSafeWithDampener(int report[], int size){
    if(isSafe(report, size)){
        return true;
    }

    // check if removing only one level makes the report safe
    for (int i = 0; i < size; i ++){
        int tempReport[MAX_LEVELS]; // temporary array to store the report
        int tempSize = 0; // variable to store the size of the temporary report

        for (int j = 0; j < size; j++){
            if (j!= i){ // skip the level that is being removed
                tempReport[tempSize] = report[j];
                tempSize++; // increment the size of the temporary report
            }
        }
        // check if the temporary report is safe
        if (isSafe(tempReport, tempSize)){ 
            return true; // the report is safe after removing one level
        }
    }
    return false; // the report is not safe even with the dampener
}