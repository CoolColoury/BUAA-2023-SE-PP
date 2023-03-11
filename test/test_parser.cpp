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
	};
}
