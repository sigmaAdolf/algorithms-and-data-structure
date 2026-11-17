#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Employee {
private:
    string name;
    double salary;

    static int employeeCount;
    static double totalSalary;

public:
    Employee(const string& n, double s) : name(n), salary(s) {
        employeeCount++;
        totalSalary += salary;
        cout << "Создан сотрудник: " << name << endl;
    }

    ~Employee() {
        employeeCount--;
        totalSalary -= salary;
        cout << "Уничтожен сотрудник: " << name << endl;
    }

    Employee(const Employee&) = delete;
    Employee& operator=(const Employee&) = delete;

    static int getCount() {
        return employeeCount;
    }

    static double getAverageSalary() {
        if (employeeCount == 0) {
            return 0;
        }
        return totalSalary / employeeCount;
    }

    void setSalary(double newSalary) {
        if (newSalary < 0) {
            cout << "Ошибка: зарплата не может быть отрицательной!" << endl;
            return;
        }

        totalSalary = totalSalary - salary + newSalary;
        salary = newSalary;
    }

    void print() const {
        cout << "Имя: " << name
            << ", зарплата: " << salary << " руб." << endl;
    }
};

int Employee::employeeCount = 0;
double Employee::totalSalary = 0;

class Company {
private:
    string name;
    vector<Employee*> employees;

    static Company* instance;

    Company(const string& n) : name(n) {
        cout << "Создана компания: " << name << endl;
    }

public:
    Company(const Company&) = delete;
    Company& operator=(const Company&) = delete;

    static Company* getInstance(const string& name = "Моя компания") {
        if (instance == nullptr) {
            instance = new Company(name);
        }
        return instance;
    }

    void addEmployee(Employee* employee) {
        if (employee == nullptr) {
            cout << "Ошибка: передан пустой указатель!" << endl;
            return;
        }

        for (const auto* existing : employees) {
            if (existing == employee) {
                cout << "Этот сотрудник уже добавлен!" << endl;
                return;
            }
        }

        employees.push_back(employee);
        cout << "Сотрудник добавлен в компанию." << endl;
    }

    void printEmployees() const {
        cout << "\nСотрудники компании " << name << ":" << endl;

        for (const auto* employee : employees) {
            employee->print();
        }
    }

    ~Company() {
        cout << "Уничтожена компания: " << name << endl;
    }

    static void destroyInstance() {
        delete instance;
        instance = nullptr;
    }
};

Company* Company::instance = nullptr;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(2);

    cout << "Количество сотрудников: "
        << Employee::getCount() << endl;

    Employee e1("Иван", 50000);
    Employee e2("Мария", 60000);
    Employee e3("Пётр", 55000);

    cout << "Количество сотрудников: "
        << Employee::getCount() << endl;
    cout << "\nСредняя зарплата: "
        << Employee::getAverageSalary() << " руб." << endl;

    {
        Company* c1 = Company::getInstance("Техно");
        Company* c2 = Company::getInstance("Другая компания");

        cout << "\nПроверка Singleton: "
            << (c1 == c2 ? "объект один" : "объекты разные")
            << endl;

        c1->addEmployee(&e1);
        c1->addEmployee(&e2);
        c1->addEmployee(&e3);

        c1->addEmployee(nullptr);

        c1->addEmployee(&e1);

        c1->printEmployees();

        cout << "\nИзменяем зарплату Марии:" << endl;
        e2.setSalary(70000);

        cout << "Новая средняя зарплата: "
            << Employee::getAverageSalary() << " руб." << endl;

        cout << "\nПроверка отрицательной зарплаты:" << endl;
        e2.setSalary(-1000);

        cout << "\nКоличество сотрудников: "
            << Employee::getCount() << endl;

        Company::destroyInstance();
    }

    cout << "\nКомпания уничтожена, сотрудники существуют:" << endl;
    e1.print();
    e2.print();
    e3.print();

    cout << "\nКоличество сотрудников после уничтожения компании: "
        << Employee::getCount() << endl;

    cout << "\nЗавершение программы." << endl;
    return 0;
}