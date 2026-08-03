#include "Examination.h"
#include "Prescription.h"
#include "../utils/InputUtils.h"

using namespace std;

//======================================
// Constructor
//======================================

Examination::Examination()
{
    examinationID[0] = '\0';
    examinationDate[0] = '\0';
    doctorName[0] = '\0';
    diagnosis[0] = '\0';
    note[0] = '\0';

    prescription = NULL;
    next = NULL;
}

Examination::Examination(const Examination &other)
{
    InputUtils::copyToBuffer(examinationID, other.examinationID);
    InputUtils::copyToBuffer(examinationDate, other.examinationDate);
    InputUtils::copyToBuffer(doctorName, other.doctorName);
    InputUtils::copyToBuffer(diagnosis, other.diagnosis);
    InputUtils::copyToBuffer(note, other.note);
    prescription = other.prescription == NULL
        ? NULL : new Prescription(*other.prescription);
    next = other.next == NULL ? NULL : new Examination(*other.next);
}

Examination& Examination::operator=(const Examination &other)
{
    if(this == &other)
    {
        return *this;
    }

    Prescription *newPrescription = other.prescription == NULL
        ? NULL : new Prescription(*other.prescription);
    Examination *newNext = NULL;

    try
    {
        newNext = other.next == NULL ? NULL : new Examination(*other.next);
    }
    catch(...)
    {
        delete newPrescription;
        throw;
    }

    delete prescription;
    delete next;

    InputUtils::copyToBuffer(examinationID, other.examinationID);
    InputUtils::copyToBuffer(examinationDate, other.examinationDate);
    InputUtils::copyToBuffer(doctorName, other.doctorName);
    InputUtils::copyToBuffer(diagnosis, other.diagnosis);
    InputUtils::copyToBuffer(note, other.note);
    prescription = newPrescription;
    next = newNext;

    return *this;
}

Examination::Examination(Examination &&other) noexcept
{
    InputUtils::copyToBuffer(examinationID, other.examinationID);
    InputUtils::copyToBuffer(examinationDate, other.examinationDate);
    InputUtils::copyToBuffer(doctorName, other.doctorName);
    InputUtils::copyToBuffer(diagnosis, other.diagnosis);
    InputUtils::copyToBuffer(note, other.note);
    prescription = other.prescription;
    next = other.next;
    other.prescription = NULL;
    other.next = NULL;
}

Examination& Examination::operator=(Examination &&other) noexcept
{
    if(this == &other)
    {
        return *this;
    }

    delete prescription;
    delete next;

    InputUtils::copyToBuffer(examinationID, other.examinationID);
    InputUtils::copyToBuffer(examinationDate, other.examinationDate);
    InputUtils::copyToBuffer(doctorName, other.doctorName);
    InputUtils::copyToBuffer(diagnosis, other.diagnosis);
    InputUtils::copyToBuffer(note, other.note);
    prescription = other.prescription;
    next = other.next;
    other.prescription = NULL;
    other.next = NULL;

    return *this;
}

//======================================
// Destructor
//======================================

Examination::~Examination()
{
    delete prescription;
    delete next;
    prescription = NULL;
    next = NULL;
}

//======================================
// Setter
//======================================

void Examination::setExaminationID(const char id[])
{
    InputUtils::copyToBuffer(examinationID, id);
}

void Examination::setExaminationDate(const char date[])
{
    InputUtils::copyToBuffer(examinationDate, date);
}

void Examination::setDoctorName(const char doctor[])
{
    InputUtils::copyToBuffer(doctorName, doctor);
}

void Examination::setDiagnosis(const char text[])
{
    InputUtils::copyToBuffer(diagnosis, text);
}

void Examination::setNote(const char text[])
{
    InputUtils::copyToBuffer(note, text);
}

void Examination::setPrescription(Prescription *p)
{
    if(prescription == p)
    {
        return;
    }

    delete prescription;
    prescription = p;
}

//======================================
// Getter
//======================================

char* Examination::getExaminationID()
{
    return examinationID;
}

char* Examination::getExaminationDate()
{
    return examinationDate;
}

char* Examination::getDoctorName()
{
    return doctorName;
}

char* Examination::getDiagnosis()
{
    return diagnosis;
}

char* Examination::getNote()
{
    return note;
}

Prescription* Examination::getPrescription()
{
    return prescription;
}

//======================================
// Nhập thông tin khám
//======================================

void Examination::input()
{
    cout << "\n=============================\n";
    cout << "NHAP THONG TIN KHAM BENH\n";
    cout << "=============================\n";

    const string date = InputUtils::readDate("Ngay kham (dd/mm/yyyy): ", false);
    const string doctor = InputUtils::readLine("Ten bac si: ", 49);
    const string result = InputUtils::readLine("Chan doan: ", 99);
    const string examinationNote = InputUtils::readLine("Ghi chu: ", 199, true);

    setExaminationDate(date.c_str());
    setDoctorName(doctor.c_str());
    setDiagnosis(result.c_str());
    setNote(examinationNote.c_str());
}

//======================================
// Hiển thị thông tin khám
//======================================

void Examination::output()
{
    const Examination *exam = this;
    int examinationNumber = 1;

    while(exam != NULL)
    {
        cout << "\n=================================\n";
        cout << "THONG TIN LAN KHAM " << examinationNumber << "\n";
        cout << "=================================\n";

        cout << "Ma lan kham : " << exam->examinationID << endl;
        cout << "Ngay kham   : " << exam->examinationDate << endl;
        cout << "Bac si      : " << exam->doctorName << endl;
        cout << "Chan doan   : " << exam->diagnosis << endl;
        cout << "Ghi chu     : " << exam->note << endl;

        if(exam->prescription != NULL)
        {
            cout << "\n----- DON THUOC -----\n";
            const Prescription *medicine = exam->prescription;
            int medicineNumber = 1;

            while(medicine != NULL)
            {
                cout << "\nThuoc " << medicineNumber << ":\n";
                medicine->output();
                medicine = medicine->next;
                ++medicineNumber;
            }
        }

        cout << "=================================\n";
        exam = exam->next;
        ++examinationNumber;
    }
}
