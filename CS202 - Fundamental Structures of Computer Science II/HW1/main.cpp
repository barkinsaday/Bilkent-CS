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
#include <cstdlib> //for using rand() function
#include <ctime> //for measuring elapsed time
#include <bits/stdc++.h> // for measuring elapsed time
using namespace std;

//Global Functions to Test Main
void displayArray(const int *arr, const int size);
void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
void createAlmostSortedArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
void createAlmostUnsortedArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
void performanceAnalysis(int *&a1, int *&a2, int *&a3, int *&a4, const int size, int type);


int main()
{
    //Insertion Sort
    cout << "Insertion Sort:" << endl;
    const int arrSize1 = 16;
    int arr1[arrSize1] = {9, 6, 7, 16, 18, 5, 2, 12, 20, 1, 16, 17, 4, 11, 13, 8};
    int compCount1 = 0, moveCount1 = 0;
    displayArray(arr1, arrSize1);
    insertionSort(arr1, arrSize1, compCount1, moveCount1);
    displayArray(arr1, arrSize1);
    cout << "Comparison: " << compCount1 << ", Movement: " << moveCount1 << endl;

    //Bubble Sort
    cout << "============================================================================" << endl;
    cout << "Bubble Sort:" << endl;
    const int arrSize2 = 16;
    int arr2[arrSize2] = {9, 6, 7, 16, 18, 5, 2, 12, 20, 1, 16, 17, 4, 11, 13, 8};
    int compCount2 = 0, moveCount2 = 0;
    displayArray(arr2, arrSize2);
    bubbleSort(arr2, arrSize2, compCount2, moveCount2);
    displayArray(arr2, arrSize2);
    cout << "Comparison: " << compCount2 << ", Movement: " << moveCount2 << endl;

    //Merge Sort
    cout << "============================================================================" << endl;
    cout << "Merge Sort:" << endl;
    const int arrSize3 = 16;
    int arr3[arrSize3] = {9, 6, 7, 16, 18, 5, 2, 12, 20, 1, 16, 17, 4, 11, 13, 8};
    int compCount3 = 0, moveCount3 = 0;
    displayArray(arr3, arrSize3);
    mergeSort(arr3, arrSize3, compCount3, moveCount3);
    displayArray(arr3, arrSize3);
    cout << "Comparison: " << compCount3 << ", Movement: " << moveCount3 << endl;

    //Quick Sort
    cout << "============================================================================" << endl;
    cout << "Quick Sort:" << endl;
    const int arrSize4 = 16;
    int arr4[arrSize4] = {9, 6, 7, 16, 18, 5, 2, 12, 20, 1, 16, 17, 4, 11, 13, 8};
    int compCount4 = 0, moveCount4 = 0;
    displayArray(arr4, arrSize4);
    quickSort(arr4, arrSize4, compCount4, moveCount4);
    displayArray(arr4, arrSize4);
    cout << "Comparison: " << compCount4 << ", Movement: " << moveCount4 << endl;








    return 0;
}
// merge sort: move ve comp countları hallet

void displayArray(const int* arr, const int n)
{
    cout << "{";
    for(int i=0; i<n-1; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << arr[n-1] << "}" << endl;
}

void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size)
{
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    for(int i=0; i<size; i++)
    {
        int random = rand() % 100 + 1;
        arr1[i] = random;
        arr2[i] = random;
        arr3[i] = random;
        arr4[i] = random;
    }
}

void createAlmostSortedArrays(int *&a1, int *&a2, int *&a3, int *&a4, const int size)
{
    a1 = new int[size];
    a2 = new int[size];
    a3 = new int[size];
    a4 = new int[size];

    int rand1 = 0, rand2 = 0;
    for(int i=0; i<size; i++)
    {
        a1[i] = i;
        a2[i] = i;
        a3[i] = i;
        a4[i] = i;
    }

    for(int i=0; i<(size/20); i++)
    {
        int temp = 0;
        rand1 = rand() % 100 -1;
        rand2 = rand() % 100 -1;
        temp = a1[rand1];

        a1[rand1] = a1[rand2];
        a1[rand2] = temp;

        a2[rand1] = a2[rand2];
        a2[rand2] = temp;

        a2[rand1] = a2[rand2];
        a2[rand2] = temp;

        a2[rand1] = a2[rand2];
        a2[rand2] = temp;
    }
}

