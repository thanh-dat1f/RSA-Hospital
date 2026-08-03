#ifndef MENU_H
#define MENU_H

#include "../manager/PatientManager.h"

class Menu
{
private:

    PatientManager manager;

public:

    //==============================
    // Constructor - Destructor
    //==============================

    Menu();

    ~Menu();

    //==============================
    // Menu chính
    //==============================

    void mainMenu();

    //==============================
    // Menu đăng ký bệnh nhân
    //==============================

    void registerMenu();

    //==============================
    // Menu quản lý bệnh nhân
    //==============================

    void managementMenu();

    //==============================
    // Menu hồ sơ bệnh nhân
    //==============================

    void patientMenu();

    //==============================
    // Menu thùng rác
    //==============================

    void trashMenu();

    //==============================
    // Menu hàng đợi khám
    //==============================

    void queueMenu();

    //==============================
    // Menu tìm kiếm
    //==============================

    void searchMenu();

    //==============================
    // Các hàm hỗ trợ giao diện
    //==============================

    void clearScreen();

    void pause();

    void exitProgram();
};

#endif