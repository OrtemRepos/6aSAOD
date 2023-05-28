#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <iostream>
using namespace std;
#include "Str.h";

//Вариант 5
int main()
{
    {
        Str str = Str("1234");

         Str str1 = str.substr(1, 3);
         cout << str1 << endl;

         str1 = str.substr(-2255, 15888);
         cout << str1 << endl;

         str = Str("1222222");


         str1 = Str("1222222");

         str += Str("oososos");

         cout << str << endl;;

         str = Str(19);
         cout << str << endl;;
    }
    _CrtDumpMemoryLeaks();
    return 0;

}

