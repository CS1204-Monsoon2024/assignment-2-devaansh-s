#include <iostream>
#include <string>
using namespace std;

class HashTable {
private:
    string* slots;
    int capacity;
    int current_entries;
    double max_load_factor;

    int hashFunction(int key) {
        return key % capacity;
    }

    bool checkPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    int findNextPrime(int n) {
        while (!checkPrime(n)) {
            n++;
        }
        return n;
    }

    void rehash() {
        int old_capacity = capacity;
        capacity = findNextPrime(2 * capacity);
        string* old_slots = slots;
        slots = new string[capacity];
        current_entries = 0;

        for (int i = 0; i < capacity; i++) {
            slots[i] = "Free";
        }

        for (int i = 0; i < old_capacity; i++) {
            if (old_slots[i] != "Free" && old_slots[i] != "Removed") {
                insert(stoi(old_slots[i]));
            }
        }
        delete[] old_slots;
    }

public:
    HashTable(int init_size) {
        max_load_factor = 0.8;
        capacity = findNextPrime(init_size);
        slots = new string[capacity];
        current_entries = 0;

        for (int i = 0; i < capacity; i++) {
            slots[i] = "Free";
        }
    }

    void insert(int key) {
    cout << "Inserting: " << key << endl;

    if (contains(key)) {
        cout << "Duplicate key insertion is not allowed" << endl;
        return;
    }

    if ((double)current_entries / capacity > max_load_factor) {
        cout << "Resizing table..." << endl;
        rehash();
    }

    int index = hashFunction(key);
    int probe_count = 0;

    while (slots[(index + probe_count * probe_count) % capacity] != "Free" &&
           slots[(index + probe_count * probe_count) % capacity] != "Removed") {
        cout << "Collision at index " << (index + probe_count * probe_count) % capacity << endl;
        probe_count++;

        if (probe_count == capacity) {
            cout << "Max probing limit reached!" << endl;
            return;
        }
    }

    slots[(index + probe_count * probe_count) % capacity] = to_string(key);
    current_entries++;

    cout << "Inserted " << key << " at index " << (index + probe_count * probe_count) % capacity << endl;
}


        slots[(index + probe_count * probe_count) % capacity] = to_string(key);
        current_entries++;
    }

    bool contains(int key) {
        int index = hashFunction(key);
        int probe_count = 0;

        while (slots[(index + probe_count * probe_count) % capacity] != "Free") {
            if (slots[(index + probe_count * probe_count) % capacity] != "Removed" &&
                stoi(slots[(index + probe_count * probe_count) % capacity]) == key) {
                return true;
            }
            probe_count++;
            if (probe_count == capacity) {
                break;
            }
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int probe_count = 0;

        while (slots[(index + probe_count * probe_count) % capacity] != "Free") {
            if (slots[(index + probe_count * probe_count) % capacity] != "Removed" &&
                stoi(slots[(index + probe_count * probe_count) % capacity]) == key) {
                slots[(index + probe_count * probe_count) % capacity] = "Removed";
                current_entries--;
                return;
            }
            probe_count++;
        }

        cout << "Element not found" << endl;
    }

    int search(int key) {
        int index = hashFunction(key);
        int probe_count = 0;

        while (slots[(index + probe_count * probe_count) % capacity] != "Free") {
            if (slots[(index + probe_count * probe_count) % capacity] != "Removed" &&
                stoi(slots[(index + probe_count * probe_count) % capacity]) == key) {
                return (index + probe_count * probe_count) % capacity;
            }
            probe_count++;
            if (probe_count == capacity) {
                break;
            }
        }
        return -1;  
    }

    void printTable() const {
        for (int i = 0; i < capacity; i++) {
            if (slots[i] == "Free" || slots[i] == "Removed") {
                cout << "- ";
            } else {
                cout << slots[i] << " ";
            }
        }
        cout << endl; 
    }

};

//int main() {
    //int initialSize = 7; 
    //HashTable ht(initialSize);

    // Example test case
   // ht.insert(1);
   // ht.printTable();
   // ht.insert(6);
   // ht.printTable();
    // ht.insert(15);
    // ht.printTable(); 
   // ht.insert(25);
   // ht.printTable();
   // ht.remove(15);
   // ht.printTable();
   // ht.insert(29);  
   // ht.printTable(); 

   // int find = ht.search(22);
   // std::cout << "Found at: " << find << std::endl;

    //return 0;
//}

