#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

// ������� ��� �������������� ���� �������� � ������ �� �������
char getReplacementSymbol(const string& pair, const map<string, char>& table) {
    auto it = table.find(pair);
    if (it != table.end()) {
        return it->second;
    }
    return '\0';  // ���� ���� ��� � �������, ���������� ������� ������.
}


string processSubstring(const string& sub, const map<string, char>& table) {
    string result = sub;

    // �������� ��������
    vector<int> to_remove = { 1, 4, 6, 11, 12, 13, 15, 16, 17, 20, 22, 27, 28, 29, 31, 32 };
    sort(to_remove.begin(), to_remove.end(), greater<int>()); // ���������� � �������� �������
    for (int pos : to_remove) {
        result.erase(pos - 1, 1);
    }


    vector<int> positions = { 4, 3, 1, 0, 7, 2, 6, 5, 12, 11, 9, 8, 15, 10, 14, 13 }; // ������� ��� ������������
    string result1 = "";

    for (int pos : positions) {
        result1 += result[pos]; // ��������� ������� �� ��������� ��������
    }


    string transformedString = "";
    for (size_t i = 0; i < result1.length() - 1; i += 2) {
        string pair = result1.substr(i, 2);
        char replacement = getReplacementSymbol(pair, table);
        if (replacement != '\0') {
            transformedString += replacement;
        }
        else {
            transformedString += pair;
        }
    }

    return transformedString;
}

int main() {
    setlocale(LC_ALL, "Rus");

    ifstream inputFile("input.txt");
    string str;

    if (inputFile.is_open()) { // ���������, ������� �� ������ ����
        std::string line;
        while (std::getline(inputFile, line)) { // ������ ���� ���������
            str += line;
        }
        inputFile.close(); // ��������� ����
    }
    else {
        std::cerr << "�� ������� ������� ����." << std::endl; // ��������� ������
    }


    // ������� ������
    map<string, char> replacement_table = {
        {"AA", ' '}, {"AF", '�'}, {"AJ", '0'}, {"AN", 'a'}, {"BE", '�'}, {"BF", '7'}, {"CC", '�'},
        {"CK", '�'}, {"CM", 'c'}, {"CP", '�'}, {"DB", '�'}, {"DC", '1'}, {"DD", '�'}, {"DL", '-'},
        {"EG", '-'}, {"EI", '�'}, {"EM", 'e'}, {"EO", '�'}, {"FH", '�'}, {"FO", '9'}, {"GA", '3'},
        {"GF", '�'}, {"GN", '.'}, {"HA", '�'}, {"HC", 'p'}, {"HD", '�'}, {"HH", '�'}, {"HI", '�'},
        {"HM", '>'}, {"HN", '�'}, {"IC", '�'}, {"IK", 'o'}, {"IL", '�'}, {"IO", '�'}, {"JA", '�'},
        {"JB", 'e'}, {"JD", 'p'}, {"JE", ','}, {"KB", '4'}, {"KC", 'x'}, {"KJ", '�'}, {"KK", '�'},
        {"KO", '�'}, {"LA", '�'}, {"LH", '�'},  {"MB", 'c'}, {"MF", '�'}, {"MH", '-'},{"CF", '<'},
        {"NB", '�'}, {"NF", '�'}, {"NO", '�'}, {"OE", '�'}, {"ON", '�'}, {"OO", '�'}, {"OP", '2'},
        {"PD", '�'}, {"PH", '5'}, {"PJ", '�'}, {"LJ", '�'}, {"FN", '�'}, {"FC", '�'}, {"FP", '�'},
        {"GH", '7'}, {"PG", '�'}, {"AL", '8'}, {"CL", '�'}, {"DH", '�'}, {"BG", ':'}, {"FD", '�'},
        {"ED", '�'}, {"PB", '�'}, {"LD", '�'}
    };

    vector<string> substrings;
    for (size_t i = 0; i < str.length(); i += 32) {
        substrings.push_back(str.substr(i, 32));
    }

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        for (const string& sub : substrings) {      // ��������� ������ � ��� ������ � ����
            string processed_sub = processSubstring(sub, replacement_table);
            outputFile << processed_sub;
        }
        outputFile.close();
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
    }

    return 0;
}