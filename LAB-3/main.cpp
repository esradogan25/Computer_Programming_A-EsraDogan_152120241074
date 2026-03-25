#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    int ratings[3];
    Song* next;
    Song* prev;
};

void addSong(Song*& head, Song*& tail, Song*& current) {
    Song* newSong = new Song;

    cout << "Song title: ";
    cin.ignore();
    getline(cin, newSong->title);

    cout << "Artist name: ";
    getline(cin, newSong->artist);

    cout << "Enter 3 ratings: ";
    for (int i = 0; i < 3; i++) {
        cin >> newSong->ratings[i];
    }

    newSong->next = NULL;
    newSong->prev = NULL;

    if (head == NULL) {
        head = newSong;
        tail = newSong;
        current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    cout << "Song added.\n";
}

void moveNext(Song*& current) {
    if (current == NULL) {
        cout << "Playlist is empty.\n";
    } else if (current->next == NULL) {
        cout << "Already at last song.\n";
    } else {
        current = current->next;
        cout << "Moved to next song.\n";
    }
}

void movePrev(Song*& current) {
    if (current == NULL) {
        cout << "Playlist is empty.\n";
    } else if (current->prev == NULL) {
        cout << "Already at first song.\n";
    } else {
        current = current->prev;
        cout << "Moved to previous song.\n";
    }
}

void removeCurrent(Song*& head, Song*& tail, Song*& current) {
    if (current == NULL) {
        cout << "No song to remove.\n";
        return;
    }

    Song* temp = current;

    if (head == tail) {
        head = NULL;
        tail = NULL;
        current = NULL;
    } else if (current == head) {
        head = head->next;
        head->prev = NULL;
        current = head;
    } else if (current == tail) {
        tail = tail->prev;
        tail->next = NULL;
        current = tail;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
    }

    delete temp;
    cout << "Current song removed.\n";
}

void displaySongs(Song* head, Song* current) {
    if (head == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = head;
    cout << "\n--- Playlist ---\n";

    while (temp != NULL) {
        if (temp == current) {
            cout << "-> ";
        } else {
            cout << "   ";
        }

        cout << "Title: " << temp->title << endl;
        cout << "   Artist: " << temp->artist << endl;
        cout << "   Ratings: ";

        for (int i = 0; i < 3; i++) {
            cout << temp->ratings[i] << " ";
        }

        cout << endl << endl;
        temp = temp->next;
    }
}

int main() {
    Song* head = NULL;
    Song* tail = NULL;
    Song* current = NULL;

    int choice;

    do {
        cout << "\n1. Add Song\n";
        cout << "2. Next Song\n";
        cout << "3. Previous Song\n";
        cout << "4. Remove Current Song\n";
        cout << "5. Display Playlist\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addSong(head, tail, current);
                break;
            case 2:
                moveNext(current);
                break;
            case 3:
                movePrev(current);
                break;
            case 4:
                removeCurrent(head, tail, current);
                break;
            case 5:
                displaySongs(head, current);
                break;
            case 0:
                cout << "Program ended.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}