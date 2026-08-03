#ifndef APPOINTMENTQUEUE_H
#define APPOINTMENTQUEUE_H

#include "../models/Patient.h"

using namespace std;

//==============================
// Node của Queue
//==============================

struct QueueNode
{
    Patient data;
    QueueNode *next;
};

//==============================
// Queue quản lý hàng đợi khám
//==============================

class AppointmentQueue
{
private:

    QueueNode *front;
    QueueNode *rear;

public:

    //==============================
    // Constructor - Destructor
    //==============================

    AppointmentQueue();

    ~AppointmentQueue();

    //==============================
    // Kiểm tra
    //==============================

    bool isEmpty();

    int count();

    //==============================
    // Thao tác Queue
    //==============================

    // Thêm bệnh nhân vào cuối hàng
    void enqueue(Patient patient);

    // Lấy bệnh nhân đầu hàng
    bool dequeue(Patient &patient);

    // Xem bệnh nhân đầu hàng
    Patient* peek();

    bool containsPatientID(const char id[]);

    int removeByPatientID(const char id[]);

    //==============================
    // Chức năng khám bệnh
    //==============================

    // Gọi bệnh nhân đầu tiên
    void callNextPatient();

    // Bệnh nhân có mặt
    bool patientPresent(Patient &patient);

    // Bệnh nhân vắng mặt
    bool patientAbsent();

    //==============================
    // Xử lý khi vắng mặt
    //==============================

    // Đổi lượt với người kế tiếp
    bool swapWithNext();

    // Hủy lượt khám
    bool cancelAppointment();

    //==============================
    // Hiển thị
    //==============================

    void display();

    //==============================
    // Xóa toàn bộ Queue
    //==============================

    void clear();
};

#endif
