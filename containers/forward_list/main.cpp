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

template <int counter_id>
class CountRefs
{
  static std::size_t& refs()
  {
    static std::size_t refs_ = 0;
    return refs_;
  }
public:
  int a, b;
  CountRefs(int a, int b) : a(a), b(b) { ++refs(); }
  
  CountRefs(CountRefs<counter_id>&& other) : a(other.a), b(other.b) { ++refs(); }
  CountRefs(CountRefs<counter_id> const& other) : a(other.a), b(other.b) { ++refs(); }
  
  CountRefs<counter_id>& operator=(CountRefs<counter_id>&& other) { a = other.a; b = other.b; }
  CountRefs<counter_id>& operator=(CountRefs<counter_id> const& other) { a = other.a; b = other.b; }
  
  bool operator==(CountRefs<counter_id> const& other) { return a == other.a && b == other.b; }
  bool operator!=(CountRefs<counter_id> const& other) { return ! (*this == other); }
  
  ~CountRefs() { --refs(); }

  static std::size_t instances() { return refs(); }
};

TEST(ALGO, DefaultConstructor)
{
  forward_list<int> l;
  ASSERT_TRUE(l.empty());
}

TEST(ALGO, NotEmptyAfterFirstPush)
{
  forward_list<int> l;
  l.push_front(0);
  ASSERT_FALSE(l.empty());
}

TEST(ALGO, NotEmptyAfterFirstEmplace)
{
  forward_list<int> l;
  l.emplace_front(0);
  ASSERT_FALSE(l.empty());
}

TEST(ALGO, EmptyAfterHavingPoppedEverything)
{
  forward_list<int> l;
  l.push_front(0);
  l.pop_front();
  ASSERT_TRUE(l.empty());
}

TEST(ALGO, PushMultipleElements)
{
  forward_list<int> l;
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
  forward_list<int> l;
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
  forward_list<int> l;
  l.push_front(65);
  l.push_front(105);
  l.emplace_front(15);
  l.push_front(5);
  l.emplace_front(4);
  l.push_front(3);

  const int expected[] = {3,4,5,15,105,65};

  std::size_t s {};
  while (! l.empty())
  {
    ASSERT_EQ(expected[s], l.front());
    l.pop_front();
    ++s;
  }
  ASSERT_EQ(6, s);
}

TEST(ALGO, RightNumberOfInstances)
{
  typedef CountRefs<0> Counter;
  ASSERT_EQ(0, Counter::instances());
  forward_list<Counter> l;
  l.push_front(Counter(1,0));
  ASSERT_EQ(1, Counter::instances());
  l.emplace_front(2,3);
  ASSERT_EQ(2, Counter::instances());
  {
    CountRefs<0>& f(l.front());
    ASSERT_EQ(2, Counter::instances());
    ASSERT_TRUE(f.a == 2 && f.b == 3);
    f.a += 1;
  }
  {
    CountRefs<0> f(l.front());
    ASSERT_EQ(3, Counter::instances());
    ASSERT_TRUE(f.a == 3 && f.b == 3);
  }
  
  std::size_t s {};
  while (! l.empty())
  {
    l.pop_front();
    ++s;
    ASSERT_EQ(2 - s, Counter::instances());
  }
  ASSERT_EQ(0, Counter::instances());
}

TEST(ALGO, DestructorRunsDestructors)
{
  typedef CountRefs<1> Counter;
  ASSERT_EQ(0, Counter::instances());
  {
    forward_list<Counter> l;
    l.push_front(Counter(1,0));
    l.emplace_front(1,0);
    ASSERT_EQ(2, Counter::instances());
  }
  ASSERT_EQ(0, Counter::instances());
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

