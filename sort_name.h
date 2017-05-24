#ifndef SORT_NAME_H
#define SORT_NAME_H

#include "ls_detailed.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <algorithm>
using namespace boost::filesystem;
using namespace std;

vector<path> ls_sort_by_name(const string& pa);

#endif // SORT_NAME_H
