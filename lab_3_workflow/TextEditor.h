#ifndef LAB_3_WORKFLOW_TEXTHOLDER_H
#define LAB_3_WORKFLOW_TEXTHOLDER_H


#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

class TextEditor {
private:
    std::vector<std::string> strings;
public:
    explicit TextEditor();
    void read_file(const std::string &);
    void write_file(const std::string &);
    void grep(const std::string &);
    void sort();
    void replace(const std::string &, const std::string &);
    void dump(const std::string &);
};


#endif //LAB_3_WORKFLOW_TEXTHOLDER_H
