#include <iostream>
using namespace std;

const int MAX_LENGTH = 100;

void InsertString(char* original, char* toInsert, int position)
{
    int originalLength = 0;
    while (original[originalLength] != '\0') {
        originalLength++;
    }

    int toInsertLength = 0;
    while (toInsert[toInsertLength] != '\0') {
        toInsertLength++;
    }

    if (position < 0 || position > originalLength) {
        cout << "Incorrect position to insert" << endl;
        return;
    }

    if (originalLength + toInsertLength > MAX_LENGTH) {
        cout << "ERROR: Max length of string was exceeded" << endl;
        return;
    }

    for (int i = originalLength; i >= position; i--) {
        original[i + toInsertLength] = original[i];
    }

    for (int i = 0; i < toInsertLength; i++) {
        original[position + i] = toInsert[i];
    }

    cout << "String after insert: " << original << endl;
}

int main()
{
    char original[MAX_LENGTH];
    char toInsert[MAX_LENGTH];
    int position;

    cout << "Input the initial string (Max length is " << MAX_LENGTH - 1 << " symbols): ";
    cin.getline(original, MAX_LENGTH);

    cout << "Input string to insert: ";
    cin.getline(toInsert, MAX_LENGTH);

    cout << "Input position to insert: ";
    cin >> position;

    InsertString(original, toInsert, position);

    return 0;
}
