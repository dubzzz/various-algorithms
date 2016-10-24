#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>

#include <memory>
#include <vector>

// Algorithm to be tested

namespace v1
{

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
class forward_list
{
  class forward_list_node
  {
    std::unique_ptr<forward_list_node> _next;
    T _value;

  public:
    template <class... Args> forward_list_node(std::unique_ptr<forward_list_node>&& next, Args&&... args) : _next(std::move(next)), _value(std::forward<Args>(args)...) {}

    T& value() { return _value; }
    std::unique_ptr<forward_list_node> del() { return std::move(_next); }
  };

  std::unique_ptr<forward_list_node> head;

public:
  forward_list() : head() {}
  ~forward_list()
  {
    while(head) { head = head->del(); }
  }
  void push_front(T&& elt)
  {
    head = make_unique<forward_list_node>(std::move(head), std::forward<T>(elt));
  }
  void push_front(T const& elt)
  {
    head = make_unique<forward_list_node>(std::move(head), elt);
  }
  template <class... Args> void emplace_front(Args&&... elts)
  {
    head = make_unique<forward_list_node>(std::move(head), std::forward<Args>(elts)...);
  }
  T& front()
  {
    return head->value();
  }
  T const& front() const
  {
    return head->value();
  }
  forward_list<T>& pop_front()
  {
    head = head->del();
    return *this;
  }
  bool empty() const
  {
    return ! head.get();
  }
};

}

using v1::forward_list;
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
  
  bool operator==(CountRefs<counter_id>const& other) { return a == other.a && b == other.b; }
  bool operator!=(CountRefs<counter_id>const& other) { return ! (*this == other); }
  
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


using FwdData = CountRefs<100>;
using RefData = CountRefs<101>;
struct forward_list_model
{
  std::vector<RefData> content;
};
using forward_list_command = rc::state::Command<forward_list_model, forward_list<FwdData>>;

struct cPushFront : forward_list_command
{
  int v1 = *rc::gen::inRange(0, 5);
  int v2 = *rc::gen::inRange(0, 5);
  void checkPreconditions(forward_list_model const& m) const override { RC_PRE(m.content.size() < 1e5); }
  void apply(forward_list_model& m) const override
  {
    RefData elt(v1, v2);
    m.content.push_back(elt);
  }
  void run(forward_list_model const& m, forward_list<FwdData>& l) const override
  {
    std::size_t num_before = FwdData::instances();
    FwdData elt(v1, v2);
    l.push_front(elt);
    RC_ASSERT(! l.empty());
    RC_ASSERT(num_before +2 == FwdData::instances());
  }
  void show(std::ostream &os) const override { os << "::push_front(Data(" << v1 << ", " << v2 << "))"; }
};
struct cEmplaceFront : forward_list_command
{
  int v1 = *rc::gen::inRange(0, 5);
  int v2 = *rc::gen::inRange(0, 5);
  void checkPreconditions(forward_list_model const& m) const override { RC_PRE(m.content.size() < 1e5); }
  void apply(forward_list_model& m) const override { m.content.emplace_back(v1, v2); }
  void run(forward_list_model const& m, forward_list<FwdData>& l) const override
  {
    std::size_t num_before = FwdData::instances();
    l.emplace_front(v1, v2);
    RC_ASSERT(! l.empty());
    RC_ASSERT(num_before +1 == FwdData::instances());
  }
  void show(std::ostream &os) const override { os << "::emplace_front(" << v1 << ", " << v2 << ")"; }
};
struct cFront : forward_list_command
{
  void checkPreconditions(forward_list_model const& m) const override { RC_PRE(! m.content.empty()); }
  void apply(forward_list_model& m) const override {}
  void run(forward_list_model const& m, forward_list<FwdData>& l) const override
  {
    RC_ASSERT(m.content.back().a == l.front().a);
    RC_ASSERT(m.content.back().b == l.front().b);
  }
  void show(std::ostream &os) const override { os << "::front"; }
};
struct cPopFront : forward_list_command
{
  void checkPreconditions(forward_list_model const& m) const override { RC_PRE(! m.content.empty()); }
  void apply(forward_list_model& m) const override { m.content.pop_back(); }
  void run(forward_list_model const& m, forward_list<FwdData>& l) const override
  {
    std::size_t num_before = FwdData::instances();
    l.pop_front();
    RC_ASSERT(num_before -1 == FwdData::instances());
  }
  void show(std::ostream &os) const override { os << "::pop_front"; }
};
struct cEmpty : forward_list_command
{
  void checkPreconditions(forward_list_model const& m) const override {}
  void apply(forward_list_model& m) const override {}
  void run(forward_list_model const& m, forward_list<FwdData>& l) const override
  {
    RC_ASSERT(l.empty() == m.content.empty());
    RC_ASSERT(l.empty() == !FwdData::instances());
  }
  void show(std::ostream &os) const override { os << "::empty"; }
};

RC_GTEST_PROP(ALGO, RandomData, ())
{
  RC_ASSERT(! FwdData::instances());
  {
    forward_list_model m;
    forward_list<FwdData> l;
    rc::state::check(m, l, rc::state::gen::execOneOfWithArgs<cPushFront,cEmplaceFront,cFront,cPopFront,cEmpty>());
  }
  RC_ASSERT(! FwdData::instances());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

