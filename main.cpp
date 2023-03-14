/*
    * by Danya Kry
    * v 1.0
 
### Задание:
 
 7. Написать программу обработки файла записей, содержащую следующие пункты меню: «Создание», «Просмотр», «Добавление», «Решение индивидуального задания».
 Каждая запись должна содержать следующую информацию о студентах:
 – фамилия;
 – номер группы;
 – оценки за семестр: по физике, математике, информатике;
 – средний балл.
     Организовать ввод исходных данных, средний балл рассчитать по введенным оценкам.
 Содержимое всего файла и результаты решения индивидуального задания записать в текстовый файл.

 7.1.8. Вычислить общий средний балл всех студентов и распечатать список студентов со средним баллом выше общего среднего балла
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

string openFile();  // открыть файл
void loadOutFile(Student [], int&, string);   // загрузить записи из файла в массив
void delFile();     // удалить файл

void addStudent(Student [], int&);
void viewStudents(Student [], int);
void solveTask(Student [], int);
// editStudents;
void saveToFile(Student [], int, string);

int main() {
    Student students[100];
    int count = 0;
    int choice;
    string fileName;
    system("open .");
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
                    cout << "5. Reaf from file" << endl;
                    cout << "6. Exit" << endl;

                    cout << "Enter your choice: ";
                    cin >> choice;
                    
                    switch (choice) {
                        case 1:
                            addStudent(students, count);
                            break;
                            
                        case 2:
                            viewStudents(students, count);
                            break;
                            
                        case 3:
                            solveTask(students, count);
                            break;
                            
                        case 4:
                            saveToFile(students, count, fileName);
                            break;
                            
                        case 5:
                            loadOutFile(students, count, fileName);
                            break;
                            
                        case 6:
                            cout << "Exiting program..." << endl;
                            break;

                        default:
                            cout << "Invalid choice. Try again." << endl;
                            break;
                    }
                } while (choice != 6);
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
        cout << "# error #" << endl;
        return 0;
    }
    
    cout << "File with name " << fileName << " created." << endl;
    file.close();
    
    return fileName;
}

void delFile() {
    char fileName[80];
    
    cout << "Enter file name: ";
    cin >> fileName;
    
    if (remove(fileName) == 0) {
        cout << "File removed." << endl;
    } else {
        perror("remove");
    }
}

void loadOutFile(Student students[], int& count, string fileName) {
    ifstream fin(fileName);
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
}

void viewStudents(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "# " << count << endl;
        cout << "Surname: " << students[i].surname << endl;
        cout << "Group number: " << students[i].groupNumber << endl;
        cout << "Physics grade: " << students[i].physicsGrade << endl;
        cout << "Math grade: " << students[i].mathGrade << endl;
        cout << "CS grade: " << students[i].csGrade << endl;
        cout << "Average grade: " << students[i].avgGrade << endl << endl;
    }
}

void solveTask(Student students[], int count) {
    // Вычислить общий средний балл всех студентов и распечатать список студентов со средним баллом выше общего среднего балла
    double generalAvgGrade = 0.0;
    for (int i = 0; i < count; i++) {
        for (int i = 0; i < count; i++) {
            generalAvgGrade += students[i].avgGrade;
        }
        
        generalAvgGrade /= count;
        
        if (students[i].avgGrade > generalAvgGrade) {
            cout << students[i].surname << endl;
            cout << students[i].groupNumber << endl << endl;
        }
    }
}

void saveToFile(Student students[], int count, string fileName) {
    ofstream fout(fileName);
    
    if (!fout.is_open()) {
        cout << "# error #" << endl;
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
}
