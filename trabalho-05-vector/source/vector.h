#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>        // std::copy, std::equal, std::fill
#include <cassert>          // assert()
#include <cstddef>          // std::size_t
#include <exception>        // std::out_of_range
#include <initializer_list> // std::initializer_list
#include <iostream>         // std::cout, std::endl
#include <iterator> // std::advance, std::begin(), std::end(), std::ostream_iterator
#include <limits> // std::numeric_limits<T>
#include <memory> // std::unique_ptr

/// Sequence container namespace.
namespace sc {

/// Implements tha infrastrcture to support a bidirectional iterator.
template <class T> class MyForwardIterator {
public:
  using iterator = MyForwardIterator; //!< Alias to iterator.
  // Below we have the iterator_traits common interface
  using difference_type = std::ptrdiff_t; //!< Difference type to calculated
                                          //!< distance between iterators.
  using value_type = T;              //!< Value type the iterator points to.
  using pointer = T *;               //!< Pointer to the value type.
  using reference = T &;             //!< Reference to the value type.
  using const_reference = const T &; //!< Reference to the value type.
  using iterator_category =
      std::bidirectional_iterator_tag; //!< Iterator category.

  /*! Create an iterator around a raw pointer.
   * \param pt raw pointer to the container.
   */
      MyForwardIterator(pointer pt = nullptr) : m_ptr(pt){};
      MyForwardIterator(const iterator& other) {m_ptr = other.m_ptr;}
      ~MyForwardIterator() = default;
      // MyForwardIterator& operator=(const MyForwardIterator& rhs){
      //   m_ptr = rhs.m_ptr;
      //   return *this;
      // }

  /// Access the content the iterator points to.
      reference operator*() const {
        assert(m_ptr != nullptr);
        return *m_ptr;
      }

  /// Overloaded `->` operator.
      pointer operator->() const {
        assert(m_ptr != nullptr);
        return m_ptr;
      }

  /// Assignment operator.
      iterator& operator=(const iterator& other){
        m_ptr = other.m_ptr;
        return *this;
      }

  /// Copy constructor.
      // MyForwardIterator<value_type>& operator=(const MyForwardIterator<value_type>& other){
      //   m_ptr = other.m_ptr;
      //   return *this;
      // }

  /// Pre-increment operator.
      iterator operator++() {
        m_ptr++;
        return *this;
      }

  /// Post-increment operator.
      iterator operator++(int) {
        iterator temp(*this);
        m_ptr++;
        return temp;
      }

  /// Pre-decrement operator.
      iterator operator--() {
        m_ptr--;
        return *this;
      }

  /// Post-decrement operator.
      iterator operator--(int) {
        iterator temp(*this);
        m_ptr--;
        return temp;
      }
  /// Offset-adition operator.
      iterator &operator+=(difference_type offset) {
        while(offset != 0){
          ++(*this);
          --offset;
        }
        return *this;
      }
  /// Offset-difference operator.
      iterator &operator-=(difference_type offset) {
        while(offset != 0){
          --(*this);
          --offset;
        }
        return *this;
      }

  /// LESS THAN operator.
      friend bool operator<(const iterator &ita, const iterator &itb) {
        return ita.m_ptr < itb.m_ptr;
      }

  /// GREATER THAN operator.
      friend bool operator>(const iterator &ita, const iterator &itb) {
        return ita.m_ptr > itb.m_ptr;
      }
  /// GREATER THAN OR EQUAL TO operator.
      friend bool operator>=(const iterator &ita, const iterator &itb) {
        return ita.m_ptr >= itb.m_ptr;
      }
  /// LESS THAN OR EQUAL TO operator.
      friend bool operator<=(const iterator &ita, const iterator &itb) {
        return ita.m_ptr <= itb.m_ptr;
      }
  /// Addition operator.
      friend iterator operator+(difference_type offset, iterator it) {
        return it + offset;
      }
  /// Addition operator.
      friend iterator operator+(iterator it, difference_type offset) {
        it += offset;
        return it;
      }
  /// Difference operator.
      friend iterator operator-(iterator it, difference_type offset) {
        it -= offset;
        return it;
      }

  /// Equality operator.
      bool operator==(const iterator &rhs) const {
        return rhs.m_ptr == m_ptr;
      }

  /// Not equality operator.
      bool operator!=(const iterator &rhs) const {
        return rhs.m_ptr != m_ptr;;
      }

  /// Returns the difference between two iterators.
      difference_type operator-(const iterator &rhs) const {
        return m_ptr - rhs.m_ptr;
      }

  /// Stream extractor operator.
      friend std::ostream &operator<<(std::ostream &os_,
        const MyForwardIterator &p_) {
        os_ << "[@ " << p_.m_ptr << ": " << *p_.m_ptr << " ]";
        return os_;
      }

    private:
  pointer m_ptr; //!< The raw pointer.
};

/// This class implements the ADT list with dynamic array.
/*!
 * sc::vector is a sequence container that encapsulates dynamic m_end_type arrays.
 *
 * The elements are stored contiguously, which means that elements can
 * be accessed not only through iterators, but also using offsets to
 * regular pointers to elements.
 * This means that a pointer to an element of a vector may be passed to
 * any function that expects a pointer to an element of an array.
 *
 * \tparam T The type of the elements.
 */
template <typename T> class vector {
  //=== Aliases
public:
  using difference_type = std::ptrdiff_t;
  using size_type = unsigned long; //!< The m_end_type type.
  using value_type = T;            //!< The value type.
  using pointer = value_type *; //!< Pointer to a value stored in the container.
  using reference =
      value_type &; //!< Reference to a value stored in the container.
  using const_reference = const value_type &; //!< Const reference to a value
                                              //!< stored in the container.

  using iterator =
      MyForwardIterator<value_type>; //!< The iterator, instantiated from a
                                     //!< template class.
      using const_iterator =
      MyForwardIterator<const value_type>; //!< The const_iterator,
                                           //!< instantiated from a template
                                           //!< class.

  //=== [I] SPECIAL MEMBERS (6 OF THEM)
/**
 * @brief Constructs a vector with a given capacity.
 * 
 * @param cp The initial capacity of the vector.
 */
        explicit vector(size_type cp = 0) {
        m_storage = new T[cp];
        m_capacity = cp;
    m_end = cp; // Array começa vazio.
    for (size_type i{0}; i < m_end; ++i) {
      m_storage[i] = T();
    }
  }

/**
 * @brief Destructor for the vector.
 */
  virtual ~vector() { delete[] m_storage; }

/**
 * @brief Copy constructor.
 * 
 * @param other The vector to copy from.
 */
   vector(const vector &other){
   m_capacity = other.m_capacity;
   m_end = other.m_end;
   m_storage = new T[m_capacity];
   std::copy(other.m_storage, other.m_storage + m_end, m_storage);
 }

/**
 * @brief Constructs a vector with elements from an initializer list.
 * 
 * @param il The initializer list containing elements to initialize the vector.
 */
  vector(const std::initializer_list<T> &il) {
    m_capacity = il.size();
    m_storage = new T[m_capacity];
    m_end = m_capacity; 
    std::copy(il.begin(), il.end(), m_storage);
}



/**
 * @brief Constructs a vector from a range of elements defined by iterators.
 * 
 * @tparam InputIterator Type of the input iterators.
 * @param first Iterator to the beginning of the range.
 * @param last Iterator to the end of the range.
 */
template <typename InputItr> vector(InputItr first, InputItr last){
  difference_type pointersRange = std::distance(first, last);
  m_storage = new value_type[pointersRange];
  std::copy(first, last, m_storage);
  m_end = pointersRange;
  m_capacity = pointersRange;
}

/**
 * @brief Copy assignment operator.
 * 
 * @param rhs The vector to copy from.
 * @return Reference to the modified vector.
 */
vector &operator=(const vector &rhs) {
  if (capacity() < rhs.m_end) {
    reserve(rhs.m_end);
  }
  m_end = rhs.m_end;
  std::copy(rhs.cbegin(), rhs.cend(), begin());
  return *this; 
}


  //=== [II] ITERATORS
iterator begin() { return iterator{&m_storage[0]}; }
iterator end() {return iterator(&m_storage[m_end]); }
const_iterator cbegin() const { return const_iterator(&m_storage[0]); }
const_iterator cend() const { return const_iterator(&m_storage[m_end]); }

  // [III] Capacity
[[nodiscard]] bool full() const { return m_end == m_capacity; }
[[nodiscard]] size_type size() const { return m_end; }
[[nodiscard]] size_type capacity() const { return m_capacity; }
[[nodiscard]] bool empty() const { return m_end == 0; }

  // [IV] Modifiers
void clear(){
  m_end = 0;
}

/**
 * @brief Inserts an element at the beginning of the vector.
 * 
 * @param value The value to be inserted.
 */
void push_front(const_reference value){
  if (full()){ reserve(m_capacity*2); }
  std::move_backward(m_storage, m_storage + m_end, m_storage+1);
  m_storage[0] = value;
  m_end++;
}

/**
 * @brief Inserts an element at the end of the vector.
 * 
 * @param value The value to be inserted.
 */
void push_back(const_reference value){
  if (full()){ reserve(capacity()+1); }
  m_storage[m_end++] = value;
}

/**
 * @brief Removes the last element from the vector.
 * 
 * @throws std::length_error if the vector is empty.
 */
void pop_back(){
  if(empty()){throw std::length_error("POP_BACK(EMPTY)\n");}
  m_storage[m_end-1] = value_type(); 
  m_end--;
}

/**
 * @brief Removes the first element from the vector.
 * 
 * @throws std::length_error if the vector is empty.
 */
void pop_front(){
  if(empty()){throw std::length_error("POP_FRONT(EMPTY)\n");}
  std::copy(m_storage+1, m_storage + m_end, m_storage);
  m_storage[m_end-1] = value_type();
  --m_end;
}

/**
 * @brief Inserts a range of elements into the vector at a specified position.
 * 
 * Inserts elements from the range [first, last) into the vector at the position indicated by pos.
 * 
 * @tparam InputItr Type of the input iterators.
 * @param pos Iterator indicating the position where the elements will be inserted.
 * @param first Iterator to the beginning of the range of elements to insert.
 * @param last Iterator to the end of the range of elements to insert.
 * @return An iterator pointing to the first inserted element, or pos if the range [first, last) is empty.
 */
template<typename InputItr>
iterator insert (iterator pos, InputItr first, InputItr last) {
  const auto pointersRange = std::distance (first, last);
  if (pointersRange == 0) { return pos; }

  const auto pointerToNewElementsAdding = std::distance (begin(), pos);
  //ao que parece, esse calculo é necessário para conseguirmos usar essa pos dnv

  //reescrevendo o m_storage+m_end com os ponteiros dispomniveis arghhh
  if (size() + pointersRange > capacity()){ 
  	reserve (size() + pointersRange); 
  }
  
  pos = begin() + pointerToNewElementsAdding;
  std::copy_backward (pos, end (), end() + pointersRange);
  std::copy (first, last, pos);
  m_end += pointersRange;

  return pos;
}

/**
 * @brief Inserts a range of elements into the vector at a specified position.
 * 
 * Inserts elements from the range [first, last) into the vector at the position indicated by pos.
 * 
 * @tparam InputItr Type of the input iterators.
 * @param pos Iterator indicating the position where the elements will be inserted.
 * @param first Iterator to the beginning of the range of elements to insert.
 * @param last Iterator to the end of the range of elements to insert.
 * @return An iterator pointing to the first inserted element, or pos if the range [first, last) is empty.
 */
template<typename InputItr>
iterator insert(const_iterator pos, InputItr first, InputItr last){
  iterator init{pos};
  return insert(init, first, last);
}

/**
 * @brief Inserts elements from an initializer list into the vector at a specified position.
 * 
 * Inserts elements from the initializer list ilist into the vector at the position indicated by pos.
 * 
 * @param pos Iterator indicating the position where the elements will be inserted.
 * @param ilist Initializer list containing elements to insert.
 * @return An iterator pointing to the first inserted element, or pos if the initializer list is empty.
 */
iterator insert(iterator pos, const std::initializer_list<value_type>&ilist){
  return insert(pos, ilist.begin(), ilist.end());
}

/**
 * @brief Inserts elements from an initializer list into the vector at a specified position.
 * 
 * Inserts elements from the initializer list ilist into the vector at the position indicated by pos.
 * 
 * @param pos Iterator indicating the position where the elements will be inserted.
 * @param ilist Initializer list containing elements to insert.
 * @return An iterator pointing to the first inserted element, or pos if the initializer list is empty.
 */
iterator insert(const_iterator pos, const std::initializer_list<value_type>&ilist){
  return insert(pos, ilist.begin(), ilist.end());
}

/**
 * @brief Inserts a single element into the vector at a specified position.
 * 
 * Inserts the element value into the vector at the position indicated by pos.
 * 
 * @param pos Iterator indicating the position where the element will be inserted.
 * @param value The value to be inserted.
 * @return An iterator pointing to the inserted element.
 */
iterator insert(iterator pos, const_reference value) { return insert(pos, {value}); }

/**
 * @brief Inserts a single element into the vector at a specified position.
 * 
 * Inserts the element value into the vector at the position indicated by pos.
 * 
 * @param pos Iterator indicating the position where the element will be inserted.
 * @param value The value to be inserted.
 * @return An iterator pointing to the inserted element.
 */
iterator insert(const_iterator pos, const_reference value) { return insert(pos, value); }


/**
 * @brief Increases the capacity of the vector to at least new_cap.
 * 
 * If new_cap is greater than the current capacity(), new storage is allocated with at least
 * new_cap size. All elements are copied to the new storage, and the old storage is deallocated.
 * 
 * @param new_cap The new capacity of the vector.
 */
void reserve(size_type new_cap){
  if(new_cap == 0 || new_cap <= m_capacity){return;}
  value_type* new_storage = new value_type[new_cap];

  std::copy(m_storage, m_storage+m_end, new_storage);
  delete[] m_storage;

  m_storage = new_storage;
  m_capacity = new_cap;
}

/**
 * @brief Reduces the capacity of the vector to fit its size.
 * 
 * If the vector is not empty, allocates a new storage with size equal to the current size()
 * and copies all elements to the new storage. Then deallocates the old storage.
 */
void shrink_to_fit(){
  if(empty()){return;}
  value_type* new_storage = new value_type[m_end];
  std::copy(m_storage, m_storage+m_end, new_storage);
  delete[] m_storage;
  m_storage = new_storage;
  m_capacity = m_end;
}

/**
 * @brief Assigns a range of elements to the vector.
 * 
 * Replaces the contents of the vector with the elements from the range [first, last).
 * 
 * @tparam InputItr Type of the input iterators.
 * @param first Iterator to the beginning of the range of elements to assign.
 * @param last Iterator to the end of the range of elements to assign.
 */
template <typename InputItr> 
void assign(InputItr first, InputItr last) {
  size_type newSize = std::distance(first, last);
  if (newSize > capacity()) {reserve(capacity()+newSize);}
  std::copy(first, last, m_storage);
  m_end = m_storage+newSize;
}

/**
 * @brief Assigns a value to the elements of the vector.
 * 
 * Replaces the contents of the vector with count copies of value.
 * 
 * @param count The number of elements to assign.
 * @param value The value to assign to the elements.
 */
void assign(size_type count, const_reference value) {
  if (count > capacity()) {
    reserve(count);
  }
  m_end = std::distance(m_storage, m_storage+count);
  std::fill(begin(), end(), value);
}

/**
 * @brief Assigns elements from an initializer list to the vector.
 * 
 * Replaces the contents of the vector with the elements from the initializer list ilist.
 * 
 * @param ilist Initializer list containing elements to assign.
 */
void assign(const std::initializer_list<T>& ilist) {
  assign(ilist.begin(), ilist.end());
}


/**
 * @brief Removes elements in the range [first, last) from the vector.
 * 
 * Removes the elements in the range [first, last) from the vector and shifts the subsequent elements
 * to the left to fill the gap. Returns an iterator pointing to the position of the first erased element.
 * 
 * @param first Iterator pointing to the beginning of the range to erase.
 * @param last Iterator pointing to the end of the range to erase.
 * @return An iterator pointing to the position of the first erased element.
 * @throws std::out_of_range if the container is empty or if the provided iterators are invalid.
 */
iterator erase(iterator first, iterator last) {
  if (empty()) { throw std::out_of_range("The container is empty."); }
  if (first < begin() || last > end()) { throw std::out_of_range("Invalid iterators provided."); }
  auto pointersRange = std::distance(first, last);
  if (last < end()) { std::copy(last, end(), first); }
  m_end -= pointersRange;
  return first;
}

/**
 * @brief Removes elements in the range [first, last) from the vector.
 * 
 * Removes the elements in the range [first, last) from the vector and shifts the subsequent elements
 * to the left to fill the gap. Returns an iterator pointing to the position of the first erased element.
 * 
 * @param first Iterator pointing to the beginning of the range to erase.
 * @param last Iterator pointing to the end of the range to erase.
 * @return An iterator pointing to the position of the first erased element.
 * @throws std::out_of_range if the container is empty or if the provided iterators are invalid.
 */
iterator erase(const_iterator first, const_iterator last){
  iterator init{first};
  iterator end{last};
  return erase(init, end);
}

/**
 * @brief Removes the element at the specified position from the vector.
 * 
 * Removes the element at the specified position pos from the vector and shifts the subsequent elements
 * to the left to fill the gap. Returns an iterator pointing to the position of the first erased element.
 * 
 * @param pos Iterator pointing to the position of the element to erase.
 * @return An iterator pointing to the position of the first erased element.
 * @throws std::out_of_range if the container is empty or if the provided iterator is invalid.
 */
iterator erase(const_iterator pos){
  iterator init{pos};
  iterator end{pos};
  return erase(init, end);
}

/**
 * @brief Removes the element at the specified position from the vector.
 * 
 * Removes the element at the specified position pos from the vector. Returns an iterator pointing
 * to the position of the first erased element.
 * 
 * @param pos Iterator pointing to the position of the element to erase.
 * @return An iterator pointing to the position of the first erased element.
 * @throws std::out_of_range if the container is empty or if the provided iterator is invalid.
 */
iterator erase(iterator pos){
  return erase(pos, std::next(pos));
}

  // [V] Element access
const_reference back() const {
  if(empty()){ throw std::length_error("there is no element in array");}
  return *(m_storage+m_end-1);
}

const_reference front() const{
  if(empty()){ throw std::length_error("there is no element in array");}
  return *m_storage;
}

reference back(){
  if(empty()){ throw std::length_error("there is no element in array");}
  return *(m_storage+m_end-1);
}

reference front(){
  if(empty()){ throw std::length_error("there is no element in array");}
  return *m_storage;
}

const_reference operator[](size_type idx) const { return m_storage[idx]; }
reference operator[](size_type idx) { return m_storage[idx]; }

/**
 * @brief Accesses the element at the specified position with bounds checking.
 * 
 * Returns a reference to the element at position pos in the vector, performing bounds checking.
 * 
 * @param pos The position of the element to access.
 * @return A reference to the element at the specified position.
 * @throws std::length_error if the vector is empty.
 * @throws std::out_of_range if pos is not within the range of the vector.
 */
const_reference at(size_type pos) const {
  if (empty()) { throw std::length_error("there is no element in array"); }
  else if (pos >= m_end) { throw std::out_of_range("dunno what u looking for...\nu should stop it"); }
  else {
    return m_storage[pos];
  }
}

/**
 * @brief Accesses the element at the specified position with bounds checking.
 * 
 * Returns a reference to the element at position pos in the vector, performing bounds checking.
 * 
 * @param pos The position of the element to access.
 * @return A reference to the element at the specified position.
 * @throws std::length_error if the vector is empty.
 * @throws std::out_of_range if pos is not within the range of the vector.
 */
reference at(size_type pos) {
  if (empty()) { throw std::length_error("there is no element in array"); }
  else if (pos >= m_end) { throw std::out_of_range("dunno what u looking for...\nu should stop it"); }
  else {
    return m_storage[pos];
  }
}

pointer data() { return m_storage; }

const_reference data() const { return m_storage; }

  // [VII] Friend functions.
friend std::ostream &operator<<(std::ostream &os, const vector<T> &vec) {
    // O que eu quero imprimir???
  os << "{ ";
  for (auto i{0U}; i < vec.m_capacity; ++i) {
    if (i == vec.m_end) {
      os << "| ";
    }
    os << vec.m_storage[i] << " ";
  }
  os << "}, m_end=" << vec.m_end << ", m_capacity=" << vec.m_capacity;

  return os;
}

friend void swap(vector<T> &first, vector<T> &second) noexcept {
    // enable ADL
  using std::swap;

    // Swap each member of the class.
  swap(first.m_end, second.m_end);
  swap(first.m_capacity, second.m_capacity);
  swap(first.m_storage, second.m_storage);
}

private:
  size_type m_end;      //!< The list's current size.
  size_type m_capacity; //!< The list's storage capacity.
  T *m_storage;         //!< The list's data storage area.
};

// [VI] Operators ================================= TODO ====================================
template <typename T>
bool operator==(const vector<T> &lhs, const vector<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (typename vector<T>::size_type i = 0; i < lhs.size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}
template <typename T>
bool operator!=(const vector<T> &lhs, const vector<T> &rhs) {
  return !(lhs == rhs);
}

} // namespace sc.

#endif