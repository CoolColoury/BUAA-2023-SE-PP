#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core.h"
#include "../src/core.cpp"
#include "../src/solver.h"
#include "../src/solver.cpp"
#include "../src/wordgraph.h"
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
            free(result);
        }

        void test_gen_chain_word(const char* words[], int len, const char* ans[], int ans_len, char head, char tail, char n_head, bool enable_loop) {
            char** result = (char**)malloc(10000);
            int out_len = gen_chain_word(words, len, result, head, tail, n_head, enable_loop);
            Assert::IsTrue(check_valid(result, out_len, head, tail, n_head, enable_loop));
            Assert::AreEqual(ans_len, out_len);
            free(result);
        }

        void test_gen_chain_char(const char* words[], int len, const char* ans[], int ans_len, char head, char tail, char n_head, bool enable_loop) {
            char** result = (char**)malloc(10000);
            int out_len = gen_chain_char(words, len, result, head, tail, n_head, enable_loop);
            Assert::IsTrue(check_valid(result, out_len, head, tail, n_head, enable_loop));
            Assert::AreEqual(get_length(ans, ans_len), get_length(result, out_len));
            free(result);
        }

        int get_length(char** words, int len)
        {
            int result = 0;
            for (int i = 0; i < len; i++)
            {
                result += int(strlen(words[i]));
            }
            return result;
        }

        int get_length(const char* words[], int len)
        {
            int result = 0;
            for (int i = 0; i < len; i++) 
            {
                result += int(strlen(words[i]));
            }
            return result;
        }

        bool check_valid(char** words, int len, char head, char tail, char n_head, bool enable_loop)
        {
            if (len == 0) 
            {
                return true;
            }
            if (n_head == words[0][0])
            {
                return false;
            }
            else if (head != 0 && head != words[0][0]) 
            {
                return false;
            }
            else if (tail != 0 && tail != words[len - 1][strlen(words[len - 1]) - 1])
            {
                return false;
            }
            for(int i = 1; i < len; i++)
            {
                if (words[i][0] != words[i - 1][strlen(words[i - 1]) - 1])
                {
                    return false;
                }
            }
            return true;
        }

    public:

        // '-n'

        TEST_METHOD(TestCoreGenChainsAll1) {
            const char* words[] = { "aa", "bb", "cc" };
            const char* ans[] = { "0" };
            test_gen_chains_all(words, 3, ans, 0);
        }

        TEST_METHOD(TestCoreGenChainsAll2) {
            const char* words[] = { "aa", "bb", "ab" };
            const char* ans[] = { "aa ab", "aa ab bb", "ab bb" };
            test_gen_chains_all(words, 3, ans, 3);
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

        // ²âÊÔsimplify·½·¨
        TEST_METHOD(TestCoreGenChainWordDuplicatedEdgeWithJ) {
            const char* words[] = { "element", "heaven", "heaveaan","able", "teach", "talk" };
            const char* ans[] = { "teach", "heaveaan" };
            test_gen_chain_word(words, 5, ans, 2, 0, 0, 'e', false);
        }

        /*-----------------------------*/

        // '-c'
        TEST_METHOD(TestCoreGenChainChar) {
            const char* words[] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "pseudopseudohypoparathyroidism", "moon" };
            test_gen_chain_char(words, 11, ans, 2, 0, 0, 0, false);
        }

        TEST_METHOD(TestCoreGenChainChar2) {
            const char* words[] = { "aaa", "ab", "bbb", "pseudopseudohypoparathyroidism" };
            const char* ans[] = { "aaa", "ab", "bbb" };
            test_gen_chain_char(words, 4, ans, 3, 0, 0, 0, false);
        }


        TEST_METHOD(TestCoreGenChainChar3) {
            const char* words[] = { "ea", "ab", "bbb", "acccccccccccc" };
            const char* ans[] = { "ea", "acccccccccccc" };
            test_gen_chain_char(words, 4, ans, 2, 0, 0, 0, false);
        }

        TEST_METHOD(TestCoreGenChainChar4) {
            const char* words[] = { "Aaaaaaa", "bbbb", "cccc", "acccccc", "abbbbbbbb"};
            const char* ans[] = { "Aaaaaaa", "abbbbbbbb", "bbbb" };
            test_gen_chain_char(words, 5, ans, 3, 0, 0, 0, false);
        }

        TEST_METHOD(TestCoreGenChainChar5) {
            const char* words[] = { "Aaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbb", "cccc", "acccccc", "abbbbbbbb" };
            const char* ans[] = { "Aaaaaaa", "abbbbbbbb", "bbbbbbbbbbbbbbbbbbbbbbb" };
            test_gen_chain_char(words, 5, ans, 3, 0, 0, 0, false);
        }

        TEST_METHOD(TestCoreGenChainChar6) {
            const char* words[] = { "Aaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbb", "cccc", "acccccc", "abbbbbbbb" };
            const char* ans[] = { "Aaaaaaa", "acccccc", "cccc" };
            test_gen_chain_char(words, 5, ans, 3, 0, 0, 'b', false);
        }

        TEST_METHOD(TestCoreGenChainChar7) {
            const char* words[] = { "Aaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbb", "cccc", "acccccc", "abbbbbbbb" };
            const char* ans[] = { "" };
            test_gen_chain_char(words, 5, ans, 0, 'b', 0, 0, false);
        }

        TEST_METHOD(TestCoreGenChainChar8) {
            const char* words[] = { "Aaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbb", "cccc", "acccccc", "abbbbbbbb", "bc" };
            const char* ans[] = { "bbbbbbbbbbbbbbbbbbbbbbb", "bc", "cccc" };
            test_gen_chain_char(words, 6, ans, 3, 'b', 0, 0, false);
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

        TEST_METHOD(TestCoreGenChainCharWithR2) {
            const char* words[] = { "element", "heaven", "table", "tablet", "teach", "talk" };
            const char* ans[] = { "tablet", "table", "element", "teach", "heaven" };
            test_gen_chain_char(words, 6, ans, 5, 0, 0, 0, true);
        }

        TEST_METHOD(TestCoreGenChainCharWithR3) {
            const char* words[] = { "ee" };
            const char* ans[] = { "" };
            test_gen_chain_char(words, 1, ans, 0, 0, 0, 0, true);
        }

        TEST_METHOD(TestCoreGenChainCharWithR4) {
            const char* words[] = { "ee", "eee", "ffffff"};
            const char* ans[] = { "ee", "eee"};
            test_gen_chain_char(words, 2, ans, 2, 0, 0, 0, true);
        }

        TEST_METHOD(TestCoreGenChainCharWithR5) {
            const char* words[] = { "ab", "bc", "cd", "de"};
            const char* ans[] = {  "ab", "bc", "cd" };
            test_gen_chain_char(words, 4, ans, 3, 0, 0, 'd', true);
        }

        // '-j'
        TEST_METHOD(TestCoreGenChainCharWithJ) {
            const char* words[] = { "element", "heaven", "able", "teach", "talk" };
            const char* ans[] = { "teach", "heaven" };
            test_gen_chain_char(words, 5, ans, 2, 0, 0, 'e', false);
        }

        TEST_METHOD(TestCoreGenChainCharLoop) {
            const char* words[] = { "AA", "ABA", "ABBBBBBA", "ABBBBBBBBBBA", "CA", "AC", "AAAAAAAAAAAAAC", "BC", "CB"};
            const char* ans[] = { "aa", "aba", "abbbbbba", "abbbbbbbbbba", "ac", "ca", "aaaaaaaaaaaaac", "cb", "bc" };
            test_gen_chain_char(words, 9, ans, 9, 0, 0, 0, true);
        }
    };
}
