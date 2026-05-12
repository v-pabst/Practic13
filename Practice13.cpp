#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class SquareMatrix {
protected:
    static int totalElements;
    static int const maxSize = 5;
    int size;
    int data[maxSize][maxSize];
public:
    SquareMatrix(int size = 1) {
        this->size = (size > 0 && size <= maxSize) ? size : 1;
        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++)
                data[i][j] = 0;
        totalElements += this->size * this->size;
    }

    int getSize() const { return size; } 

    void setValue(int i, int j, int value) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            data[i][j] = value;
        }
    }

    int getValue(int i, int j) const { 
        if (i >= 0 && i < size && j >= 0 && j < size) {
            return data[i][j];
        }
        return 0;
    }

    virtual void print() const {  
        cout << "Square Matrix" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                cout << data[i][j] << "\t";
            cout << endl;
        }
    }

    virtual void multiplyScalar(int scalar) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                data[i][j] *= scalar;
        cout << "Матрица умножена на " << scalar << endl;
    }

    static int getTotalElements() {
        return totalElements;
    }
};


int SquareMatrix::totalElements = 0;

class ScalarMatrix : public SquareMatrix {
    int diagonalValue;
public:
    ScalarMatrix(int size = 1, int value = 0) : SquareMatrix(size), diagonalValue(value >= 0 ? value : 0) {
        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++)
                if (i == j)
                    setValue(i, j, diagonalValue);
                else
                    setValue(i, j, 0);
    }

    void print() {
        SquareMatrix::print();
        cout << "Type: \tScalar Matrix" << endl;
    }

    void multiplyScalar(int scalar) {
        SquareMatrix::multiplyScalar(scalar);
    }
};


class TriangularMatrix : public SquareMatrix {
    bool isUpper;
public:
    TriangularMatrix(int size = 1, bool upper = true) : SquareMatrix(size), isUpper(upper) {
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                if (isUpper) {
                    if (i > j)
                        setValue(i, j, 0);
                }
                else {

                    if (i < j)
                        setValue(i, j, 0);
                }
            }
        }
    }

    void print() {
        SquareMatrix::print();
        cout << "Type: \tTriangular Matrix" << endl;
        cout << "Form: \t" << (isUpper ? "Upper" : "Lower") << endl;
    }

    void multiplyScalar(int scalar) {
        SquareMatrix::multiplyScalar(scalar);
    }

    void setTriangularElement(int i, int j, int value) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            if (isUpper && i > j && value != 0) {
                cout << "Error!" << endl;
                return;
            }
            if (!isUpper && i < j && value != 0) {
                cout << "Error!" << endl;
                return;
            }
            setValue(i, j, value);
        }
    }
};

int main() {
    setlocale(LC_ALL, "");

    SquareMatrix m1(3);
    m1.setValue(0, 0, 1);
    m1.setValue(1, 1, 2);
    m1.setValue(2, 2, 3);
    m1.print();
    cout << endl;

    m1.multiplyScalar(2);
    m1.print();
    cout << endl;

    ScalarMatrix sm(3, 5);
    sm.print();
    cout << endl;

    sm.multiplyScalar(3);
    sm.print();
    cout << endl;

    TriangularMatrix tm1(3, true);
    tm1.setTriangularElement(0, 1, 7);
    tm1.setTriangularElement(0, 2, 8);
    tm1.setTriangularElement(1, 2, 9);
    tm1.print();
    cout << endl;

    tm1.multiplyScalar(2);
    tm1.print();
    cout << endl;

    TriangularMatrix tm2(3, false);
    tm2.setTriangularElement(1, 0, 4);
    tm2.setTriangularElement(2, 0, 5);
    tm2.setTriangularElement(2, 1, 6);
    tm2.print();
    cout << endl;

    tm2.multiplyScalar(3);
    tm2.print();
    cout << endl;

    cout << "Всего элементов: " << SquareMatrix::getTotalElements() << endl;

    return 0;
}

//Абстрактный тип данных - множество set
const int MAX_SIZE = 20;

class Set {
    int count;
    char* elem;

public:
    Set();
    Set(int COUNT);
    Set(const Set& obj); // конструктор копирования
    ~Set();

