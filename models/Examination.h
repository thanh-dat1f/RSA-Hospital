#ifndef EXAMINATION_H
#define EXAMINATION_H

#include <iostream>
#include <cstring>

using namespace std;

// Khai báo trước
class Prescription;

class Examination
{
private:

    char examinationID[15];      // Mã lần khám
    char examinationDate[15];    // Ngày khám
    char doctorName[50];         // Bác sĩ khám
    char diagnosis[100];         // Chẩn đoán
    char note[200];              // Ghi chú

    Prescription *prescription;  // Đơn thuốc

public:

    // Node của Linked List
    Examination *next;

    //============================
    // Constructor - Destructor
    //============================

    Examination();

    Examination(const Examination &other);

    Examination& operator=(const Examination &other);

    Examination(Examination &&other) noexcept;

    Examination& operator=(Examination &&other) noexcept;

    ~Examination();

    //============================
    // Setter
    //============================

    void setExaminationID(const char id[]);
    void setExaminationDate(const char date[]);
    void setDoctorName(const char doctor[]);
    void setDiagnosis(const char diagnosis[]);
    void setNote(const char note[]);
    void setPrescription(Prescription *prescription);

    //============================
    // Getter
    //============================

    char* getExaminationID();
    char* getExaminationDate();
    char* getDoctorName();
    char* getDiagnosis();
    char* getNote();
    Prescription* getPrescription();

    //============================
    // Nhập dữ liệu
    //============================

    void input();

    //============================
    // Hiển thị
    //============================

    void output();
};

#endif
