// COMSC-210 | Mauricio Espinosa | Lab 22
// IDE Used: Visual Studios Code & Github

#include <iostream>
#include <ctime> // for seeding time
#include <cstdlib> // for randoms
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    // revised name to delete_val, functionality unchanged
    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    // delete by position
    void delete_pos(int position) {
        if (!head || position < 0) return; // Empty list

        Node* temp = head;
        for (int i = 0; i < position && temp; i++) {
            temp = temp->next;
        }

        if (!temp) return;   // if temp reaches past the list

        // deleting the head
        if (temp->prev) {
            temp->prev->next = temp->next;
        }
        else {
            head = temp->next;
        }

        // deleting the tail
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        else {
            head = temp->prev;
        }

        delete temp; 

    }

    // Function to delete head node
    void pop_front() {
        delete_val(head->data);        
    }

    // Function to delete tail node
    void pop_back() {
        delete_val(tail->data);
    }


    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    int userPosition;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);

    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    // Print after pop functions
    list.pop_front();
    cout << "List after pop front: ";
    list.print();

    list.pop_back();
    cout << "List after pop back: ";
    list.print();

    // Print after deleting a position
    cout << "Which position to delete? ";
    cin >> userPosition;
    list.delete_pos(userPosition);
    cout << "List after position #" << userPosition << " was deleted: ";
    list.print();   

    return 0;
}
