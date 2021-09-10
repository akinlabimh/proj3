#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "dlist.h"
#include "catch.hpp"
using namespace std;

static int intval = 0;
static const int numints = 4;

TEST_CASE( "Test 03a", "Calc Test 1" )
{
	if (system("diff -u -w student.output1 correct.output1") != 0){
		system("diff -u -w student.output1 correct.output1");
	}
 SECTION("Canvas Example") {
        REQUIRE(system("diff -u -w student.output1 correct.output1") == 0);
    }
}

TEST_CASE( "Test 03b", "Calc Test 2" )
{
	if (system("diff -u -w student.output2 correct.output2") != 0){
		system("diff -u -w student.output2 correct.output2");
	}
	
 SECTION("'a' Operations") {
        REQUIRE(system("diff -u -w student.output2 correct.output2") == 0);
    }
}

TEST_CASE( "Test 03c", "Calc Test 3" )
{
	if (system("diff -u -w student.output3 correct.output3") != 0){
		system("diff -u -w student.output3 correct.output3");
	}
	
 SECTION("Extra Example") {
        REQUIRE(system("diff -u -w student.output3 correct.output3") == 0);
    }
}
