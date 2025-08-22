/**
 * WIP Implementation of a Map class in C++ based on examples provided in
 *the Algorithmic Methods course at Norwegian University of Science and Technology (NTNU).
 *
 **/
#include <iostream>
#include <string>
#include <utility>
using namespace std;

template<typename K, typename V>

class Map {

private:
    struct KeyValuePair {
        K key;
        V value;
        KeyValuePair(K  k, const V& v) : key(std::move(k)), value(v) {} // Constructor to initialize key and value
        KeyValuePair() : key(), value() {} // Default constructor to initialize key and value to their default types
    };

    KeyValuePair* data; // Pointer to an array of KeyValuePair
    int amount;
    int capacity;

public:
    Map(const int len = 200) {
        data = new KeyValuePair[len]; // Allocate memory for the array of KeyValuePair
        capacity = len;
        amount = 0;
    }
    ~Map () {
        delete [] data; // Free allocated memory
    }

    bool isEmpty() {
        return amount == 0;
    }

    bool isKey(const K& key) {
        for (int i = 0; i < amount; ++i) {
            if (data[i].key == key) { // Check if the key exists in the map
                return true;
            }
        }
        return false;
    }

    void resize(const int newLenght) {
        if (newLenght > capacity) {
            KeyValuePair *newData = new KeyValuePair[newLenght]; // Allocate new array of KeyValuePair
            for (int i = 0; i < amount; i++) {
                newData[i] = data[i]; // Copy old key-value pairs to the new array
            }
            delete[] data; // Free old array
            data = newData; // Set the new array as the data
            capacity = newLenght; // Update capacity
        }
    }

    void put(const K& key, const V& value) {
        if (!isKey(key)) {
            data[amount++] = KeyValuePair(key, value); // Add new key-value pair if key does not exist
            if (amount >= capacity) { // Check if capacity needs to be increased
                resize(capacity + 100);
            }
        } else {
            cout << "Key already exists!";
        }
    }

    void display() {
        for (int i = 0; i < amount; ++i) {
            cout << data[i].key <<  " " << data[i].value << "\n"; // Display each key-value pair
        }
    }
};

int main() {
    Map<string, int> map; // Create a Map with string keys and int values

    map.put("Johannes", 8);
    map.put("Nupen", 5);
    map.put("Theigen", 7);
    map.display();
    return 0;
}