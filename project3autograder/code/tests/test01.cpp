#include <iostream>
#include <string>
#include "dlist.h"

#include "catch.hpp"
using namespace std;

static int intval = 0;
static const int numints = 4;


TEST_CASE( "Test 01a", "Dlist Test Case 1" )
{
  Dlist<int> d;
  int x = d.IsEmpty();

 SECTION("Dlist empty list validations") {
        REQUIRE( x == 1);
    }
}

TEST_CASE( "Test 01b", "Dlist Test Case 2" )
{
  string answer = "Caught front\nCaught back\n";
  string results = "";
  Dlist<int> d1;
  Dlist<int> d2;

    try {
      d1.RemoveFront();
    } catch (emptyList e) {
        results += "Caught front\n";
    }

    try {
	d2.RemoveBack();
    } catch (emptyList e) {
	    results += "Caught back\n";
    }
  SECTION("Dlist empty list validations") {
        REQUIRE(answer == results);
    }
}

TEST_CASE( "Test 01c", "Dlist Test Case 3" )
{
  string answer = "20134";
  string results = "";
  Dlist<int> d;
  int numints_5 =5;
  int ints[numints_5];
  int iv;
  int i;

  for (i=0; i<numints_5; i++) {
    ints[i] = i;
  }

  d.InsertFront(ints[0]);
  d.InsertFront(ints[1]);
  d.InsertFront(ints[2]);
  iv = d.RemoveFront();
  results.append(to_string(iv));
  iv = d.RemoveBack();
  results.append(to_string(iv));
  iv = d.RemoveBack();
  results.append(to_string(iv));

  d.InsertFront(ints[3]);
  d.InsertFront(ints[4]);

  iv = d.RemoveBack();
  results.append(to_string(iv));
  iv = d.RemoveBack();
  results.append(to_string(iv));

  SECTION("Dlist list validations") {
        REQUIRE(answer == results);
    }
}



TEST_CASE( "Test 01d", "Dlist Test Case 4" )
{
  string answer = "01230123";
  string results = "";
  Dlist<int> *d1, *d2;
    int ints[numints];
    int ip;
    int i;

    d1 = new Dlist<int>;

    for (i=0; i<numints; i++) {
      ints[i] = i;
      d1->InsertFront(ints[i]);
    }

    d2 = new Dlist<int>(*d1);

    for (i=0; i<numints; i++) {
      ip = d1->RemoveBack();
      results.append(to_string(ip));
    }

    delete d1;

    for (i=0; i<numints; i++) {
      ip = d2->RemoveBack();
      results.append(to_string(ip));
    }

    delete d2;


  SECTION("Dlist list validations") {
        REQUIRE(answer == results);
    }
}

TEST_CASE( "Test 01e", "Dlist Test Case 5" )
{
  string answer = "000111222333done";
  string results = "";
  Dlist<int> d1, d2, d3;
  int ip;
  int i;

  for (i=0; i<numints; i++) {
    d1.InsertFront(i);
    d2.InsertFront(i);
  }

  d2 = d1;
  d3 = d1;
  d1 = d1;

  for (i=0; i<numints; i++) {
    ip = d1.RemoveBack();
    results.append(to_string(ip));

    ip = d2.RemoveBack();
   results.append(to_string(ip));

    ip = d3.RemoveBack();
    results.append(to_string(ip));

  }

 results.append("done");

  SECTION("Dlist list validations") {
        REQUIRE(answer == results);
    }
}

TEST_CASE( "Test 01f", "Dlist Test Case 6" )
{
  int answer = 12;
  Dlist<int> *d1, *d2, *d3;
    int ip;
    int i, sum = 0;

    d1 = new Dlist<int>;
    d2 = new Dlist<int>;
    d3 = new Dlist<int>;

    for (i=0; i<numints; i++) {
      d1->InsertFront(i);
      d2->InsertFront(i);
      d3->InsertFront(i);
    }

    delete d1;
    *d2 = *d3;

    for (i=0; i<numints; i++) {
      ip = d2->RemoveBack();
      sum += ip;
    }

    for (i=0; i<numints; i++) {
      ip = d3->RemoveBack();
      sum += ip;
    }

    delete d2;
    delete d3;

  int results = sum;

  SECTION("Dlist list validations") {
        REQUIRE(answer == results);
    }
}
