#include <iostream> // Подключаем библиотеку для ввода-вывода
#include <map> // Подключаем библиотеку для работы с ассоциативными массивами (словари)
#include <vector> // Подключаем библиотеку для работы с динамическими массивами
#include <string> // Подключаем библиотеку для работы со строками
#include <utility> // Подключаем библиотеку для работы с парами (std::pair)

using namespace std; // Используем стандартное пространство имен для удобства

// Определяем класс Student (Студент)
class Student {
public:
    string name; // Имя студента
    map<string, vector<string>> reports; // Карта, где ключ - предмет, значение - вектор тем докладов
    map<string, vector<string>> assignments; // Карта, где ключ - предмет, значение - вектор заданий
    map<string, vector<pair<string, int>>> grades; // Карта, где ключ - предмет, значение - вектор пар (тип работы, оценка)
    pair<string, string> registeredReport; // Пара для хранения информации о выбранном докладе (предмет, тема)

    // Конструктор класса Student, который инициализирует имя студента и сбрасывает информацию о зарегистрированном докладе
    Student(string name) : name(name), registeredReport("", "") {}

    // Метод для регистрации доклада
    void registerReport(string subject, string topic) {
        reports[subject].push_back(topic); // Добавляем тему доклада в соответствующий предмет
    }

    // Метод для регистрации задания
    void registerAssignment(string subject, string assignment) {
        assignments[subject].push_back(assignment); // Добавляем задание в соответствующий предмет
    }

    // Метод для установки оценки
    void setGrade(string subject, const string& type, int grade) {
        grades[subject].emplace_back(type, grade); // Добавляем пару (тип работы, оценка) в соответствующий предмет
    }

    // Метод для отображения всех докладов студента
    void displayReports() {
        cout << "Доклады студента " << name << ":\n"; // Выводим заголовок
        for (const auto& report : reports) { // Проходим по всем предметам
            for (const auto& topic : report.second) { // Проходим по всем темам докладов
                cout << report.first << ": " << topic << endl; // Выводим предмет и тему
            }
        }
    }

    // Метод для отображения всех заданий студента
    void displayAssignments() {
        cout << "Задания студента " << name << ":\n"; // Выводим заголовок
        for (const auto& assignment : assignments) { // Проходим по всем предметам
            for (const auto& topic : assignment.second) { // Проходим по всем заданиям
                cout << assignment.first << ": " << topic << endl; // Выводим предмет и задание
            }
        }
    }

    // Метод для отображения всех оценок студента
    void displayGrades() {
        cout << "Оценки студента " << name << ":\n"; // Выводим заголовок
        for (const auto& subject : grades) { // Проходим по всем предметам
            for (const auto& grade : subject.second) { // Проходим по всем оценкам
                cout << subject.first << " (" << grade.first << "): " << grade.second << endl; // Выводим предмет, тип работы и оценку
            }
        }
    }

    // Метод для регистрации на доклад
    void registerForReport(const pair<string, string>& report) {
        registeredReport = report; // Устанавливаем зарегистрированный доклад
    }

    // Метод для отказа от доклада
    void unregisterFromReport() {
        registeredReport = {"", ""}; // Сбрасываем информацию о зарегистрированном докладе
    }

    // Метод для получения информации о зарегистрированном докладе
    pair<string, string> getRegisteredReport() const {
        return registeredReport; // Возвращаем зарегистрированный доклад
    }
};

// Определяем класс Teacher (Преподаватель)
class Teacher {
public:
    string name; // Имя преподавателя
    string subject; // Предмет, который ведет преподаватель
    map<string, vector<string>> assignments; // Карта, где ключ - предмет, значение - вектор заданий
    map<string, vector<string>> reports; // Карта, где ключ - предмет, значение - вектор тем докладов

    // Конструктор класса Teacher, который инициализирует имя преподавателя и предмет
    Teacher(string name, string subject) : name(name), subject(subject) {}

    // Метод для назначения темы доклада
    void assignReport(string topic) {
        reports[subject].push_back(topic); // Добавляем тему доклада в соответствующий предмет
    }

    // Метод для назначения задания
    void assignAssignment(string topic) {
        assignments[subject].push_back(topic); // Добавляем задание в соответствующий предмет
    }

    // Метод для отображения всех заданий преподавателя
    void displayAssignments() {
        cout << "Задания преподавателя " << name << " по предмету " << subject << ":\n"; // Выводим заголовок
        for (const auto& topic : assignments[subject]) { // Проходим по всем заданиям
            cout << topic << endl; // Выводим задание
        }
    }

