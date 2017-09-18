#include "module1.h"
#include "module2.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello world!" << "\n";

    std::cout << Module1::getMyName() << "\n";
    std::cout << Module2::getMyName() << "\n";

    using namespace Module1;
    //используем функцию getMyName(), объявленную в пространстве имен Module1
    std::cout << getMyName() << "\n";
    //используем функцию getMyName(), объявленную в пространстве имен Module2
    std::cout << Module2::getMyName() << "\n";

    //using namespace Module2; // (B)
    /*
     * Ошибка компиляции возникает в связи с конфликтом двух пространств имен.
     * В обоих определена функция getMyName(). Во избежание ошибки следует использовать
     * using-объявление, которое имеет больший приоритет, чем using-директива.
     * (показано ниже)
     *
     * Примечание с http://www.sbp-program.ru/cpp/sbp-cpp-namespace.htm :
     * "Using-объявление делает доступной переменную в локальной области видимости, т.е. происходит
     * локальное объявление имени. Using-директива делает доступными все имена из данного пространства
     * имен, но не объявляет их локально."
    */
    //std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)

    using Module2::getMyName;
    //используем функцию getMyName(), объявленную в пространстве имен Module2
    std::cout << getMyName() << "\n";

}
