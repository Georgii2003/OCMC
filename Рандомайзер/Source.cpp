#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // »нициализируем генератор случайных чисел текущим временем
    srand(time(0));

    // √енерируем случайное число от 2 до 28
    int randomNumber = 2 + rand() % 28;

    cout << "Random Number: " << randomNumber << endl;

    return 0;
}