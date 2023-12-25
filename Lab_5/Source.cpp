#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int BigN = 5000;
const int N = 20 + 1;

vector<int> CRC(vector<int>& data)
{
    vector<int> polinome{ 1, 0, 1, 1, 1, 1, 1, 1 }; //1 вариант, G=x^7+x^5+x^4+x^3+x^2+x+1
    //vector<int> polinome {1, 1, 0, 1, 1, 1, 1, 0}; 10 вариант, G = x^7 + x^6 + x^4 + x^3 + x^2 + x
    //vector<int> polinome {1, 1, 0, 0, 0, 0, 0, 0}; 23 вариант, G = x^7 + x^6
    //vector<int> polinome{ 1, 1, 0, 1, 1, 1, 1, 1 }; 2 вариант, G=x^7+x^6+x^4+x^3+x^2+x+1
    //vector<int> polinome{ 1, 0, 1, 1, 1, 1, 0, 1 }; 13 вариант, G=x^7+x^5+x^4+x^3+x^2+1
    vector<int> temporary_div;
    vector<int> zero_polinome(polinome.size(), 0);

    //Дополнение массива данных нулями
    for (int i = 0; i < polinome.size() - 1; i++) {
        data.push_back(0);
    }

    //Копирование данных в новый массив для произведения операции деления
    copy_if(data.begin(), data.begin() + polinome.size(), back_inserter(temporary_div), [](int i) { return true; });
    int end_temp = polinome.size();

    //xor первых polinome.size() битов и запись в конец temporary_div
    for (int i = 0; i < end_temp; i++) {
        temporary_div.push_back(temporary_div[i] ^ polinome[i]);
    }

    //Удаление первых использованных битов
    temporary_div.erase(temporary_div.begin(), temporary_div.begin() + polinome.size() + 1);
    temporary_div.push_back(data[polinome.size() + 1]);
    int count = 0;

    for (int j = polinome.size(); (j < data.size()) && (count < data.size() - polinome.size() + 1); j++, count++) {
        if (temporary_div[0] == 1) {
            for (int i = 0; i < end_temp; i++) {
                temporary_div.push_back(temporary_div[i] ^ polinome[i]);
            }
            temporary_div.erase(temporary_div.begin(), temporary_div.begin() + polinome.size() + 1);
            if (j + 1 != data.size()) { temporary_div.push_back(data[j + 1]); }
        }
        else {
            for (int i = 0; i < end_temp; i++) {
                temporary_div.push_back(temporary_div[i] ^ zero_polinome[i]);
            }
            temporary_div.erase(temporary_div.begin(), temporary_div.begin() + polinome.size() + 1);
            if (j + 1 != data.size()) { temporary_div.push_back(data[j + 1]); }
        }
    }

    return temporary_div;

}
int main()
    {
        setlocale(LC_ALL, "Russian");
        vector<int> data_tx(N), big_data_tx(BigN);

        cout << "\nИсходная битовая последовательность: " << endl;
        for (auto& d : data_tx) {
            d = rand() % 2;
            cout << d << " ";
        }

        vector<int> data_rx(data_tx);
        vector<int> CRC_tx = CRC(data_tx);

        cout << endl << "\nCRC для передаваемого пакета: ";
        for (auto& i : CRC_tx) {
            cout << i << " ";
            data_rx.push_back(i);
        }
        vector<int> CRC_rx = CRC(data_rx);
        int CRC_rx_summ = 0;

        cout << endl << "\nCRC для получаемого пакета: ";
        for (auto& i : CRC_rx) {
            cout << i << " ";
            CRC_rx_summ += i;
        }

        auto error_msg = [](int cntr) {
            if (cntr != 0) {
                cout << endl << "\nПакет принят с ошибкой!";
            }
            else cout << endl << "\nОшибок в пакете нет!";
        };

        error_msg(CRC_rx_summ);

        cout << endl << "\nИсходная битовая последовательность для N = 5000: " << endl;
        for (auto& d : big_data_tx) {
            d = rand() % 2;
            cout << d << " ";
        }

        vector<int> big_data_rx(big_data_tx);
        vector<int> big_CRC_tx = CRC(big_data_tx);

        cout << endl << "\nCRC для передаваемого пакета N = 5000: ";
        for (auto& i : big_CRC_tx) {
            cout << i << " ";
            big_data_rx.push_back(i);
        }
        vector<int> big_CRC_rx = CRC(big_data_rx);
        int big_CRC_rx_summ = 0;

        cout << endl << "\nCRC для получаемого пакета N = 5000: ";
        for (auto& i : big_CRC_rx) {
            cout << i << " ";
            big_CRC_rx_summ += i;
        }

        error_msg(big_CRC_rx_summ);

        cout << endl << "\nДля цикла 5000+CRC length итераций: ";
        int errors_detected = 0, errors_not_detected = 0;

        for (int i = 0; i < big_data_rx.size(); i++) {
            int flag = 0;
            vector<int> copy_big_data_rx;
            copy_if(big_data_rx.begin(), big_data_rx.end(), back_inserter(copy_big_data_rx), [](int i) { return true; });
            copy_big_data_rx[i] = -1;
            vector<int> copy_big_CRC_rx = CRC(copy_big_data_rx);
            for (auto& j : copy_big_CRC_rx) {
                if (j != 0) {
                    flag++;
                }
            }
            if (flag != 0) errors_detected++;
            else errors_not_detected++;
        }
        cout << endl << "\nОшибок обнаружено: " << errors_detected << endl << "\nОшибок не обнаружено: " << errors_not_detected;
    }