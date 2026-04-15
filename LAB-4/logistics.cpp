#include <iostream>
#include <string>

using namespace std;

struct Package {
    string packageID;
    string destinationCity;
    int dimensions[3];
    Package* next;
};

struct Courier {
    string courierName;
    string vehicleType;
};

class PackageStack {
private:
    Package* top;
public:
    PackageStack() { top = nullptr; }

    void push(string id, string city, int l, int w, int h) {
        Package* newPkg = new Package();
        newPkg->packageID = id;
        newPkg->destinationCity = city;
        newPkg->dimensions[0] = l; newPkg->dimensions[1] = w; newPkg->dimensions[2] = h;
        newPkg->next = top;
        top = newPkg;
        cout << "Paket eklendi: " << id << endl;
    }

    Package* pop() {
        if (top == nullptr) return nullptr;
        Package* temp = top;
        top = top->next;
        return temp;
    }

    void display() {
        cout << "\n--- PAKET YIGINI ---\n";
        Package* temp = top;
        if (!temp) cout << "Yigin bos.\n";
        while (temp) {
            cout << "ID: " << temp->packageID << " | Sehir: " << temp->destinationCity << endl;
            temp = temp->next;
        }
    }
};

class CourierQueue {
private:
    static const int SIZE = 5;
    Courier items[SIZE];
    int front, rear;

public:
    CourierQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(string name, string vehicle) {
        if (isFull()) {
            cout << "Kurye sirasi dolu!\n";
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear].courierName = name;
        items[rear].vehicleType = vehicle;
        cout << "Kurye eklendi: " << name << endl;
    }

    Courier dequeue() {
        Courier empty = {"", ""};
        if (isEmpty()) return empty;
        Courier element = items[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
        return element;
    }

    void display() {
        cout << "\n--- KURYELER ---\n";
        if (isEmpty()) {
            cout << "Kurye sirasi bos.\n";
            return;
        }
        int i;
        for (i = front; i != rear; i = (i + 1) % SIZE) {
            cout << "Isim: " << items[i].courierName << " (" << items[i].vehicleType << ")\n";
        }
        cout << "Isim: " << items[i].courierName << " (" << items[i].vehicleType << ")\n";
    }
};

int main() {
    PackageStack stack;
    CourierQueue queue;
    int choice;

    while (true) {
        cout << "\n1. Paket Ekle\n2. Kurye Ekle\n3. Sevkiyat\n4. Listele\n5. Cikis\nSecim: ";
        cin >> choice;

        if (choice == 1) {
            string id, city;
            int l, w, h;
            cout << "ID ve Sehir: "; cin >> id >> city;
            cout << "Boyutlar (L W H): "; cin >> l >> w >> h;
            stack.push(id, city, l, w, h);
        } 
        else if (choice == 2) {
            string name, vtype;
            cout << "Ad ve Arac: "; cin >> name >> vtype;
            queue.enqueue(name, vtype);
        } 
        else if (choice == 3) {
            if (queue.isEmpty()) {
                cout << "Kurye yok!\n";
            } else {
                Package* p = stack.pop();
                if (p == nullptr) {
                    cout << "Paket yok!\n";
                } else {
                    Courier c = queue.dequeue();
                    cout << "SEVKIYAT: " << c.courierName << " -> " << p->packageID << " (" << p->destinationCity << ")\n";
                    delete p;
                }
            }
        } 
        else if (choice == 4) {
            stack.display();
            queue.display();
        } 
        else if (choice == 5) break;
    }
    return 0;
}