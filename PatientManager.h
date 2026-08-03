#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include "../struct/PatientLinkedList.h"
#include "../struct/PatientStack.h"
#include "../struct/AppointmentQueue.h"
#include "../models/Examination.h"
#include "../models/Prescription.h"

class PatientManager
{
private:

    PatientLinkedList patientList;

    AppointmentQueue waitingQueue;

    PatientStack trash;

    int patientCount;
    Patient currentPatient;      // Bệnh nhân đang khám
     bool examining;              // Có đang khám hay không

public:

    //==============================
    // Constructor
    //==============================

    PatientManager();

    ~PatientManager();

    //==============================
    // Đăng ký
    //==============================

    void registerNewPatient();

    void registerReturningPatient();

    //==============================
    // Hàng đợi khám
    //==============================

    void callNextPatient();

    void finishExamination();

    //==============================
    // Hồ sơ bệnh nhân
    //==============================

    void showAllPatients();

    void showPatientDetail();

    void deletePatient();

    //==============================
    // Thùng rác
    //==============================

    void showTrash();

    void restorePatient();

    void deleteForever();

    //==============================
    // Tìm kiếm
    //==============================

    void searchByID();

    void searchByCCCD();

    void searchByName();

    //==============================
    // Sinh mã bệnh nhân
    //==============================

    void generatePatientID(char id[]);
    //=========================
// Hàng đợi khám
//=========================

void displayWaitingQueue();

void displayCurrentPatient();
};

#endif