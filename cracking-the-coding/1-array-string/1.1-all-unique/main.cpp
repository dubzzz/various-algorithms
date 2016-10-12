#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <string>
#include <unordered_set>

// Algorithm to be tested

// With ADDITIONAL DATA STRUCTURE

bool all_unique_struct(std::string const& in)
{
  std::unordered_set<char> helper;
  for (auto c : in)
  {
    if (helper.find(c) != helper.end())
    {
      return false;
    }
    helper.insert(c);
  }
  return true;
}

inline bool all_unique(std::string const& in)
{
  return all_unique_struct(in);
}

// Running tests

TEST(AllUnique, EmptyString)
{
  ASSERT_TRUE(all_unique(""));
}

TEST(AllUnique, OneCharacter)
{
  ASSERT_TRUE(all_unique("a"));
}

TEST(AllUnique, DistinctCharacters)
{
  ASSERT_TRUE(all_unique("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(AllUnique, TwoIdenticalCharacters)
{
  ASSERT_FALSE(all_unique("AabcdefghijklmnopqrstuvAwxyz"));
}

TEST(AllUnique, TwoIdenticalCharactersInRow)
{
  ASSERT_FALSE(all_unique("AAabcdefghijklmnopqrstuvwxyz"));
}

RC_GTEST_PROP(AllUnique, RandomData, (const std::string& _data))
{
  std::string data = _data;
  std::sort(data.begin(), data.end());
  bool unique = std::unique(data.begin(), data.end()) == data.end();
  RC_ASSERT(all_unique(_data) == unique);
}

RC_GTEST_PROP(AllUnique, RandomDataWithDuplicate, (const std::string& _data))
{
  std::string data = _data;
  if (_data.size() == 0)
  {
    const auto random_char = *rc::gen::inRange(0, 256);
    data = std::string(2, static_cast<char>(random_char));
  }
  else
  {
    const auto clone_from = *rc::gen::inRange(std::basic_string<char>::size_type(), _data.size());
    const auto clone_at = *rc::gen::inRange(std::basic_string<char>::size_type(), _data.size()+1);
    char to_clone = _data[clone_from];
    data = clone_at < _data.size() ? (_data.substr(0, clone_at) + to_clone + _data.substr(clone_at)) : (_data + to_clone);
  }
  RC_ASSERT(! all_unique(data));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

