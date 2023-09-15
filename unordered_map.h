#ifndef HASH_MAP
#define HASH_MAP

#include <vector>
#include <forward_list>
#include <string>
#include <initializer_list>
#include <utility>

class unordered_map
{
private:
    std::vector<std::forward_list<std::pair<std::string, std::string>>> m_buckets;

    int hash_function(const std::string& str);  // Compute the hash value for a key
    int hash_function(const std::string& str, int bucket_count);
    void rehash(int count); // Rehash the hash set with a new count
    void update_load_factor(); // Helper function for load factor updates

public:
    // Constructors
    unordered_map();
    explicit unordered_map(int count);
    unordered_map(const std::pair<std::string, std::string>& elem);
    unordered_map(const std::initializer_list<std::pair<std::string, std::string>>& init_list);

    unordered_map(const unordered_map& other); // Copy Constructor
    unordered_map& operator=(const unordered_map& other); // Copy Assignment Operator
    unordered_map(unordered_map&& other)  noexcept; // Move Constructor
    unordered_map& operator=(unordered_map&& other) noexcept; // Move Assignment Operator
    ~unordered_map(); // Destructor

    // Modifiers
    void insert(const std::string& key, const std::string& value); // Inserts elements 
    void remove(const std::string& key); // Remove an element
    void clear(); // Clears the contents

    // Lookup
    std::string& operator[](const std::string& key); // Access or insert specified element
    std::string& at(const std::string& key); // Access specified element with bounds checking

    // Hash policy
    float load_factor() const; // Calculate the current load factor

    // Bucket interface
    int bucket_count() const; // Get the total number of buckets
    int bucket_size(int index) const; // Get the size of a specific bucket

    // Capacity
    int size() const; // Get the number of elements
    bool empty() const; // Check if the hash set is empty

    // helper
    void print() const; // Print the contents of the hash map  
}; 

#endif
