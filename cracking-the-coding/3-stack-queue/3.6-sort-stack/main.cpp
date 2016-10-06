#include "gtest/gtest.h"
#include <stack>
#include <vector>

// Algorithm to be testes

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
  std::stack<int> st = make_stack<int>({10,23,8,93,55});
  sort_stack(st);
  test_stack({8,10,23,55,93}, st);
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

