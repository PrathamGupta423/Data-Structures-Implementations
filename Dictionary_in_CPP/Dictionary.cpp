#include <iostream>
#include <vector>
#include <list>
#include <functional>

// Structure to represent key-value pairs
template<typename K, typename V>
struct KeyValuePair {
    K key;
    V value;
    
    KeyValuePair(const K& k, const V& v){
    key = k;
    value = v;
    }
};

// Hash table implementation using chaining for collision resolution
template<typename K, typename V>
class Dictionary {
private:
    size_t size;
    std::vector<std::list<KeyValuePair<K, V>>> table;
    
    size_t hash(const K& key) {
        static std::hash<K> hasher;
        return hasher(key) % size;
    }

public:
    Dictionary(size_t initialSize = 10) : size(initialSize), table(initialSize) {}  
    
    void insert(const K& key, const V& value) {
        size_t index = hash(key);

        // Check if key already exists : required for hash collision
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                // Key already exists, update the value
                pair.value = value;
                return;
            }
        }
        // Key doesn't exist, add a new key-value pair
        table[index].emplace_back(key, value);
    }
    
    bool search(const K& key, V& value) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                // Key found, return the corresponding value
                value = pair.value;
                return true;
            }
        }
        // Key not found
        return false;
    }
    void printDictionary() {
        for (size_t i = 0; i < size; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (auto& pair : table[i]) {
                std::cout << "(" << pair.key << ": " << pair.value << ") ";
            }
            std::cout << std::endl;
        }
    }

    void deleteKey(const K& key) {
        size_t index = hash(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                return;
            }
        }
    }
    
    // Other methods like delete, size, etc., can be implemented similarly
};

int main() {
    Dictionary<std::string, int> myDictionary;

    // Inserting key-value pairs
    myDictionary.insert("apple", 5);
    myDictionary.insert("banana", 10);
    myDictionary.insert("orange", 7);

    // Searching for values using keys
    int value;
    if (myDictionary.search("apple", value)) {
        std::cout << "Value for key 'apple': " << value << std::endl;
    } else {
        std::cout << "Key 'apple' not found!" << std::endl;
    }
    
    // Printing the dictionary
    std::cout << "Dictionary contents:" << std::endl;
    myDictionary.printDictionary();

    // Deleting a key
    std::cout << "\nDeleting key 'banana'...\n";
    myDictionary.deleteKey("banana");

    // Printing the dictionary after deletion
    std::cout << "\nDictionary contents after deletion:" << std::endl;
    myDictionary.printDictionary();

    myDictionary.insert("a", 1);
    myDictionary.insert("b", 2);
    myDictionary.insert("c", 3);
    myDictionary.insert("d", 4);
    myDictionary.insert("e", 5);
    myDictionary.insert("f", 6);
    myDictionary.insert("g", 7);
    myDictionary.insert("h", 8);
    myDictionary.insert("i", 9);
    myDictionary.insert("j", 10);
    myDictionary.insert("k", 11);
    myDictionary.insert("l", 12);

    std::cout << "\nDictionary contents after insertion:" << std::endl;
    myDictionary.printDictionary();



    return 0;
}

