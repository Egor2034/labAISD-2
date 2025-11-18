#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {
public:
    LinkedList() : head_(nullptr), count_(0) {}
    LinkedList(size_t count, T min, T max) requires std::integral<T>;
    LinkedList(size_t count, T min, T max) requires std::floating_point<T>;

    LinkedList(const LinkedList<T>& other) { copy(other); }

    ~LinkedList() { clear(); }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            clear();
            copy(other);
        }

        return *this;
    }

    const T& operator[](size_t index) const {
        if (index >= count_ || index < 0) { throw std::out_of_range("Out of range!"); }

        Node* current = head_;

        for (size_t i = 0; i != index; i++) {
            current = current->next;
        }

        return current->data;
    }

    T& operator[](size_t index) {
        if (index >= count_ || index < 0) { throw std::out_of_range("Out of range!"); }

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
            count_++;
        }
        else {
            Node* tail = head_;

            while (tail->next != head_) {
                tail = tail->next;
            }

            tail->next = new Node(head_, el);
            count_++;
        }
    }

    void push_tail(const LinkedList<T>& other);

    void push_head(T el) {
        if (head_ == nullptr) {
            head_ = new Node(nullptr, el);
            head_->next = head_;
            count_++;
        }
        else {
            Node* new_node = new Node(head_, el);
            Node* last = head_;

            while (last->next != head_) {
                last = last->next;
            }

            last->next = new_node;
            head_ = new_node;
            count_++;
        }
    }

    void push_head(const LinkedList<T>& other);

    void pop_head() {
        if (!head_) { return; }

        if (count_ == 1) {
            delete head_;
            head_ = nullptr;
            count_ = 0;
            return;
        }

        Node* last = head_;

        while (last->next != head_) {
            last = last->next;
        }

        Node* after_head = head_->next;
        delete head_;
        count_--;
        head_ = after_head;
        last->next = head_;
    }

    void pop_tail() {
        if (!head_) { return; }

        if (count_ == 1) {
            pop_head();
        }

        Node* current = head_;

        while (current->next->next != head_) {
            current = current->next;
        }

        Node* to_delete = current->next;
        current->next = head_;
        delete to_delete;
        count_--;
    }

    //TODO у меня есть метод contains
    void delete_node(T el) {
        if (head_) {
            Node* current = head_;

            do {
                if (current->next->data == el) {
                    Node* to_delete = current->next;
                    current->next = current->next->next;
                    current = current->next;
                    delete to_delete;
                    count_--;
                }
                else {
                    current = current->next;
                }
            } while (current != head_);
        }
    }

    bool contains(T el) const {
        if (head_ == nullptr) { return false; }

        Node* current = head_;

        do {
            if (current->data == el) { return true; }
            current = current->next;
        } while (current != head_);

        return false;
    }

    size_t count() const { return count_; }
private:
    void clear() {
        if (head_) {
            Node* current = head_->next;

            while (current != head_) {
                Node* to_delete = current;
                current = current->next;
                delete to_delete;
            }

            delete head_;
            head_ = nullptr;
            count_ = 0;
        }
    }

    void copy(const LinkedList<T>& other) {
        Node* current = other.head_;

        if (current) {
            do {
                push_tail(current->data);
                current = current->next;
            } while (current != other.head_);
        }
    }

    struct Node {
        Node* next;
        T data;
        Node(Node* next = nullptr, T data = T()) {
            this->next = next;
            this->data = data;
        }
    } *head_ = nullptr;

    size_t count_ = 0;
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