// String.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

using namespace std;

class String {
private:
    char* text;
public:
    // Конструктор за замовчуванням
    String() {
        text = new char[1];
        text[0] = '\0';
    }
    // Конструктор за замовчуванням
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
    //Перевантаженя оператора []
    char& operator[](size_t index) {
        if (index >= strlen(text)) {
            cout<<"Error";
        }
        return text[index];
    }
    const char& operator[](size_t index) const {
        if (index >= strlen(text)) {
            cout << "Error";
        }
        return text[index];
    }

    // replace - замінює вказану кількість символів починаючи зі вказаного індексу на переданий рядок
    String& replace(size_t index, size_t count, const String& str) {
        size_t oldLen = strlen(text);
        if (index > oldLen) {
            throw out_of_range("Index out of range");
        }

        size_t actualCount = count;
        if (index + count > oldLen) {
            actualCount = oldLen - index;
        }

        size_t newLen = oldLen - actualCount + strlen(str.text);
        char* newText = new char[newLen + 1];

        strncpy_s(newText, newLen + 1, text, index);
        newText[index] = '\0';

        strcat_s(newText, newLen + 1, str.text);

        strcat_s(newText, newLen + 1, text + index + actualCount);

        delete[] text;
        text = newText;

        return *this;
    }

    // substr - повертає копію підрядка між двома індексами
    String substr(size_t start, size_t length) const {
        size_t strLen = strlen(text);

        if (start >= strLen) {
            throw out_of_range("Start index out of range");
        }

        size_t actualLength = length;
        if (start + length > strLen) {
            actualLength = strLen - start;
        }

        char* sub = new char[actualLength + 1];
        strncpy_s(sub, actualLength + 1, text + start, actualLength);
        sub[actualLength] = '\0';

        String result(sub);
        delete[] sub;
        return result;
    }

    // substr - перевантаження з одним параметром (до кінця рядка)
    String substr(size_t start) const {
        return substr(start, strlen(text) - start);
    }

    // empty - повертає true якщо в рядку нема символів, false - якщо є
    bool empty() const {
        return size() == 0;
    }

    // insert - вставляє зазначений рядок на зазначений індекс
    String& insert(size_t index, const String& str) {
        size_t oldLen = strlen(text);

        if (index > oldLen) {
            throw out_of_range("Index out of range");
        }

        size_t newLen = oldLen + strlen(str.text);
        char* newText = new char[newLen + 1];

        strncpy_s(newText, newLen + 1, text, index);
        newText[index] = '\0';

        strcat_s(newText, newLen + 1, str.text);

        strcat_s(newText, newLen + 1, text + index);

        delete[] text;
        text = newText;

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
    //3
    String testStr("Hello");
    cout << "До зміни: " << testStr << endl;
    testStr[0] = 'h';
    testStr[1] = 'E';
    cout << "Після зміни: " << testStr << endl;
    const String constStr("Constant");
    cout << "Константний рядок: " << constStr << endl;
    cout << "Перший символ: " << constStr[0] << endl;
    cout << "Останній символ: " << constStr[constStr.size() - 1] << endl;
    //4
    String s4("Hello World!");
    cout << "Оригінальний рядок: " << s4 << endl;
    s4.replace(6, 5, "C++");
    cout << "Після replace(6, 5, \"C++\"): " << s4 << endl;
    String sub = s4.substr(0, 5);
    cout << "substr(0, 5): " << sub << endl;
    String emptyStr;
    cout << "emptyStr.empty(): " << (emptyStr.empty() ? "true" : "false") << endl;
    cout << "s1.empty(): " << (s4.empty() ? "true" : "false") << endl;
    s4.insert(5, " Beautiful");
    cout << "Після insert(5, \" Beautiful\"): " << s4 << endl;
    String test("Програмування");
    test.replace(0, 12, "Кодування").insert(8, " на C++");
    cout << "Комбінований тест: " << test << endl;

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
