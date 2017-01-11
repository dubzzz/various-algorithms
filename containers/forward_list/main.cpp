#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

#include SPECIFIC_HEADER

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
  
  CountRefs<counter_id>& operator=(CountRefs<counter_id>&& other) { a = other.a; b = other.b; return *this; }
  CountRefs<counter_id>& operator=(CountRefs<counter_id> const& other) { a = other.a; b = other.b; return *this; }
  
  bool operator==(CountRefs<counter_id>const& other) { return a == other.a && b == other.b; }
  bool operator!=(CountRefs<counter_id>const& other) { return ! (*this == other); }
  
  ~CountRefs() { --refs(); }

  static std::size_t instances() { return refs(); }
};

TEST(TEST_NAME, DefaultConstructor)
{
  forward_list<int> l;
  ASSERT_TRUE(l.empty());
}

TEST(TEST_NAME, NotEmptyAfterFirstPush)
{
  forward_list<int> l;
  l.push_front(0);
  ASSERT_FALSE(l.empty());
}

TEST(TEST_NAME, NotEmptyAfterFirstEmplace)
{
  forward_list<int> l;
  l.emplace_front(0);
  ASSERT_FALSE(l.empty());
}

TEST(TEST_NAME, EmptyAfterHavingPoppedEverything)
{
  forward_list<int> l;
  l.push_front(0);
  l.pop_front();
  ASSERT_TRUE(l.empty());
}

TEST(TEST_NAME, PushMultipleElements)
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

TEST(TEST_NAME, EmplaceMultipleElements)
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

TEST(TEST_NAME, PopExpectedElements)
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

TEST(TEST_NAME, EmptyAfterClear)
{
  forward_list<int> l;
  l.push_front(0);
  l.clear();
  ASSERT_TRUE(l.empty());
}

TEST(TEST_NAME, RightNumberOfInstances)
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

TEST(TEST_NAME, DestructorRunsDestructors)
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

TEST(TEST_NAME, CopyEmptyListUsingIterators)
{
  forward_list<int> l;

  std::vector<int> const expected = {};
  std::vector<int> out;
  std::copy(l.begin(), l.end(), std::back_inserter(out));
  ASSERT_EQ(expected, out);
}

TEST(TEST_NAME, CopyUsingIterators)
{
  forward_list<int> l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);

  std::vector<int> const expected = { 3, 2, 1 };
  std::vector<int> out;
  std::copy(l.begin(), l.end(), std::back_inserter(out));
  ASSERT_EQ(expected, out);
}

TEST(TEST_NAME, TransformUsingIterators)
{
  forward_list<int> l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);

  std::vector<int> const expected = { 6, 4, 2 };
  std::vector<int> out;
  std::transform(l.begin(), l.end(), l.begin(), [](int i){return 2*i;});
  std::copy(l.begin(), l.end(), std::back_inserter(out));
  ASSERT_EQ(expected, out);
}

TEST(TEST_NAME, TransformUsingIteratorsLeakFree)
{
  typedef CountRefs<2> Counter;
  ASSERT_EQ(0, Counter::instances());
  {
    forward_list<int> l;
    l.push_front(1);
    l.push_front(2);
    l.push_front(3);

    std::vector<int> out;
    std::transform(l.begin(), l.end(), l.begin(), [](int i){return 2*i;});
    std::copy(l.begin(), l.end(), std::back_inserter(out));
  }
  ASSERT_EQ(0, Counter::instances());
}

TEST(TEST_NAME, CopyUsingConstIterators)
{
  forward_list<int> l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);

  std::vector<int> const expected = { 3, 2, 1 };
  std::vector<int> out;
  std::copy(l.cbegin(), l.cend(), std::back_inserter(out));
  ASSERT_EQ(expected, out);
}

TEST(TEST_NAME, CopyForwardListConstructor)
{
  forward_list<int> l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);

  forward_list<int> l2(l);

  std::vector<int> const expected = { 3, 2, 1 };
  std::vector<int> out_l;
  std::copy(l.cbegin(), l.cend(), std::back_inserter(out_l));
  ASSERT_EQ(expected, out_l);
  
  std::vector<int> out_l2;
  std::copy(l2.cbegin(), l2.cend(), std::back_inserter(out_l2));
  ASSERT_EQ(expected, out_l2);
}

TEST(TEST_NAME, CopyMoveForwardListConstructor)
{
  forward_list<int> l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);

  forward_list<int> l2(std::move(l));

  std::vector<int> const expected = { 3, 2, 1 };
  std::vector<int> out_l2;
  std::copy(l2.cbegin(), l2.cend(), std::back_inserter(out_l2));
  ASSERT_EQ(expected, out_l2);
}