void performanceAnalysis(int *&a1, int *&a2, int *&a3, int *&a4, const int size, int type)
{

    if(type == 1)
    {
        createRandomArrays(a1, a2, a3, a4, size);
        cout << "Performance Analysis for Random Array / Size: " << size << endl;
        cout << "=============================================================================" << endl;

        int comp1 = 0;
        int move1 = 0;
        double duration1 = 0;
        cout << "Insertion Sort:" << endl;
        clock_t startTime1 = clock();
        insertionSort(a1, size, comp1, move1);
        duration1 = 1000 * float( clock() - startTime1 ) / CLOCKS_PER_SEC;
        cout << "Execution time for Insertion Sort: " << duration1 << " ms" << endl;
        cout << "Comparison: " << comp1 << " Movement: " << move1 << endl;

        cout << "=============================================================================" << endl;

        int comp2 = 0;
        int move2 = 0;
        double duration2 = 0;
        cout << "Bubble Sort:" << endl;
        clock_t startTime2 = clock();
        bubbleSort(a2, size, comp2, move2);
        duration2 = 1000 * float( clock() - startTime2 ) / CLOCKS_PER_SEC;
        cout << "Execution time for Bubble Sort: " << duration2 << " ms" << endl;
        cout << "Comparison: " << comp2 << " Movement: " << move2 << endl;

        cout << "=============================================================================" << endl;

        int comp3 = 0;
        int move3 = 0;
        double duration3 = 0;
        cout << "Merge Sort:" << endl;
        clock_t startTime3 = clock();
        mergeSort(a3, size, comp3, move3);
        duration3 = 1000 * float( clock() - startTime3 ) / CLOCKS_PER_SEC;
        cout << "Execution time for Merge Sort: " << duration3 << " ms" << endl;
        cout << "Comparison: " << comp3 << " Movement: " << move3 << endl;

        cout << "=============================================================================" << endl;

        int comp4 = 0;
        int move4 = 0;
        double duration4 = 0;
        cout << "Quick Sort:" << endl;
        clock_t startTime4 = clock();
        quickSort(a4, size, comp4, move4);
        duration4 = 1000 * float( clock() - startTime4 ) / CLOCKS_PER_SEC;
        cout << "Execution time for Quick Sort: " << duration3 << " ms" << endl;
        cout << "Comparison: " << comp4 << " Movement: " << move4 << endl;
    }

    if(type == 2)
    {
        createAlmostSortedArrays(a1, a2, a3, a4, size);
        cout << "Performance Analysis for Almost Sorted Array / Size: " << size << endl;
        cout << "=============================================================================" << endl;

        int comp1 = 0;
        int move1 = 0;
        double duration1 = 0;
        cout << "Insertion Sort:" << endl;
        clock_t startTime1 = clock();
        insertionSort(a1, size, comp1, move1);
        duration1 = 1000 * float( clock() - startTime1 ) / CLOCKS_PER_SEC;
        cout << "Execution time for Insertion Sort: " << duration1 << " ms" << endl;
        cout << "Comparison: " << comp1 << " Movement: " << move1 << endl;

        cout << "=============================================================================" << endl;

        int comp2 = 0;
        int move2 = 0;
        double duration2 = 0;
        cout << "Bubble Sort:" << endl;
        clock_t startTime2 = clock();
        bubbleSort(a2, size, comp2, move2);
        duration2 = 1000 * float( clock() - startTime2 ) / CLOCKS_PER_SEC;
        cout << "Execution time for Bubble Sort: " << duration2 << " ms" << endl;
        cout << "Comparison: " << comp2 << " Movement: " << move2 << endl;

        cout << "=============================================================================" << endl;

        int comp3 = 0;
        int move3 = 0;
        double duration3 = 0;
        cout << "Merge Sort:" << endl;
        clock_t startTime3 = clock();
        mergeSort(a3, size, comp3, move3);
        duration3 = 1000 * float( clock() - startTime3 ) / CLOCKS_PER_SEC;
        cout << "Execution time for Merge Sort: " << duration3 << " ms" << endl;
        cout << "Comparison: " << comp3 << " Movement: " << move3 << endl;

        cout << "=============================================================================" << endl;

        int comp4 = 0;
        int move4 = 0;
        double duration4 = 0;
        cout << "Quick Sort:" << endl;
        clock_t startTime4 = clock();
        quickSort(a4, size, comp4, move4);
        duration4 = 1000 * float( clock() - startTime4 ) / CLOCKS_PER_SEC;
        cout << "Execution time for Quick Sort: " << duration3 << " ms" << endl;
        cout << "Comparison: " << comp4 << " Movement: " << move4 << endl;
    }
}

