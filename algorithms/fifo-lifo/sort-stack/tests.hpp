#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <stack>
#include <vector>

// Sort stack

// Algorithm to be tested
// template <class T> void sort_stack(std::stack<T>& st)

// Tests helpers

template <class T> void test_stack(std::vector<T> const& expected, std::stack<T> &out);
template <class T> std::stack<T> make_stack(std::vector<T> const& elts);

// Running tests

TEST(TEST_NAME, AlreadySorted)
{
  std::stack<int> st = make_stack<int>({3,2,1});
  sort_stack(st);
  test_stack({1,2,3}, st);
}

TEST(TEST_NAME, ReverseSorted)
{
  std::stack<int> st = make_stack<int>({1,2,3});
  sort_stack(st);
  test_stack({1,2,3}, st);
}

TEST(TEST_NAME, EmptyStack)
{
  std::stack<int> st = make_stack<int>({});
  sort_stack(st);
  test_stack({}, st);
}

TEST(TEST_NAME, DifferentElements)
{
  std::stack<int> st = make_stack<int>({10,23,8,93,55,105});
  sort_stack(st);
  test_stack({8,10,23,55,93,105}, st);
}

TEST(TEST_NAME, WithDuplicates)
{
  std::stack<int> st = make_stack<int>({1,1,4,1,2,2,3});
  sort_stack(st);
  test_stack({1,1,1,2,2,3,4}, st);
}

TEST(TEST_NAME, WithNullOrNegative)
{
  std::stack<int> st = make_stack<int>({-10,-100,0,9,-3});
  sort_stack(st);
  test_stack({-100,-10,-3,0,9}, st);
}

RC_GTEST_PROP(TEST_NAME, RandomData, (const std::vector<int>& _data))
{
  std::vector<int> data = _data;
  
  std::stack<int> st = make_stack<int>(data);
  sort_stack(st);
  std::sort(data.begin(), data.end());
  test_stack(data, st);
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

