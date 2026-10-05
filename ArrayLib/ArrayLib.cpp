#include "pch.h"
#include "ArrayLib.h"

void ReplaceMinMax(int* arr, int n, int value)
{
    int iMin = 0, iMax = 0;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[iMin]) iMin = i;
        if (arr[i] > arr[iMax]) iMax = i;
    }
    arr[iMin] = value;
    arr[iMax] = value;
}