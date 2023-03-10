#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core.h"
#include "../src/core.cpp"
#include "../src/solver.cpp"
#include "sstream"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
    TEST_CLASS(test_core)
    {
    private:
        void test_gen_chains_all(const char* words[], int len, const char* ans[], int ans_len) {
            char** result = (char**)malloc(10000);
            int out_len = gen_chains_all(words, len, result);
            Assert::AreEqual(ans_len, out_len);
            for (int i = 0; i < ans_len; i++) {
                if (result != nullptr)
                {
                    Assert::AreEqual(strcmp(ans[i], result[i]), 0);
                }
            }
        }

        void test_gen_chain_word(const char* words[], int len, const char* ans[], int ans_len, char head, char tail, char n_head, bool enable_loop) {
            char** result = (char**)malloc(10000);
            int out_len = gen_chain_word(words, len, result, head, tail, n_head, enable_loop);
            Assert::AreEqual(ans_len, out_len);
            for (int i = 0; i < ans_len; i++) {
                if (result != nullptr) Assert::AreEqual(strcmp(ans[i], result[i]), 0);
            }
        }

        void test_gen_chain_char(const char* words[], int len, const char* ans[], int ans_len, char head, char tail, char n_head, bool enable_loop) {
            char** result = (char**)malloc(10000);
            int out_len = gen_chain_char(words, len, result, head, tail, n_head, enable_loop);
            Assert::AreEqual(ans_len, out_len);
            for (int i = 0; i < ans_len; i++) {
                if (result != nullptr) Assert::AreEqual(strcmp(ans[i], result[i]), 0);
            }
        }

    public:

        // '-n'

        TEST_METHOD(TestCoreGenChainsAll1) {
            const char* words[] = { "aa", "bb", "cc" };
            const char* ans[] = { "0" };
            test_gen_chains_all(words, 3, ans, 1);
        }

        TEST_METHOD(TestCoreGenChainsAll2) {
            const char* words[] = { "aa", "bb", "ab" };
            const char* ans[] = { "3", "aa ab", "aa ab bb", "ab bb" };
            test_gen_chains_all(words, 3, ans, 4);
        }


        /*----------------------*/

        // '-w'
        TEST_METHOD(TestCoreGenChainWord) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "algebra", "apple", "elephant", "trick" };
            test_gen_chain_word(words, 11, ans, 4, 0, 0, 0, false);
        }

        // '-h'
        TEST_METHOD(TestCoreGenChainWordWithH) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "elephant", "trick" };
            test_gen_chain_word(words, 11, ans, 2, 'e', 0, 0, false);
        }

        // '-t'
        TEST_METHOD(TestCoreGenChainWordWithT) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "algebra", "apple", "elephant" };
            test_gen_chain_word(words, 11, ans, 3, 0, 't', 0, false);
        }

        // '-t' ºÍ '-h'
        TEST_METHOD(TestCoreGenChainWordWithHT) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "algebra", "apple", "elephant" };
            test_gen_chain_word(words, 11, ans, 3, 'a', 't', 0, false);
        }

        // '-r'
        TEST_METHOD(TestCoreGenChainWordWithR) {
            const char* words[] = { "element", "heaven", "table", "teach", "talk" };
            const char* ans[] = { "table", "element", "teach", "heaven" };
            test_gen_chain_word(words, 5, ans, 4, 0, 0, 0, true);
        }

        // '-j'
        TEST_METHOD(TestCoreGenChainWordWithJ) {
            const char* words[] = { "element", "heaven", "able", "teach", "talk" };
            const char* ans[] = { "teach", "heaven" };
            test_gen_chain_word(words, 5, ans, 2, 0, 0, 'e', false);
        }

        /*-----------------------------*/

        // '-c'
        TEST_METHOD(TestCoreGenChainChar) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "pseudopseudohypoparathyroidism", "moon" };
            test_gen_chain_char(words, 11, ans, 2, 0, 0, 0, false);
        }

        // '-h'
        TEST_METHOD(TestCoreGenChainCharWithH) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "algebra", "apple", "elephant", "trick" };
            test_gen_chain_char(words, 11, ans, 4, 'a', 0, 0, false);
        }

        // '-t'
        TEST_METHOD(TestCoreGenChainCharWithT) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "algebra", "apple", "elephant", "trick" };
            test_gen_chain_char(words, 11, ans, 4, 0, 'k', 0, false);
        }

        // '-h and -t'
        TEST_METHOD(TestCoreGenChainCharWithHT) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "algebra", "apple", "elephant" };
            test_gen_chain_char(words, 11, ans, 3, 'a', 't', 0, false);
        }

        // '-r'
        TEST_METHOD(TestCoreGenChainCharWithR) {
            const char* words[] = { "element", "heaven", "table", "teach", "talk" };
            const char* ans[] = { "table", "element", "teach", "heaven" };
            test_gen_chain_char(words, 5, ans, 4, 0, 0, 0, true);
        }

        // '-j'
        TEST_METHOD(TestCoreGenChainCharWithJ) {
            const char* words[] = { "element", "heaven", "able", "teach", "talk" };
            const char* ans[] = { "teach", "heaven" };
            test_gen_chain_char(words, 5, ans, 2, 0, 0, 'e', false);
        }
    };
}
