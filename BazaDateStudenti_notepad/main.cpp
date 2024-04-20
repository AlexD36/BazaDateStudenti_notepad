#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Definirea structurilor
struct Student {
    int id;
    string nume;
    string prenume;
};

struct Nota {
    int idNota; // Adaugarea unui camp pentru id-ul notei
    int idStudent; // Adaugarea unui camp pentru id-ul studentului
    float valoareNota;
    string dataNota;
};

// Functie pentru a citi ultimul ID de student din baza de date
int citesteUltimulIdStudent() {
    ifstream file("studenti.txt");
    int id = 0;
    if (file.is_open()) {
        int tempId;
        string nume, prenume;
        while (file >> tempId >> nume >> prenume) {
            id = tempId;
        }
        file.close();
    }
    return id;
}

// Functie pentru a adauga un student in baza de date
void adaugaStudent(const Student& student) {
    ofstream file("studenti.txt", ios::app);
    file << student.id << ' ' << student.nume << ' ' << student.prenume << endl;
    file.close();
}

//Functie pentru a sterge un student din baza de date
void stergeStudent(int idStudent) {
    // Șterge studentul din fișierul "studenti.txt"
    ifstream inFile("studenti.txt");
    ofstream outFile("temp.txt");
    int id;
    string nume, prenume;
    bool studentSters = false; // Flag pentru a indica dacă studentul a fost deja șters
    while (inFile >> id >> nume >> prenume) {
        if (id == idStudent) {
            studentSters = true; // Marcaj pentru a indica că studentul a fost găsit și șters
        }
        else {
            if (studentSters) {
                // Actualizează id-ul studentului dacă acesta urmează după studentul șters
                outFile << id - 1 << ' ' << nume << ' ' << prenume << endl;
            }
            else {
                outFile << id << ' ' << nume << ' ' << prenume << endl;
            }
        }
    }
    inFile.close();
    outFile.close();
    remove("studenti.txt");
    rename("temp.txt", "studenti.txt");

    // Șterge toate notele asociate studentului din fișierul "note.txt"
    ifstream inFile2("note.txt");
    ofstream outFile2("temp2.txt");
    int idNota, idStudentNota;
    float nota;
    string dataNota;
    while (inFile2 >> idNota >> idStudentNota >> nota >> dataNota) {
        if (idStudentNota != idStudent) {
            outFile2 << idNota << ' ' << idStudentNota << ' ' << nota << ' ' << dataNota << endl;
        }
    }
    inFile2.close();
    outFile2.close();
    remove("note.txt");
    rename("temp2.txt", "note.txt");

    cout << "Studentul si toate notele asociate au fost sterse cu succes." << endl;
}

// Functie pentru a afisa studentii din baza de date
void afiseazaStudenti() {
    ifstream file("studenti.txt");
    if (file.is_open()) {
        int id;
        string nume, prenume;
        while (file >> id >> nume >> prenume) {
            cout << "ID: " << id << ", Nume: " << nume << ", Prenume: " << prenume << endl;
        }
        file.close();
    }
    else {
        cout << "Nu exista studenti in baza de date." << endl;
    }
}

// Functie pentru a afisa notele unui student
void afiseazaNoteleStudentului(int idStudent) {
    ifstream file("note.txt");
    if (file.is_open()) {
        int idNota;
        int idStudentNota;
        float nota;
        string dataNota;
        bool found = false;
        while (file >> idNota >> idStudentNota >> nota >> dataNota) {
            if (idStudent == idStudentNota) {
                cout << "ID Nota: " << idNota << ", Nota: " << nota << ", Data: " << dataNota << endl;
                found = true;
            }
        }
        file.close();
        if (!found) {
            cout << "Nu exista note pentru acest student." << endl;
        }
    }
    else {
        cout << "Nu exista note in baza de date." << endl;
    }
}

// Functie pentru a afisa meniul principal
void afiseazaMeniuPrincipal() {
    cout << "\nMeniu Principal:";
    cout << "\n1. Afiseaza studenti";
    cout << "\n2. Selecteaza student";
    cout << "\n3. Adauga student";
    cout << "\n0. Iesire\n";
}

// Functie pentru a afisa meniul studentului
void afiseazaMeniuStudent(const string& numeStudent) {
    cout << "\nMeniu Student (" << numeStudent << "):";
    cout << "\n1. Afiseaza notele";
    cout << "\n2. Modifica note";
    cout << "\n3. Sterge student";
    cout << "\n0. Inapoi la meniul principal\n";
}

// Functie pentru a afisa meniul de modificare a notelor
void afiseazaMeniuModificareNote() {
    cout << "\nMeniu Modificare Note:";
    cout << "\n1. Adauga nota";
    cout << "\n2. Sterge nota";
    cout << "\n0. Inapoi la meniul studentului\n";
}

