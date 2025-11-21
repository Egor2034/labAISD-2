#ifndef LINKED_LIST
#define LINKED_LIST

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <random>

template <typename T>
class LinkedList {
public:
    LinkedList() : head_(nullptr), count_(0) {}

    LinkedList(size_t count, T min, T max) requires std::integral<T> {
        if (min > max) std::swap(min, max);

        if (count == 0) {
            count_ = 0;
            head_ = nullptr;
            return;
        }

        std::random_device seed;
        std::mt19937 generator(seed());
        std::uniform_int_distribution distribution(min, max);      
        
        for (size_t i = 0; i < count; i++) {
            push_tail(distribution(generator));
        }
    }

    LinkedList(size_t count, T min, T max) requires std::floating_point<T> {
        if (min > max) std::swap(min, max);

        if (count == 0) {
            count_ = 0;
            head_ = nullptr;
            return;
        }

        std::random_device seed;
        std::mt19937 generator(seed());
        std::uniform_real_distribution distribution(min, max);

        for (size_t i = 0; i < count; i++) {
            push_tail(distribution(generator));
        }
    }

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

    void push_tail(const LinkedList<T>& other) {
        if (other.head_ == nullptr) { return; }
        if (head_ == nullptr) { 
            copy(other);
            return;
        }

        Node* current = head_;

        do {
            current = current->next;
        } while (current->next != head_);

        for (size_t i = 0; i < other.count_; i++) {
            push_tail(other[i]);
        }
    }

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

    void push_head(const LinkedList<T>& other) {
        if (other.head_ == nullptr) { return; }
        if (head_ == nullptr) { 
            copy(other); 
            return; 
        }

        LinkedList<T> temp(*this);
        clear();
        
        for (size_t i = 0; i < other.count_; i++) {
            push_tail(other[i]);
        }

        push_tail(temp);
    }

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
            return;
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

    void delete_node(T el) {
        if (!contains(el)) { return; }

        if (head_) {
            LinkedList<T> temp;
            Node* current = head_;
            
            do {
                if (current->data != el) { temp.push_tail(current->data); }
                current = current->next;
            } while (current != head_);

            clear();
            copy(temp);
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

    T max() const {
        if (head_ == nullptr) {
            throw std::exception("List is empty!");
        }

        Node* current = head_;
        T max = current->data;

        do {
            max = (current->data > max) ? current->data : max;
            current = current->next;
        } while (current != head_);

        return max;
    }
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

template <typename T>
void eratosthenes(LinkedList<T>& list) requires std::integral<T> {
    if (list.count() == 0) { return; }

    list.delete_node(1);

    size_t count = list.count();
    T max = list.max();

    LinkedList<T> temp(list);
    for (size_t i = 0; i < count; i++) {
        if (temp.contains(list[i])) {
            for (T mult = 2 * list[i]; mult <= max; mult += list[i]) {
                temp.delete_node(mult);
            }
        }
    }

    list = temp;
}

#endif  