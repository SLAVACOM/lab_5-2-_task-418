#include "utils.h"
#include "constants.h"

#include<iostream>
#include <fstream>
#include <sstream>

using namespace constants;

void readFromConsole(int& size) {
    std::regex valid_size("^[1-9][0-9]*$");
    std::string input;
    do {
        std::cout << "Введите размерность матрицы: ";
        std::getline(std:: cin, input);
    } while (!regex_match(input, valid_size));
    size = stoi(input);
}

bool readFromFile(std::string filename, int& size) {
    std::regex valid_size("^[1-9][0-9]*$");
    ifstream file(filename == "" ? DinputFileName : filename);

    if (file.is_open()) {
        std::string line;
        std::vector<string> data;
        if (!(file >> size)) {
            cerr << "Неверные данные в файле" << endl;
            return false;
        }
        char e;
        if (file >> e) {
            cerr << "Неверные данные в файле"<<endl;
            return false;
        }

        return true;
    }
    else {
        cerr << "Ошибка при открытии файла" << endl;
        return false;
    }
}

void displayMatrix(vector<vector<int>> matrix) {
    int windowSize = matrix.size() * pixelSize;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Матрица");

    sf::Font font;
    if (!font.loadFromFile(constants::fontName)) {
        cerr << "Ошибка при загрузке шрифта!" << endl;
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                int colorNumber = (((i * i) + (j * j * j)) % colors.size());
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(matrix[i][j]));
                text.setCharacterSize(pixelSize - 1);
                if (matrix[i][j] == 1)text.setFillColor(colors[colorNumber]);
                else text.setFillColor(zeroColor);
                text.setPosition(j * pixelSize, i * pixelSize);
                window.draw(text);
            }
        }
        window.display();
    }
}

void constructMatrix(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int newSize = 3 * n;
    vector<vector<int>> newMat(newSize, vector<int>(newSize, 0));
    for (int br = 0; br < 3; br++) {
        for (int bc = 0; bc < 3; bc++) {
            if ((br != 1 && bc != 1) || (br == 1 && bc == 1)) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        newMat[br * n + i][bc * n + j] = matrix[i][j];
                    }
                }
            }
        }
    }
    matrix = newMat;
}

void saveMatrixToImage(vector<vector<int>> matrix, const string filename) {
    int windowSize = matrix.size() * pixelSize;
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(windowSize, windowSize)) {
        cerr << "Ошибка при создании изображения!" << endl;
        return;
    }

    sf::Font font;
    if (!font.loadFromFile(fontName)) {
        cerr << "Ошибка при загрузке шрифта!" << endl;
        return;
    }

    renderTexture.clear();
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
                int colorNumber = (((i+1) * (i+1) + ((j+1) * (j + 1) * (j + 1))) % colors.size());
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(matrix[i][j]));
                text.setCharacterSize(pixelSize - 1);
                if (matrix[i][j] == 1)text.setFillColor(colors[colorNumber]);
                else text.setFillColor(zeroColor);
                text.setPosition(j * pixelSize, i * pixelSize);
                renderTexture.draw(text);
            
        }
    }
    renderTexture.display();

    sf::Texture texture = renderTexture.getTexture();
    sf::Image image = texture.copyToImage();

    if (!image.saveToFile(filename != "" ? filename : DoutputFileName))cerr << "Ошибка при сохранении!" << endl;
    else cout << "Изображение успешно сохранено в файл " << filename << endl;

}