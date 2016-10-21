#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>

#include <forward_list>
#include <vector>

using std::forward_list;

// Algorithm to be tested

namespace v1
{

class forward_list
{};

}

using std::forward_list;
#define ALGO FORWARD_LIST

// Running tests

typedef int InnerData;

TEST(ALGO, DefaultConstructor)
{
  forward_list<InnerData> l;
  ASSERT_TRUE(l.empty());
}

TEST(ALGO, NotEmptyAfterFirstPush)
{
  forward_list<InnerData> l;
  l.push_front(0);
  ASSERT_FALSE(l.empty());
}

TEST(ALGO, NotEmptyAfterFirstEmplace)
{
  forward_list<InnerData> l;
  l.emplace_front(0);
  ASSERT_FALSE(l.empty());
}

TEST(ALGO, EmptyAfterHavingPoppedEverything)
{
  forward_list<InnerData> l;
  l.push_front(0);
  l.pop_front();
  ASSERT_TRUE(l.empty());
}

TEST(ALGO, PushMultipleElements)
{
  forward_list<InnerData> l;
  l.push_front(5);
  l.push_front(4);
  l.push_front(3);

  std::size_t s {};
  while (! l.empty())
  {
    l.pop_front();
    ++s;
  }
  ASSERT_EQ(3, s);
}

TEST(ALGO, EmplaceMultipleElements)
{
  forward_list<InnerData> l;
  l.emplace_front(65);
  l.emplace_front(105);
  l.emplace_front(15);
  l.emplace_front(5);
  l.emplace_front(4);
  l.emplace_front(3);

  std::size_t s {};
  while (! l.empty())
  {
    l.pop_front();
    ++s;
  }
  ASSERT_EQ(6, s);
}

TEST(ALGO, PopExpectedElements)
{
  forward_list<InnerData> l;
  l.push_front(65);
  l.push_front(105);
  l.emplace_front(15);
  l.push_front(5);
  l.emplace_front(4);
  l.push_front(3);

  const InnerData expected[] = {3,4,5,15,105,65};

  std::size_t s {};
  while (! l.empty())
  {
    ASSERT_EQ(expected[s], l.front());
    l.pop_front();
    ++s;
  }
  ASSERT_EQ(6, s);
}

struct forward_list_model
{
  std::vector<InnerData> content;
};

using forward_list_command = rc::state::Command<forward_list_model, forward_list<InnerData>>;

struct cPushFront : forward_list_command
{
  int value = *rc::gen::inRange(0, 20);
  void checkPreconditions(forward_list_model const& m) const override { RC_PRE(m.content.size() < 1e5); }
  void apply(forward_list_model& m) const override
  {
    InnerData elt(value);
    m.content.push_back(elt);
  }
  void run(forward_list_model const& m, forward_list<InnerData>& l) const override
  {
    InnerData elt(value);
    l.push_front(elt);
    RC_ASSERT(! l.empty());
  }
  void show(std::ostream &os) const override { os << "::push_front(InnerData(" << value << "))"; }
};
struct cEmplaceFront : forward_list_command
{
  int value = *rc::gen::inRange(0, 20);
  void checkPreconditions(forward_list_model const& m) const override { RC_PRE(m.content.size() < 1e5); }
  void apply(forward_list_model& m) const override { m.content.emplace_back(value); }
  void run(forward_list_model const& m, forward_list<InnerData>& l) const override
  {
    l.emplace_front(value);
    RC_ASSERT(! l.empty());
  }
  void show(std::ostream &os) const override { os << "::emplace_front(" << value << ")"; }
};
struct cFront : forward_list_command
{
  void checkPreconditions(forward_list_model const& m) const override { RC_PRE(! m.content.empty()); }
  void apply(forward_list_model& m) const override {}
  void run(forward_list_model const& m, forward_list<InnerData>& l) const override
  {
    RC_ASSERT(m.content.back() == l.front());
  }
  void show(std::ostream &os) const override { os << "::front"; }
};
struct cPopFront : forward_list_command
{
  void checkPreconditions(forward_list_model const& m) const override { RC_PRE(! m.content.empty()); }
  void apply(forward_list_model& m) const override { m.content.pop_back(); }
  void run(forward_list_model const& m, forward_list<InnerData>& l) const override
  {
    l.pop_front();
  }
  void show(std::ostream &os) const override { os << "::pop_front"; }
};
struct cEmpty : forward_list_command
{
  void checkPreconditions(forward_list_model const& m) const override {}
  void apply(forward_list_model& m) const override {}
  void run(forward_list_model const& m, forward_list<InnerData>& l) const override
  {
    RC_ASSERT(l.empty() == m.content.empty());
  }
  void show(std::ostream &os) const override { os << "::empty"; }
};

RC_GTEST_PROP(ALGO, RandomData, ())
{
  forward_list_model m;
  forward_list<InnerData> l;
  rc::state::check(m, l, rc::state::gen::execOneOfWithArgs<cPushFront,cEmplaceFront,cFront,cPopFront,cEmpty>());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

