#include "pch.h"
#include "CppUnitTest.h"
#include "../src/parser.h"
#include "../src/core.h"
#include "sstream"
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
    TEST_CLASS(test_parser_error)
    {
    public:
        TEST_METHOD(TestMissingArgument)
        {
            Parser parser;
            int argc = 0;
            char* argv[] = { "" };
            try
            {
                parser.parse(argc, argv);
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(strcmp(e.what(), "Missing Argument:"), 0);
            }
        }

        TEST_METHOD(TestMissingArgument2)
        {
            Parser parser;
            int argc = 3;
            char* argv[] = { "-w", "stdin.txt", "-w" };
            try
            {
                parser.parse(argc, argv);
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(strcmp(e.what(), "Missing Argument:"), 0);
            }
        }

        TEST_METHOD(TestConflictedArgument)
        {
            Parser parser;
            int argc = 4;
            char* argv[] = { "-w", "stdin.txt", "-w", "s.txt"};
            try
            {
                parser.parse(argc, argv);
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(strcmp(e.what(), "Conflicted Argument:"), 0);
            }
        }

        TEST_METHOD(TestUnexpectedArgument)
        {
            Parser parser;
            int argc = 1;
            char* argv[] = { "-l" };
            try
            {
                parser.parse(argc, argv);
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(strcmp(e.what(), "Unexpected Argument:"), 0);
            }
        }

        TEST_METHOD(TestInvalidArgument)
        {
            Parser parser;
            int argc = 2;
            char* argv[] = { "-h", "aa"};
            try
            {
                parser.parse(argc, argv);
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(strcmp(e.what(), "Invalid Argument:"), 0);
            }
        }

        TEST_METHOD(TestInvalidFile)
        {
            Parser parser;
            int argc = 2;
            char* argv[] = { "-w", "ss.png" };
            try
            {
                parser.parse(argc, argv);
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(strcmp(e.what(), "Invalid File:"), 0);
            }
        }

        TEST_METHOD(TestConflictedArgumentWithR)
        {
            Parser parser;
            int argc = 2;
            char* argv[] = { "-r", "-r" };
            try
            {
                parser.parse(argc, argv);
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(strcmp(e.what(), "Conflicted Argument:"), 0);
            }
        }

        TEST_METHOD(TestConflictedArgumentWithNR)
        {
            Parser parser;
            int argc = 3;
            char* argv[] = { "-n", ".txt", "-r"};
            try
            {
                parser.parse(argc, argv);
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(strcmp(e.what(), "Conflicted Argument:"), 0);
            }
        }
        

    };
}
