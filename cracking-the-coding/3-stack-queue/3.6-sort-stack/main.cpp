#include "gtest/gtest.h"
#include <stack>
#include <vector>

// Algorithm to be tested

// QUICK SORT

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

void quick_sort_stack(std::stack<int>& st)
{
  std::stack<int> helper1;
  std::stack<int> helper2;
  quick_sort_helper(st, helper1, helper2, st.size());
}

// MERGE SORT

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

void merge_sort_stack(std::stack<int>& st)
{
  std::stack<int> helper1;
  std::stack<int> helper2;
  merge_sort_helper<false>(st, helper1, helper2, st.size());
}

// SELECTION SORT

template <class T>
void selection_sort_stack(std::stack<T>& st)
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

template <class T>
inline void sort_stack(std::stack<T>& st)
{
#ifdef QUICK
  return quick_sort_stack(st);
#elif MERGE
  return merge_sort_stack(st);
#else
  return selection_sort_stack(st);
#endif
}

// Tests helpers

template <class T> void test_stack(std::vector<T> const& expected, std::stack<T> &out);
template <class T> std::stack<T> make_stack(std::vector<T> const& elts);

// Running tests

TEST(Ascending, AlreadySorted)
{
  std::stack<int> st = make_stack<int>({3,2,1});
  sort_stack(st);
  test_stack({1,2,3}, st);
}

TEST(Ascending, ReverseSorted)
{
  std::stack<int> st = make_stack<int>({1,2,3});
  sort_stack(st);
  test_stack({1,2,3}, st);
}

TEST(Ascending, EmptyStack)
{
  std::stack<int> st = make_stack<int>({});
  sort_stack(st);
  test_stack({}, st);
}

TEST(Ascending, DifferentElements)
{
  std::stack<int> st = make_stack<int>({10,23,8,93,55,105});
  sort_stack(st);
  test_stack({8,10,23,55,93,105}, st);
}

TEST(Ascending, WithDuplicates)
{
  std::stack<int> st = make_stack<int>({1,1,4,1,2,2,3});
  sort_stack(st);
  test_stack({1,1,1,2,2,3,4}, st);
}

TEST(Ascending, WithNullOrNegative)
{
  std::stack<int> st = make_stack<int>({-10,-100,0,9,-3});
  sort_stack(st);
  test_stack({-100,-10,-3,0,9}, st);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

// Tests helpers: implementation

template <class T>
void test_stack(std::vector<T> const& expected, std::stack<T> &out)
{
  ASSERT_EQ(expected.size(), out.size());
  for (auto elt : expected)
  {
    ASSERT_EQ(elt, out.top());
    out.pop();
  }
  for (auto it = expected.crbegin() ; it != expected.crend() ; ++it)
  {
    out.push(*it);
  }
}

template <class T>
std::stack<T> make_stack(std::vector<T> const& elts)
{
  std::stack<T> st;
  for (auto elt : elts)
  {
    st.push(elt);
  }
  return st;
}

