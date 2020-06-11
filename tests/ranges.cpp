
#include <unordered_set>
#include <unordered_map>

#include <gtest/gtest.h>

#include <sfy/sfy.hpp>

TEST(FundamentalsTest, ConvertToString)
{
    EXPECT_EQ(sfy::to_string(5), "5");
    EXPECT_EQ(sfy::to_string(0.5), "0.5");
    EXPECT_EQ(sfy::to_string('a'), "'a'");
    EXPECT_EQ(sfy::to_string(true), "true");
    EXPECT_EQ(sfy::to_string(false), "false");
}

TEST(StringTest, StringToString)
{
    std::string str = "Hello";
    EXPECT_EQ(sfy::to_string(str), R"("Hello")");
    EXPECT_EQ(sfy::to_string(""), R"("")");
    EXPECT_EQ(sfy::to_string("World"), R"("World")");
    char str1[] = "Hello, world!";
    EXPECT_EQ(sfy::to_string(str1), R"("Hello, world!")");
}

TEST(PairTest, PairToString)
{
    std::pair<int, int> pair = {5, 10};
    EXPECT_EQ(sfy::to_string(pair), "(5, 10)");

    std::pair<std::vector<int>, std::vector<char>> pair1;
    pair1.first = {1, 2, 3};
    pair1.second = {'a', 'b', 'c'};
    EXPECT_EQ(sfy::to_string(pair1), "([1, 2, 3], ['a', 'b', 'c'])");

    const std::pair<int, int> cpair = {10, 20};
    EXPECT_EQ(sfy::to_string(cpair), "(10, 20)");
}

TEST(TupleTest, TupleToString)
{
    std::tuple<int, char, std::string> t = {1, 'a', "Hello world"};
    EXPECT_EQ(sfy::to_string(t), R"((1, 'a', "Hello world"))");
}

TEST(RatioTest, RatioToString)
{
    std::ratio<2, 4> ratio1;
    EXPECT_EQ(sfy::to_string(ratio1), "1/2");
}

TEST(ComplexTest, ComplexToString)
{
    std::complex<double> complex1(1.0, 2.0);
    EXPECT_EQ(sfy::to_string(complex1), "1.0 + 2.0i");
}

TEST(ChoroTest, DurationToString)
{
    std::chrono::nanoseconds dur(1);
    EXPECT_EQ(sfy::to_string(dur), "1 nanosecond");

    std::chrono::microseconds dur1(1000);
    EXPECT_EQ(sfy::to_string(dur1), "1000 microseconds");

    std::chrono::milliseconds dur2(500);
    EXPECT_EQ(sfy::to_string(dur2), "500 milliseconds");

    std::chrono::seconds dur3(10);
    EXPECT_EQ(sfy::to_string(dur3), "10 seconds");

    std::chrono::hours dur4(1);
    EXPECT_EQ(sfy::to_string(dur4), "1 hour");

    std::chrono::years dur5(4);
    EXPECT_EQ(sfy::to_string(dur5), "4 years");
}

TEST(ChronoTest, TimePointToString)
{
    std::chrono::system_clock::time_point tp(std::chrono::seconds(1));
    EXPECT_EQ(sfy::to_string(tp), "Wed Dec 31 16:00:01 1969\n");
}

TEST(CArraysTest, CArrayToString)
{
    // Integers.
    int values[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(sfy::to_string(values), "[1, 2, 3, 4, 5]");

    // Pairs.
    std::pair<int, char> pairs[] = {{1, 'a'},
                                    {2, 'b'}};
    EXPECT_EQ(sfy::to_string(pairs), "[(1, 'a'), (2, 'b')]");

    // Tuples.
    std::tuple<int, std::string, char> tuples[] = {{1, "hello", 'h'},
                                                   {2, "world", 'w'}};
    EXPECT_EQ(sfy::to_string(tuples), R"([(1, "hello", 'h'), (2, "world", 'w')])");
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
    EXPECT_EQ(sfy::to_string(vec1), R"([("Hello", "World")])");

    // Tuples.
    std::vector<std::tuple<int, char>> vec2;
    vec2.push_back(std::make_tuple(1, 'a'));
    EXPECT_EQ(sfy::to_string(vec2), "[(1, 'a')]");

    std::vector<std::tuple<char, std::pair<int, char>>> vec3;
    vec3.push_back(std::make_tuple('a', std::make_pair(1, 'a')));
    EXPECT_EQ(sfy::to_string(vec3), "[('a', (1, 'a'))]");
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
    EXPECT_EQ(sfy::to_string(map), "{'a': 10, 'b': 20}");
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
    EXPECT_EQ(sfy::to_string(map), R"({"hello": 10, "world": 20})");

    std::vector<std::unordered_map<std::string, int>> maps;
    maps.push_back(map);
    maps.push_back(map);
    EXPECT_EQ(sfy::to_string(maps), R"([{"world": 20, "hello": 10}, {"world": 20, "hello": 10}])");
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}