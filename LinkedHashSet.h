#ifndef LINKEDHASHMAP_H
#define LINKEDHASHMAP_H

#include <vector>
#include <utility>
#include <functional>

template <typename Key,
          typename Hash = std::hash<Key>, 
          typename KeyEqual = std::equal_to<Key>, 
          typename Allocator = std::allocator<Key>>
class LinkedHashSet {
private:
    struct Node;
    struct OrderedList;
public:
    class Iterator;
    class constIterator;

public:  
    // Typedefs for convenience and STL-like usage
    using key_type = Key;
    using size_type = size_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using reference = key_type&;
    using const_reference = const key_type&;
    using pointer = key_type*;
    using const_pointer = const key_type*;
    using node_pointer = typename OrderedList::Node*;
    using iterator = typename LinkedHashSet::Iterator;
    using const_iterator = typename LinkedHashSet::constIterator;

private:
    // Nested OrderedList struct
    struct OrderedList {
        OrderedList();
        ~OrderedList();

        // Nested Node struct
        struct Node {
            Node();
            Node(key_type value);
            template <typename... Args>
            Node(Args&&... args);

            key_type value;
            Node* orderPrev;
            Node* next;
            Node* orderNext;
        };

        std::pair<Node*, bool> push_back(key_type value);
        template <typename... Args>
        std::pair<Node*, bool> emplace_back(Args&&... args);
        Node* erase(key_type value);
        Node* find(key_type value);
        void clear();

        Node* ListHead;
    };
public:
    // Nested const_iterator class
    class constIterator {
    public:
        // Constructors
        constIterator();
        constIterator(node_pointer);

        // Operators
        const_reference operator*() const;
        const_pointer operator->() const;

        friend bool operator==(const constIterator& lhv, const constIterator& rhv) {
            return lhv.ptr == rhv.ptr;
        }

        friend bool operator!=(const constIterator& lhv, const constIterator& rhv) {
            return lhv.ptr != rhv.ptr;
        }

        const const_iterator& operator++();
        const const_iterator operator++(int);

        const const_iterator& operator--();
        const const_iterator operator--(int);

    protected:
        node_pointer ptr;
    };

    // Nested iterator class, derived from const_iterator
    class Iterator : public constIterator {
    public:
        // Constructors
        Iterator();
        Iterator(node_pointer ptr);

        // Operators
        reference operator*();
        pointer operator->();

        friend bool operator==(const Iterator& lhv, const Iterator& rhv) {
            return lhv.ptr == rhv.ptr;
        }

        friend bool operator!=(const Iterator& lhv, const Iterator& rhv) {
            return lhv.ptr != rhv.ptr;
        }

        iterator& operator++();
        iterator operator++(int);

        iterator& operator--();
        iterator operator--(int);
    };

    // Constructors, destructor, and assignment operators
    LinkedHashSet();
    explicit LinkedHashSet(size_type bucket_count);
    template <typename InputIt>
    LinkedHashSet(InputIt first, InputIt last);
    LinkedHashSet(const LinkedHashSet& other);
    LinkedHashSet(LinkedHashSet&& other) noexcept;
    LinkedHashSet(const std::initializer_list<key_type>& list);
    ~LinkedHashSet();

    LinkedHashSet& operator=(const LinkedHashSet& other);
    LinkedHashSet& operator=(LinkedHashSet&& other) noexcept;

    // Capacity functions
    bool empty() const;
    size_type size() const;

    // Lookup functions
    bool contains(const key_type& value) const;
    size_type count(const key_type& value) const;
    const_iterator find(const key_type& value) const;
    iterator find(const key_type& value);

    // Hash table management
    float load_factor() const;
    float max_load_factor() const;
    void rehash(size_type new_size);
    void reserve(size_type new_size);

    // Set operations
    bool subSet(const LinkedHashSet& other) const;
    LinkedHashSet clone() const;

    // Modifiers
    std::pair<iterator, bool> insert(key_type value);
    template <typename InputIt>
    void insert(InputIt first, InputIt last);

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args);

    void clear();
    iterator erase(iterator it);
    void swap(LinkedHashSet& other);
    void merge(LinkedHashSet& other);


    // Iterators
    iterator begin() const;
    iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    //geters
    KeyEqual key_eq() const;
    Allocator get_allocator() const;
    Hash hash_function() const;

private:
    std::vector<OrderedList*> vec;
    size_type allElemCount;
    node_pointer head;
    node_pointer tail;

    //helpers
    bool is_prime(int num);
    size_type next_prime(int num);
};

#endif // LINKED_HASH_MAP_H


