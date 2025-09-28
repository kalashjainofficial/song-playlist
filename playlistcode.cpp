#include <iostream>
using namespace std;

// copy from src -> dest
void copystr(const char src[], char dest[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
}

bool equals(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false; // mismatch
        }
        i++;
    }
    // if both ended at the same time, strings are equal
    return a[i] == '\0' && b[i] == '\0';
}

class song {
public:
    char name[50];
    char singer[50];
    song* next;
    song* previous;

    song(const char n[], const char s[]) {
        copystr(n, name);     // source -> destination
        copystr(s, singer);
        next = previous = nullptr;
    }
};


//insert a song
void insertattail(song* &head, song* &tail, const char n[], const char s[]) {
    // Check for duplicates first
    if (head != nullptr) {
        song* check = head;
        do {
            if (equals(check->name, n)) {
                cout << "song already exists" << endl;
                return;
            }
            check = check->next;
        } while (check != head);  // stop when we come back to head
    }

    // Create new node after confirming no duplicate
    song* temp = new song(n, s);

    if (head == nullptr) {
        // first node: circular to itself
        head = tail = temp;
        head->next = head->previous = head;
    } else {
        // append after tail and fix circular links
        tail->next = temp;
        temp->previous = tail;
        temp->next = head;
        head->previous = temp;
        tail = temp;
    }
}



// to remove a particular song
void remove(const char songn[], song* &head, song* &tail) {
    if (head == nullptr) return;

    song* temp = head;
    do {
        if (equals(temp->name, songn)) {
            // Case 1: only one node
            if (temp == head && temp == tail) {
                delete temp;
                head = tail = nullptr;
                return;
            }

            // Case 2: deleting head
            if (temp == head) {
                head = head->next;
            }

            // Case 3: deleting tail
            if (temp == tail) {
                tail = tail->previous;
            }

            // unlink
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;

            delete temp;
            return;  // stop after first deletion
        }
        temp = temp->next;
    } while (temp != head);
}


//to print playlist
void printlist(song* head) {
    if (head == nullptr) {
        cout << "playlist is empty" << endl;
        return;
    }
    song* temp = head;
    do {
        cout << temp->name << " -> " << temp->singer << endl;
        temp = temp->next;
    } while (temp != head);
}


//to delete a playlist
void deleteplaylist(song* &head, song* &tail) {
    if (head == nullptr) return;

    song* current = head;

    // Break circularity
    tail->next = nullptr; 
    head->previous = nullptr;

    while (current != nullptr) {
        song* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
}


//to search by name
void searchbyname(const char n[], song* head) {
    if (head == nullptr) {
        cout << "song not found" << endl;
        return;
    }

    song* temp = head;
    do {
        if (equals(temp->name, n)) {
            cout << temp->name << endl;
            cout << temp->singer << endl;
            return;
        }
        temp = temp->next;
    } while (temp != head);

    cout << "song not found" << endl;
}


//to search by singer
void searchbysinger(const char n[], song* head) {
    if (head == nullptr) {
        cout << "song not found" << endl;
        return;
    }

    song* temp = head;
    bool found = false;

    do {
        if (equals(temp->singer, n)) {
            cout << temp->name << " " << temp->singer << endl;
            found = true;
        }
        temp = temp->next;
    } while (temp != head);

    if (!found) {
        cout << "song not found" << endl;
    }
}



int main() {
    song* head = nullptr;
    song* tail = nullptr;
    cout << "SONG" << " -> " << "SINGER" << endl;

    insertattail(head, tail, "a", "A");
    insertattail(head, tail, "b", "B"); 
    insertattail(head, tail, "c", "A"); 

    printlist(head);

    cout << endl;

    remove("b" , head , tail);

    printlist(head);

    cout << endl;  

    searchbyname("a", head);
    searchbysinger("A", head);

    cout << endl;

    deleteplaylist(head , tail);
    cout << "deleted" << endl;

    printlist(head);

    return 0;
}
