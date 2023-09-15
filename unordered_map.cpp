#include "unordered_map.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

unordered_map::unordered_map() 
    : m_buckets(7)
{

}

unordered_map::unordered_map(int count)
    : m_buckets(count) 
{

}

unordered_map::unordered_map(const std::pair<std::string, std::string>& elem) 
    : m_buckets(7) 
{
    insert(elem.first, elem.second);
}

unordered_map::unordered_map(const std::initializer_list<std::pair<std::string, std::string>>& init_list) 
    : m_buckets(10) 
{    
    for (const auto& elem : init_list) {
        insert(elem.first, elem.second);
    }
}

unordered_map::unordered_map(const unordered_map& other) 
    : m_buckets{other.m_buckets}
{
    
}

unordered_map& unordered_map::operator=(const unordered_map& other) {
    if(this != &other) {
        m_buckets = other.m_buckets;
    }
    return *this;
}

unordered_map::unordered_map(unordered_map&& other)  noexcept 
    : m_buckets{std::move(other.m_buckets)}
{

}

unordered_map& unordered_map::operator=(unordered_map&& other) noexcept {
    if(this != &other) {
        m_buckets = std::move(other.m_buckets);
    }
    return *this;
}

unordered_map::~unordered_map() {
    clear();
}

void unordered_map::insert(const std::string& key, const std::string& value) {
    update_load_factor();

    int index = hash_function(key);

    for(auto& elem : m_buckets[index]) {
        if(elem.first == key) {
            elem.second = value;
            return;
        }
    }

    m_buckets[index].emplace_front(key, value);
}

void unordered_map::remove(const std::string& key) {
    int index = hash_function(key);

    auto prev = m_buckets[index].before_begin();

    for(auto& elem : m_buckets[index]) {
        if(elem.first == key) {
            m_buckets[index].erase_after(prev);
            return;
        }
        ++prev;
    }
}

void unordered_map::clear() {
    m_buckets.clear();
}

std::string& unordered_map::operator[](const std::string& key) {
    int index = hash_function(key);

    for(auto& elem : m_buckets[index]) {
        if(elem.first == key) {
            return elem.second;
        }
    }

    m_buckets[index].emplace_front(key, std::string());
    return m_buckets[index].front().second;
}

std::string& unordered_map::at(const std::string& key) {
    int index = hash_function(key);

    for(auto& elem : m_buckets[index]) {
        if(elem.first == key) {
            return elem.second;
        }
    }

    throw std::out_of_range("Invalid index!");
}

float unordered_map::load_factor() const {
    if(m_buckets.size() == 0) {
        return 0.0;
    }

    return static_cast<float>(size()) / m_buckets.size();
}

int unordered_map::bucket_count() const {
    return m_buckets.size();
}

int unordered_map::bucket_size(int index) const {
    if(index >= m_buckets.size()) {
        return 0;
    }

    int count = 0;
    for(const auto& elem : m_buckets[index]) {
        ++count;
    }

    return count;
}

int unordered_map::size() const {
    int elemet = 0;
    for(const auto& bucket : m_buckets) {
        for(const auto& elem : bucket) {
            ++elemet;
        }
    }
    return elemet;
}

bool unordered_map::empty() const {
    for(const auto& bucket : m_buckets) {
        if(!bucket.empty()) {
            return false;
        }
    }

    return true;
}

void unordered_map::print() const {
    for(const auto& bucket : m_buckets) {
        for(const auto& elem : bucket) {
            std::cout << "Key: " << elem.first << ", value: " << elem.second << std::endl;
        }
    }
}

int unordered_map::hash_function(const std::string& str, int bucket_count) 
{
    int hash = 0;
    for (char ch : str) {
        hash = (hash * 31) + ch;
    }
    return std::abs(hash) % bucket_count;
}

int unordered_map::hash_function(const std::string& str) 
{
    return hash_function(str, m_buckets.size());
}

void unordered_map::rehash(int count) {
    if(count <= 0) {
        return;
    }

    std::vector<std::forward_list<std::pair<std::string, std::string>>> new_map(count);

    for(const auto& bucket : m_buckets) {
        for(const auto& elem : bucket) {
            int index = hash_function(elem.first, count);
            new_map[index].emplace_front(elem.first, elem.second);
        }
    }

    m_buckets = std::move(new_map);
}

void unordered_map::update_load_factor() {
    if (load_factor() > 0.735) {
        rehash(m_buckets.size() * 2);
    }
}