    // Метод для отображения всех докладов, назначенных преподавателем
    void displayReports() {
        cout << "Доклады, назначенные преподавателем " << name << " по предмету " << subject << ":\n"; // Выводим заголовок
        for (const auto& topic : reports[subject]) { // Проходим по всем темам докладов
            cout << topic << endl; // Выводим тему доклада
        }
    }

    // Метод для выставления оценки студенту
    void setGrade(Student* student, string subject, const string& type, int grade) {
        student->setGrade(subject, type, grade); // Устанавливаем оценку у студента
        cout << "Оценка " << grade << " за " << type << " по предмету " << subject << " выставлена студенту " << student->name << ".\n"; // Подтверждение
    }
};

// Определяем класс GP (Управление)
class GP {
public:
    vector<Student*> students; // Вектор указателей на студентов
    vector<Teacher*> teachers; // Вектор указателей на преподавателей
    map<pair<string, string>, bool> reportAvailability; // Карта для хранения доступности докладов (предмет, тема) -> доступность

    // Метод для добавления нового студента
    void addStudent(string name) {
        students.push_back(new Student(name)); // Создаем нового студента и добавляем в вектор
    }

    // Метод для добавления нового преподавателя
    void addTeacher(string name, string subject) {
        teachers.push_back(new Teacher(name, subject)); // Создаем нового преподавателя и добавляем в вектор
    }

    // Метод для отображения всех студентов
    void displayStudents() {
        cout << "Список студентов:\n"; // Выводим заголовок
        for (auto student : students) { // Проходим по всем студентам
            cout << student->name << endl; // Выводим имя студента
        }
    }

    // Метод для отображения всех преподавателей
    void displayTeachers() {
        cout << "Список преподавателей:\n"; // Выводим заголовок
        for (auto teacher : teachers) { // Проходим по всем преподавателям
            cout << teacher->name << " (" << teacher->subject << ")\n"; // Выводим имя и предмет преподавателя
        }
    }

    // Метод для отображения результатов всех студентов
    void displayAllStudentsResults() {
        cout << "Результаты всех студентов:\n"; // Выводим заголовок
        for (auto student : students) { // Проходим по всем студентам
            cout << "Студент: " << student->name << endl; // Выводим имя студента

            cout << "Доклады:\n"; // Заголовок для докладов
            student->displayReports(); // Вызываем метод отображения докладов

            cout << "Задания:\n"; // Заголовок для заданий
            student->displayAssignments(); // Вызываем метод отображения заданий

            cout << "Оценки:\n"; // Заголовок для оценок
            student->displayGrades(); // Вызываем метод отображения оценок

            cout << endl; // Разделение между студентами
        }
    }

    // Метод для назначения доклада
    void assignReport(string teacherName, string subject, string topic) {
        for (auto& teacher : teachers) { // Проходим по всем преподавателям
            if (teacher->name == teacherName && teacher->subject == subject) { // Находим нужного преподавателя
                teacher->assignReport(topic); // Назначаем доклад
                reportAvailability[{subject, topic}] = true; // Устанавливаем доступность доклада
                return; // Выходим из метода
            }
        }
        cout << "Преподаватель не найден.\n"; // Если преподаватель не найден
    }
};

