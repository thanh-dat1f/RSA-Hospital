#include "menu.h"
#include "InputUtils.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//======================================
// Constructor
//======================================

Menu::Menu()
{

}

//======================================
// Destructor
//======================================

Menu::~Menu()
{

}

//======================================
// Xóa màn hình
//======================================

void Menu::clearScreen()
{
    system("cls");
}

//======================================
// Tạm dừng
//======================================

void Menu::pause()
{
    system("pause");
}

//======================================
// Thoát chương trình
//======================================

void Menu::exitProgram()
{
    clearScreen();

    cout << "\n=====================================\n";
    cout << " CAM ON BAN DA SU DUNG CHUONG TRINH ";
    cout << "\n=====================================\n";
}
//======================================
// Menu chính
//======================================

void Menu::mainMenu()
{
    int choice = 0;

    do
    {
        clearScreen();

        cout << "\n=========================================\n";
        cout << "      HOSPITAL MANAGEMENT SYSTEM\n";
        cout << "=========================================\n";

        cout << "1. Dang ky benh nhan\n";
        cout << "2. Quan ly benh nhan\n";
        cout << "3. Hang doi kham\n";
        cout << "4. Tim kiem benh nhan\n";
        cout << "0. Thoat\n";

        cout << "=========================================\n";

        choice = InputUtils::readInt("Nhap lua chon: ", 0, 4);

        switch(choice)
        {
            case 1:

                registerMenu();

                break;

            case 2:

                managementMenu();

                break;

            case 3:

                queueMenu();

                break;

            case 4:

                searchMenu();

                break;

            case 0:

                exitProgram();

                break;

            default:

                cout << "\nLua chon khong hop le!\n";

                pause();
        }

    }while(choice != 0);
}
//======================================
// Menu đăng ký
//======================================

void Menu::registerMenu()
{
    int choice = 0;

    do
    {
        clearScreen();

        cout << "\n=====================================\n";
        cout << " DANG KY BENH NHAN\n";
        cout << "=====================================\n";

        cout << "1. Kham lan dau\n";
        cout << "2. Tai kham\n";
        cout << "0. Quay lai\n";

        choice = InputUtils::readInt("\nNhap lua chon: ", 0, 2);

        switch(choice)
        {
            case 1:

                manager.registerNewPatient();

                pause();

                break;

            case 2:

                manager.registerReturningPatient();

                pause();

                break;

            case 0:

                return;

            default:

                cout << "\nLua chon khong hop le!\n";

                pause();
        }

    }while(true);
}
//======================================
// Menu quản lý bệnh nhân
//======================================

void Menu::managementMenu()
{
    int choice = 0;

    do
    {
        clearScreen();

        cout << "\n=====================================\n";
        cout << " QUAN LY BENH NHAN\n";
        cout << "=====================================\n";

        cout << "1. Ho so benh nhan\n";
        cout << "2. Thung rac\n";
        cout << "0. Quay lai\n";

        choice = InputUtils::readInt("\nNhap lua chon: ", 0, 2);

        switch(choice)
        {
            case 1:

                patientMenu();

                break;

            case 2:

                trashMenu();

                break;

            case 0:

                return;

            default:

                cout << "\nLua chon khong hop le!\n";

                pause();
        }

    }while(true);
}
//======================================
// Menu hồ sơ bệnh nhân
//======================================

void Menu::patientMenu()
{
    int choice = 0;

    do
    {
        clearScreen();

        cout << "\n=====================================\n";
        cout << " HO SO BENH NHAN\n";
        cout << "=====================================\n";

        cout << "1. Danh sach benh nhan\n";
        cout << "2. Xem chi tiet\n";
        cout << "3. Xoa benh nhan\n";
        cout << "0. Quay lai\n";

        choice = InputUtils::readInt("\nNhap lua chon: ", 0, 3);

        switch(choice)
        {
            case 1:

                manager.showAllPatients();

                pause();

                break;

            case 2:

                manager.showPatientDetail();

                pause();

                break;

            case 3:

                manager.deletePatient();

                pause();

                break;

            case 0:

                return;

            default:

                cout << "\nLua chon khong hop le!\n";

                pause();
        }

    }while(true);
}
//======================================
// Menu thùng rác
//======================================

void Menu::trashMenu()
{
    int choice = 0;

    do
    {
        clearScreen();

        cout << "\n=====================================\n";
        cout << " THUNG RAC\n";
        cout << "=====================================\n";

        cout << "1. Danh sach da xoa\n";
        cout << "2. Khoi phuc benh nhan\n";
        cout << "3. Xoa vinh vien\n";
        cout << "0. Quay lai\n";

        choice = InputUtils::readInt("\nNhap lua chon: ", 0, 3);

        switch(choice)
        {
            case 1:

                manager.showTrash();

                pause();

                break;

            case 2:

                manager.restorePatient();

                pause();

                break;

            case 3:

                manager.deleteForever();

                pause();

                break;

            case 0:

                return;

            default:

                cout << "\nLua chon khong hop le!\n";

                pause();
        }

    }while(true);
}
//======================================
// Menu hàng đợi khám
//======================================

void Menu::queueMenu()
{
    int choice = 0;

    do
    {
        clearScreen();

        cout << "\n=====================================\n";
        cout << " HANG DOI KHAM\n";
        cout << "=====================================\n";

        cout << "1. Danh sach dang cho\n";
        cout << "2. Benh nhan dang kham\n";
        cout << "3. Goi benh nhan tiep theo\n";
        cout << "4. Hoan thanh kham\n";
        cout << "0. Quay lai\n";

        choice = InputUtils::readInt("\nNhap lua chon: ", 0, 4);

        switch(choice)
        {
            case 1:

                manager.displayWaitingQueue();

                pause();

                break;

            case 2:

                manager.displayCurrentPatient();

                pause();

                break;

            case 3:

                manager.callNextPatient();

                pause();

                break;

            case 4:

                manager.finishExamination();

                pause();

                break;

            case 0:

                return;

            default:

                cout << "\nLua chon khong hop le!\n";

                pause();
        }

    }while(true);
}
//======================================
// Menu tìm kiếm
//======================================

void Menu::searchMenu()
{
    int choice = 0;

    do
    {
        clearScreen();

        cout << "\n=====================================\n";
        cout << " TIM KIEM BENH NHAN\n";
        cout << "=====================================\n";

        cout << "1. Theo ma benh nhan\n";
        cout << "2. Theo CCCD\n";
        cout << "3. Theo ho ten\n";
        cout << "0. Quay lai\n";

        choice = InputUtils::readInt("\nNhap lua chon: ", 0, 3);

        switch(choice)
        {
            case 1:

                manager.searchByID();

                pause();

                break;

            case 2:

                manager.searchByCCCD();

                pause();

                break;

            case 3:

                manager.searchByName();

                pause();

                break;

            case 0:

                return;

            default:

                cout << "\nLua chon khong hop le!\n";

                pause();
        }

    }while(true);
}
