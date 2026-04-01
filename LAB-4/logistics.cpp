#include <iostream>
#include <string>
using namespace std;

struct package {
    string packageid;
    string destinationcity;
    int dimensions[3];
    package* next;
};

struct courier {
    string couriername;
    string vehicletype;
};

class packagestack {
private:
    package* top;

public:
    packagestack() {
        top = NULL;
    }

    bool isempty() {
        return top == NULL;
    }

    void push(string id, string city, int l, int w, int h) {
        package* p = new package();
        p->packageid = id;
        p->destinationcity = city;
        p->dimensions[0] = l;
        p->dimensions[1] = w;
        p->dimensions[2] = h;

        p->next = top;
        top = p;

        cout << "package added\n";
    }

    void pop() {
        if (isempty()) return;

        package* temp = top;
        top = top->next;
        delete temp;
    }

    package* peek() {
        return top;
    }

    void show() {
        if (isempty()) {
            cout << "stack empty\n";
            return;
        }

        package* cur = top;
        while (cur != NULL) {
            cout << cur->packageid << " -> " << cur->destinationcity << " ("
                 << cur->dimensions[0] << ","
                 << cur->dimensions[1] << ","
                 << cur->dimensions[2] << ")\n";
            cur = cur->next;
        }
    }
};

class courierqueue {
private:
    static const int size = 5;
    courier arr[size];
    int front, rear, count;

public:
    courierqueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isempty() {
        return count == 0;
    }

    bool isfull() {
        return count == size;
    }

    void enqueue(string name, string vehicle) {
        if (isfull()) {
            cout << "queue full\n";
            return;
        }

        rear = (rear + 1) % size;
        arr[rear].couriername = name;
        arr[rear].vehicletype = vehicle;
        count++;
    }

    void dequeue() {
        if (isempty()) return;

        front = (front + 1) % size;
        count--;
    }

    courier* peek() {
        if (isempty()) return NULL;
        return &arr[front];
    }

    void show() {
        if (isempty()) {
            cout << "queue empty\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            int index = (front + i) % size;
            cout << arr[index].couriername << " (" << arr[index].vehicletype << ")\n";
        }
    }
};

    package* p = stack.peek();
    courier* c = queue.peek();

    cout << c->couriername << " delivers " << p->packageid
         << " to " << p->destinationcity << endl;

    stack.pop();
    queue.dequeue();
}

int main() {
    packagestack stack;
    courierqueue queue;

    int choice;

    do {
        cout << "\n1 add package\n2 add courier\n3 dispatch\n4 show\n5 exit\n";
        cin >> choice;

        if (choice == 1) {
            string id, city;
            int l, w, h;
            cin >> id >> city >> l >> w >> h;
            stack.push(id, city, l, w, h);
        }
        else if (choice == 2) {
            string name, vehicle;
            cin >> name >> vehicle;
            queue.enqueue(name, vehicle);
        }
        else if (choice == 3) {
            dispatch(stack, queue);
        }
        else if (choice == 4) {
            cout << "packages:\n";
            stack.show();
            cout << "couriers:\n";
            queue.show();
        }

    } while (choice != 5);

    return 0;
}