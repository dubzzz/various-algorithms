#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <stack>
#include <string>
#include <vector>

// http://www.programcreek.com/2012/12/leetcode-evaluate-reverse-polish-notation/
// Evaluate the value of an arithmetic expression in Reverse Polish Notation. Valid operators are +, -, *, /. Each operand may be an integer or another expression.
// ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
// ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

// Algorithm to be tested


template <class It> int eval(It beg, It end)
{// take a valid expression
  std::stack<int> data;
  for ( ; beg != end ; ++beg)
  {
    std::string const& s = *beg;
    bool is_op = s.size() == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/');
    if (is_op)
    {
      int d2 = data.top();
      data.pop();
      int d1 = data.top();
      data.pop();
      switch (s[0])
      {
        case '+':
          data.push(d1+d2);
          break;
        case '-':
          data.push(d1-d2);
          break;
        case '*':
          data.push(d1*d2);
          break;
        case '/':
          data.push(d1/d2);
          break;
      }
    }
    else
    {
      data.push(std::stoi(s));
    }
  }
  return data.top();
}

#define ALGO ReversePolishNotation_DEFAULT

// Running tests

TEST(ALGO, OnlyOneValue)
{
  std::vector<std::string> vs = { "42" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(ALGO, OnlyPlus)
{
  std::vector<std::string> vs = { "41", "1", "+" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(ALGO, OnlyMinus)
{
  std::vector<std::string> vs = { "43", "1", "-" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(ALGO, OnlyMultiply)
{
  std::vector<std::string> vs = { "21", "2", "*" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(ALGO, OnlyDivide)
{
  std::vector<std::string> vs = { "84", "2", "/" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(ALGO, BasicExample1)
{
  std::vector<std::string> vs = { "2", "1", "+", "3", "*" };
  ASSERT_EQ(9, eval(std::begin(vs), std::end(vs)));
}

TEST(ALGO, BasicExample2)
{
  std::vector<std::string> vs = { "4", "13", "5", "/", "+" };
  ASSERT_EQ(6, eval(std::begin(vs), std::end(vs)));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

