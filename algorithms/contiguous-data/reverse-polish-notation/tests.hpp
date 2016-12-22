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
// template <class It> int eval(It beg, It end);

// Running tests

TEST(TEST_NAME, OnlyOneValue)
{
  std::vector<std::string> vs = { "42" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(TEST_NAME, OnlyPlus)
{
  std::vector<std::string> vs = { "41", "1", "+" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(TEST_NAME, OnlyMinus)
{
  std::vector<std::string> vs = { "43", "1", "-" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(TEST_NAME, OnlyMultiply)
{
  std::vector<std::string> vs = { "21", "2", "*" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(TEST_NAME, OnlyDivide)
{
  std::vector<std::string> vs = { "84", "2", "/" };
  ASSERT_EQ(42, eval(std::begin(vs), std::end(vs)));
}

TEST(TEST_NAME, BasicExample1)
{
  std::vector<std::string> vs = { "2", "1", "+", "3", "*" };
  ASSERT_EQ(9, eval(std::begin(vs), std::end(vs)));
}

TEST(TEST_NAME, BasicExample2)
{
  std::vector<std::string> vs = { "4", "13", "5", "/", "+" };
  ASSERT_EQ(6, eval(std::begin(vs), std::end(vs)));
}

class Expression
{
public:
  virtual std::unique_ptr<Expression> clone() const = 0;
  virtual long long eval() const = 0; // evaluate the expression
  virtual std::vector<std::string> polish() const = 0; // construct a polish interpretation of the expression
};

class Number final : public Expression
{
  const short _value;

public:
  explicit Number(short value) : Expression(), _value(value) {}
  Number(Number const&) = default;
  Number(Number&&) = default;
  Number& operator=(Number const&) = delete;
  Number& operator=(Number&&) = delete;
  
  std::unique_ptr<Expression> clone() const override { return std::make_unique<Number>(*this); }
  long long eval() const override { return _value; }
  std::vector<std::string> polish() const override { return std::vector<std::string>{ std::to_string(_value) }; }
};

struct Plus
{
  static constexpr char symbol() { return '+'; }
  static long long eval(long long a, long long b) { return a+b; }
  static bool overflow(long long a, long long b) { return ~((a > 0) ^ (b > 0)) && std::abs(a) > std::numeric_limits<long long>::max() - std::abs(b); }
};
struct Minus
{
  static constexpr char symbol() { return '-'; }
  static long long eval(long long a, long long b) { return a-b; }
  static bool overflow(long long a, long long b) { return Plus::overflow(a, -b); }
};
struct Multiply
{
  static constexpr char symbol() { return '*'; }
  static long long eval(long long a, long long b) { return a*b; }
  static bool overflow(long long a, long long b) { return b != 0L && std::abs(a) > std::numeric_limits<long long>::max() / std::abs(b); }
};
struct Divide
{
  static constexpr char symbol() { return '/'; }
  static long long eval(long long a, long long b) { return b != 0L ? a/b : 0L; }
  static bool overflow(long long /*a*/, long long b) { return b == 0L; }
};

template <class Operation> class BinaryOperation final : public Expression
{
  std::unique_ptr<Expression> _left;
  std::unique_ptr<Expression> _right;

public:
  BinaryOperation(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right) : Expression(), _left(std::move(left)), _right(std::move(right))
  {
    assert(_left);
    assert(_right);
  }
  
  BinaryOperation(BinaryOperation<Operation> const& other) : Expression(), _left(other._left->clone()), _right(other._right->clone()) {}
  BinaryOperation(BinaryOperation<Operation>&&) = default;
  BinaryOperation& operator=(BinaryOperation<Operation> const&) = delete;
  BinaryOperation& operator=(BinaryOperation<Operation>&&) = delete;
  
  std::unique_ptr<Expression> clone() const override { return std::make_unique<BinaryOperation<Operation>>(_left->clone(), _right->clone()); }
  long long eval() const override { return Operation::eval(_left->eval(), _right->eval()); }
  std::vector<std::string> polish() const override
  {
    auto ret = std::vector<std::string>{ _left->polish() };
    auto&& right_ret { _right->polish() };
    std::copy(std::begin(right_ret), std::end(right_ret), std::back_inserter(ret));
    ret.emplace_back(Operation::symbol());
    return ret;
  }
};

RC_GTEST_PROP(TEST_NAME, RandomValidExpression, ())
{
  /*std::string s2 = *rc::gen::apply([s](unsigned seed) {
    std::vector<char> remap(UCHAR_MAX +1);
    std::iota(std::begin(remap), std::end(remap), CHAR_MIN);
    std::mt19937 g(seed);
    std::shuffle(std::begin(remap), std::end(remap), g);
    
    std::string s2;
    std::transform(std::begin(s), std::end(s), std::back_inserter(s2), [&remap](char cur) { return remap[static_cast<int>(cur) - CHAR_MIN]; });
    return s2;
  }, rc::gen::arbitrary<unsigned>()).as("isomorphic transformation of s (s2)");
*/
  RC_ASSERT(true);
}

