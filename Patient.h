#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <cstring>

using namespace std;

// Khai báo trước
class Examination;

class Patient
{
private:

    //=========================
    // Thông tin bệnh nhân
    //=========================

    char patientID[15];
    char fullName[50];
    char dateOfBirth[15];
    bool gender;
    char citizenID[20];
    char phone[15];
    char email[50];
    char address[100];
    char insuranceID[20];

    //=========================
    // Lịch sử khám
    //=========================

    Examination *history;

    //=========================
    // Số lần vắng mặt
    //=========================

    int missedCall;

public:

    //=========================
    // Constructor - Destructor
    //=========================

    Patient();

    Patient(const Patient &other);

    Patient& operator=(const Patient &other);

    Patient(Patient &&other) noexcept;

    Patient& operator=(Patient &&other) noexcept;

    ~Patient();

    //=========================
    // Setter
    //=========================

    void setPatientID(const char id[]);
    void setFullName(const char name[]);
    void setDateOfBirth(const char dob[]);
    void setGender(bool g);
    void setCitizenID(const char cccd[]);
    void setPhone(const char phone[]);
    void setEmail(const char email[]);
    void setAddress(const char address[]);
    void setInsuranceID(const char insurance[]);

    void setHistory(Examination *history);

    // Nếu bạn dùng tên này trong PatientManager.cpp
    void setExamination(Examination *exam);

    //=========================
    // Getter
    //=========================

    char* getPatientID();
    char* getFullName();
    char* getDateOfBirth();
    bool getGender();
    char* getCitizenID();
    char* getPhone();
    char* getEmail();
    char* getAddress();
    char* getInsuranceID();

    Examination* getHistory();

    // Nếu PatientManager.cpp dùng tên này
    Examination* getExamination();

    //=========================
    // Quản lý số lần vắng
    //=========================

    void increaseMissedCall();

    void resetMissedCall();

    int getMissedCall();

    //=========================
    // Nhập xuất
    //=========================

    void input();

    void output();
};

#endif
