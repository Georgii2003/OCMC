#include <iostream>

#define LENGTH 5
#define SEQUENCE_LENGTH 31

using namespace std;

// Функция для вывода массива
void printArray(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функция для вывода таблицы
void printArrayShift(int arr[], int len) 
{
    for (int i = 0; i < len; i++) 
    {
        cout  << arr[i] << " ";
    }
}

// Функция автокорреляции
double autocorrelation(int original[], int shifted[], int length) 
{
    int matches = 0;
    for (int i = 0; i < length; i++) 
    {
        if (original[i] == shifted[i]) 
        {
            matches++;
        }
    }
    return (double)(matches - (length - matches)) / length;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int x[LENGTH] = { 0, 0, 0, 0, 1 };
    int y[LENGTH] = { 0, 1, 0, 0, 0 };

    cout << "Массив x: " << endl;
    printArray(x, LENGTH);
    cout << "Массив y: " << endl;
    printArray(y, LENGTH);
    cout << endl;

    int original[SEQUENCE_LENGTH] = { 0 };
    int shifted[SEQUENCE_LENGTH] = { 0 };

    cout << "Сгенерированная последовательность Голда: " << endl;

    int goldSequence[SEQUENCE_LENGTH];
    for (int i = 0; i < SEQUENCE_LENGTH; i++) 
    {
        goldSequence[i] = x[4] ^ y[4];

        original[i] = goldSequence[i]; // Копирование в original
        shifted[i] = goldSequence[i];  // Копирование в shifted

        cout << i + 1 << ": x: ";
        printArray(x, LENGTH);
        cout << "   y: ";
        printArray(y, LENGTH);

        int temp = x[3] ^ x[4];
        for (int j = 4; j >= 0; j--) 
        {
            x[j] = x[j - 1];
        }
        x[0] = temp;

        temp = y[1] ^ y[4];
        for (int j = 4; j >= 0; j--) 
        {
            y[j] = y[j - 1];
        }
        y[0] = temp;
    }

    cout << "Сгенерированная последовательность Голда: ";
    printArray(goldSequence, SEQUENCE_LENGTH);

    cout << "\n\nShift|                              Bits                            |AutoCorr" << endl;

    for (int shift = 0; shift < 33; shift++) 
    {
        double autocorr = autocorrelation(original, shifted, SEQUENCE_LENGTH);
        cout << "    " << shift + 1 << "|";
        printArrayShift(shifted, SEQUENCE_LENGTH);
        cout << "| " << autocorr;
        cout << endl;

        int temp = shifted[SEQUENCE_LENGTH - 1];
        for (int i = SEQUENCE_LENGTH - 1; i >= 0; i--) 
        {
            shifted[i] = shifted[i - 1];
        }
        shifted[0] = temp;
    }
    return 0;
}