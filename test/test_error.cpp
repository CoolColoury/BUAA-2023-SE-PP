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
        }

        void test_gen_chain_word(const char* words[], int len, const char* ans[], int ans_len, char head, char tail, char n_head, bool enable_loop) {
            char** result = (char**)malloc(10000);
            int out_len = gen_chain_word(words, len, result, head, tail, n_head, enable_loop);
        }

        void test_gen_chain_char(const char* words[], int len, const char* ans[], int ans_len, char head, char tail, char n_head, bool enable_loop) {
            char** result = (char**)malloc(10000);
            int out_len = gen_chain_char(words, len, result, head, tail, n_head, enable_loop);
        }

    public:


        TEST_METHOD(TestCoreGenChainCharLoopError)
        {
            const char* words[] = { "element", "te", "eee", "ttt", "talk" };
            const char* ans[] = { 0 };
            try
            {
                test_gen_chain_char(words, 5, ans, 0, 0, 0, 'e', false);
            }
            catch (const std::exception&)
            {
                char* error = get_error_message();
                Assert::AreEqual(strcmp(get_error_message(), "Ring Check Exception:"), 0);
            }
        }

        TEST_METHOD(TestCoreGenChainWordLoopError)
        {
            const char* words[] = { "element", "te", "eee", "ttt", "talk" };
            const char* ans[] = { 0 };
            try
            {
                test_gen_chain_word(words, 5, ans, 0, 0, 0, 'e', false);
            }
            catch (const std::exception&)
            {
                char* error = get_error_message();
                Assert::AreEqual(strcmp(get_error_message(), "Ring Check Exception:"), 0);
            }
        }

        TEST_METHOD(TestCoreGenChainsAllLoopError)
        {
            const char* words[] = { "element", "te", "eee", "ttt", "talk" };
            const char* ans[] = { 0 };
            try
            {
                test_gen_chains_all(words, 5, ans, 0);
            }
            catch (const std::exception&)
            {
                char* error = get_error_message();
                Assert::AreEqual(strcmp(get_error_message(), "Ring Check Exception:"), 0);
            }
        }

    };
}
