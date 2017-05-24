#ifndef SORT_SIZE_H
#define SORT_SIZE_H

#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <algorithm>
#include <map>
using namespace boost::filesystem;
using namespace std;

#include "ls_detailed.h"

vector<string> ls_sort_by_size(const string& pa);

#endif // SORT_SIZE_H
