#include <SFML/Graphics.hpp>
#include <iostream>

#include "constants.h"
#include "utils.h"

#include <Windows.h>

#include <fstream>

using namespace std;
using namespace constants;

int main() {
    
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    regex valid_input("^[01]$");
    regex valid_path(R"(^(?:(?:[^\\/][^\\/:*?"<>|\r\n]*[\\/])*(?:[^\\/:*?"<>|\r\n]+)\.txt)?$)");

    string input, in_option, out_option;
    
    int size;
    do {
        do {
            cout << "¬ведите '0' дл€ ввода с консоли, '1' дл€ ввода из файла: ";
            getline(cin, input);
        } while (!regex_match(input, valid_input));
        in_option = input;

        do {
            cout << "¬ведите '0' дл€ вывода на консоль, '1' дл€ вывода в файл: ";
            getline(cin, input);
        } while (!regex_match(input, valid_input));
        out_option = input;

        
        if (in_option == "0") readFromConsole(size);
        else if (in_option == "1") {
            do {
                cout << "”кажите файл дл€ ввода исходных данных дл€ работы программы (enter дл€ файла по умолчанию): ";
                getline(cin, input);
            } while (!regex_match(input, valid_path));
            readFromFile(input, size);
        }

        vector<vector<int>> matrix = { {1, 0, 1}, {0, 1, 0}, {1, 0, 1} };
        for (int i = 2; i <= size; ++i) {
            constructMatrix(matrix);
        }

        if (out_option == "0") displayMatrix(matrix);
        else if (out_option == "1") {
            do {
                cout << "”кажите файл дл€ вывода исходных данных дл€ работы программы (enter дл€ файла по умолчанию): ";
                getline(cin, input);
            } while (!regex_match(input, valid_path));
            saveMatrixToImage(matrix, input);
        }

        if (in_option == "0") {
            do {
                cout << "¬ведите '0' дл€ повтора программы, '1' дл€ завершени€ программы: ";
                getline(cin, input);
            } while (!regex_match(input, valid_input));
            in_option = input;
        }
    } while (in_option != "1");
   
    return 0;
}