// Функция для меню управления
void gpMenu(GP &gp) {
    while (true) {
        // Выводим доступные команды
        cout << "1. Назначить доклад\n2. Назначить задание\n3. Создать нового студента\n4. Создать преподавателя\n5. Выставить оценки\n6. Показать всех студентов\n7. Показать всех преподавателей\n8. Показать результаты всех студентов\n9. Выйти из ГП\n";
        int command; // Переменная для хранения команды
        cin >> command; // Ввод команды

        // Обработка команд
        if (command == 1) {
            cout << "Введите имя преподавателя: "; // Запрос имени преподавателя
            string teacherName; // Переменная для хранения имени преподавателя
            cin >> teacherName; // Ввод имени

            Teacher* teacher = nullptr; // Указатель на преподавателя
            for (auto t : gp.teachers) { // Проходим по всем преподавателям
                if (t->name == teacherName) { // Находим нужного преподавателя
                    teacher = t; // Сохраняем указатель на преподавателя
                    break; // Выходим из цикла
                }
            }

            // Если преподаватель найден
            if (teacher) {
                cout << "Введите тему доклада: "; // Запрос темы доклада
                string topic; // Переменная для хранения темы
                cin >> topic; // Ввод темы
                gp.assignReport(teacherName, teacher->subject, topic); // Назначаем доклад
                cout << "Доклад " << topic << " назначен для преподавателя " << teacherName << ".\n"; // Подтверждение
            } else {
                cout << "Преподаватель не найден.\n"; // Если преподаватель не найден
            }
        } else if (command == 2) {
            cout << "Введите имя преподавателя: "; // Запрос имени преподавателя
            string teacherName; // Переменная для хранения имени преподавателя
            cin >> teacherName; // Ввод имени

            Teacher* teacher = nullptr; // Указатель на преподавателя
            for (auto t : gp.teachers) { // Проходим по всем преподавателям
                if (t->name == teacherName) { // Находим нужного преподавателя
                    teacher = t; // Сохраняем указатель на преподавателя
                    break; // Выходим из цикла
                }
            }

            // Если преподаватель найден
            if (teacher) {
                cout << "Введите задание (тема): "; // Запрос темы задания
                string topic; // Переменная для хранения темы
                cin >> topic; // Ввод темы
                teacher->assignAssignment(topic); // Назначаем задание
                cout << "Задание " << topic << " назначено для преподавателя " << teacherName << ".\n"; // Подтверждение
            } else {
                cout << "Преподаватель не найден.\n"; // Если преподаватель не найден
            }
        } else if (command == 3) {
            cout << "Введите имя студента: "; // Запрос имени студента
            string name; // Переменная для хранения имени студента
            cin >> name; // Ввод имени
            gp.addStudent(name); // Добавляем нового студента
            cout << "Студент " << name << " добавлен.\n"; // Подтверждение
        } else if (command == 4) {
            cout << "Введите имя преподавателя: "; // Запрос имени преподавателя
            string name; // Переменная для хранения имени преподавателя
            cin >> name; // Ввод имени
            cout << "Введите предмет преподавателя: "; // Запрос предмета
            string subject; // Переменная для хранения предмета
            cin >> subject; // Ввод предмета
            gp.addTeacher(name, subject); // Добавляем нового преподавателя
            cout << "Преподаватель " << name << " по предмету " << subject << " добавлен.\n"; // Подтверждение
        } else if (command == 5) {
            cout << "Введите имя студента: "; // Запрос имени студента
            string studentName; // Переменная для хранения имени студента
            cin >> studentName; // Ввод имени

            Student* student = nullptr; // Указатель на студента
            for (auto s : gp.students) { // Проходим по всем студентам
                if (s->name == studentName) { // Находим нужного студента
                    student = s; // Сохраняем указатель на студента
                    break; // Выходим из цикла
                }
            }

            // Если студент найден
            if (student) {
                cout << "Введите предмет для выставления оценки: "; // Запрос предмета
                string subject; // Переменная для хранения предмета
                cin >> subject; // Ввод предмета
                cout << "Введите тип работы (лаба/доклад/задание): "; // Запрос типа работы
                string type; // Переменная для хранения типа работы
                cin >> type; // Ввод типа
                cout << "Введите оценку: "; // Запрос оценки
                int grade; // Переменная для хранения оценки
                cin >> grade; // Ввод оценки
                student->setGrade(subject, type, grade); // Устанавливаем оценку
                cout << "Оценка " << grade << " за " << type << " по предмету " << subject << " выставлена студенту " << studentName << ".\n"; // Подтверждение
            } else {
                cout << "Студент не найден.\n"; // Если студент не найден
            }
        } else if (command == 6) {
            gp.displayStudents(); // Выводим список студентов
        } else if (command == 7) {
            gp.displayTeachers(); // Выводим список преподавателей
        } else if (command == 8) {
            gp.displayAllStudentsResults(); // Вывод результатов всех студентов
        } else if (command == 9) {
            break; // Выходим из меню
        }
    }
}

