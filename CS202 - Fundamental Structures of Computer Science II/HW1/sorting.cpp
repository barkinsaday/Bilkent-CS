/*
* Title: sorting Algorithms and Efficiency
* Author: Barkýn Saday
* ID: 21902967
* Section: 1
* Assignment: 1
* Description: Main file for Homework 1 CS202
*/
#include "sorting.h"
#include <iostream>
using namespace std;

void insertionSort(int *arr, const int size, int &compCount, int &moveCount)
{
    compCount = 0;
    moveCount = 0;
    int i, key, j;
    for (j = 1; j < size; j++)
    {
        key = arr[j];
        moveCount++;
        i = j - 1;

        while (i >= 0 && arr[i] > key)
        {
            compCount++; //each time we compare arr[i] > key
            arr[i + 1] = arr[i];
            moveCount++;
            i = i - 1;
        }
        arr[i + 1] = key; //data move
        moveCount++;
    }

}

//bubbleSort algorithm from lecture slides (slightly modified)
void bubbleSort(int *arr, const int size, int &compCount, int &moveCount)
{
    compCount = moveCount = 0;
    bool sorted = 0; //assume not sorted by default
    for(int pass = 1; (pass < size ) && !sorted; pass++)
    {
        sorted = 1; // assume it is sorted, it will change to false if not sorted
        for(int i=0; i < size-pass; i++)
        {
            if(arr[i] > arr[i+1])
            {
                compCount++; //compared in if statement
                //swap
                int temp = arr[i];
                moveCount++;
                arr[i] = arr[i+1];
                moveCount++; //moved data
                arr[i+1] = temp;
                moveCount++;//moved data
                sorted = 0;//if arr[i] > arr[next] our assumption was wrong
            }
        }
    }
}

void mergeSort(int *arr, const int size, int &compCount, int &moveCount)
{
    myMergeSort(arr, 0, size-1, compCount, moveCount, size);
}

void quickSort(int *arr, const int size, int &compCount, int &moveCount)
{
    myQuickSort(arr, 0, size-1, compCount, moveCount);

}




//My Functions:

//mergeSort algorithm from lecture notes (slightly modified)
void myMerge(int *arr, int first, int mid, int last, int &compCount, int &moveCount, int maxSize)
{
    int tempArray[maxSize];
    int first1 = first;
    int last1 = mid;
    int first2 = mid+1;
    int last2 = last;
    int i = first1;

    for( ;(first1<=last1) && (first2<=last2); i++ )
    {
        moveCount++;
        compCount++;
        if(arr[first1] < arr[first2] )
        {
            tempArray[i] = arr[first1];
            first1++;
        }
        else
        {
            tempArray[i] = arr[first2];
            first2++;
        }
    }

    for( ;first1 <= last1; first1++, i++)
    {
        tempArray[i] = arr[first1];
        moveCount++;

    }

    for( ;first2 <= last2; first2++, i++)
    {
        tempArray[i] = arr[first2];
        moveCount++;
    }

    for(i = first; i<=last; i++ )
    {
        arr[i] = tempArray[i];
        moveCount++;
    }
}

void myMergeSort(int *arr, int first, int last, int &compCount, int &moveCount, int maxSize)
{
    if(first >= last)
        return;
    int mid = (first+last)/2;
    myMergeSort(arr, first, mid, compCount, moveCount, maxSize);
    myMergeSort(arr, mid+1, last, compCount, moveCount, maxSize);
    myMerge(arr, first, mid, last, compCount, moveCount, maxSize);
}

//partition algorithm from lecture slides (modified)
int myPartition(int *arr, int first, int last, int &compCount, int &moveCount)
{
    int pivot = arr[first];
    int lastS1 = first;
    int firstUnknown = first+1;

    for( ;firstUnknown <= last; firstUnknown++)
    {
        if(arr[firstUnknown] < pivot) // belong to S1
        {
            compCount++;
            lastS1++;
            int temp = arr[firstUnknown];
            moveCount++;
            arr[firstUnknown] = arr[lastS1];
            moveCount++;
            arr[lastS1] = temp;
            moveCount++;
        }//else belongs to S2
    }
    int temp = arr[first];
    moveCount++;
    arr[first] = arr[lastS1];
    moveCount++;
    arr[lastS1] = temp;
    moveCount++;
    return lastS1;
}

//quickSort algorithm from lecture slides (modified)
void myQuickSort(int *arr, int first, int last, int &compCount, int &moveCount)
{
    int pivot;
    if(first>=last)
        return;

    pivot = myPartition(arr, first, last, compCount, moveCount);
    myQuickSort(arr, first, pivot-1, compCount, moveCount);
    myQuickSort(arr, pivot+1, last, compCount, moveCount);
}

