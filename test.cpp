#include <iostream>
#include "unordered_map.h" 

void test_unordered_map() {
    // Create an empty unordered_map
    unordered_map myMap;

    // Insert some key-value pairs
    myMap.insert("apple", "red");
    myMap.insert("banana", "yellow");
    myMap.insert("grape", "purple");
    
    // Access elements using operator[]
    std::cout << "Color of apple: " << myMap["apple"] << std::endl;
    std::cout << "Color of grape: " << myMap["grape"] << std::endl;

    // Access elements using at() with bounds checking
    try {
        std::cout << "Color of cherry: " << myMap.at("cherry") << std::endl; // This will throw an exception
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // Check if the map is empty
    std::cout << "Is the map empty? " << (myMap.empty() ? "Yes" : "No") << std::endl;

    // Print the contents of the map
    myMap.print();

    // Remove an element
    myMap.remove("banana");

    // Check the size of the map
    std::cout << "Size of the map: " << myMap.size() << std::endl;

    // Check the load factor
    std::cout << "Load Factor: " << myMap.load_factor() << std::endl;

    // Check the bucket count
    std::cout << "Bucket Count: " << myMap.bucket_count() << std::endl;

    // Check the bucket size of a specific bucket
    std::cout << "Bucket Size of 0: " << myMap.bucket_size(0) << std::endl;

    // Clear the map
    myMap.clear();

    // Check if the map is empty after clearing
    std::cout << "Is the map empty after clearing? " << (myMap.empty() ? "Yes" : "No") << std::endl;
}

int main() {
    test_unordered_map();
    return 0;
}
