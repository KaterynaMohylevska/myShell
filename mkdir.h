#ifndef MKDIR_H
#define MKDIR_H

#include "mkdir.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
using namespace boost::filesystem;
using namespace std;
int makeDir(const string& dir_name);

#endif // MKDIR_H
