#include <iostream>
#include "utils/menu.h"
#include "utils/InputUtils.h"

using namespace std;

int main()
{
    try
    {
        Menu menu;
        menu.mainMenu();
    }
    catch(const InputUtils::InputClosed &)
    {
        cout << "\nDa dong luong nhap. Ket thuc chuong trinh.\n";
    }

    return 0;
}
