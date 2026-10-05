#include <windows.h>
#include <iostream>
using namespace std;

struct Data
{
    int* arr;
    int n;
    int min, max;
    double avg;
};

typedef void (*ReplaceFunc)(int*, int, int);

DWORD WINAPI MinMax(LPVOID param)
{
    Data* d = (Data*)param;
    d->min = d->max = d->arr[0];
    for (int i = 1; i < d->n; i++)
    {
        if (d->arr[i] < d->min) d->min = d->arr[i];
        Sleep(7);
        if (d->arr[i] > d->max) d->max = d->arr[i];
        Sleep(7);
    }
    cout << "min = " << d->min << ", max = " << d->max << endl;
    return 0;
}

DWORD WINAPI Average(LPVOID param)
{
    Data* d = (Data*)param;
    long long sum = 0;
    for (int i = 0; i < d->n; i++)
    {
        sum += d->arr[i];
        Sleep(12);
    }
    d->avg = (double)sum / d->n;
    cout << "average = " << d->avg << endl;
    return 0;
}

int main()
{
    Data d;
    cout << "Size: ";
    cin >> d.n;
    d.arr = new int[d.n];
    cout << "Elements: ";
    for (int i = 0; i < d.n; i++) cin >> d.arr[i];

    HANDLE hMinMax = CreateThread(NULL, 0, MinMax, &d, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, Average, &d, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);
    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    // доп. задание: подключаем DLL ровно здесь, вызываем и сразу отключаем
    HMODULE hLib = LoadLibraryA("ArrayLib.dll");
    ReplaceFunc replace = (ReplaceFunc)GetProcAddress(hLib, "ReplaceMinMax");
    replace(d.arr, d.n, (int)d.avg);
    FreeLibrary(hLib);

    cout << "Result: ";
    for (int i = 0; i < d.n; i++) cout << d.arr[i] << " ";
    cout << endl;

    delete[] d.arr;
    return 0;
}