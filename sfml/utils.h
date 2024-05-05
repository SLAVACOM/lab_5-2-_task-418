#pragma once

#include <string>
#include<regex>

using namespace std;

void readFromConsole(int& size);

void readFromFile(std::string filename, int& size);

void displayMatrix(vector<vector<int>> matrix);

void constructMatrix(vector<vector<int>> &matrix);

void saveMatrixToImage(const vector<vector<int>> matrix, const string filename);