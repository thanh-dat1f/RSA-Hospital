#ifndef PATIENTSTACK_H
#define PATIENTSTACK_H

#include "../models/Patient.h"

struct StackNode
{
    Patient data;
    StackNode *next;
};

class PatientStack
{
private:

    StackNode *top;

public:

    // Constructor
    PatientStack();

    // Destructor
    ~PatientStack();

    // Kiểm tra rỗng
    bool isEmpty();

    // Đưa bệnh nhân vào thùng rác
    void push(Patient patient);

    // Khôi phục bệnh nhân gần nhất
    bool pop(Patient &patient);

    // Xem bệnh nhân trên cùng
    Patient* peek();

    Patient* searchByID(const char id[]);

    bool removeByID(const char id[], Patient &patient);

    // Hiển thị thùng rác
    void display();

    // Đếm số lượng
    int count();

    // Xóa toàn bộ
    void clear();
};

#endif
