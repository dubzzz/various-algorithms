/*
  The aim of this topic is to write your own implementation of
  std::forward_list<T>
*/

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
  void push_front(T const& elt)
  template <class... Args> void emplace_front(Args&&... elts);
  forward_list<T>& pop_front();
  void clear();
  
  T& front();
  T const& front() const;
  bool empty() const;
  
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};

