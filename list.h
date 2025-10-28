#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

template <typename T>
class LinkedList {
public:
    LinkedList();
    LinkedList(size_T count, T min, T max) requires std::integral<Type>;
    LinkedList(size_t count, T min, T max) requires std::floating_point<Type>;
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();

    LinkedList<T>& operator=(const LinkedList<T>& other);
    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    void print() const;
    void push_tail(T el);
    void push_tail(const LinkedList<T>& other);
    void push_head(T el);
    void push_head(const LinkedList<T>& other);
    void pop_head();
    void pop_tail();
    void delete_node(T el);
    bool contains() const;
    size_t get_count() const;
private:
    struct Node {
        Node* next;
        T data;
        Node(Node* next = nullptr, T data = Type()) {
            this->next = next;
            this->data = data;
        }
    } *_tail = nullptr;

    size_t _count;
};

template <typename T>
bool is_prime(T number) requires std::integral<T> {
    if (number <= 1) { return false; }

    for (T i = 2; i < number; i++) {
        if (number % i == 0) { return false; }
    }

    return true;
}

#endif