    bool operator>(char ch) const; // проверка принадлежности
    Set operator*(const Set& op) const; // пересечение множеств
    bool operator<(const Set& op) const; // проверка на подмножество

    void add(char ch); // добавление элемента
    bool contains(char ch) const;
    char getElem(int NUM) const;
    void setElem(int NUM, char ELEM);
    void show() const;
    int getCount() const { return count; }
};

Set::Set() {
    count = 0;
    elem = new char[MAX_SIZE];
}

Set::Set(int COUNT) {
    count = 0;
    if (COUNT > 0) {
        elem = new char[COUNT];
    }
    else {
        elem = new char[MAX_SIZE];
    }
}

// Конструктор копирования
Set::Set(const Set& obj) {
    count = obj.count;
    elem = new char[count];
    for (int i = 0; i < count; i++) {
        elem[i] = obj.elem[i];
    }
}

// Деструктор
Set::~Set() {
    delete[] elem;
}

bool Set::operator>(char ch) const {
    return contains(ch);
}

Set Set::operator*(const Set& op) const {
    Set result;
    for (int i = 0; i < count; i++) {
        if (op.contains(elem[i])) {
            result.add(elem[i]);
        }
    }
    return result;
}

bool Set::operator<(const Set& op) const {
    for (int i = 0; i < count; i++) {
        if (!op.contains(elem[i])) {
            return false;
        }
    }
    return true;
}

// Добавление элемента (без дубликатов)
void Set::add(char ch) {
    if (!contains(ch) && count < MAX_SIZE) {
        elem[count] = ch;
        count++;
    }
}

// Проверка: есть ли элемент во множестве
bool Set::contains(char ch) const {
    for (int i = 0; i < count; i++) {
        if (elem[i] == ch) {
            return true;
        }
    }
    return false;
}

// Получить элемент по индексу
char Set::getElem(int NUM) const {
    if (NUM >= 0 && NUM < count) {
        return elem[NUM];
    }
    return '\0';
}

// Установить элемент по индексу (используется для заполнения)
void Set::setElem(int NUM, char ELEM) {
    if (NUM >= 0 && NUM < count) {
        elem[NUM] = ELEM;
    }
}

// Вывод множества на экран
void Set::show() const {
    cout << "{ ";
    for (int i = 0; i < count; i++) {
        cout << elem[i] << " ";
    }
    cout << "}" << endl;
}

//int main() {
//    setlocale(LC_ALL, "");
//
//    Set A(10);
//    A.add('a');
//    A.add('b');
//    A.add('c');
//    A.add('b');
//    cout << "Множество A: ";
//    A.show();
//
//    Set B(10);
//    B.add('b');
//    B.add('c');
//    B.add('d');
//    B.add('e');
//    cout << "Множество B: ";
//    B.show();
//
//    char ch = 'b';
//    if (A > ch) {
//        cout << "'" << ch << "' принадлежит A" << endl;
//    }
//    else {
//        cout << "'" << ch << "' НЕ принадлежит A" << endl;
//    }
//
//    ch = 'z';
//    if (A > ch) {
//        cout << "'" << ch << "' принадлежит A" << endl;
//    }
//    else {
//        cout << "'" << ch << "' НЕ принадлежит A" << endl;
//    }
//
//    Set C = A * B;
//    cout << "A * B (пересечение): ";
//    C.show();
//
//    Set D;
//    D.add('b');
//    D.add('c');
//    cout << "Множество D: ";
//    D.show();
//
//    if (D < B) {
//        cout << "D является подмножеством B" << endl;
//    }
//    else {
//        cout << "D НЕ является подмножеством B" << endl;
//    }
//
//    if (A < B) {
//        cout << "A является подмножеством B" << endl;
//    }
//    else {
//        cout << "A НЕ является подмножеством B" << endl;
//    }
//
//    return 0;
//}

//Шаблонный класс
template <typename T>
class SetTemplate {
private:
    T* elements;
    int count;
    int capacity; //вместимость

