#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "copy_files.h"
using namespace boost::filesystem;
using namespace std;

void c_files(vector<string> files, const string& dir){
    for( auto &i : files){
        string file = dir + "/" + i;
        cp(i, file);
        }
}
