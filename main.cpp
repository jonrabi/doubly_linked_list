#include <iostream>
#include <cassert>

template<typename T>
class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};

template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void pop_back() {
        assert(head);

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        size--;
    }

    void push_front(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void pop_front() {
        assert(head);

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        size--;
    }

    void insert(const T& val, int pos) {
        assert(pos >= 0 && pos <= size);

        if (pos == 0) {
            push_front(val);
        } else if (pos == size) {
            push_back(val);
        } else {
            Node<T>* newNode = new Node<T>(val);
            Node<T>* current = head;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            size++;
        }
    }

    void remove(int pos) {
        assert(pos >= 0 && pos < size);

        if (pos == 0) {
            pop_front();
        } else if (pos == size - 1) {
            pop_back();
        } else {
            Node<T>* current = head;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            size--;
        }
    }

    T& at(int pos) {
        assert(pos >= 0 && pos < size);

        Node<T>* current = head;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    int getSize() const {
        return size;
    }
};

#include <gtest/gtest.h>

TEST(DoublyLinkedListTest, PushBackPopBackTest) {
    DoublyLinkedList<int> dll;
    dll.push_back(1);
    dll.push_back(2);
    dll.push_back(3);

    dll.pop_back();
    dll.pop_back();

    EXPECT_EQ(dll.pop_back(), 1);
}

TEST(DoublyLinkedListTest, PushFrontPopFrontTest) {
    DoublyLinkedList<int> dll;
    dll.push_front(1);
    dll.push_front(2);
    dll.push_front(3);

    dll.pop_front();
    dll.pop_front();

    EXPECT_EQ(dll.pop_front(), 1);
}

TEST(DoublyLinkedListTest, InsertRemoveTest) {
    DoublyLinkedList<int> dll;
    dll.push_back(1);
    dll.push_back(2);
    dll.push_back(4);

    dll.insert(3, 2);

    EXPECT_EQ(dll.at(2), 3);

    dll.remove(2);

    EXPECT_EQ(dll.at(2), 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
