/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: Ziv Morgan
 * 
 * Date: 2021-02
 */

#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}


TEST_CASE("writing over text") {
	Notebook n;
	n.write(100, 100,50, Direction::Horizontal, "abcd");
    CHECK_THROWS(n.write(100, 100,50, Direction::Horizontal, "abcd"));
	CHECK_THROWS(n.write(100, 100,50, Direction::Horizontal, "abc"));
	CHECK_THROWS(n.write(100, 100,50, Direction::Vertical, "abcdas"));
	CHECK_THROWS(n.write(100, 99 ,51, Direction::Vertical, "abcdas"));
	n.erase(100, 99 ,51, Direction::Vertical, 3);
	CHECK_THROWS(n.write(100, 99 ,51, Direction::Vertical, "abcdas"));
}

TEST_CASE("allowed areas to write over twice") {
	Notebook n;
	n.write(100, 100,50, Direction::Horizontal, "ab_cd");
	n.write(100, 98,52, Direction::Vertical, "12_34");
	CHECK(n.read(100,98,52,Direction::Vertical,5) == "12_34");
	CHECK(n.read(100,100,50,Direction::Horizontal,5) == "ab_cd");

	n.erase(100, 100,50, Direction::Horizontal, 5);
	CHECK(n.read(100,100,50,Direction::Horizontal,5) == "~~~~~");
	n.erase(100, 100,50, Direction::Horizontal, 5);
	CHECK_THROWS(n.write(100, 100,50, Direction::Horizontal, "~~~~~"));

	n.erase(100, 98,52, Direction::Vertical, 5);
	CHECK(n.read(100,98,52,Direction::Vertical,5) == "~~~~~");
	n.erase(100, 98,52, Direction::Vertical, 5);
	CHECK_THROWS(n.write(100, 98,52, Direction::Vertical, "~~~~~"));


}

TEST_CASE("out of bounds") {
	Notebook n;
	CHECK_THROWS(n.write(100, 100,98, Direction::Horizontal, "ab_cd"));
	CHECK_THROWS(n.read(100, 100,98, Direction::Horizontal, 5));
	CHECK(n.read(100, 100,98, Direction::Horizontal, 2) == "__");
}

TEST_CASE("multiple pages") {
	Notebook n;
	n.write(99, 100,50, Direction::Horizontal, "123");
	n.write(100, 100,50, Direction::Horizontal, "456");
	n.write(265, 100,50, Direction::Horizontal, "789");
	n.erase(101, 100,50, Direction::Horizontal, 3);
	CHECK(n.read(99, 100,50, Direction::Horizontal, 3) == "123");
	CHECK(n.read(100, 100,50, Direction::Horizontal, 3) == "456");
	CHECK(n.read(265, 100,50, Direction::Horizontal, 3) == "789");
	CHECK(n.read(101, 100,50, Direction::Horizontal, 3) == "~~~");
    
}

TEST_CASE("bad chars"){
	Notebook n;
	CHECK_THROWS(n.write(100, 100,50, Direction::Horizontal, "\n"));
	CHECK_THROWS(n.write(101, 100,50, Direction::Horizontal, "\r"));
	CHECK_THROWS(n.write(102, 100,50, Direction::Horizontal, "\t"));
	CHECK_THROWS(n.write(103, 100,50, Direction::Horizontal, "a\tasdas"));
	CHECK(n.read(103, 100,50, Direction::Horizontal, 5)=="_____");
}
TEST_CASE("read without write"){
	Notebook n;
	CHECK(n.read(103, 100,50, Direction::Horizontal, 5)=="_____");
}


