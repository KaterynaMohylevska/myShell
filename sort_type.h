#ifndef SORT_TYPE_H
#define SORT_TYPE_H


#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <algorithm>
#include "sort_size.h"
#include <map>
using namespace boost::filesystem;
using namespace std;

#include "ls_detailed.h"

vector<string> ls_sort_by_type(const string& pa);


#endif // SORT_TYPE_H
