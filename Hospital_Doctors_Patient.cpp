#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//Define an abstract Person class that has virtual print() function for printing the
//information about a person.
class Person {
private:
    const string name;
    const int age;
    const int ss_number;
public:
    // Constructor with no parameters
    Person() : name(""), age(0), ss_number(0) {}
    // Constructor with parameters
    Person(string name, int age, int ss_number) : name(name), age(age), ss_number(ss_number) {}
    virtual void printInfo(){
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Social Security Number: " << ss_number << endl;
    }
    //getter and setter
    string getName() { return name; }
    int getAge() { return age; }
    int getSSNumber() { return ss_number; }
};

//Define Patient class as derived classes of Person.
class Patient : public Person {
private:
    int days; //number of days stayed in hospital
    double daily_charge; //daily charge
public:
    void printInfo() { //Overriden function
    }
    //constructor with parameters
    Patient(string name, int age, int ss_number) : Person(name, age, ss_number) {
        days = 0; //at the beginning the number of days stayed is 0
        daily_charge = 0; //at the beginning the daily charge is 0
        //print the information of a given patient in a .txt file, each information on a separate line with
        //title on the left side and use "Patient Information" as the header of the form.
        ifstream myFile("patient_information.txt");
        if (!myFile) {
            ofstream myFile("patient_information.txt");
            //write "Patient Information" to the file
            myFile << "Patient Information" << endl;
        }
        //open a file named "patient.txt" in append mode
        ofstream patient_file("patient_information.txt", ios::app);
        //write the patient information to the file
        patient_file << "Name: " << name << endl;
        patient_file << "Age: " << age << endl;
        patient_file << "Social Security Number: " << ss_number << endl;
        patient_file << "--------------------------------------------" << endl;
    }
    //setter functions
    int getDaysStayed() { return days; }
    double getDailyCharge() { return daily_charge; }

    //getter functions
    void setDaysStayed(int days_stayed) { this->days = days_stayed; }
    void setDailyCharge(double daily_charge) { this->daily_charge = this->daily_charge+daily_charge; }


    //The destructor of each class.
    ~Patient() {
        cout << "Total hospital charges: " << daily_charge << endl; //total hospital charges
    }

    // A friend function of the Patient class to calculate total expenses.
    friend double calculate_total_expenses(Patient patient);
};

double calculate_total_expenses(Patient patient) {
    double total_hospital_charge = patient.days * patient.daily_charge;
    return total_hospital_charge;
}

//Define Doctor class as derived classes of Person.
class Doctor : public Person {
private:
    const int officeNo;
    static int num_patients;
public:
    //constructor with parameters
    Doctor(string name, int age, int social_security_number, int office_number) : Person(name, age, social_security_number), officeNo(office_number) {}
    //getter and setter functions

    const int getOfficeNo() const {
        return officeNo;
    }

    static int getNumberOfPatients() {
        return num_patients;
    }

    static void setNumberOfPatients(int numberOfPatients) {
        num_patients = numberOfPatients;
    }

    void printInfo() {
    }
};





int main() {
    //create a hospital with at least 3 doctors and 5 patients
    vector<Doctor*> doctors;
    vector<Patient*> patients;

    //create 3 doctors
    Doctor* doctor1 = new Doctor("Ahmet Polat", 24, 64180006, 546);
    Doctor* doctor2 = new Doctor("Emre", 23, 64180009, 683);
    Doctor* doctor3 = new Doctor("Hasan", 22, 64180008, 420);
    //using push_back method, doctors added to the doctors vector that created above
    doctors.push_back(doctor1);
    doctors.push_back(doctor2);
    doctors.push_back(doctor3);

    //create 5 patients
    Patient* patient1 = new Patient("Gulsum", 21, 10004090);
    Patient* patient2 = new Patient("Ikbal", 20, 77080022);
    Patient* patient3 = new Patient("Ahmet", 24, 87654321);
    Patient* patient4 = new Patient("Polat", 23, 12345678);
    Patient* patient5 = new Patient("Hilal", 18, 75315985);

    patients.push_back(patient1);
    patients.push_back(patient2);
    patients.push_back(patient3);
    patients.push_back(patient4);
    patients.push_back(patient5);
    return 0;
}
