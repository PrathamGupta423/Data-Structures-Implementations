#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> myMap;

    // Inserting key-value pairs
    myMap["apple"] = 5;
    myMap["banana"] = 10;
    myMap["orange"] = 7;

    // Accessing elements
    std::cout << "Value for key 'apple': " << myMap["apple"] << std::endl;

    // Iterating through the map
    std::cout << "Contents of the map:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Finding and deleting an element
    auto it = myMap.find("banana");
    if (it != myMap.end()) {
        myMap.erase(it);
        std::cout << "Deleted key 'banana'." << std::endl;
    }

    return 0;
}
