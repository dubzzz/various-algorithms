#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

// Algorithm to be tested

template <class T>
class forward_list
{
  class forward_list_node
  {
    std::unique_ptr<forward_list_node> _next;
    T _value;

  public:
    template <class... Args> forward_list_node(std::unique_ptr<forward_list_node>&& next, Args&&... args) : _next(std::move(next)), _value(std::forward<Args>(args)...) {}
    
    forward_list_node* next() { return _next.get(); }
    T& value() { return _value; }
    std::unique_ptr<forward_list_node> del() { return std::move(_next); }
  };

  std::unique_ptr<forward_list_node> head;

public:
  forward_list() : head() {}
  forward_list(forward_list<T>&& other) : head(std::move(other.head)) {}
  forward_list(forward_list<T> const& other) : head()
  {
    std::vector<T> h;
    std::copy(other.begin(), other.end(), std::back_inserter(h));
    std::for_each(h.rbegin(), h.rend(), [this](T const& item) {this->push_front(std::move(item));});
  }
  forward_list<T>& operator=(forward_list<T>&& other) { head = std::move(other.head); return *this; }
  forward_list<T>& operator=(forward_list<T> const& other)
  {
    if (this == &other) return *this;
    head.reset(nullptr);
    std::vector<T> h;
    std::copy(other.begin(), other.end(), std::back_inserter(h));
    std::for_each(h.rbegin(), h.rend(), [this](T const& item) {this->push_front(std::move(item));});
    return *this;
  }
  void clear()
  {
    while(head) { head = head->del(); }
  }
  ~forward_list()
  {
    clear();
  }
  void push_front(T&& elt)
  {
    head = std::make_unique<forward_list_node>(std::move(head), std::forward<T>(elt));
  }
  void push_front(T const& elt)
  {
    head = std::make_unique<forward_list_node>(std::move(head), elt);
  }
  template <class... Args> void emplace_front(Args&&... elts)
  {
    head = std::make_unique<forward_list_node>(std::move(head), std::forward<Args>(elts)...);
  }
  T& front()
  {
    return head->value();
  }
  T const& front() const
  {
    return head->value();
  }
  forward_list<T>& pop_front()
  {
    head = head->del();
    return *this;
  }
  bool empty() const
  {
    return ! head.get();
  }

  class const_iterator : public std::iterator<std::forward_iterator_tag, T>
  {
    friend forward_list<T>;
    forward_list_node* it;
    explicit const_iterator(forward_list_node* it = nullptr) : it(it) {}
  
  public:
    const_iterator& operator++()
    {
      it = it != nullptr ? it->next() : nullptr;
      return *this;
    }
    const_iterator operator++(int)
    {
      const iterator ret = *this;
      ++(*this);
      return ret;
    }
    bool operator==(const_iterator other) const { return it == other.it; }
    bool operator!=(const_iterator other) const { return !(*this == other); }
    T const& operator*() const { return it->value(); }
  };
  class iterator : public const_iterator
  {
    friend forward_list<T>;
    explicit iterator(forward_list_node* it = nullptr) : const_iterator(it) {}
  public:
    iterator(const_iterator it) : const_iterator(it) {}    
    iterator& operator++() { return static_cast<iterator&>(const_iterator::operator++());}
    iterator operator++(int) { return const_iterator::operator++(0);}
    T& operator*() const { return const_cast<T&>(const_iterator::operator*()); }
  };
  iterator begin() { return iterator(head.get()); }
  iterator end() { return iterator(); }
  const_iterator begin() const { return const_iterator(head.get()); }
  const_iterator end() const { return const_iterator(); }
  const_iterator cbegin() const { return const_iterator(head.get()); }
  const_iterator cend() const { return const_iterator(); }
};

#include "tests.hpp"

