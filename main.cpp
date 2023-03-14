/*
     ** by Danya Kry
     ** v 2.0
     ** https://vk.com/lol_funtik
*/

#include <iostream>     // для cout и cin
#include <fstream>      // для файлов
#include <cstdio>       // для remove()

using namespace std;

struct Student {    // информация о студенте
    string surname;
    int groupNumber;
    int physicsGrade;
    int mathGrade;
    int csGrade;
    float avgGrade;
};

/* ************************************ */
string openFile();
void loadOutFile(Student [], int&, string);   // загрузить записи из файла в массив
void delFile();

void addStudent(Student [], int&);
void viewStudents(Student [], int);
void solveTask(Student [], int);
void saveToFile(Student [], int, string);
void editStudents(Student [], int);

void nullCount();
/* ************************************ */

int main() {
    Student students[100];
    int count = 0;
    int choice;
    string fileName;
    
    system("open ."); // DEBUG
    
    do {
        cout << endl;
        cout << "1. Open file" << endl;
        cout << "2. Delete file" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                fileName = openFile();
                do {
                    cout << endl;
                    cout << "1. Add student" << endl;
                    cout << "2. View students" << endl;
                    cout << "3. Solve task" << endl;
                    cout << "4. Save to file" << endl;
                    cout << "5. Read from file" << endl;
                    cout << "6. Edit the student" << endl;
                    cout << "7. Exit" << endl;

                    cout << "Enter your choice: ";
                    cin >> choice;
                    
                    switch (choice) {
                        case 1:
                            addStudent(students, count);
                            break;
                            
                        case 2:
                            if (count == 0) {
                                nullCount();
                            } else {
                                viewStudents(students, count);
                            }
                            break;
                            
                        case 3:
                            if (count == 0) {
                                nullCount();
                            } else {
                                solveTask(students, count);
                            }
                            break;
                            
                        case 4:
                            if (count == 0) {
                                nullCount();
                            } else {
                                saveToFile(students, count, fileName);
                            }
                            break;
                            
                        case 5:
                            loadOutFile(students, count, fileName);
                            break;
                            
                        case 6:
                            if (count == 0) {
                                nullCount();
                            } else {
                                editStudents(students, count);
                            }
                            break;
                            
                        case 7:
                            cout << "Exiting program..." << endl;
                            break;

                        default:
                            cout << "Invalid choice. Try again." << endl;
                            break;
                    }
                } while (choice != 7);
                break;
                
            case 2:
                delFile();
                break;
                
            case 3:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
        

    } while (choice != 3);
    
}

string openFile() {
    string fileName;
    
    cout << "Enter file name: ";
    cin >> fileName;
    
    fstream file(fileName, ios_base::app);
    
    if (!file.is_open()) {
        cout << "**** file opening error ****" << endl;
        perror("open the file");
    }
    
    cout << "File with name " << fileName << " opened successfully." << endl;
    file.close();
    
    return fileName;
}

void delFile() {
    char fileName[80];
    
    cout << "Enter file name: ";
    cin >> fileName;
    
    if (remove(fileName) == 0) {
        cout << "File is removed successfully." << endl;
    } else {
        perror("remove");
    }
}

void loadOutFile(Student students[], int& count, string fileName) {
    ifstream fin(fileName);
    
    if (!fin.is_open()) {
        cout << "**** file opening error ****" << endl;
        return;
    }
    
    string line;
    
    while (getline(fin, line)) {
        if (line == "#") {
            count++;
            continue;
        }

        students[count].surname = line;

        getline(fin, line);
        students[count].groupNumber = stoi(line);

        getline(fin, line);
        students[count].physicsGrade = stoi(line);

        getline(fin, line);
        students[count].mathGrade = stoi(line);

        getline(fin, line);
        students[count].csGrade = stoi(line);

        getline(fin, line);
        students[count].avgGrade = stof(line);
    }

    fin.close();
    
    cout << "Successfully." << endl;
}

void addStudent(Student students[], int& count) {
    cout << "Enter student surname: ";
    cin >> students[count].surname;
    
    cout << "Enter student group number: ";
    cin >> students[count].groupNumber;

    cout << "Enter student physics grade: ";
    cin >> students[count].physicsGrade;

    cout << "Enter student math grade: ";
    cin >> students[count].mathGrade;

    cout << "Enter student CS grade: ";
    cin >> students[count].csGrade;

    students[count].avgGrade = (students[count].physicsGrade + students[count].mathGrade + students[count].csGrade) / 3.0;

    count++;
    
    cout << "Successfully." << endl;
}

void viewStudents(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "# " << i+1 << endl;
        cout << "Surname: " << students[i].surname << endl;
        cout << "Group number: " << students[i].groupNumber << endl;
        cout << "Physics grade: " << students[i].physicsGrade << endl;
        cout << "Math grade: " << students[i].mathGrade << endl;
        cout << "CS grade: " << students[i].csGrade << endl;
        cout << "Average grade: " << students[i].avgGrade << endl << endl;
    }
}

// Вычислить общий средний балл всех студентов и распечатать список студентов со средним баллом выше общего среднего балла
void solveTask(Student students[], int count) {
    double generalAvgGrade = 0.0;   // общий средний бал
    
    for (int i = 0; i < count; i++) {
        for (int i = 0; i < count; i++) {
            generalAvgGrade += students[i].avgGrade;
        }
        
        generalAvgGrade /= count;
        
        if (students[i].avgGrade > generalAvgGrade) {
            cout << "Surname: " << students[i].surname << endl;
            cout << "Group number: " << students[i].groupNumber << endl << endl;
        }
    }
}

void saveToFile(Student students[], int count, string fileName) {
    ofstream fout(fileName);
    
    if (!fout.is_open()) {
        cout << "**** file opening error ****" << endl;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fout << students[i].surname << endl;
        fout << students[i].groupNumber << endl;
        fout << students[i].physicsGrade << endl;
        fout << students[i].mathGrade << endl;
        fout << students[i].csGrade << endl;
        fout << students[i].avgGrade << endl;
        fout << "#" << endl;
    }

    fout.close();
    
    cout << "Successfully." << endl;
}

void editStudents(Student students[], int count) {
    string findName;
    
    cout << "Enter surname: ";
    cin >> findName;
    
    for (int i = 0; i < count; i++) {
        if (findName == students[i].surname) {
            cout << "It is okay." << endl;
            
            cout << "Enter student surname: ";
            cin >> students[i].surname;
            
            cout << "Enter student group number: ";
            cin >> students[i].groupNumber;

            cout << "Enter student physics grade: ";
            cin >> students[i].physicsGrade;

            cout << "Enter student math grade: ";
            cin >> students[i].mathGrade;

            cout << "Enter student CS grade: ";
            cin >> students[i].csGrade;

            students[i].avgGrade = (students[i].physicsGrade + students[i].mathGrade + students[i].csGrade) / 3.0;
            
            cout << "Successfully." << endl;
            
            return;
        }
    }
    
    cout << "Couldn't find a student with that name :(" << endl;
}

void nullCount() {
    cout << "* I can't do it because there are 0 students loaded." << endl;
}
