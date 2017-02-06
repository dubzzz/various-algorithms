#include "gtest/gtest.h"

#include <string>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto data = std::vector<std::string>{"a","b","c","d"};
  ASSERT_EQ("a", business_tasks(data, 2));
}
TEST(TEST_NAME, Example1)
{
  auto data = std::vector<std::string>{"a","b","c","d","e"};
  ASSERT_EQ("d", business_tasks(data, 3));
}
TEST(TEST_NAME, Example2)
{
  auto data = std::vector<std::string>{"alpha","beta","gamma","delta","epsilon"};
  ASSERT_EQ("epsilon", business_tasks(data, 1));
}
TEST(TEST_NAME, Example3)
{
  auto data = std::vector<std::string>{"a","b"};
  ASSERT_EQ("a", business_tasks(data, 1000));
}
TEST(TEST_NAME, Example4)
{
  auto data = std::vector<std::string>{"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t",
"u","v","w","x","y","z"};
  ASSERT_EQ("n", business_tasks(data, 17));
}
TEST(TEST_NAME, Example5)
{
  auto data = std::vector<std::string>{"zlqamum","yjsrpybmq","tjllfea","fxjqzznvg","nvhekxr","am","skmazcey","piklp",
"olcqvhg","dnpo","bhcfc","y","h","fj","bjeoaxglt","oafduixsz","kmtbaxu",
"qgcxjbfx","my","mlhy","bt","bo","q"};
  ASSERT_EQ("fxjqzznvg", business_tasks(data, 9000000));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
