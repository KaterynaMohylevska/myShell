#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include "remove.h"
using namespace boost::filesystem;
using namespace std;

void rm(vector<string>& rem){
    for(auto& i : rem){
        wpath file(i);
        if(exists(file)){
            remove(file);
            cout << "file: " << i << " removed" << endl;
        }
        else{
            cout << "file: " << i << " does not exist" << endl;
        }
    }
}
