/**
 * Implementation of a Map class in C++ based on examples provided in
 * the Algorithmic Methods course at Norwegian University of Science and Technology (NTNU).
 *
 * Functions include:
 *
 * isEmpty(): checks if the Map is empty.
 * keyExists(): checks if the key is already in use.
 * put(): puts a new key-value-pair into an array sorted by keys (e.g. key of integer values: 1-2-3...)
 * get(): retrieves the value of key-value-pair by using its key to retrieve it.
 * resize(): expands the Map if its capacity is exceeded.
 *
 * @author Johannes Nupen Theigen
 * @version 24.08.2025
 * @since 23.08.2025
 **/
#include <iostream>
#include <string>
#include <utility>
using namespace std;

template<typename K, typename V>

class Map {
    struct KeyValuePair {
        K key;
        V value;

        KeyValuePair(K k, const V &v) : key(std::move(k)), value(v) {
        } // Constructor to initialize key and value
        KeyValuePair() : key(), value() {
        } // Default constructor to initialize key and value to their default types
    };

    KeyValuePair *data; // Pointer to an array of KeyValuePair
    int amount;
    int capacity;

public:
    Map(const int len = 200) {
        data = new KeyValuePair[len]; // Allocate memory for the array of KeyValuePair
        capacity = len;
        amount = 0;
    }

    ~Map() {
        delete [] data; // Free allocated memory
    }

    bool isEmpty() const { // Check if the map is empty
        return amount == 0;
    }

    bool findKey(const K &key) const { // Check if the key exists in the map
        for (int i = 0; i < amount; ++i) {
            if (data[i].key == key) {
                return true;
            }
        }
        return false;
    }

    void put(const K &key, const V &value) { // Insert a new key-value pair into the map
        if (amount == capacity) {
            resize(capacity + 100);
        }
        int newIndex = 0;
        if (!findKey(key)) {
            if (amount < capacity) {
                while (newIndex < amount && data[newIndex].key < key)
                    newIndex++;
                amount++;
                for (int i = amount - 1; i > newIndex; --i) {
                    data[i] = data[i - 1];
                }
                data[newIndex] = KeyValuePair(key, value);
            }
        } else cout << "Key already exists, cannot add duplicate keys.\n";
    }

    bool replace(const K &key, const V &oldValue, const V &newValue) { // Replace the value of a key-value pair with a new value
            bool wasReplaced = false;
            for (int i = 0; i < amount; i++) {
                if (data[i].key == key && data[i].value == oldValue) {
                    data[i].value = newValue;
                    wasReplaced = true;
                }
            }
            return wasReplaced;
    }

    V get(const K &key) const {
        // Retrieve the value associated with the given key
        for (int i = 0; i < amount; i++) {
            if (findKey(key)) {
                return data[i].value;
            }
        }
        return V();
    }


    bool remove(const K &key) { // Remove the key-value pair with the given key
        bool wasRemoved = false;
        for (int i = 0; i < amount; i++) {
            if (data[i].key == key) {
                for (int j = i; j < amount - 1; j++) {
                    data[j] = data[j + 1];
                }
                amount--;
                wasRemoved = true;
            }
        }
        return wasRemoved;
    }

    void resize(const int newLenght) { // Resize the internal array to a new length
        if (newLenght > capacity) {
            KeyValuePair *newData = new KeyValuePair[newLenght];
            for (int i = 0; i < amount; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newLenght;
        }
    }

    void display() { // Display all key-value pairs in the map
        for (int i = 0; i < amount; ++i) {
            cout << data[i].key << " " << data[i].value << "\n";
        }
    }
};

int main() {
    Map<string, int> map; // Create a Map with string keys and int values based on my real name and the lenght of each name

    map.put("Johannes", 8);
    map.put("Nupen", 5);
    map.put("Theigen", 7);
    map.display();
    return 0;
}
