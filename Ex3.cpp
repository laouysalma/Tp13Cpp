#include <iostream>
#include <memory>
#include <stdexcept>
#include <iterator>
using namespace std;

class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "attention !!! Stack overflow";
    }
};

class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "attention !!! Stack underflow";
    }
};

template<typename T>
class Stack {
private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t top;

public:
    Stack(size_t cap = 10)
        : capacity(cap), top(0), data(make_unique<T[]>(cap)) {}

    template<typename Iter>
    Stack(Iter begin, Iter end)
        : capacity(distance(begin, end)), top(0), data(make_unique<T[]>(capacity)) {
        for (auto it = begin; it != end; ++it) push(*it);
    }

    void push(const T& value) {
        if (top == capacity) throw StackOverflow();
        data[top++] = value;
    }

    void pop() {
        if (empty()) throw StackUnderflow();
        --top;
    }

    T peek() const {
        if (empty()) throw StackUnderflow();
        return data[top - 1];
    }

    bool empty() const { return top == 0; }

    size_t size() const { return top; }

    ~Stack() = default; 
};

int main() {
    try {
        Stack<int> st(5);
        st.push(3);
        st.push(0);
        st.push(5);
        st.push(21);
        st.push(9);
        cout << "top: " << st.peek() << endl;
        st.pop();
        cout << "top: " << st.peek() << endl;

        int t[] = {12, 3, 6, 1};
        Stack<int> s2(begin(t), end(t));
        cout << "Top s2: " << s2.peek() << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