    bool equal(const T& a, const T& b) const {
        if constexpr (is_same<T, char>::value) {
            return a == b;
        }
        else {
            if (a.getSize() != b.getSize()) return false;
            for (int i = 0; i < a.getSize(); i++)
                for (int j = 0; j < a.getSize(); j++)
                    if (a.getValue(i, j) != b.getValue(i, j)) return false;
            return true;
        }
    }

public:
    SetTemplate() : count(0), capacity(10) {
        elements = new T[capacity];
    }

    ~SetTemplate() { delete[] elements; }

    void add(const T& item) {
        for (int i = 0; i < count; i++)
            if (equal(elements[i], item)) return;
        if (count >= capacity) {
            capacity *= 2;
            T* newArr = new T[capacity];
            for (int i = 0; i < count; i++) newArr[i] = elements[i];
            delete[] elements;
            elements = newArr;
        }
        elements[count++] = item;
    }

    bool contains(const T& item) const {
        for (int i = 0; i < count; i++)
            if (equal(elements[i], item)) return true;
        return false;
    }

    SetTemplate<T> intersection(const SetTemplate<T>& other) const {
        SetTemplate<T> result;
        for (int i = 0; i < count; i++)
            if (other.contains(elements[i]))
                result.add(elements[i]);
        return result;
    }

    bool isSubset(const SetTemplate<T>& other) const {
        for (int i = 0; i < count; i++)
            if (!other.contains(elements[i])) return false;
        return true;
    }

    void show() const {
        cout << "{ ";
        for (int i = 0; i < count; i++) {
            if constexpr (is_same<T, char>::value) {
                cout << elements[i] << " ";
            }
            else {
                elements[i].print();
                cout << " ";
            }
        }
        cout << "}" << endl;
    }

    int getCount() const { return count; }
};
//
//int main() {
//    setlocale(LC_ALL, "");
//
//    //Множество символов
//    cout << "Множество символов" << endl;
//    SetTemplate<char> charSet;
//    charSet.add('A');
//    charSet.add('B');
//    charSet.add('C');
//    charSet.add('A'); // дубликат
//    cout << "Множество символов: ";
//    charSet.show();
//
//    SetTemplate<char> charSet2;
//    charSet2.add('B');
//    charSet2.add('C');
//    charSet2.add('D');
//    cout << "Множество символов 2: ";
//    charSet2.show();
//
//    SetTemplate<char> intersect = charSet.intersection(charSet2);
//    cout << "Пересечение: ";
//    intersect.show();
//    cout << "Подмножество? " << (intersect.isSubset(charSet) ? "да" : "нет") << endl;
//
//    //Множество квадратных матриц
//    cout << "\n Множество квадратных матриц" << endl;
//    SetTemplate<SquareMatrix> matrixSet;
//    SquareMatrix m1(2);
//    m1.setValue(0, 0, 1); m1.setValue(0, 1, 2);
//    m1.setValue(1, 0, 3); m1.setValue(1, 1, 4);
//
//    SquareMatrix m2(2);
//    m2.setValue(0, 0, 5); m2.setValue(0, 1, 6);
//    m2.setValue(1, 0, 7); m2.setValue(1, 1, 8);
//
//    matrixSet.add(m1);
//    matrixSet.add(m2);
//    matrixSet.add(m1); // дубликат не добавится
//    cout << "Множество матриц:" << endl;
//    matrixSet.show();
//
//    //Множество скалярных матриц
//    cout << "\n Множество скалярных матриц" << endl;
//    SetTemplate<ScalarMatrix> scalarSet;
//    ScalarMatrix sm1(2, 3);
//    ScalarMatrix sm2(2, 5);
//    scalarSet.add(sm1);
//    scalarSet.add(sm2);
//    cout << "Множество скалярных матриц:" << endl;
//    scalarSet.show();
//
//    //Множество треугольных матриц
//    cout << "\n Множество треугольных матриц" << endl;
//    SetTemplate<TriangularMatrix> triSet;
//    TriangularMatrix tm1(2, true);
//    tm1.setTriangularElement(0, 1, 7);
//    TriangularMatrix tm2(2, false);
//    tm2.setTriangularElement(1, 0, 8);
//    triSet.add(tm1);
//    triSet.add(tm2);
//    cout << "Множество треугольных матриц:" << endl;
//    triSet.show();
//
//    return 0;
//}
