#include <iostream>
#include "HighwayHashLibrary.hpp"

// g++ -fsanitize=address -fconcepts Example.cpp -Lhighwayhash

// Define a simple struct
struct MyStruct {
    int id;
    double value;
    char name[20]; // Fixed-size character array

    // Constructor for easy initialization
    MyStruct(int i, double v, const char* n) : id(i), value(v) {
        std::strncpy(name, n, sizeof(name));
        name[sizeof(name) - 1] = '\0'; // Ensure null-termination
    }
};

// Main function to demonstrate hashing
int main() {
    // Create an instance of MyStruct
    MyStruct obj1(1, 42.0, "Example");
    MyStruct obj2(2, 3.14, "Test");

    // Create a hasher for MyStruct
    Hasher<MyStruct> myStructHasher;

    // Compute hashes for both objects
    size_t hash1 = myStructHasher(obj1);
    size_t hash2 = myStructHasher(obj2);

    // Output the hash values
    std::cout << "Hash of obj1: " << hash1 << std::endl;
    std::cout << "Hash of obj2: " << hash2 << std::endl;

    // Check equality using the overloaded operators
    if (obj1 == obj2) {
        std::cout << "obj1 and obj2 are equal." << std::endl;
    } else {
        std::cout << "obj1 and obj2 are not equal." << std::endl;
    }

    return 0;
}
