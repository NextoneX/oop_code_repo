#include <iostream>

template<typename T>
class MyClass {
public:
    MyClass& operator<<(const T& value) {
        a = value;
        count++;
        return *this;
    }
    MyClass& operator,(const T& value) {
        if (count == 0) {
            a = value;
        } else if (count == 1) {
            b = value;
        } else if (count == 2) {
            c = value;
        }
        count++;
        return *this;
    }
    void print() const {
        std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    }

private:
    T a;
    T b;
    T c;
    int count = 0;
};

int main() {
    MyClass<int> a;
    a << 1, 2, 3;
    a.print(); // 输出：a = 1, b = 2, c = 3
    return 0;
}
