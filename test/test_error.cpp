#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core.h"
#include "../src/solver.h"
#include "../src/wordgraph.h"
#include "sstream"
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
    TEST_CLASS(test_error)
    {
    private:
        void test_gen_chains_all(const char* words[], int len, const char* ans[], int ans_len) {
            char** result = (char**)malloc(10000);
            int out_len = gen_chains_all(words, len, result);
            Assert::AreEqual(ans_len, out_len);
            for (int i = 0; i < ans_len; i++) {
                if (result != nullptr)
                {
                    Assert::AreEqual(strcmp(ans[i + 1], result[i + 1]), 0);
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
            for (int i = 1; i < len; i++)
            {
                if (words[i][0] != words[i - 1][strlen(words[i - 1]) - 1])
                {
                    return false;
                }
            }
            return true;
        }

    public:

        
        TEST_METHOD(TestCoreGenChainLoopError) {
            const char* words[] = { "element", "te", "eee", "ttt", "talk" };
            const char* ans[] = { 0 };
            try
            {
                test_gen_chain_char(words, 5, ans, 0, 0, 0, 'e', false);
            }
            catch (const std::exception& e)
            {
                char* error = get_error_message();
                Assert::AreEqual(strcmp(get_error_message(), "Invalid Argument:"), 0);
            }
        }   
    };
}
