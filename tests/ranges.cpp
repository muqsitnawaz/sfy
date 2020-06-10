
#include <unordered_set>
#include <unordered_map>

#include <gtest/gtest.h>

#include <sfy/sfy.hpp>

TEST(FundamentalsTest, ConvertToString)
{
    EXPECT_EQ(sfy::to_string(5), "5");
    EXPECT_EQ(sfy::to_string(0.5), "0.5");
    EXPECT_EQ(sfy::to_string('a'), "a");
    EXPECT_EQ(sfy::to_string(true), "true");
    EXPECT_EQ(sfy::to_string(false), "false");
}

TEST(StringTest, StringToString)
{
    std::string str = "Hello";
    EXPECT_EQ(sfy::to_string(str), "Hello");

    EXPECT_EQ(sfy::to_string("World"), "World");
}

TEST(SequenceTest, VectorToString)
{
    // Integers.
    std::vector<int> vec = {1, 2, 3};
    EXPECT_EQ(sfy::to_string(vec), "[1, 2, 3]");
    vec.clear();
    EXPECT_EQ(sfy::to_string(vec), "[]");
    vec.push_back(5);
    EXPECT_EQ(sfy::to_string(vec), "[5]");

    // Pairs.
    std::vector<std::pair<std::string, std::string>> vec1(1);
    for (auto& p : vec1)
    {
        p.first = "Hello";
        p.second = "World";
    }
    EXPECT_EQ(sfy::to_string(vec1), "[(Hello, World)]");

    // Fundamental Tuples.
    std::vector<std::tuple<int, char>> vec2;
    vec2.push_back(std::make_tuple(1, 'a'));
    EXPECT_EQ(sfy::to_string(vec2), "[(1, a)]");

    // Tuple of pairs.
    std::vector<std::tuple<char, std::pair<int, char>>> vec3;
    vec3.push_back(std::make_tuple('a', std::make_pair(1, 'a')));
    EXPECT_EQ(sfy::to_string(vec3), "[(a, (1, a))]");
}

TEST(OrderedTest, SetToString)
{
    std::set<int> set = {10, 20, 30, 40, 50};
    EXPECT_EQ(sfy::to_string(set), "[10, 20, 30, 40, 50]");
}

TEST(OrderedTest, MapToString)
{
    std::map<char, int> map = {
            {'a', 10},
            {'b', 20}
    };
    EXPECT_EQ(sfy::to_string(map), "{a: 10, b: 20}");
}

TEST(UnorderedTest, UnorderedSetToString)
{
    std::unordered_set<int> set = {10, 20, 30, 40, 50};
    EXPECT_EQ(sfy::to_string(set), "[10, 20, 30, 40, 50]");
}

TEST(UnorderedTest, UnorderedMapToString)
{
    std::unordered_map<std::string, int> map = {
            {"hello", 10},
            {"world", 20}
    };
    EXPECT_EQ(sfy::to_string(map), "{hello: 10, world: 20}");

    std::vector<std::unordered_map<std::string, int>> maps;
    maps.push_back(map);
    maps.push_back(map);
    EXPECT_EQ(sfy::to_string(maps), "[{world: 20, hello: 10}, {world: 20, hello: 10}]");
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}