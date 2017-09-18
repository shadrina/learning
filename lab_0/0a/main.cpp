#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    cout << "Hello world!" << "\n";

    cout << Module1::getMyName() << "\n";
    cout << Module2::getMyName() << "\n";

    using namespace Module1;
    //используем функцию getMyName(), объявленную в пространстве имен Module1
    cout << getMyName() << "\n";
    //используем функцию getMyName(), объявленную в пространстве имен Module2
    cout << Module2::getMyName() << "\n";

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
    //cout << getMyName() << "\n"; // COMPILATION ERROR (C)

    using Module2::getMyName;
    //используем функцию getMyName(), объявленную в пространстве имен Module2
    cout << getMyName() << "\n";

    //COMPILATION ERROR
    //повторное using-объявление
    /*
     * using Module3::getMyName;
     * cout << getMyName() << "\n";
    */
    cout << Module3::getMyName() << "\n";

}
