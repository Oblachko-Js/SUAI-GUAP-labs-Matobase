#include <iostream>
#include <string>

using namespace std;

int main()
{
    int i, b, n;
    cout << "Введите размер массива n = ";
    cin >> n;
    int* a = new int[n];
    for (i = 0; i < n; i++)
    {
        cout << "Введите " << i << "-й элемент массива = ";
        cin >> b;
        a[i] = b;
    }
    for (i = 0; i < n; i++)
    {
        cout << "Массив[" << i << "] = " << a[i] << '\n';
    }
    delete[] a;

    return 0;
}
