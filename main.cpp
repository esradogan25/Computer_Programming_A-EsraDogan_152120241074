#include <iostream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
};

void appendWord(Node*& head, string word) {
    Node* newNode = new Node();
    newNode->data = word;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}


void undoLast(Node*& head) {
    if (head == nullptr) {
        cout << "Liste zaten bos!" << endl;
        return;
    }

    
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    
    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }

    
    delete temp->next;
    temp->next = nullptr;
}


void displayList(Node* head) {
    Node* temp = head;
    cout << "Metin: ";
    while (temp != nullptr) {
        cout << "[" << temp->data << "] -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}


int main() {
    Node* head = nullptr;
    string input;

    cout << " 'UNDO', 'EXIT' " << endl;

    while (true) {
        cout << ">> ";
        cin >> input;

        if (input == "EXIT") {
            break;
        } 
        else if (input == "UNDO") {
            undoLast(head);
        } 
        else {
            appendWord(head, input);
        }

        displayList(head);
    }

   
    while (head != nullptr) {
        undoLast(head);
    }

    return 0;
}