//Functie pentru al ID al ultimei note
int citesteUltimulIdNota(int idStudent) {
    ifstream file("note.txt");
    int id = 0;
    if (file.is_open()) {
        int tempId;
        int tempIdStudent;
        float nota;
        string dataNota;
        while (file >> tempId >> tempIdStudent >> nota >> dataNota) {
            if (idStudent == tempIdStudent) {
                id = tempId;
            }
        }
        file.close();
    }
    return id;
}


// Functie pentru a adauga nota unui student
void adaugaNota(const Nota& nota) {
    int idUltimaNota = citesteUltimulIdNota(nota.idStudent); // Citeste ultimul ID al notei pentru studentul selectat
    ofstream file("note.txt", ios::app);
    file << ++idUltimaNota << ' ' << nota.idStudent << ' ' << nota.valoareNota << ' ' << nota.dataNota << endl;
    file.close();
}

// Functie pentru a selecta un student dupa ID
Student selecteazaStudentDupaId(int idCautat) {
    ifstream file("studenti.txt");
    Student student;
    if (file.is_open()) {
        while (file >> student.id >> student.nume >> student.prenume) {
            if (student.id == idCautat) {
                file.close();
                return student;
            }
        }
        file.close();
    }
    student.id = -1;
    return student;
}

// Functie pentru a modifica notele unui student
void modificaNoteleStudentului(int idStudent) {
    int optiune;
    bool iesire = false;
    while (!iesire) {
        afiseazaMeniuModificareNote();
        cout << "Introduceti optiunea: ";
        cin >> optiune;
        switch (optiune) {
        case 1: {
            Nota nota;
            nota.idStudent = idStudent;
            cout << "Introduceti nota: ";
            cin >> nota.valoareNota;
            cout << "Introduceti data pentru nota (de tipul zi/luna/an): ";
            cin >> nota.dataNota;
            adaugaNota(nota);
            cout << "Nota a fost adaugata cu succes." << endl;
            break;
        }
        case 2: {
            // Implementare pentru a șterge nota (opțional)
            cout << "Optiunea pentru stergerea notei nu este implementata inca." << endl;
            break;
        }
        case 0: {
            iesire = true;
            break;
        }
        default: {
            cout << "Optiune invalida! Va rugam selectati din nou." << endl;
            break;
        }
        }
    }
}

int main() {
    int optiune;
    bool iesire = false;
    int ultimulIdStudentSelectat = -1; // Variabila pentru a stoca ID-ul ultimului student selectat

    do {
        afiseazaMeniuPrincipal();
        cout << "Introduceti optiunea: ";
        cin >> optiune;
        switch (optiune) {
        case 1: {
            cout << "Studentii din baza de date sunt:" << endl;
            afiseazaStudenti();
            break;
        }
        case 2: {
            int idStudent;
            cout << "Introduceti ID-ul studentului: ";
            cin >> idStudent;
            Student student = selecteazaStudentDupaId(idStudent);
            if (student.id != -1) {
                ultimulIdStudentSelectat = student.id; // Actualizeaza ID-ul ultimului student selectat
                do {
                    afiseazaMeniuStudent(student.nume);
                    cout << "Introduceti optiunea: ";
                    cin >> optiune;
                    switch (optiune) {
                    case 1: {
                        // Afiseaza notele studentului
                        afiseazaNoteleStudentului(student.id);
                        break;
                    }
                    case 2: {
                        // Modifica notele studentului
                        modificaNoteleStudentului(student.id);
                        break;
                    }
                    case 3: {
                        // Intrebare de confirmare pentru stergerea studentului
                        char confirmare;
                        cout << "Esti sigur/a ca vrei sa stergi studentul " << student.nume << " din baza de date? (DA/NU): ";
                        cin >> confirmare;

                        if (confirmare == 'Y' || confirmare == 'y') {
                            // Implementarea pentru a șterge studentul
                            stergeStudent(idStudent);
                            optiune = 0; // Setati variabila pentru a reveni la meniul principal
                        }
                        else if (confirmare == 'N' || confirmare == 'n') {
                            // Revenirea la meniul studentului
                            optiune = 0;
                            break;
                        }
                        else {
                            cout << "Optiune invalida! Va rugam selectati din nou." << endl;
                        }
                        optiune = 0;
                        break;
                    }
                    case 0: {
                        break;
                    }
                    default: {
                        cout << "Optiune invalida! Va rugam selectati din nou." << endl;
                        break;
                    }
                    }
                } while (optiune != 0);
            }
            else {
                cout << "Nu exista student cu ID-ul specificat." << endl;
            }
            break;
        }
        case 3: {
            Student student;
            student.id = citesteUltimulIdStudent() + 1;
            cout << "Introduceti numele studentului: ";
            cin >> student.nume;
            cout << "Introduceti prenumele studentului: ";
            cin >> student.prenume;
            adaugaStudent(student);
            cout << "Studentul a fost adaugat cu succes. ID-ul studentului este: " << student.id << endl;
            break;
        }
        case 0: {
            iesire = true;
            break;
        }
        default: {
            cout << "Optiune invalida! Va rugam selectati din nou." << endl;
            break;
        }
        }
    } while (!iesire);

    return 0;
}