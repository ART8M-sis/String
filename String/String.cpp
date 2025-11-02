// String.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

using namespace std;

class String {
private:
    char* text;
public:
    // Конструктор
    String(const char* text) {
        this->text = new char[strlen(text) + 1];
        strcpy_s(this->text, strlen(text) + 1, text);
    }
    // Конструктор копіювання
    String(const String& other) {
        this->text = new char[strlen(other.text) + 1];
        strcpy_s(this->text, strlen(other.text) + 1, other.text);
    }
    // Довжина рядка
    int size() const {
        return strlen(text);
    }
    // Отримати як char
    char* getRad() const {
        return text;
    }
    // Отримати як const char*
    const char* getCChar() const {
        return text;
    }
    // Оператор +
    String operator+(const String& other) const {
        int newLen = (int)strlen(this->text) + (int)strlen(other.text);
        char* dln = new char[newLen + 1];
        strcpy_s(dln, newLen + 1, this->text);
        strcat_s(dln, newLen + 1, other.text);
        String result(dln);
        delete[] dln;
        return result;
    }
    // Деструктор
    ~String() {
        delete[] this->text;
    }
    // Перевантаження оператора << для cout
    friend ostream& operator<<(ostream& os, const String& str) {
        os << str.text;
        return os;
    }
    // Переміщення
    String(String&& other) {
        this->text = other.text;   
        other.text = nullptr;      
    }
    // Присвоєння з переміщенням 
    String& operator=(String&& other) {
        if (this == &other) return *this;
        delete[] this->text;   
        this->text = other.text;
        other.text = nullptr;   
        return *this;
    }
    // Присвоєння з копіюванням
    String& operator=(const String& other) {
        if (this == &other) return *this;
        delete[] this->text;
        this->text = new char[strlen(other.text) + 1];
        strcpy_s(this->text, strlen(other.text) + 1, other.text);
        return *this;
    }
};


int main() {
    SetConsoleOutputCP(1251);

    //1
    String s1("Hello");
    String s2("World!");
    cout << "s1 size: " << s1.size() << endl;
    cout << "s2 size: " << s2.size() << endl;
    cout << "s1: " << s1.getRad() << endl;
    cout << "s2: " << s2.getRad() << endl;
    cout << "s1 CChar: " << s1.getCChar() << endl;
    cout << "s2 CChar: " << s2.getCChar() << endl;
    String s3 = s1 + s2;
    cout << "s3 = s1 + s2: " << s3 << endl;
    //2
    String copy = s1;
    cout << "сopy: " << copy << endl;
    copy = s2;
    cout << "сopy2: " << copy << endl;
    String move = std::move(s3);
    cout << "move: " << move << endl;
    move = std::move(s1);
    cout << "Moved: " << move << endl;
    cout << "a";
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
