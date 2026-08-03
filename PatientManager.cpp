#include "PatientManager.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "../models/Prescription.h"

using namespace std;

//======================================
// Constructor
//======================================

PatientManager::PatientManager()
{
    patientCount = 0;
    examining = false;
}

//======================================
// Destructor
//======================================

PatientManager::~PatientManager()
{

}

//======================================
// Sinh mã bệnh nhân
//======================================

void PatientManager::generatePatientID(char id[])
{
    patientCount++;

    sprintf(id, "BN%06d", patientCount);
}

//======================================
// Đăng ký bệnh nhân mới
//======================================

void PatientManager::registerNewPatient()
{
    Patient patient;

    char id[15];

    generatePatientID(id);

    patient.setPatientID(id);

    cout << "\n==============================\n";
    cout << "DANG KY BENH NHAN MOI\n";
    cout << "==============================\n";

    patient.input();

    patientList.addLast(patient);

    waitingQueue.enqueue(patient);

    cout << "\n==============================\n";
    cout << "DANG KY THANH CONG!\n";
    cout << "==============================\n";

    cout << "Ma benh nhan : " << id << endl;
    cout << "Da them vao hang doi kham.\n";
}

//======================================
// Đăng ký tái khám
//======================================

void PatientManager::registerReturningPatient()
{
    char id[15];

    cout << "\nNhap ma benh nhan: ";

    cin >> id;

    PatientNode *node = patientList.searchByID(id);

    if(node == NULL)
    {
        cout << "\nKhong tim thay benh nhan!\n";
        return;
    }

    waitingQueue.enqueue(node->data);

    cout << "\n==============================\n";
    cout << "DANG KY TAI KHAM THANH CONG!\n";
    cout << "==============================\n";

    cout << "Benh nhan da duoc them vao hang doi.\n";
}
//======================================
// Gọi bệnh nhân tiếp theo
//======================================

void PatientManager::callNextPatient()
{
    if(examining)
    {
        cout << "\nDang co benh nhan trong phong kham!\n";
        return;
    }

    Patient *patient = waitingQueue.peek();

    if(patient == NULL)
    {
        cout << "\nKhong con benh nhan nao trong hang doi!\n";
        return;
    }

    cout << "\n=====================================\n";
    cout << "GOI BENH NHAN\n";
    cout << "=====================================\n";

    patient->output();

    cout << "\n";

    cout << "1. Benh nhan co mat\n";
    cout << "2. Benh nhan vang mat\n";

    int choose;

    cin >> choose;

    switch(choose)
    {
        case 1:
        {
            waitingQueue.patientPresent(currentPatient);

            examining = true;

            cout << "\nBenh nhan da vao phong kham.\n";

            break;
        }

        case 2:
        {
            waitingQueue.patientAbsent();

            cout << "\nDang goi benh nhan tiep theo...\n";

            callNextPatient();

            break;
        }

        default:

            cout << "\nLua chon khong hop le!\n";
    }
}
//======================================
// Hoàn thành khám
//======================================

void PatientManager::finishExamination()
{
    if(examining == false)
    {
        cout << "\nKhong co benh nhan nao dang kham!\n";
        return;
    }

    Examination *exam = new Examination;

    exam->input();

    cout << "\nNhap don thuoc ? (1-Co / 0-Khong): ";

    int choose;

    cin >> choose;

    if(choose == 1)
    {
        Prescription *head = NULL;
        Prescription *tail = NULL;

        while(true)
        {
            Prescription *medicine = new Prescription;

            medicine->input();

            if(head == NULL)
            {
                head = tail = medicine;
            }
            else
            {
                tail->next = medicine;
                tail = medicine;
            }

            cout << "\nThem thuoc nua ? (1-Co /0-Khong): ";

            cin >> choose;

            if(choose == 0)
                break;
        }

        exam->setPrescription(head);
    }

    PatientNode *node =
        patientList.searchByID(currentPatient.getPatientID());

    if(node != NULL)
    {
        node->data.setExamination(exam);
    }

    examining = false;

    cout << "\n=====================================\n";
    cout << "KHAM BENH THANH CONG!\n";
    cout << "=====================================\n";
}
//======================================
// Hiển thị danh sách bệnh nhân
//======================================

void PatientManager::showAllPatients()
{
    if(patientList.isEmpty())
    {
        cout << "\nDanh sach rong!\n";
        return;
    }

    patientList.display();
}

//======================================
// Hiển thị chi tiết bệnh nhân
//======================================

