#include "stdafx.h"
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int mem_fun_refTest () {
  vector<string> numbers;

  // populate vector:
  numbers.push_back("one");
  numbers.push_back("two");
  numbers.push_back("three");
  numbers.push_back("four");
  numbers.push_back("five");

  vector <int> lengths (numbers.size());

  transform (numbers.begin(), numbers.end(), lengths.begin(), mem_fun_ref(&string::length));
	
  for (int i=0; i<5; i++) {
	  cout << numbers[i] << " has " << lengths[i] << " letters.\n";
  }
  return 0;
}