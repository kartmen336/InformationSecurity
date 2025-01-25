#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;

// Функция для удаления, а потом и перестановки символов в строке
string f(const string str);

// Функция для преобразования пары символов в символ из таблицы
char getReplacementSymbol(const string& pair, const map<string, char>& table) {
    auto it = table.find(pair);
    if (it != table.end()) {
        return it->second;
    }
    return '\0';  // Если пары нет в таблице, возвращаем нулевой символ.
}


string processSubstring(const string sub, const map<string, char>& table) {
    string result = sub;

    string result1 = f(result);

    string transformedString = "";
    // Проходим по строке с шагом в 2 символа
    for (size_t i = 0; i < result1.length() - 1; i += 2) {
        string pair = result1.substr(i, 2);
        char replacement = getReplacementSymbol(pair, table); //если в таблице есть замена, заменяет
        if (replacement != '\0') {
            transformedString += replacement;
        }
        else {
            transformedString += pair;
        }
    }

    return transformedString;
}

void Check_in(string str) { //Cчитает и выводит на экран пару символов и их количество вхождений в тексте
    
    unordered_map<std::string, int> pair_count;

    // Проходим по строке с шагом в 2 символа
    for (size_t i = 0; i < str.length() - 1; i += 2) {
        // Формируем пару символов
        std::string pair = str.substr(i, 2);
        pair_count[pair]++;
    }

    vector<pair<string, int>> sorted_pairs(pair_count.begin(), pair_count.end());

    // Сортировка по количеству вхождений
    std::sort(sorted_pairs.begin(), sorted_pairs.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Сортируем по убыванию
        });
    // Выводим результаты
    std::cout << "Количество вхождений пар символов:\n";
    for (const auto& entry : sorted_pairs) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
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
        {"AA", ' '}, {"FA", 'з'}, {"JA", '0'}, {"NA", 'a'}, {"EB", 'я'}, {"FB", '7'}, {"CC", 'ф'},
        {"KC", 'ч'}, {"MC", 'c'}, {"PC", 'ц'}, {"BD", 'Я'}, {"CD", '1'}, {"DD", 'г'}, {"LD", '-'},
        {"GE", '-'}, {"IE", 'й'}, {"ME", 'e'}, {"OE", 'В'}, {"HF", 'в'}, {"OF", '9'}, {"AG", '3'},
        {"FG", 'т'}, {"NG", '.'}, {"AH", 'У'}, {"CH", 'p'}, {"DH", 'м'}, {"HH", 'п'}, {"IH", 'э'},
        {"MH", '>'}, {"NH", 'Б'}, {"CI", 'г'}, {"KI", 'o'}, {"LI", 'ъ'}, {"OI", 'и'}, {"AJ", 'н'},
        {"BJ", 'e'}, {"DJ", 'p'}, {"EJ", ','}, {"BK", '4'}, {"CK", 'x'}, {"JK", 'К'}, {"KK", 'б'},
        {"OK", 'О'}, {"AL", 'П'}, {"HL", 'и'}, {"BM", 'c'}, {"FM", 'ы'}, {"HM", '-'}, {"FC", '<'},
        {"BN", 'ж'}, {"FN", 'ь'}, {"ON", 'д'}, {"EO", 'ш'}, {"NO", 'к'}, {"OO", 'у'}, {"PO", '2'},
        {"DP", 'л'}, {"HP", '5'}, {"JP", 'ю'}, {"JL", 'Ч'}, {"NF", 'З'}, {"CF", 'Ш'}, {"PF", 'Т'},
        {"HG", '7'}, {"GP", 'А'}, {"LA", '8'}, {"LC", 'Л'}, {"HD", 'Д'}, {"GB", ':'}, {"DF", '№'},
        {"DE", 'щ'}, {"BP", 'М'}, {"DL", 'Ф'}
    };

    vector<string> substrings;
    for (size_t i = 0; i < str.length(); i += 32) {
        substrings.push_back(str.substr(i, 32));
    }

    /*string new_str; 
    for (const string sub : substrings) {     
        new_str += f(sub);
    }
    Check_in(new_str);*/ // Cчитает и выводит на экран пару символов и их количество вхождений в тексте

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        for (const string sub : substrings) {      // обработка текста и его запись в файл
            string processed_sub = processSubstring(sub, replacement_table) ;
            outputFile << processed_sub;
        }
        outputFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }

    return 0;
}

string f(const string str) {
    string str1 = str;
    vector<int> to_remove = {1, 4, 6, 11, 12, 13, 15, 16, 17, 20, 22, 27, 28, 29, 31, 32};
    sort(to_remove.begin(), to_remove.end(), greater<int>()); // Сортировка в обратном порядке
    for (int pos : to_remove) {
        str1.erase(pos - 1, 1);
    }

    vector<int> positions = {3,4,0,1,2,7,5,6,11,12,8,9,10,15,13,14 }; // Позиции для перестановки

    string result1 = "";

    for (int pos : positions) {
        result1 += str1[pos]; // Добавляем символы на указанных позициях
    }
    return (result1);
}
