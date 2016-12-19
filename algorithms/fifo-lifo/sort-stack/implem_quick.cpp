#include <stack>

// Algorithm to be tested

void quick_sort_helper(std::stack<int>& st, std::stack<int>& helper1, std::stack<int>& helper2, int size)
{
  // Sort the size 1st elements of st using helper*
  // At the end:
  // - helper* has the same elements as before without any order change
  // - elements of st deeper than size are not modified nor in value nor in order
  
  if (size <= 1)
  {
    return;
  }
  --size;
  
  const int pivot { st.top() };
  st.pop();
  
  // Partition the stack given the pivot
  
  int num_less_eq { 0 };
  for (int i = 0 ; i != size ; ++i)
  {
    const int current { st.top() };
    st.pop();
    
    if (current <= pivot)
    {
      helper1.push(current);
      ++num_less_eq;
    }
    else
    {
      helper2.push(current);
    }
  }
  
  // num_sup 1st elements of helper2 are coming from st
  // and are > pivot
    
  const int num_sup { size - num_less_eq };
  for (int i = 0 ; i != num_sup ; ++i)
  {
    st.push(helper2.top());
    helper2.pop();
  }
  quick_sort_helper(st, helper1, helper2, num_sup);
  
  // push pivot
  
  st.push(pivot);
  
  // num_less_eq 1st elements of helper1 are coming from st
  // and are <= pivot
  
  for (int i = 0 ; i != num_less_eq ; ++i)
  {
    st.push(helper1.top());
    helper1.pop();
  }
  quick_sort_helper(st, helper1, helper2, num_less_eq);
}

void sort_stack(std::stack<int>& st)
{
  std::stack<int> helper1;
  std::stack<int> helper2;
  quick_sort_helper(st, helper1, helper2, st.size());
}

#include "tests.hpp"

