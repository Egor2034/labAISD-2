#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {
public:
    LinkedList() : head_(nullptr) {}
    LinkedList(size_t count, T min, T max) requires std::integral<T>;
    LinkedList(size_t count, T min, T max) requires std::floating_point<T>;
    LinkedList(const LinkedList<T>& other);

    ~LinkedList() {
        if (head_) {
            Node* current = head_->next;

            while (current != head_) {
                Node* to_delete = current;
                current = current->next;
                delete to_delete;
            }

            delete head_;
        }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other);

    const T& operator[](size_t index) const {
        if (index >= count() || index < 0) { throw std::out_of_range("Out of range!"); }

        Node* current = head_;

        for (size_t i = 0; i != index; i++) {
            current = current->next;
        }

        return current->data;
    }

    T& operator[](size_t index) {
        if (index >= count() || index < 0) { throw std::out_of_range("Out of range!"); }

        Node* current = head_;

        for (size_t i = 0; i != index; i++) {
            current = current->next;
        }

        return current->data;
    }

    void print() const {
        if (head_ == nullptr) {
            std::cout << "";
            return;
        }

        Node* current = head_;

        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head_);

        std::cout << "\n";
    }

    void push_tail(T el) {
        if (head_ == nullptr) {
            head_ = new Node(nullptr, el);
            head_->next = head_;
        }
        else {
            Node* tail = head_;

            while (tail->next != head_) {
                tail = tail->next;
            }

            tail->next = new Node(head_, el);
        }
    }
    void push_tail(const LinkedList<T>& other);

    void push_head(T el) {
        if (head_ == nullptr) {
            head_ = new Node(nullptr, el);
            head_->next = head_;
        }
        else {
            Node* new_node = new Node(head_, el);
            Node* last = head_;

            while (last->next != head_) {
                last = last->next;
            }

            last->next = new_node;
            head_ = new_node;
        }
    }

    void push_head(const LinkedList<T>& other);
    void pop_head();
    void pop_tail();
    void delete_node(T el);

    bool contains(T el) const {
        if (head_ == nullptr) { return false; }

        Node* current = head_;

        do {
            if (current->data == el) { return true; }
            current = current->next;
        } while (current != head_);

        return false;
    }

    size_t count() const {
        if (head_ == nullptr) { return 0; }

        Node* current = head_;
        size_t size = 0;

        do {
            size++;
            current = current->next;
        } while (current != head_);
        
        return size;
    }
private:
    struct Node {
        Node* next;
        T data;
        Node(Node* next = nullptr, T data = T()) {
            this->next = next;
            this->data = data;
        }
    } *head_ = nullptr;
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