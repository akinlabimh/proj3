#include <iostream>
#include <string>
#include "dlist.h"
#include "catch.hpp"
using namespace std;


TEST_CASE( "Test 02a", "Call Test Case 1" )
{
	if (system("diff -u -w student.output1 call1.out") != 0){
		system("diff -u -w student.output1 call1.out");
	}
  SECTION("Canvas Example") {
        REQUIRE(system("diff -u -w student.output1 call1.out") == 0);
    }
}

TEST_CASE( "Test 02b", "Call Test Case 2" )
{
	if (system("diff -u -w student.output2 call2.out") != 0){
		system("diff -u -w student.output2 call2.out");
	}
  SECTION("Canvas Example") {
        REQUIRE(system("diff -u -w student.output2 call2.out") == 0);
    }
}

