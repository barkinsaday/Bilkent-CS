/*
* Title: sorting Algorithms and Efficiency
* Author: Barkýn Saday
* ID: 21902967
* Section: 1
* Assignment: 1
* Description: Main file for Homework 1 CS202
*/
#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

void insertionSort(int *arr, const int size, int &compCount, int &moveCount);
void bubbleSort(int *arr, const int size, int &compCount, int &moveCount);
void mergeSort(int *arr, const int size, int &compCount, int &moveCount);
void quickSort(int *arr, const int size, int &compCount, int &moveCount);

//my functions
void myMerge(int *arr, int first, int mid, int last, int &compCount, int &moveCount, int maxSize);
void myMergeSort(int *arr, int first, int last, int &compCount, int &moveCount, int maxSize);
int myPartition(int *arr, int first, int last);
void myQuickSort(int *arr, int first, int last, int &compCount, int &moveCount);
#endif // SORTING_H_INCLUDED
