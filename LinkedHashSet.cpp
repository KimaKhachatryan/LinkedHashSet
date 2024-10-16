#include "LinkedHashSet.h"
#include <iostream>

// Constructor/Destructor for LinkedHashSet
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
inline LinkedHashSet<Key, Hash, KeyEqual, Allocator>::LinkedHashSet() 
    : vec(7), 
      allElemCount(0), 
      head(nullptr), 
      tail(nullptr) 
    {
        for (size_t i = 0; i < vec.size(); ++i) {
            vec[i] = new OrderedList();  
        }
    }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
inline LinkedHashSet<Key, Hash, KeyEqual, Allocator>::LinkedHashSet(size_type bucket_count) 
  : vec(next_prime(bucket_count)),
    allElemCount(0),
    head(nullptr), 
    tail(nullptr) 
  {  
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = new OrderedList();  
    }
  }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
template <typename InputIt>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::LinkedHashSet(InputIt first, InputIt last)
    : LinkedHashSet()
    {
      insert(first, last);
    }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::LinkedHashSet(const LinkedHashSet& other)
    : vec(next_prime(other.vec.size())), 
      allElemCount(0), 
      head(nullptr), 
      tail(nullptr) 
    {
      for (size_type i = 0; i < vec.size(); ++i) {
        vec[i] = new OrderedList();
      }

      for (const auto& value : other) {
        insert(value); 
      }
    }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::LinkedHashSet(LinkedHashSet&& other) noexcept
    : vec(std::move(other.vec)), 
      allElemCount(other.allElemCount), 
      head(other.head), 
      tail(other.tail) 
    {
      other.allElemCount = 0;
      other.head = nullptr;
      other.tail = nullptr;
    }

