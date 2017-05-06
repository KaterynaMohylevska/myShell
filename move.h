#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "copy_files.h"
#include "remove.h"
using namespace boost::filesystem;
using namespace std;
void mv(vector<string>& files, const string& dir);
#endif // MOVE_H
