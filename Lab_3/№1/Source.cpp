/*�������� �� ����� C/C++ ������� ���������� ���������� �
��������������� ���������� ����� ��������� a, b � �, ��������� �
������� 2, �������� ��������, ��������� ������� (3.2) � (3.3). �����
�������� � ���������� ����� � ������� ������. (1 �������)*/



#include <stdio.h>
#include <math.h>

// ����������
int Corr(int a[], int b[], int n) {
    int p = 0;
    for (int i = 0; i < n; i++) {
        p += a[i] * b[i];
    }
    return p;
}

// ����������������� ����������
double Corr2(int a[], int b[], int n) {
    double p = 0;
    double a_2 = 0;
    double b_2 = 0;

    for (int i = 0; i < n; i++) {
        p += (double)a[i] * b[i];
        a_2 += (double)a[i] * a[i];
        b_2 += (double)b[i] * b[i];
    }

    double corr = p / (sqrt(a_2) * sqrt(b_2));

    return corr;
}

int main() {
    // �������� ������, 1 �������
    int a[] = { 1, 2, 5, -2, -4, -2, 1, 4 };
    int b[] = { 3, 6, 7, 0, -5, -4, 2, 5 };
    int c[] = { -1, 0, -3, -9, 2, -2, 5, 1 };

    // ������������� ����� �������
    int n = sizeof(a) / sizeof(a[0]); 

    int ab = Corr(a, b, n);
    int bc = Corr(b, c, n);
    int ac = Corr(a, c, n);
    // ����� ����������
    printf("Correlation of a, b & c\n");
    printf("  |  a  |  b  |  c  |\n");
    printf(" a|  -  |%5.d|%5.d|\n", ab, ac);
    printf(" b|%5.d|  -  |%5.d|\n", ab, bc);
    printf(" c|%5.d|%5.d|  -  |\n", ac, bc);


    float ab_2 = Corr2(a, b, n);
    float bc_2 = Corr2(b, c, n);
    float ac_2 = Corr2(a, c, n);
    // ����� ����������������� ����������
    printf("Cross-correlation of a, b & c\n");
    printf("  |  a   |  b  |  c  |\n");
    printf(" a|   -  |%.2f |%.2f |\n", ab_2, ac_2);
    printf(" b| %.2f |  -  |%.2f|\n", ab_2, bc_2);
    printf(" c| %.2f |%.2f |  -  |\n", ac_2, bc_2);
    return 0;
}