void PatientManager::showPatientDetail()
{
    char id[15];

    cout << "\nNhap ma benh nhan: ";
    cin >> id;

    PatientNode *node = patientList.searchByID(id);

    if(node == NULL)
    {
        cout << "\nKhong tim thay benh nhan!\n";
        return;
    }

    cout << "\n========== THONG TIN ==========\n";

    node->data.output();

    Examination *exam = node->data.getExamination();

    if(exam != NULL)
    {
        exam->output();
    }
    else
    {
        cout << "\nBenh nhan chua duoc kham.\n";
    }
}
//======================================
// Xóa bệnh nhân
//======================================

void PatientManager::deletePatient()
{
    char id[15];

    cout << "\nNhap ma benh nhan: ";

    cin >> id;

    PatientNode *node = patientList.searchByID(id);

    if(node == NULL)
    {
        cout << "\nKhong tim thay benh nhan!\n";
        return;
    }

    trash.push(node->data);

    patientList.deletePatient(id);

    cout << "\nDa chuyen vao thung rac.\n";
}
//======================================
// Hiển thị thùng rác
//======================================

void PatientManager::showTrash()
{
    if(trash.isEmpty())
    {
        cout << "\nThung rac rong!\n";
        return;
    }

    trash.display();
}
//======================================
// Khôi phục bệnh nhân
//======================================

void PatientManager::restorePatient()
{
    Patient patient;

    if(trash.pop(patient))
    {
        patientList.addLast(patient);

        cout << "\nKhoi phuc thanh cong.\n";
    }
    else
    {
        cout << "\nKhong co du lieu de khoi phuc.\n";
    }
}
//======================================
// Xóa vĩnh viễn
//======================================

void PatientManager::deleteForever()
{
    Patient patient;

    if(trash.pop(patient))
    {
        cout << "\nDa xoa vinh vien.\n";
    }
    else
    {
        cout << "\nThung rac rong.\n";
    }
}
//======================================
// Tìm theo mã bệnh nhân
//======================================

void PatientManager::searchByID()
{
    char id[15];

    cout << "\nNhap ma benh nhan: ";
    cin >> id;

    PatientNode *node = patientList.searchByID(id);

    if(node == NULL)
    {
        cout << "\nKhong tim thay benh nhan!\n";
        return;
    }

    cout << "\n=========== KET QUA ===========\n";

    node->data.output();

    Examination *exam = node->data.getExamination();

    if(exam != NULL)
    {
        exam->output();
    }
}
//======================================
// Tìm theo CCCD
//======================================

void PatientManager::searchByCCCD()
{
    char cccd[20];

    cout << "\nNhap CCCD: ";

    cin >> cccd;

    PatientNode *node = patientList.searchByCCCD(cccd);

    if(node == NULL)
    {
        cout << "\nKhong tim thay benh nhan!\n";
        return;
    }

    cout << "\n=========== KET QUA ===========\n";

    node->data.output();

    Examination *exam = node->data.getExamination();

    if(exam != NULL)
    {
        exam->output();
    }
}
//======================================
// Tìm theo họ tên
//======================================

void PatientManager::searchByName()
{
    char name[50];

    cin.ignore();

    cout << "\nNhap ho ten: ";

    cin.getline(name,50);

    PatientNode *node = patientList.searchByName(name);

    if(node == NULL)
    {
        cout << "\nKhong tim thay benh nhan!\n";
        return;
    }

    cout << "\n=========== KET QUA ===========\n";

    node->data.output();

    Examination *exam = node->data.getExamination();

    if(exam != NULL)
    {
        exam->output();
    }
}
//======================================
// Hiển thị hàng đợi khám
//======================================

void PatientManager::displayWaitingQueue()
{
    if(waitingQueue.isEmpty())
    {
        cout << "\n====================================\n";
        cout << "KHONG CO BENH NHAN DANG CHO KHAM!\n";
        cout << "====================================\n";
        return;
    }

    cout << "\n====================================\n";
    cout << "DANH SACH BENH NHAN DANG CHO KHAM\n";
    cout << "====================================\n";

    waitingQueue.display();
}
//======================================
// Hiển thị bệnh nhân đang khám
//======================================

void PatientManager::displayCurrentPatient()
{
    if(examining == false)
    {
        cout << "\n====================================\n";
        cout << "KHONG CO BENH NHAN DANG KHAM!\n";
        cout << "====================================\n";
        return;
    }

    cout << "\n====================================\n";
    cout << "BENH NHAN DANG KHAM\n";
    cout << "====================================\n";

    currentPatient.output();

    if(currentPatient.getExamination() != NULL)
    {
        cout << "\n========== KET QUA KHAM ==========\n";

        currentPatient.getExamination()->output();
    }
}
