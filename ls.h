#ifndef LS_H
#define LS_H
#include "ls_detailed.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <string>
#include <algorithm>
#include <boost/algorithm/string/replace.hpp>
#include "sort_name.h"
#include "sort_time.h"
#include "sort_size.h"
using namespace boost::filesystem;
using namespace std;


int files(vector<string>& param);
#endif // LS_H
