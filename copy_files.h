#ifndef COPY_FILES_H
#define COPY_FILES_H

#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "cp.h"

using namespace boost::filesystem;
using namespace std;

void c_files(vector<string> files, const string& dir);
#endif // COPY_FILES_H
