#include <stack>

// Algorithm to be tested

template <bool reversed> inline bool merge_compare(int a, int b);

template <> inline bool merge_compare<false>(int a, int b) { return a < b; }
template <> inline bool merge_compare<true>(int a, int b) { return a > b; }

template <bool reversed>
void merge_sort_helper(std::stack<int>& st, std::stack<int>& helper1, std::stack<int>& helper2, int size)
{
  // Sort the size 1st elements of st using helper*
  // At the end:
  // - helper* has the same elements as before without any order change
  // - elements of st deeper than size are not modified nor in value nor in order

  if (size <= 1)
  {
    return;
  }
  
  // Split stack into two others
  
  for (int i = 0 ; i != size ; ++i)
  {
    const int current { st.top() };
    st.pop();
  
    if (i & 0x01)
    {
      helper1.push(current);
    }
    else
    {
      helper2.push(current);
    }
  }
  
  const int num_in_1 { size / 2 };
  const int num_in_2 { size - num_in_1 };
  
  merge_sort_helper<!reversed>(helper1, st, helper2, num_in_1);
  merge_sort_helper<!reversed>(helper2, st, helper1, num_in_2);
  
  int taken_from_1 { 0 };
  int taken_from_2 { 0 };
  for (int i = 0 ; i != size ; ++i)
  {
    if (taken_from_1 < num_in_1)
    {
      if (taken_from_2 < num_in_2)
      {
        if (merge_compare<reversed>(helper1.top(), helper2.top()))
        {
          st.push(helper2.top());
          helper2.pop();
          ++taken_from_2;
        }
        else
        {
          st.push(helper1.top());
          helper1.pop();
          ++taken_from_1;
        }
      }
      else
      {
        st.push(helper1.top());
        helper1.pop();
      }
    }
    else
    {
      st.push(helper2.top());
      helper2.pop();
    }
  }
}

void sort_stack(std::stack<int>& st)
{
  std::stack<int> helper1;
  std::stack<int> helper2;
  merge_sort_helper<false>(st, helper1, helper2, st.size());
}

#include "tests.hpp"

