#include "pch.h"
#include "CppUnitTest.h"
#include "../src/parser.h"
#include "../src/parser.cpp"
#include "../src/error.cpp"
#include "sstream"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
    TEST_CLASS(test_parser)
    {
    private:
        void test_config(Config& config, char head, char tail, char n_head, char type, bool enable_loop)
        {
            Assert::AreEqual(config.head == head, true);
            Assert::AreEqual(config.tail == tail, true);
            Assert::AreEqual(config.n_head == n_head, true);
            Assert::AreEqual(config.type == type, true);
            Assert::AreEqual(config.enable_loop, enable_loop);
        }

    public:

        TEST_METHOD(TestParseWordsFromCode)
        {
            Parser parser;
            char input[] = "aa 1 aaa";
            std::istringstream f(input);
            parser.parse_words(f);
            Assert::AreEqual(int(parser.get_words().size()), 2);
            Assert::AreEqual(parser.get_words()[0].compare("aa"), 0);
            Assert::AreEqual(parser.get_words()[1].compare("aaa"), 0);
        }

        TEST_METHOD(TestParseWith1)
        {
            Parser parser;
            int argc = 2;
            char* argv[] = { "-n", "stdin.txt" };
            parser.parse(argc, argv);
            test_config(parser.get_config(), 0, 0, 0, 'n', false);
        }

        TEST_METHOD(TestParseWith2)
        {
            Parser parser;
            int argc = 4;
            char* argv[] = { "-c", "stdin.txt", "-j", "h"};
            parser.parse(argc, argv);
            test_config(parser.get_config(), 0, 0, 'h', 'c', false);
        }

        TEST_METHOD(TestParseWith3)
        {
            Parser parser;
            int argc = 4;
            char* argv[] = { "-w", "stdin.txt", "-t", "b"};
            parser.parse(argc, argv);
            test_config(parser.get_config(), 0, 'b', 0, 'w', false);
        }

        TEST_METHOD(TestParseWith4)
        {
            Parser parser;
            int argc = 4;
            char* argv[] = { "-w", "stdin.txt", "-h", "a"};
            parser.parse(argc, argv);
            test_config(parser.get_config(), 'a', 0, 0, 'w', false);
        }

        TEST_METHOD(TestParseWith5)
        {
            Parser parser;
            int argc = 3;
            char* argv[] = { "-c", "stdin.txt", "-r"};
            parser.parse(argc, argv);
            test_config(parser.get_config(), 0, 0, 0, 'c', true);
        }

        TEST_METHOD(TestParseWithUPPER)
        {
            Parser parser;
            int argc = 4;
            char* argv[] = { "-c", "stdin.txt", "-h", "V"};
            parser.parse(argc, argv);
            test_config(parser.get_config(), 'v', 0, 0, 'c', false);
        }
    };
}
