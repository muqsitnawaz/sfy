
#include <gtest/gtest.h>

#include <range/v3/view/filter.hpp>
#include <range/v3/numeric/iota.hpp>

#include <sfy/sfy.hpp>

TEST(FundamentalsTest, ConvertToString)
{
    EXPECT_EQ(sfy::to_string(5), "5");
    EXPECT_EQ(sfy::to_string(0.5), "0.5");
    EXPECT_EQ(sfy::to_string('a'), "a");
    EXPECT_EQ(sfy::to_string(true), "true");
    EXPECT_EQ(sfy::to_string(false), "false");
}

TEST(ContainersTest, VectorToString)
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

TEST(RangesTest, RangeToString)
{
    std::vector<int> vec(10);
    ranges::iota(vec, 0);
    auto even_vec = vec | ranges::views::filter([](const auto i) { return i % 2 == 0; });
    EXPECT_EQ(sfy::to_string(even_vec), "[0, 2, 4, 6, 8]");
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}