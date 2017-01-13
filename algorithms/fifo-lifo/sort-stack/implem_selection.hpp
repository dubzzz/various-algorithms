#include <stack>

// Algorithm to be tested

template <class T>
void sort_stack(std::stack<T>& st)
{
  const int size = st.size();
  for (int i = 0 ; i != size ; ++i)
  {
    // At i-th step, st contains all the elements with the i-th last elements correctly ordered for final ascending
    
    std::stack<T> helper;
    T maxi = st.top();
    st.pop();
    
    // Find the max of the unsorted part
    for (int j = i+1 ; j < size ; ++j)
    {
      if (maxi < st.top())
      {
        helper.push(maxi);
        maxi = st.top();
      }
      else
      {
        helper.push(st.top());
      }
      st.pop();
    }
    st.push(maxi);
    while (! helper.empty())
    {
      st.push(helper.top());
      helper.pop();
    }
  }
}

