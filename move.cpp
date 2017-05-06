#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "cp.h"
#include "remove.h"
#include "move.h"
using namespace boost::filesystem;
using namespace std;

void mv(vector<string>& files, const string& dir){
    c_files(files, dir);
    rm(files);
}
