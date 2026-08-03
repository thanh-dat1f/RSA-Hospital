#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <iostream>
#include <cstring>

using namespace std;

class Prescription
{
private:

    char medicineName[50];      // Tên thuốc
    int quantity;               // Số lượng
    char dosage[50];            // Liều dùng
    char instruction[100];      // Hướng dẫn sử dụng

public:

    // Node của Linked List
    Prescription *next;

    //==============================
    // Constructor - Destructor
    //==============================

    Prescription();

    Prescription(const Prescription &other);

    Prescription& operator=(const Prescription &other);

    Prescription(Prescription &&other) noexcept;

    Prescription& operator=(Prescription &&other) noexcept;

    ~Prescription();

    //==============================
    // Setter
    //==============================

    void setMedicineName(const char name[]);
    void setQuantity(int quantity);
    void setDosage(const char dosage[]);
    void setInstruction(const char instruction[]);

    //==============================
    // Getter
    //==============================

    char* getMedicineName();
    int getQuantity();
    char* getDosage();
    char* getInstruction();

    //==============================
    // Nhập thông tin thuốc
    //==============================

    void input();

    //==============================
    // Hiển thị thuốc
    //==============================

    void output() const;
};

#endif
