#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "cp.h"
using namespace boost::filesystem;
using namespace std;

void cp(const string& src_path, const string& dst_path){
    try{
        if (exists(dst_path)){
            boost::filesystem::remove(dst_path);
            boost::filesystem::copy_file(src_path, dst_path);
            cout<<src_path<< " copied" << endl;
        }
        else{
            boost::filesystem::copy_file(src_path, dst_path);
            cout<< src_path<< " copied" << endl;
        }
    }
    catch (const filesystem_error& e){
        cout << "Something went wrong. Maybe no such directory"<< endl;
    }
}