TEST(TEST_NAME, CopyForwardListOperator)
{
  forward_list<int> l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);

  forward_list<int> l2;
  l2.push_front(5);

  l2 = l;

  std::vector<int> const expected = { 3, 2, 1 };
  std::vector<int> out_l;
  std::copy(l.cbegin(), l.cend(), std::back_inserter(out_l));
  ASSERT_EQ(expected, out_l);
  
  std::vector<int> out_l2;
  std::copy(l2.cbegin(), l2.cend(), std::back_inserter(out_l2));
  ASSERT_EQ(expected, out_l2);
}

TEST(TEST_NAME, CopyMoveForwardListOperator)
{
  forward_list<int> l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);

  forward_list<int> l2;
  l2.push_front(5);
  
  l2 = std::move(l);

  std::vector<int> const expected = { 3, 2, 1 };
  std::vector<int> out_l2;
  std::copy(l2.cbegin(), l2.cend(), std::back_inserter(out_l2));
  ASSERT_EQ(expected, out_l2);
}

TEST(TEST_NAME, CopyMoveLeakFree)
{
  typedef CountRefs<3> Counter;
  ASSERT_EQ(0, Counter::instances());
  {
    forward_list<int> l;
    l.push_front(1);
    l.push_front(2);
    l.push_front(3);
    
    forward_list<int> l2;
    l2.push_front(5);
    l2.push_front(6);
    l2.push_front(7);

    forward_list<int> l3(l2);
    l2 = std::move(l3);
    l3 = std::move(l2);

    forward_list<int>& ref_l2 = l2;
    ref_l2 = std::move(l2);

    forward_list<int> l4(std::move(l));
    l = l4;
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

struct cIteratorTransformAll : forward_list_command
{
  void checkPreconditions(forward_list_model const& /*m*/) const override {}
  void apply(forward_list_model& m) const override
  {
    std::transform(m.content.begin(), m.content.end(), m.content.begin(), [](RefData const& data){return RefData(data.b, data.a);});
  }
  void run(forward_list_model const& /*m*/, forward_list<FwdData>& l) const override
  {
    std::size_t num_before = FwdData::instances();
    std::transform(l.begin(), l.end(), l.begin(), [](FwdData const& data){return FwdData(data.b, data.a);});
    RC_ASSERT(num_before == FwdData::instances());
  }
  void show(std::ostream &os) const override { os << "::iterator<TransformAll>"; }
};
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
  void run(forward_list_model const& /*m*/, forward_list<FwdData>& l) const override
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
  void run(forward_list_model const& /*m*/, forward_list<FwdData>& l) const override
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
  void apply(forward_list_model& /*m*/) const override {}
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
  void run(forward_list_model const& /*m*/, forward_list<FwdData>& l) const override
  {
    std::size_t num_before = FwdData::instances();
    l.pop_front();
    RC_ASSERT(num_before -1 == FwdData::instances());
  }
  void show(std::ostream &os) const override { os << "::pop_front"; }
};
struct cEmpty : forward_list_command
{
  void checkPreconditions(forward_list_model const& /*m*/) const override {}
  void apply(forward_list_model& /*m*/) const override {}
  void run(forward_list_model const& m, forward_list<FwdData>& l) const override
  {
    RC_ASSERT(l.empty() == m.content.empty());
    RC_ASSERT(l.empty() == !FwdData::instances());
  }
  void show(std::ostream &os) const override { os << "::empty"; }
};
struct cClear : forward_list_command
{
  void checkPreconditions(forward_list_model const& /*m*/) const override {}
  void apply(forward_list_model& m) const override { m.content.clear(); }
  void run(forward_list_model const& /*m*/, forward_list<FwdData>& l) const override
  {
    l.clear();
    RC_ASSERT(l.empty());
    RC_ASSERT(! FwdData::instances());
  }
  void show(std::ostream &os) const override { os << "::clear"; }
};

RC_GTEST_PROP(TEST_NAME, RandomData, ())
{
  RC_ASSERT(! FwdData::instances());
  {
    forward_list_model m;
    forward_list<FwdData> l;
    rc::state::check(m, l, rc::state::gen::execOneOfWithArgs<cIteratorTransformAll,cPushFront,cEmplaceFront,cFront,cPopFront,cEmpty,cClear>());
  }
  RC_ASSERT(! FwdData::instances());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

