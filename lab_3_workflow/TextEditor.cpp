#include "TextEditor.h"

TextEditor::TextEditor() : strings({}) {}

void TextEditor::read_file(const std::string &file_name) {
    std::ifstream file(file_name);
    // TODO if (!file.is_open()) throw NoFileException;
    std::string s;
    while (getline(file, s)) strings.push_back(s);
    file.close();
}

void TextEditor::write_file(const std::string &file_name) {
    std::ofstream file(file_name);
    // TODO if (!file.is_open()) throw NoFileException;
    int i = 0;
    while (i != strings.size()) {
        file << strings[i];
        strings.erase(strings.begin() + i);
        i++;
    }
    file.close();
}

void TextEditor::grep(const std::string &s) {
    for (int i = 0; i < strings.size(); i++) {
        if (strings[i].find(s) == std::string::npos) {
            strings.erase(strings.begin() + i, strings.begin() + i + 1);
            i--;
        }
    }
}

void TextEditor::sort() {
    std::sort(strings.begin(), strings.end());
}

void TextEditor::replace(const std::string &search, const std::string &replace) {
    for (auto &string : strings) {
        for (size_t pos = 0;; pos += replace.length()) {
            pos = string.find(search, pos);
            if (pos == std::string::npos) break;
            string.erase(pos, search.length());
            string.insert(pos, replace);
        }
    }
}

void TextEditor::dump(const std::string &file_name) {
    std::ofstream file(file_name);
    // TODO if (!file.is_open()) throw NoFileException;
    int i = 0;
    while (i != strings.size()) {
        file << strings[i];
        i++;
    }
    file.close();
}



