#include "pch.h"
#include "CppUnitTest.h"
#include "../src/wordgraph.h"
#include "../src/wordgraph.cpp"
#include "sstream"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
    TEST_CLASS(test_graph)
    {
    public:

        TEST_METHOD(TestCircleWithTwoWords)
        {
            std::vector<std::string> words = { "ab", "ba" };
            WordGraph g(words);
            Assert::AreEqual(g.contain_circle(), true);
        }

        TEST_METHOD(TestCircleWithSameHeadTail1)
        {
            std::vector<std::string> words = { "aa" };
            WordGraph g(words);
            Assert::AreEqual(g.contain_circle(), false);
        }

        TEST_METHOD(TestCircleWithSameHeadTail2)
        {
            std::vector<std::string> words = { "aa", "aaa" };
            WordGraph g(words);
            Assert::AreEqual(g.contain_circle(), true);
        }

        TEST_METHOD(TestCircleWithSameHeadTail3)
        {
            std::vector<std::string> words = { "w", "w" };
            WordGraph g(words);
            Assert::AreEqual(g.contain_circle(), true);
        }

        TEST_METHOD(TestCircleWithBasicSample)
        {
            std::vector<std::string> words_1 = { "aa", "ab", "bb" };
            WordGraph g_1(words_1);
            Assert::AreEqual(g_1.contain_circle(), false);
        }

        TEST_METHOD(TestCircleWithCaseSensitive)
        {
            std::vector<std::string> words_1 = { "Aa", "aB", "bA" };
            WordGraph g_1(words_1);
            Assert::AreEqual(g_1.contain_circle(), true);
        }
    };
}
