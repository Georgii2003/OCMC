#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // �������������� ��������� ��������� ����� ������� ��������
    srand(time(0));

    // ���������� ��������� ����� �� 2 �� 28
    int randomNumber = 2 + rand() % 28;

    cout << "Random Number: " << randomNumber << endl;

    return 0;
}