// Функция для меню преподавателя
void teacherMenu(Teacher* teacher, GP& gp) {
    while (true) { // Бесконечный цикл для отображения меню
        // Выводим доступные команды для преподавателя
        cout << "1. Показать задания\n2. Показать доклады\n3. Назначить доклад\n4. Назначить задание\n5. Выставить оценки\n6. Выйти\n";
        int command; // Переменная для хранения команды
        cin >> command; // Ввод команды

        // Обработка команды
        if (command == 1) {
            teacher->displayAssignments(); // Показываем задания преподавателя
        } else if (command == 2) {
            teacher->displayReports(); // Показываем доклады преподавателя
        } else if (command == 3) {
            cout << "Введите тему доклада: "; // Запрос темы доклада
            string topic; // Переменная для хранения темы
            cin >> topic; // Ввод темы
            teacher->assignReport(topic); // Назначаем доклад
            cout << "Доклад " << topic << " назначен.\n"; // Подтверждение назначения доклада
        } else if (command == 4) {
            cout << "Введите задание (тема): "; // Запрос темы задания
            string topic; // Переменная для хранения темы
            cin >> topic; // Ввод темы
            teacher->assignAssignment(topic); // Назначаем задание
            cout << "Задание " << topic << " назначено.\n"; // Подтверждение назначения задания
        } else if (command == 5) {
            cout << "Введите имя студента: "; // Запрос имени студента
            string studentName; // Переменная для хранения имени студента
            cin >> studentName; // Ввод имени

            Student* student = nullptr; // Указатель на студента
            // Поиск студента в списке студентов
            for (auto s : gp.students) {
                if (s->name == studentName) { // Если имя совпадает
                    student = s; // Сохраняем указатель на студента
                    break; // Выходим из цикла
                }
            }

            // Если студент найден
            if (student) {
                cout << "Введите предмет для выставления оценки: "; // Запрос предмета
                string subject; // Переменная для хранения предмета
                cin >> subject; // Ввод предмета
                cout << "Введите тип работы (лаба/доклад/задание): "; // Запрос типа работы
                string type; // Переменная для хранения типа работы
                cin >> type; // Ввод типа
                cout << "Введите оценку: "; // Запрос оценки
                int grade; // Переменная для хранения оценки
                cin >> grade; // Ввод оценки
                teacher->setGrade(student, subject, type, grade); // Устанавливаем оценку студенту
            } else {
                cout << "Студент не найден.\n"; // Если студент не найден
            }
        } else if (command == 6) {
            break; // Выход из меню
        }
    }
}

// Функция для меню студента
void studentMenu(Student* student, GP& gp) {
    while (true) { // Бесконечный цикл для отображения меню
        // Выводим доступные команды для студента
        cout << "1. Записаться на доклад\n2. Отказ от доклада\n3. Показать оценки\n4. Выйти\n";
        int command; // Переменная для хранения команды
        cin >> command; // Ввод команды

        // Обработка команды
        if (command == 1) {
            vector<pair<string, string>> availableReports; // Вектор для хранения доступных докладов
            // Проходим по всем доступным докладам в системе
            for (const auto& report : gp.reportAvailability) {
                if (report.second) { // Проверяем доступность доклада
                    availableReports.push_back(report.first); // Добавляем доступные доклады
                }
            }

            // Если нет доступных докладов
            if (availableReports.empty()) {
                cout << "Нет доступных докладов.\n"; // Сообщение об отсутствии доступных докладов
            } else {
                cout << "Доступные доклады:\n"; // Заголовок для списка докладов
                // Выводим доступные доклады
                for (const auto& report : availableReports) {
                    cout << "Предмет: " << report.first << ", Тема: " << report.second << endl; // Выводим предмет и тему доклада
                }

                // Запрос предмета и темы для записи на доклад
                cout << "Введите предмет и тему доклада (через пробел): ";
                string subject, topic; // Переменные для хранения предмета и темы
                cin >> subject >> topic; // Ввод предмета и темы

                bool found = false; // Флаг для проверки найденного доклада
                // Проверка, существует ли указанный доклад
                for (const auto& report : availableReports) {
                    if (report.first == subject && report.second == topic) { // Если предмет и тема совпадают
                        student->registerForReport({subject, topic}); // Регистрируем студента на доклад
                        gp.reportAvailability[{subject, topic}] = false; // Отмечаем доклад как занятый
                        cout << "Вы записались на доклад: " << subject << " - " << topic << endl; // Подтверждение записи
                        found = true; // Устанавливаем флаг найденного доклада
                        break; // Выходим из цикла
                    }
                }
                if (!found) {
                    cout << "Доклад не найден.\n"; // Если доклад не найден
                }
            }
        } else if (command == 2) {
            // Проверяем, записан ли студент на доклад
            if (student->getRegisteredReport().first.empty()) {
                cout << "Вы не записаны ни на один доклад.\n"; // Сообщение об отсутствии записи на доклад
            } else {
                // Выводим информацию о зарегистрированном докладе
                cout << "Вы записаны на доклад: " << student->getRegisteredReport().first << " - " << student->getRegisteredReport().second << endl;
                cout << "Вы уверены, что хотите отказаться? (да/нет): "; // Запрос на подтверждение отказа
                string answer; // Переменная для хранения ответа
                cin >> answer; // Ввод ответа
                if (answer == "да") { // Если пользователь подтверждает отказ
                    gp.reportAvailability[student->getRegisteredReport()] = true; // Освобождаем доклад
                    student->unregisterFromReport(); // Отменяем регистрацию студента на доклад
                    cout << "Вы отказались от доклада.\n"; // Подтверждение отказа
                }
            }
        } else if (command == 3) {
            student->displayGrades(); // Показываем оценки студента
        } else if (command == 4) {
            break; // Выход из меню
        }
    }
}

