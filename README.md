# LinkedHashSet

## Overview
The `LinkedHashSet` is a custom C++ container that combines features of both a hash set and a linked list. It ensures unique element storage, constant time complexity for search, insertion, and deletion operations (on average), while also preserving the insertion order of the elements.

This data structure is similar to an STL container, offering iterators, modifiers, lookup, and capacity functions. It is implemented using a combination of hash tables for fast lookup and an ordered linked list to maintain element order.

## Features
- **Unique element storage**: Ensures that each key is stored only once.
- **Ordered elements**: Maintains the insertion order of the elements.
- **Fast access**: Provides constant average time complexity for insertion, deletion, and lookup operations.
- **Iterator support**: Supports forward and reverse iteration through the elements while maintaining order.
- **Resizable**: Allows dynamic resizing of the underlying hash table.

## Key Components
- **Key Type**: Defined by `Key`, the type of the elements stored in the set.
- **Hasher**: Customizable hash function, defaulting to `std::hash<Key>`.
- **Key Equal**: Customizable equality comparator, defaulting to `std::equal_to<Key>`.
- **Allocator**: Customizable memory allocator, defaulting to `std::allocator<Key>`.

## Public API

### Constructors and Destructors
- **LinkedHashSet()**: Default constructor.
- **explicit LinkedHashSet(size_type bucket_count)**: Constructs a `LinkedHashSet` with a specific bucket count.
- **LinkedHashSet(InputIt first, InputIt last)**: Constructs a set with elements from an input range.
- **LinkedHashSet(const LinkedHashSet& other)**: Copy constructor.
- **LinkedHashSet(LinkedHashSet&& other)**: Move constructor.
- **LinkedHashSet(std::initializer_list<key_type> list)**: Constructs a set from an initializer list.
- **~LinkedHashSet()**: Destructor.

### Assignment Operators
- **LinkedHashSet& operator=(const LinkedHashSet& other)**: Copy assignment operator.
- **LinkedHashSet& operator=(LinkedHashSet&& other)**: Move assignment operator.

### Capacity Functions
- **bool empty() const**: Returns whether the set is empty.
- **size_type size() const**: Returns the number of elements in the set.

### Lookup Functions
- **bool contains(const key_type& value) const**: Checks if the set contains a value.
- **size_type count(const key_type& value) const**: Returns the number of occurrences of a value.
- **iterator find(const key_type& value)**: Finds an element and returns an iterator to it.
- **const_iterator find(const key_type& value) const**: Finds an element and returns a const iterator to it.

### Modifiers
- **std::pair<iterator, bool> insert(key_type value)**: Inserts a value into the set.
- **void insert(InputIt first, InputIt last)**: Inserts a range of elements.
- **std::pair<iterator, bool> emplace(Args&&... args)**: Emplaces an element in the set.
- **void clear()**: Clears the set.
- **iterator erase(iterator it)**: Erases an element by iterator.
- **void swap(LinkedHashSet& other)**: Swaps contents with another set.
- **void merge(LinkedHashSet& other)**: Merges another set into this one.

### Set Operations
- **bool subSet(const LinkedHashSet& other) const**: Checks if the current set is a subset of another.
- **LinkedHashSet clone() const**: Returns a deep copy of the current set.

### Hash Table Management
- **float load_factor() const**: Returns the current load factor of the hash table.
- **float max_load_factor() const**: Returns the maximum load factor of the hash table.
- **void rehash(size_type new_size)**: Resizes the hash table.
- **void reserve(size_type new_size)**: Reserves capacity in the hash table.

### Iterators
- **iterator begin() const**: Returns an iterator to the beginning.
- **iterator end() const**: Returns an iterator to the end.
- **const_iterator cbegin() const**: Returns a const iterator to the beginning.
- **const_iterator cend() const**: Returns a const iterator to the end.

### Getters
- **KeyEqual key_eq() const**: Returns the equality function used by the set.
- **Allocator get_allocator() const**: Returns the allocator used by the set.
- **Hash hash_function() const**: Returns the hash function used by the set.

## Internal Details
The `LinkedHashSet` stores its elements in an internal hash table for fast lookups, while also maintaining an ordered doubly linked list to track insertion order. The `OrderedList` class manages the linked list, and each node in the list contains a key and pointers to the next and previous nodes.

### Helper Functions
- **bool is_prime(int num)**: Checks if a number is prime.
- **size_type next_prime(int num)**: Returns the next prime number greater than a given value.

## Usage Example

```cpp
LinkedHashSet<int> set;
set.insert(1);
set.insert(2);
set.insert(3);

for (auto it = set.begin(); it != set.end(); ++it) {
    std::cout << *it << " ";  // Output: 1 2 3
}

if (set.contains(2)) {
    std::cout << "Set contains 2";
}

set.erase(set.find(2));
