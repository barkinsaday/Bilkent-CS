/*
@author: Barkın Saday
@student ID: 21902967
@course: CS201-01
@topic: CS201 HW 2
*/
#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

int binarySearch( int* arr, int low, int high, int key )//from lecture slides
 {
     if ( low > high )
        return -1;
     int mid = (low + high) / 2;
     if ( arr[mid] == key )
        return mid;
     if ( arr[mid] > key )
        return binarySearch( arr, low, mid - 1, key );
     return binarySearch( arr, mid + 1, high, key );
}

bool method_Two(int arr1[], int arr2[], const int size1, const int size2)//arrays must be sorted
{
    for(int i=0; i<size2; i++)
    {
        if( binarySearch(arr1, 0, size1-1, arr2[i]) == -1 )//failed search
            return false;
    }
    return true;
}

bool method_Three(int arr1[], int arr2[], const int size1, const int size2, int freq[])
{
    for(int i=0; i<size1; i++)
    {
        freq[arr1[i]]=1;
    }

    for (int i=0; i<size2; i++)
    {
        if (freq[arr2[i]] == 0)
        {
            return false;
        }
    }
    return true;
}

bool method_One(int arr1[], int arr2[], int size1, int size2)
{
    int counter;

    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < size1; j++) {
            if (arr2[i] == arr1[j])
                counter++;
        }
    }
    if(counter==size2)
        return 1;
    return 0;
}


//main function
int main()
{
    int power_1, power_2, a=1, b=1;

    cout << "Enter a number for size n (n = x^10): ";
    cin >> power_1;
    cout << "Enter a number for size m (3 or 4): ";
    cin >> power_2;

    for(int i=0; i<power_1; i++)
        a = a*10;

    for(int i=0; i<power_2; i++)
        b = b*10;

    int k;
    cout << "Enter k (n = k * 10^n): ";
    cin >> k;
    const int size1 = a*k; //10^6 * x
    const int size2 = b; //10^3 or 10^4

    int* arr1 = new int[size1];
    int* arr2 = new int[size2];

    for(int i=0; i<size1; i++)
        arr1[i] = i+1;

    for(int i=0; i<size2; i++)
        arr2[i] = i+1;

    cout << "=======================================================================================" << endl;
    cout << "arr1[0]= " << arr1[0] << ", arr2[0]= " << arr2[0] << endl;
    cout << "arr1[n-1]= " << arr1[size1-1] << ", arr2[m-1]=" <<arr2[size2-1] << endl;
    cout << "Size1: " << size1 << ", Size2: " << size2 << endl;

    double duration1;
    double duration2;
    double duration3;

    cout << "=======================================================================================" << endl;
    clock_t startTime2 = clock();
    for(int i=0; i<50; i++)
    {
        cout << "Method 2 returns: " << method_Two(arr1, arr2, size1, size2) << endl;
    }
    duration2 = (1000 * float( clock() - startTime2 ) / CLOCKS_PER_SEC) / 50;
    cout << "Execution took for method 2: " << duration2 << " milliseconds." << endl;

    int maxVal = 0;
    for(int i=0; i<size1; i++)
    {
        if(maxVal < arr1[i])
            maxVal = arr1[i];
    }

    int* freq = new int[maxVal];//initialized frequency table (current all 0)

    cout << "=======================================================================================" << endl;
    cout << "Max Value (for frequency array): " << maxVal << endl;
    clock_t startTime3 = clock();
    for(int i=0; i<10; i++)
        cout << "Method 3 returns: " << method_Three(arr1, arr2, size1, size2, freq) << endl;
    duration3 = (1000 * double( clock() - startTime3 ) / CLOCKS_PER_SEC)/10;
    cout << "Execution took for method 3: " << duration3 << " milliseconds." << endl;

    cout << "=======================================================================================" << endl;
    clock_t startTime = clock();
    cout << "Method 1 returns: " << method_One(arr1, arr2, size1, size2) << endl;
    duration1 = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Execution took for method 1: " << duration1 << " milliseconds." << endl;
    cout << "=======================================================================================" << endl;
    cout << "Done" << endl;

    return 0;
}
