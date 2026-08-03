#include "AppointmentQueue.h"
#include <iostream>
#include <cstring>

using namespace std;

//======================================
// Constructor
//======================================

AppointmentQueue::AppointmentQueue()
{
    front = NULL;
    rear = NULL;
}

//======================================
// Destructor
//======================================

AppointmentQueue::~AppointmentQueue()
{
    clear();
}

//======================================
// Kiểm tra rỗng
//======================================

bool AppointmentQueue::isEmpty()
{
    return front == NULL;
}

//======================================
// Đếm số lượng bệnh nhân
//======================================

int AppointmentQueue::count()
{
    int dem = 0;

    QueueNode *p = front;

    while(p != NULL)
    {
        dem++;

        p = p->next;
    }

    return dem;
}

//======================================
// Thêm bệnh nhân vào cuối hàng
//======================================

void AppointmentQueue::enqueue(Patient patient)
{
    QueueNode *p = new QueueNode;

    p->data = patient;
    p->data.resetMissedCall();
    p->next = NULL;

    if(front == NULL)
    {
        front = rear = p;
    }
    else
    {
        rear->next = p;
        rear = p;
    }
}

//======================================
// Lấy bệnh nhân đầu hàng
//======================================

bool AppointmentQueue::dequeue(Patient &patient)
{
    if(front == NULL)
    {
        return false;
    }

    QueueNode *temp = front;

    patient = temp->data;

    front = front->next;

    if(front == NULL)
    {
        rear = NULL;
    }

    delete temp;

    return true;
}

//======================================
// Xem bệnh nhân đầu hàng
//======================================

Patient* AppointmentQueue::peek()
{
    if(front == NULL)
    {
        return NULL;
    }

    return &(front->data);
}

bool AppointmentQueue::containsPatientID(const char id[])
{
    QueueNode *current = front;
    while(current != NULL)
    {
        if(strcmp(current->data.getPatientID(), id) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

int AppointmentQueue::removeByPatientID(const char id[])
{
    int removed = 0;
    QueueNode *current = front;
    QueueNode *previous = NULL;

    while(current != NULL)
    {
        if(strcmp(current->data.getPatientID(), id) == 0)
        {
            QueueNode *deleted = current;
            current = current->next;

            if(previous == NULL)
            {
                front = current;
            }
            else
            {
                previous->next = current;
            }

            if(deleted == rear)
            {
                rear = previous;
            }

            delete deleted;
            ++removed;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    if(front == NULL)
    {
        rear = NULL;
    }

    return removed;
}

//======================================
// Gọi bệnh nhân tiếp theo
//======================================

void AppointmentQueue::callNextPatient()
{
    if(front == NULL)
    {
        cout << "\nKhong co benh nhan nao dang cho!\n";
        return;
    }

    cout << "\n=================================\n";
    cout << "GOI BENH NHAN TIEP THEO\n";
    cout << "=================================\n";

    front->data.output();
}

//======================================
// Bệnh nhân có mặt
//======================================

bool AppointmentQueue::patientPresent(Patient &patient)
{
    return dequeue(patient);
}

//======================================
// Đổi lượt với người kế tiếp
//======================================

bool AppointmentQueue::swapWithNext()
{
    if(front == NULL)
    {
        return false;
    }

    if(front->next == NULL)
    {
        return false;
    }

    QueueNode *first = front;

    QueueNode *second = front->next;

    first->next = second->next;

    second->next = first;

    front = second;

    if(first->next == NULL)
    {
        rear = first;
    }

    return true;
}

//======================================
// Hủy lượt khám
//======================================

bool AppointmentQueue::cancelAppointment()
{
    if(front == NULL)
    {
        return false;
    }

    Patient temp;

    dequeue(temp);

    cout << "\n=================================\n";
    cout << "HUY LUOT KHAM\n";
    cout << "=================================\n";

    cout << "Benh nhan:\n";

    temp.output();

    cout << "\nDa vang mat 3 lan.\n";

    return true;
}

//======================================
// Bệnh nhân vắng mặt
//======================================

bool AppointmentQueue::patientAbsent()
{
    if(front == NULL)
    {
        return false;
    }

    front->data.increaseMissedCall();

    cout << "\nBenh nhan vang mat!\n";

    cout << "So lan vang: "
         << front->data.getMissedCall()
         << "/3\n";

    if(front->data.getMissedCall() >= 3)
    {
        cancelAppointment();

        return !isEmpty();
    }

    if(swapWithNext())
    {
        cout << "\nDa doi luot voi benh nhan ke tiep.\n";
        return true;
    }

    cout << "\nKhong co benh nhan ke tiep. Giu nguyen luot cho lan goi sau.\n";
    return false;
}

//======================================
// Hiển thị Queue
//======================================

void AppointmentQueue::display()
{
    if(front == NULL)
    {
        cout << "\nHang doi rong!\n";

        return;
    }

    QueueNode *p = front;

    cout << "\n==============================\n";
    cout << "HANG DOI KHAM\n";
    cout << "==============================\n\n";

    cout << "Front\n\n";

    while(p != NULL)
    {
        p->data.output();

        if(p->next != NULL)
        {
            cout << "       |\n";
            cout << "       V\n";
        }

        p = p->next;
    }

    cout << "\nRear\n";
}

//======================================
// Xóa toàn bộ Queue
//======================================

void AppointmentQueue::clear()
{
    while(front != NULL)
    {
        QueueNode *temp = front;

        front = front->next;

        delete temp;
    }

    rear = NULL;
}
