#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;

// ������� ��� ��������, � ����� � ������������ �������� � ������
string f(const string str);

// ������� ��� �������������� ���� �������� � ������ �� �������
char getReplacementSymbol(const string& pair, const map<string, char>& table) {
    auto it = table.find(pair);
    if (it != table.end()) {
        return it->second;
    }
    return '\0';  // ���� ���� ��� � �������, ���������� ������� ������.
}


string processSubstring(const string sub, const map<string, char>& table) {
    string result = sub;

    string result1 = f(result);

    string transformedString = "";
    // �������� �� ������ � ����� � 2 �������
    for (size_t i = 0; i < result1.length() - 1; i += 2) {
        string pair = result1.substr(i, 2);
        char replacement = getReplacementSymbol(pair, table); //���� � ������� ���� ������, ��������
        if (replacement != '\0') {
            transformedString += replacement;
        }
        else {
            transformedString += pair;
        }
    }

    return transformedString;
}

void Check_in(string str) { //C������ � ������� �� ����� ���� �������� � �� ���������� ��������� � ������
    
    unordered_map<std::string, int> pair_count;

    // �������� �� ������ � ����� � 2 �������
    for (size_t i = 0; i < str.length() - 1; i += 2) {
        // ��������� ���� ��������
        std::string pair = str.substr(i, 2);
        pair_count[pair]++;
    }

    vector<pair<string, int>> sorted_pairs(pair_count.begin(), pair_count.end());

    // ���������� �� ���������� ���������
    std::sort(sorted_pairs.begin(), sorted_pairs.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // ��������� �� ��������
        });
    // ������� ����������
    std::cout << "���������� ��������� ��� ��������:\n";
    for (const auto& entry : sorted_pairs) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
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
        {"AA", ' '}, {"FA", '�'}, {"JA", '0'}, {"NA", 'a'}, {"EB", '�'}, {"FB", '7'}, {"CC", '�'},
        {"KC", '�'}, {"MC", 'c'}, {"PC", '�'}, {"BD", '�'}, {"CD", '1'}, {"DD", '�'}, {"LD", '-'},
        {"GE", '-'}, {"IE", '�'}, {"ME", 'e'}, {"OE", '�'}, {"HF", '�'}, {"OF", '9'}, {"AG", '3'},
        {"FG", '�'}, {"NG", '.'}, {"AH", '�'}, {"CH", 'p'}, {"DH", '�'}, {"HH", '�'}, {"IH", '�'},
        {"MH", '>'}, {"NH", '�'}, {"CI", '�'}, {"KI", 'o'}, {"LI", '�'}, {"OI", '�'}, {"AJ", '�'},
        {"BJ", 'e'}, {"DJ", 'p'}, {"EJ", ','}, {"BK", '4'}, {"CK", 'x'}, {"JK", '�'}, {"KK", '�'},
        {"OK", '�'}, {"AL", '�'}, {"HL", '�'}, {"BM", 'c'}, {"FM", '�'}, {"HM", '-'}, {"FC", '<'},
        {"BN", '�'}, {"FN", '�'}, {"ON", '�'}, {"EO", '�'}, {"NO", '�'}, {"OO", '�'}, {"PO", '2'},
        {"DP", '�'}, {"HP", '5'}, {"JP", '�'}, {"JL", '�'}, {"NF", '�'}, {"CF", '�'}, {"PF", '�'},
        {"HG", '7'}, {"GP", '�'}, {"LA", '8'}, {"LC", '�'}, {"HD", '�'}, {"GB", ':'}, {"DF", '�'},
        {"DE", '�'}, {"BP", '�'}, {"DL", '�'}
    };

    vector<string> substrings;
    for (size_t i = 0; i < str.length(); i += 32) {
        substrings.push_back(str.substr(i, 32));
    }

    /*string new_str; 
    for (const string sub : substrings) {     
        new_str += f(sub);
    }
    Check_in(new_str);*/ // C������ � ������� �� ����� ���� �������� � �� ���������� ��������� � ������

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        for (const string sub : substrings) {      // ��������� ������ � ��� ������ � ����
            string processed_sub = processSubstring(sub, replacement_table) ;
            outputFile << processed_sub;
        }
        outputFile.close();
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
    }

    return 0;
}

string f(const string str) {
    string str1 = str;
    vector<int> to_remove = {1, 4, 6, 11, 12, 13, 15, 16, 17, 20, 22, 27, 28, 29, 31, 32};
    sort(to_remove.begin(), to_remove.end(), greater<int>()); // ���������� � �������� �������
    for (int pos : to_remove) {
        str1.erase(pos - 1, 1);
    }

    vector<int> positions = {3,4,0,1,2,7,5,6,11,12,8,9,10,15,13,14 }; // ������� ��� ������������

    string result1 = "";

    for (int pos : positions) {
        result1 += str1[pos]; // ��������� ������� �� ��������� ��������
    }
    return (result1);
}