template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::LinkedHashSet(const std::initializer_list<key_type>& list)
    : LinkedHashSet() 
    {
      for (const auto& value : list) {
        insert(value);
      }
    }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::~LinkedHashSet()
{
    clear();
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>& 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::operator=(const LinkedHashSet& other) 
{
    if (this == &other) {
        return *this;
    }

    clear(); 

    vec.resize(next_prime(other.vec.size()));
    for (size_type i = 0; i < vec.size(); ++i) {
        vec[i] = new OrderedList();
    }

    for (const auto& value : other) {
        insert(value);
    }

    allElemCount = other.allElemCount;
    head = other.head;
    tail = other.tail;

    return *this;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>& 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::operator=(LinkedHashSet&& other) noexcept 
{
    if (this == &other) {
        return *this;
    }

    clear();

    vec = std::move(other.vec);
    allElemCount = other.allElemCount;
    head = other.head;
    tail = other.tail;

    other.allElemCount = 0;
    other.head = nullptr;
    other.tail = nullptr;

    return *this;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
bool LinkedHashSet<Key, Hash, KeyEqual, Allocator>::empty() const
{
    return !allElemCount;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::size_type 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::size() const
{
    return allElemCount;
}

// Constructor/Destructor for OrderedList
template<typename Key, 
         typename Hash, 
         typename KeyEqual, 
         typename Allocator> 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::OrderedList()
    : ListHead{nullptr}
    {
    }

template<typename Key, 
         typename Hash, 
         typename KeyEqual, 
         typename Allocator> 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::~OrderedList()
{
    clear();
}


// Constructor/Destructor for OrderedList::Node
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::Node::Node() 
    : value{}, 
      orderPrev(nullptr), 
      next(nullptr), 
      orderNext(nullptr) 
    {
    }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::Node::Node(key_type val)
    : value(val),
      orderPrev(nullptr), 
      next(nullptr), 
      orderNext(nullptr) 
    {
    }

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
template <typename... Args>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::Node::Node(Args &&...args)
    : value(std::forward(args)...)
    {
    }

// Constructor/Destructor for Iterators
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
inline LinkedHashSet<Key, Hash, KeyEqual, Allocator>::constIterator::constIterator()
    : ptr{nullptr}
    {
    }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
inline LinkedHashSet<Key, Hash, KeyEqual, Allocator>::constIterator::constIterator(node_pointer ptr)
    : ptr(ptr)
    {
    }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
inline LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator::Iterator() 
    : constIterator()
    {
    }

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator::Iterator(node_pointer ptr)
    : constIterator(ptr)
    {
    }

//OrederedList functions
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
std::pair<typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::Node*, bool>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::push_back(key_type value)
{
    if (!ListHead) {
        ListHead = new Node(value);
        return {ListHead, true};
    }

    Node* tmp = ListHead;
    while (tmp->next) {
        if (KeyEqual{}(value, tmp->value)) {
            return {tmp, false};
        }
        tmp = tmp->next;
    }
    if (KeyEqual{}(value, tmp->value)) {
            return {tmp, false};
    }
    tmp->next = new Node(value);
    return {tmp->next, true};
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
template <typename... Args>
std::pair<typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::Node*, bool> 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::emplace_back(Args &&...args)
{
    Node* newNode = new Node();
    new (&newNode->value) key_type(std::forward<Args>(args)...); 

    if (!ListHead) {
        ListHead = newNode;
    } else {
        Node* ListTail = ListHead;
        while (ListTail -> next) {
            ListTail = ListTail->next;
        }
        ListTail->next = newNode;
    }
     return {newNode, true};
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::Node*
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::erase(key_type value) {
    if (ListHead == nullptr) {
        return nullptr; 
    }

    if (KeyEqual{}(ListHead->value, value)) {
        Node* removable = ListHead;
        ListHead = ListHead->next;
        if (removable->orderNext) {
            removable->orderNext->orderPrev = removable->orderPrev;
        }
        if (removable->orderPrev) {
            removable->orderPrev->orderNext = removable->orderNext;
        }
        delete removable;
        return ListHead;
    }

    Node* prev = ListHead;
    while (prev->next) {
        if (KeyEqual{}(prev->next->value, value)) {
            Node* removable = prev->next;
            prev->next = prev->next->next;
            if (removable->orderNext) {
                removable->orderNext->orderPrev = removable->orderPrev;
            }
            if (removable->orderPrev) {
               removable->orderPrev->orderNext = removable->orderNext;
            }
            delete removable;
            return prev->orderPrev;
        }
        prev = prev->next;
    }

    return nullptr;
}


template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::Node* 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::find(key_type value)
{
    Node* tmp = ListHead;
    while (tmp) {
        if (KeyEqual{}(tmp->value, value)) {
            return tmp;
        }
        tmp = tmp->next;
    }

    return nullptr;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
void LinkedHashSet<Key, Hash, KeyEqual, Allocator>::OrderedList::clear()
{
    Node* nextTo = nullptr;
    while (ListHead) {
        nextTo = ListHead->next;
        delete ListHead;
        ListHead = nextTo;
    }
    ListHead = nullptr;
}

//iterators
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_reference 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::constIterator::operator*() const
{
    return this->ptr->value;
}

template <typename Key,  
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_pointer 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::constIterator::operator->() const
{
    return &this->ptr->value;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
const typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_iterator&
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::constIterator::operator++()
{
    this->ptr = this->ptr->orderNext;
    return *this;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
const typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_iterator
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::constIterator::operator++(int)
{
    if (!this->ptr) {
        return Iterator();
    };

    Iterator tmp = *this;
    this->ptr = this->ptr->orderNext;
    return tmp;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
const typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_iterator&
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::constIterator::operator--()
{
    this->ptr = this->ptr->orderPrev;
    return *this;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
const typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_iterator
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::constIterator::operator--(int)
{
    Iterator tmp = *this;
    this->ptr = this->ptr->orderPrev;
    return tmp;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::reference 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator::operator*()
{
    return this->ptr->value;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::pointer 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator::operator->()
{
    return &(this->ptr->value);
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::iterator& 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator::operator++()
{
    this->ptr = this->ptr->orderNext;
    return *this;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    this->ptr = this->ptr->orderNext;
    return tmp;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::iterator& 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator::operator--()
{
    this->ptr = this->ptr->orderPrev;
    return *this;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator::operator--(int)
{
    Iterator tmp = *this;
    this->ptr = this->ptr->orderPrev;
    return tmp;
}

//////////////////////////////-MAIN_FUNCTIONALITY-////////////////////////////////


//geters
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
inline KeyEqual LinkedHashSet<Key, Hash, KeyEqual, Allocator>::key_eq() const
{
    return KeyEqual();
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
Allocator LinkedHashSet<Key, Hash, KeyEqual, Allocator>::get_allocator() const
{
    return Allocator();
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
Hash LinkedHashSet<Key, Hash, KeyEqual, Allocator>::hash_function() const
{
    return Hash();
}

//iterator access
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::begin() const
{
    return iterator(head);
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::end() const
{
    return iterator(nullptr);
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::cbegin() const
{
    return const_iterator(head);
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::cend() const
{
    return const_iterator(nullptr);
}

// Modifiers

template <typename Key,
          typename Hash,
          typename KeyEqual,
          typename Allocator>
bool LinkedHashSet<Key, Hash, KeyEqual, Allocator>::subSet(const LinkedHashSet &other) const
{
    for (auto it = other.begin(); it != other.end(); ++it) {
        if (this->find(*it) == this->end()) {
            return false;
        }
    }
    return true;
}

template <typename Key,
          typename Hash,
          typename KeyEqual,
          typename Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::clone() const
{
    LinkedHashSet<Key, Hash, KeyEqual, Allocator> clone;
    for (auto it = this->begin(); it != this->end(); ++it) {
        clone.insert(*it);
    }
    
    return clone;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
std::pair<typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator, bool>
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::insert(key_type value)
{
    size_type currSize = vec.size();
    float load_factor = static_cast<float>(allElemCount + 1) / currSize;

    if (load_factor >= 1.0f) {
        rehash(currSize);
        currSize = vec.size();
    }

    size_type index = hash_function()(value) % currSize;
    auto[ptr, success] = vec[index] -> push_back(value);
    
    if (success)  {    
        if (!allElemCount) {
            head = tail = ptr;
        } else {
            tail->orderNext = ptr;
            ptr->orderPrev = tail;
            tail = ptr;
        } 
        ++allElemCount;
    }

    return {Iterator(ptr), success};
}

template <typename Key,
          typename Hash,
          typename KeyEqual,
          typename Allocator>
template <typename InputIt>
void LinkedHashSet<Key, Hash, KeyEqual, Allocator>::insert(InputIt first, InputIt last)
{
    while (first != last) {
        insert(*first);
        ++first;
    }
}

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
template <typename... Args>
std::pair<typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::Iterator, bool> 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::emplace(Args &&...args)
{
    key_type value(std::forward<Args>(args)...);
    auto it = this->find(value);
    if (it != this->end()) {
        return {it, false};
    }

    size_type currSize = vec.size();
    float load_factor = static_cast<float>(allElemCount + 1) / currSize;

    if (load_factor >= 1.0f) {
        rehash(currSize);
        currSize = vec.size();
    }

    size_type index = hash_function()(value) % currSize;
    auto [ptr, inserted] = vec[index]->emplace_back(std::forward<Args>(args)...);
    ++allElemCount;
   
    if (!allElemCount) {
        head = tail = ptr;
    } else {
        tail->orderNext = ptr;
        ptr->orderPrev = tail;
        tail = ptr;
    }

    return {iterator(ptr), true};
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
void LinkedHashSet<Key, Hash, KeyEqual, Allocator>::clear()
{
    for (auto& bucket : vec) {
        delete bucket;
    }

    vec.clear();
    allElemCount = 0;
    head = nullptr;
    tail = nullptr;
}

template <typename Key,
          typename Hash,
          typename KeyEqual,
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::erase(iterator it)
{
    if (it == end()) {
        return end();
    }

    size_type index = hash_function()(*it) % vec.size();

    if(!vec[index]) {
        return end();                     
    }

    if (KeyEqual{}(*it, head->value)) {
        head = head->orderNext;
            if (!head) {
                tail = nullptr;
            } else {
                head->orderPrev = nullptr; 
            }
    } else if (KeyEqual{}(*it, tail->value)) {
        tail = tail->orderPrev;
        tail -> orderNext = nullptr;
    }

    auto prevNode = vec[index]->erase(*it);

    if (!prevNode) {
        return end();
    }

    --allElemCount;
    return iterator(prevNode);
}

template <typename Key,
          typename Hash,
          typename KeyEqual,
          typename Allocator>
void LinkedHashSet<Key, Hash, KeyEqual, Allocator>::swap(LinkedHashSet &other)
{
    std::swap(other, *this);
}

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
void LinkedHashSet<Key, Hash, KeyEqual, Allocator>::merge(LinkedHashSet &other)
{
    this->insert(other.begin(), other.end());
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
float LinkedHashSet<Key, Hash, KeyEqual, Allocator>::load_factor() const
{
    return static_cast<float>(allElemCount) / vec.size();
}

// Lookup functions
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
bool LinkedHashSet<Key, Hash, KeyEqual, Allocator>::contains(const key_type &value) const
{
    auto it = this->find(value);

    return it != this->end() ? true : false;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::size_type 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::count(const key_type &value) const
{
    auto it = find(value);
    
    return it != end() ? 1 : 0;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::const_iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::find(const key_type &value) const
{
    size_type index = hash_function()(value) % vec.size();

    if (!vec[index]) {
        return this->cend();
    }

    return const_iterator(vec[index]->find(value));
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::iterator 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::find(const key_type &value)
{
    size_type index = hash_function()(value) % vec.size();
    
    if (!vec[index]) {
        return this->end();
    }

    return iterator(vec[index]->find(value));
}

// Hash table management
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
inline float LinkedHashSet<Key, Hash, KeyEqual, Allocator>::max_load_factor() const
{
    return 1.0f;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
void LinkedHashSet<Key, Hash, KeyEqual, Allocator>::rehash(size_type new_size)
{
    if (!is_prime(new_size)) {
        new_size = next_prime(vec.size());
    }

    std::vector<OrderedList*> tmp(new_size);
    for (int i = 0; i < new_size; ++i) {
        tmp[i] = new OrderedList();
    }

    for (auto it = this->begin(); it != this->end(); ++it) {
        size_type index = hash_function()(*it) % vec.size();
        tmp[index]->push_back(*it);
    }

    vec = std::move(tmp);
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
void LinkedHashSet<Key, Hash, KeyEqual, Allocator>::reserve(size_type new_size)
{
    if (new_size < vec.size()) {
        return;
    }

    new_size = next_prime(new_size);

    rehash(new_size);
}

//////////////////-HELPERS-/////////////////////

// Helper functions to get next prime number for rehashing
template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
bool LinkedHashSet<Key, Hash, KeyEqual, Allocator>::is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

template <typename Key, 
          typename Hash, 
          typename KeyEqual, 
          typename Allocator>
typename LinkedHashSet<Key, Hash, KeyEqual, Allocator>::size_type 
LinkedHashSet<Key, Hash, KeyEqual, Allocator>::next_prime(int num) {
    if (num <= 1) return 2;
    int next = num + 1;
    while (!is_prime(next)) {
        ++next;
    }
    return next;
}
