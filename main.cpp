#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

// Функция для преобразования пары символов в символ из таблицы
char getReplacementSymbol(const string& pair, const map<string, char>& table) {
    auto it = table.find(pair);
    if (it != table.end()) {
        return it->second;
    }
    return '\0';  // Если пары нет в таблице, возвращаем нулевой символ.
}


string processSubstring(const string& sub, const map<string, char>& table) {
    string result = sub;

    // Удаление символов
    vector<int> to_remove = { 1, 4, 6, 11, 12, 13, 15, 16, 17, 20, 22, 27, 28, 29, 31, 32 };
    sort(to_remove.begin(), to_remove.end(), greater<int>()); // Сортировка в обратном порядке
    for (int pos : to_remove) {
        result.erase(pos - 1, 1);
    }


    vector<int> positions = { 4, 3, 1, 0, 7, 2, 6, 5, 12, 11, 9, 8, 15, 10, 14, 13 }; // Позиции для перестановки
    string result1 = "";

    for (int pos : positions) {
        result1 += result[pos]; // Добавляем символы на указанных позициях
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

    if (inputFile.is_open()) { // Проверяем, успешно ли открыт файл
        std::string line;
        while (std::getline(inputFile, line)) { // Читаем файл построчно
            str += line;
        }
        inputFile.close(); // Закрываем файл
    }
    else {
        std::cerr << "Не удалось открыть файл." << std::endl; // Обработка ошибки
    }


    // Таблица замены
    map<string, char> replacement_table = {
        {"AA", ' '}, {"AF", 'з'}, {"AJ", '0'}, {"AN", 'a'}, {"BE", 'я'}, {"BF", '7'}, {"CC", 'ф'},
        {"CK", 'ч'}, {"CM", 'c'}, {"CP", 'ц'}, {"DB", 'Я'}, {"DC", '1'}, {"DD", 'г'}, {"DL", '-'},
        {"EG", '-'}, {"EI", 'й'}, {"EM", 'e'}, {"EO", 'В'}, {"FH", 'в'}, {"FO", '9'}, {"GA", '3'},
        {"GF", 'т'}, {"GN", '.'}, {"HA", 'У'}, {"HC", 'p'}, {"HD", 'м'}, {"HH", 'п'}, {"HI", 'э'},
        {"HM", '>'}, {"HN", 'Б'}, {"IC", 'г'}, {"IK", 'o'}, {"IL", 'ъ'}, {"IO", 'и'}, {"JA", 'н'},
        {"JB", 'e'}, {"JD", 'p'}, {"JE", ','}, {"KB", '4'}, {"KC", 'x'}, {"KJ", 'К'}, {"KK", 'б'},
        {"KO", 'О'}, {"LA", 'П'}, {"LH", 'и'},  {"MB", 'c'}, {"MF", 'ы'}, {"MH", '-'},{"CF", '<'},
        {"NB", 'ж'}, {"NF", 'ь'}, {"NO", 'д'}, {"OE", 'ш'}, {"ON", 'к'}, {"OO", 'у'}, {"OP", '2'},
        {"PD", 'л'}, {"PH", '5'}, {"PJ", 'ю'}, {"LJ", 'Ч'}, {"FN", 'З'}, {"FC", 'Ш'}, {"FP", 'Т'},
        {"GH", '7'}, {"PG", 'А'}, {"AL", '8'}, {"CL", 'Л'}, {"DH", 'Д'}, {"BG", ':'}, {"FD", '№'},
        {"ED", 'щ'}, {"PB", 'М'}, {"LD", 'Ф'}
    };

    vector<string> substrings;
    for (size_t i = 0; i < str.length(); i += 32) {
        substrings.push_back(str.substr(i, 32));
    }

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        for (const string& sub : substrings) {      // обработка текста и его запись в файл
            string processed_sub = processSubstring(sub, replacement_table);
            outputFile << processed_sub;
        }
        outputFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }

    return 0;
}