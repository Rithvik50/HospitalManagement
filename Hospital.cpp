#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Patient
{
    public:
        string name;
        int age;
        string address;
        string disease;

        Patient(string n, int a, string addr, string dis) : name(n), age(a), address(addr), disease(dis) {}

        void displayDetails() const
        {
            cout << "\nName: " << name << "\nAge: " << age << "\nAddress: " << address << "\nDisease: " << disease << "\n\n";
        }
};

void savePatientsToFile(const vector<Patient> &patients)
{
    ofstream outFile("patients.txt");

    if (outFile.is_open())
    {
        for (const auto &patient : patients)
        {
            outFile << patient.name << " " << patient.age << " " << patient.address << " " << patient.disease << "\n";
        }
        outFile.close();
        cout << "Patient data saved to 'patients.txt'.\n";
    }
    else
    {
        cout << "Unable to open the file for saving patient data.\n";
    }
}

void loadPatientsFromFile(vector<Patient> &patients)
{
    ifstream inFile("patients.txt");

    if (inFile.is_open())
    {
        string name, address, disease;
        int age;

        while (inFile >> name >> age >> address >> ws)
        {
            getline(inFile, disease);
            patients.push_back(Patient(name, age, address, disease));
        }

        inFile.close();
        cout << "Patient data loaded from 'patients.txt'.\n";
    }
    else
    {
        cout << "No existing patient data found.\n";
    }
}

int main()
{
    vector<Patient> patients;

    loadPatientsFromFile(patients);

    char choice;

    do
    {
        cout << "1. Add Patient\n";
        cout << "2. Display Patients\n";
        cout << "3. Retrieve Patient Data\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            string name, address, disease;
            int age;

            cout << "Enter patient name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter patient age: ";
            cin >> age;

            cout << "Enter patient address: ";
            cin.ignore();
            getline(cin, address);

            cout << "Enter patient disease: ";
            cin.ignore();
            getline(cin, disease);

            patients.push_back(Patient(name, age, address, disease));

            cout << "Patient added successfully!\n\n";
            break;
        }

        case '2':
        {
            if (patients.empty())
            {
                cout << "No patients to display.\n\n";
            }
            else
            {
                cout << "Patient Details:\n";
                for (const auto &patient : patients)
                {
                    patient.displayDetails();
                }
            }
            break;
        }

        case '3':
        {
            if (patients.empty())
            {
                cout << "No patients to retrieve.\n\n";
            }
            else
            {
                int index;
                cout << "Enter the index of the patient to retrieve: ";
                cin >> index;

                if (index >= 0 && index < patients.size())
                {
                    cout << "Retrieved Patient Details:\n";
                    patients[index].displayDetails();
                }
                else
                {
                    cout << "Invalid index.\n";
                }
            }
            break;
        }

        case '4':
            savePatientsToFile(patients);
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "Invalid choice. Please enter a valid option.\n\n";
        }
    } while (choice != '4');

    return 0;
}
