/*
  The aim of this topic is to write your own implementation of
  std::forward_list<T>
*/

#pragma once
#include <iterator>

// Algorithm to be tested

template <class T> class forward_list
{
public:
  forward_list();
  forward_list(forward_list<T>&& other);
  forward_list(forward_list<T> const& other);
  ~forward_list();
  
  forward_list<T>& operator=(forward_list<T>&& other);
  forward_list<T>& operator=(forward_list<T> const& other);
  
  void push_front(T&& elt);
  void push_front(T const& elt);
  template <class... Args> void emplace_front(Args&&... elts);
  forward_list<T>& pop_front();
  void clear();
  
  T& front();
  T const& front() const;
  bool empty() const;
  
  class const_iterator : public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const_iterator) const;
    bool operator!=(const_iterator) const;
    T const& operator*() const;
  };
  class iterator : public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    iterator& operator++();
    iterator operator++(int);
    bool operator==(iterator) const;
    bool operator!=(iterator) const;
    T& operator*();
  };
  
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};

