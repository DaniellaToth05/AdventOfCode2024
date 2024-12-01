#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1000

/*
    This is my code for the first day of the Advent of Code 2024
    The goal is to pair elements from two lists, such that the smallest number
    in the left list pairs with the smallest number in the right list, and so on.
    Then, the distance between the two numbers needs to be calculated using the formula
    abs(left[i] - right[i]) and the sum of all distances needs to be calculated.
*/

// function prototypes
int calculateDistance(int left[], int right[], int size);
void bubbleSort(int list[], int size);

int main(){

    int left[MAX_SIZE];
    int right[MAX_SIZE];
    int size = 0;
    int result;

    // open the file containing the two lists
    FILE *file;
    file = fopen("AOC_Day1.txt", "r");
    if(file == NULL){
        printf("Sorry, there was an error opening the file!\n");
        return 1;
    }

    // read the two lists from the file
    while(fscanf(file, "%d %d", &left[size], &right[size]) == 2){ // while there are still elements to read, read them and store them in the lists
        size++; // increment the size of the lists
    }

    fclose(file); // close the file

    result = calculateDistance(left, right, size); // calculate the result
    printf("The total distance is: %d\n", result); // print the result  

    return 0;
    
}

// function to calculate the distance between the two indexes of the lists
int calculateDistance(int left[], int right[], int size){

    int totalDistance = 0; // variable to store the total distance
    bubbleSort(left, size); // sort the left list
    bubbleSort(right, size); // sort the right list

    // calculate the distance between the two lists
    for (int i = 0; i < size; i++){
        totalDistance = totalDistance + abs(left[i] - right[i]);
    }

    return totalDistance; // return the total distance

}

// function to sort the list using the bubble sort algorithm
void bubbleSort(int list[], int size){
    // iterate through the list
    for (int i = 0; i < size; i ++){
        // iterate through the list again 
        for(int j = 0; j < size - i - 1; j++){
            // if the current element is greater than the next element, swap them
            if (list[j] > list[j + 1]){
                int temp = list[j]; // store the current element in a temporary variable
                list[j] = list[j + 1]; // set the current element to the next element
                list [j + 1] = temp; // set the next element to the temporary variable
            }
        }
    }
}