// Основная функция программы
int main() {
    GP gp; // Создаем объект управления

    // Добавление студентов
    cout << "Сколько студентов вы хотите добавить? "; // Запрос количества студентов
    int studentCount; // Переменная для хранения количества студентов
    cin >> studentCount; // Ввод количества студентов

    // Цикл для добавления студентов
    for (int i = 0; i < studentCount; ++i) {
        cout << "Введите имя студента: "; // Запрос имени студента
        string name; // Переменная для хранения имени студента
        cin >> name; // Ввод имени
        gp.addStudent(name); // Добавляем нового студента в систему
    }

    // Добавление преподавателей
    cout << "Сколько преподавателей вы хотите добавить? "; // Запрос количества преподавателей
    int teacherCount; // Переменная для хранения количества преподавателей
    cin >> teacherCount; // Ввод количества преподавателей

    // Цикл для добавления преподавателей
    for (int i = 0; i < teacherCount; ++i) {
        cout << "Введите имя преподавателя: "; // Запрос имени преподавателя
        string name; // Переменная для хранения имени преподавателя
        cin >> name; // Ввод имени
        cout << "Введите предмет преподавателя: "; // Запрос предмета
        string subject; // Переменная для хранения предмета
        cin >> subject; // Ввод предмета
        gp.addTeacher(name, subject); // Добавляем нового преподавателя в систему
    }

    // Основной цикл для выбора действия
    while (true) {
        cout << "Выберите действие (гп/преподаватель/студент/выход): "; // Запрос роли пользователя
        string role; // Переменная для хранения роли
        cin >> role; // Ввод роли

        // Обработка ролей
        if (role == "гп") {
            gpMenu(gp); // Вызов меню управления
        } else if (role == "преподаватель") {
            cout << "Введите имя преподавателя: "; // Запрос имени преподавателя
            string teacherName; // Переменная для хранения имени преподавателя
            cin >> teacherName; // Ввод имени

            Teacher* teacher = nullptr; // Указатель на преподавателя
            // Поиск преподавателя в списке преподавателей
            for (auto t : gp.teachers) {
                if (t->name == teacherName) { // Если имя совпадает
                    teacher = t; // Сохраняем указатель на преподавателя
                    break; // Выходим из цикла
                }
            }

            // Если преподаватель найден
            if (teacher) {
                teacherMenu(teacher, gp); // Вызов меню преподавателя
            } else {
                cout << "Преподаватель не найден.\n"; // Если преподаватель не найден
            }
        } else if (role == "студент") {
            cout << "Введите имя студента: "; // Запрос имени студента
            string studentName; // Переменная для хранения имени студента
            cin >> studentName; // Ввод имени

            Student* student = nullptr; // Указатель на студента
            // Поиск студента в списке студентов
            for (auto s : gp.students) {
                if (s->name == studentName) { // Если имя совпадает
                    student = s; // Сохраняем указатель на студента
                    break; // Выходим из цикла
                }
            }

            // Если студент найден
            if (student) {
                studentMenu(student, gp); // Вызов меню студента
            } else {
                cout << "Студент не найден.\n"; // Если студент не найден
            }
        } else if (role == "выход") {
            break; // Выход из программы
        } else {
            cout << "Некорректная команда.\n"; // Сообщение об ошибке
        }
    }

    // Освобождение памяти
    for (auto student : gp.students) {
        delete student; // Освобождаем память для студентов
    }
    for (auto teacher : gp.teachers) {
        delete teacher; // Освобождаем память для преподавателей
    }

    return 0; // Завершение программы
}
