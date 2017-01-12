#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <string>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, EmptyString)
{
  ASSERT_TRUE(all_unique(""));
}

TEST(TEST_NAME, OneCharacter)
{
  ASSERT_TRUE(all_unique("a"));
}

TEST(TEST_NAME, DistinctCharacters)
{
  ASSERT_TRUE(all_unique("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(TEST_NAME, TwoIdenticalCharacters)
{
  ASSERT_FALSE(all_unique("AabcdefghijklmnopqrstuvAwxyz"));
}

TEST(TEST_NAME, TwoIdenticalCharactersInRow)
{
  ASSERT_FALSE(all_unique("AAabcdefghijklmnopqrstuvwxyz"));
}

RC_GTEST_PROP(TEST_NAME, RandomData, (const std::string& _data))
{
  std::string data = _data;
  std::sort(data.begin(), data.end());
  bool unique = std::unique(data.begin(), data.end()) == data.end();
  RC_ASSERT(all_unique(_data) == unique);
}

RC_GTEST_PROP(TEST_NAME, RandomDataWithDuplicate, (const std::string& _data))
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
