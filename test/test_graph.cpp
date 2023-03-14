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
            Config c;
            c.enable_loop = true;
            c.type = 'n';
            WordGraph g(words, c);
            Assert::AreEqual(g.contain_circle(), true);
        }

        TEST_METHOD(TestCircleWithSameHeadTail1)
        {
            Config c;
            c.type = 'n';
            std::vector<std::string> words = { "aa" };
            WordGraph g(words, c);
            Assert::AreEqual(g.contain_circle(), false);
        }

        TEST_METHOD(TestCircleWithSameHeadTail2)
        {
            Config c;
            c.type = 'n';
            c.enable_loop = true;
            std::vector<std::string> words = { "aa", "aaa" };
            WordGraph g(words, c);
            Assert::AreEqual(g.contain_circle(), true);
        }

        TEST_METHOD(TestCircleWithSameHeadTail3)
        {
            Config c;
            c.type = 'n';
            c.enable_loop = true;
            std::vector<std::string> words = { "w", "w" };
            WordGraph g(words, c);
            Assert::AreEqual(g.contain_circle(), true);
        }

        TEST_METHOD(TestCircleWithBasicSample)
        {
            Config c;
            c.type = 'n';
            std::vector<std::string> words_1 = { "aa", "ab", "bb" };
            WordGraph g_1(words_1, c);
            Assert::AreEqual(g_1.contain_circle(), false);
        }

        TEST_METHOD(TestCircleWithCaseSensitive)
        {
            Config c;
            c.type = 'n';
            c.enable_loop = true;
            std::vector<std::string> words_1 = { "Aa", "aB", "bA" };
            WordGraph g_1(words_1, c);
            Assert::AreEqual(g_1.contain_circle(), true);
        }
    };
}
