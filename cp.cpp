#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "cp.h"
using namespace boost::filesystem;
using namespace std;

void cp(const string& src_path, const string& dst_path){
    try{
        if (exists(dst_path)){
            cout << "This file already exists, do you want to copy it? [Y/N]" << endl;
            string command;
            getline(cin,command);
            if(command == "Y" || command == "y"){
                boost::filesystem::remove(dst_path);
                boost::filesystem::copy_file(src_path, dst_path);
                cout<< "Success" << endl;
            }
            else{
                return;
            }
        }
        else{
            boost::filesystem::copy_file(src_path, dst_path);
            cout<< "Success\n" << endl;
        }
    }
    catch (const filesystem_error& e){
            cout << "Something went wrong. Maybe no such directory" << endl;
    }
}
