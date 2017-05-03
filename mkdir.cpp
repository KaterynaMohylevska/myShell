#include "mkdir.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>


using namespace boost::filesystem;
using namespace std;
int makeDir(const string& dir_name){

    path dir(dir_name);
    if(create_directory(dir)){
        cout<< "Success\n" << endl;
        return 1;
    }
    else{
        cout << "Directory already exists\n" << endl;
        return 0;
    }
}
