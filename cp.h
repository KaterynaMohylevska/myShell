#ifndef CP_H
#define CP_H

#include <iostream>
#include <boost/filesystem.hpp>
#include <string>

using namespace boost::filesystem;
using namespace std;

void cp(const string& src_path, const string& dst_path);

#endif // CP_H
