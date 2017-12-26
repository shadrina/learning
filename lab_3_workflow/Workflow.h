#ifndef LAB_3_WORKFLOW_WORKFLOW_H
#define LAB_3_WORKFLOW_WORKFLOW_H


#include <map>
#include "Command.h"
#include "Parser.h"

class Workflow {
private:
    TextEditor *text;
    std::map<std::string, Command *> commands;
    std::map<unsigned int, std::string> blocks;
    std::queue<unsigned int> queue;
public:
    Workflow();
    ~Workflow();
    void parse_config(std::ifstream &);
    void work(std::string);
};


#endif //LAB_3_WORKFLOW_WORKFLOW_H
