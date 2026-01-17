//
// Created by ppiqu on 12/01/2026.
//

#ifndef GESTION_ACCESOS_H
#define GESTION_ACCESOS_H

#include <iostream>

class Analista;

template<typename T>
class LinkedList {
    friend class Analista;
private:
    struct Node {
        T data;
        Node *next;

        Node(T val) : data(val), next(nullptr) {
        }
    };
    Node *head;
    Node *tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {
    }

    LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr), size(0) {
        Node *current = other.head;
        while (current != nullptr) {
            insertAtLast(current->data);
            current = current->next;
        }
    }

    // se usa para asignar una lista a otra
    LinkedList &operator=(const LinkedList &other) {
        if (this != &other) {
            // Evitar auto-asignación
            clear(); // Vaciamos la lista actual
            Node *current = other.head;
            while (current != nullptr) {
                insertAtLast(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    ~LinkedList() {
        clear();
    }

    // inserta un elemento al final de la lista
    void insertAtLast(T data) {
        Node *newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // elimina duplicados
    void removeDuplicates() {
        if (!head || !head->next) return; // no hay nada que hacer si la lista está empty o solo un elemneto

        Node *current = head;
        while (current) {
            Node *runner = current;

            while (runner->next) {
                if (current->data == runner->next->data) {
                    Node *duplicate = runner->next;
                    runner->next = runner->next->next;

                    if (duplicate == tail) {
                        tail = runner;
                    }

                    delete duplicate;
                    size--;
                } else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    // elimina un nodo de la lista buscando por su valor.
    bool remove(T data) {
        if (!head) return false;

        // el nodo a borrar es el primero.
        if (head->data == data) {
            Node *temp = head;
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete temp;
            size--;
            return true;
        }

        // Bbscamos el nodo a borrar
        Node *current = head;
        while (current->next) {
            if (current->next->data == data) {
                Node *toDelete = current->next;
                current->next = toDelete->next;
                if (toDelete == tail) tail = current; // si era el último, actualizamos la cola
                delete toDelete;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    T &getAtIndex(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node *temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    const T &getAtIndex(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node *temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    int getSize() const {
        return size;
    }
    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        Node *current = head;
        while (current) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void printList() const {
        Node *temp = head;
        while (temp) {
            std::cout << "  - " << temp->data.toString() << std::endl;
            temp = temp->next;
        }
    }
};


#endif //GESTION_ACCESOS_H