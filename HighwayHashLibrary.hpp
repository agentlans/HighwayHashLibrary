// HighwayHashLibrary.h
#ifndef HIGHWAY_HASH_LIBRARY_H
#define HIGHWAY_HASH_LIBRARY_H

#include <array>
#include <cstring>
#include <type_traits>
#include <concepts>
#include <cstdint>
#include <random>
#include <algorithm>
#include <limits>
#include <highwayhash/highwayhash.h>

// Concept to check if a type is trivially copyable
template<typename T>
concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

// Convert an object to an array of bytes
template<TriviallyCopyable T>
std::array<unsigned char, sizeof(T)> objectToBytes(const T& obj) {
    std::array<unsigned char, sizeof(T)> bytes;
    std::memcpy(bytes.data(), &obj, sizeof(T));
    return bytes;
}

// Convert an array of bytes back to an object
template<TriviallyCopyable T>
T bytesToObject(const std::array<unsigned char, sizeof(T)>& bytes) {
    T obj;
    std::memcpy(&obj, bytes.data(), sizeof(T));
    return obj;
}

// Equality operators for trivially copyable types
template<TriviallyCopyable T>
bool operator==(const T& lhs, const T& rhs) {
    return objectToBytes(lhs) == objectToBytes(rhs);
}

template<TriviallyCopyable T>
bool operator!=(const T& lhs, const T& rhs) {
    return !(lhs == rhs);
}

// Constants for size limits
constexpr size_t maxSizeT = std::numeric_limits<size_t>::max();
constexpr uint64_t maxUInt64 = std::numeric_limits<uint64_t>::max();

// Convert uint64_t to size_t safely using if constexpr
constexpr size_t convertToSizeT(uint64_t x) {
    if constexpr (maxUInt64 == maxSizeT) {
        return static_cast<size_t>(x); // No need for modulo operation
    } else {
        return static_cast<size_t>(x % (maxSizeT + 1)); // Use modulo operation
    }
}

// Class for hashing using HighwayHash
class HighwayHasher {
public:
    using Key = std::array<uint64_t, 4>;
    using Result64 = uint64_t;

    HighwayHasher() : key_{}, generator_(std::random_device{}()) {
        generateSecureKey();
    }

    explicit HighwayHasher(const Key& key) : key_(key), generator_(std::random_device{}()) {}

    void resetKey() {
        generateSecureKey();
    }

    Result64 hash64(const char* data, size_t size) const {
        Result64 result;
        highwayhash::HHStateT<HH_TARGET> state(key_.data());
        highwayhash::HighwayHashT(&state, data, size, &result);
        return result;
    }

private:
    alignas(32) Key key_;
    std::mt19937_64 generator_;

    void generateSecureKey() {
        std::uniform_int_distribution<uint64_t> distribution;
        std::generate(key_.begin(), key_.end(), [&]() { return distribution(generator_); });
    }
};

// Hasher class template for objects of type T
template <typename T>
class Hasher {
public:
    using HashType = size_t;

    HashType operator()(const T& obj) const {
        auto representation = objectToBytes(obj);
        uint64_t hashValue = hasher_.hash64(reinterpret_cast<const char*>(representation.data()), sizeof(T));
        return convertToSizeT(hashValue);
    }

private:
    HighwayHasher hasher_;
};

#endif // HIGHWAY_HASH_LIBRARY_H
