#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "ls_detailed.h"
using namespace boost::filesystem;
using namespace std;

void file_details(const string& f_name){
    if(exists(f_name)){
        cout << f_name << " size:"<< file_size(f_name)<< " last modified: " << last_write_time(f_name) << endl;
    }
    else{
        cout<< "No such file or directory" << endl;
    }
}
