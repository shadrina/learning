#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");
    CSVParser<int, int, double, int, int, char> parser(&file);
    for (std::tuple<int, int, double, int, int, char> rs : parser)
        std::cout << rs << std::endl;

    return 0;
}