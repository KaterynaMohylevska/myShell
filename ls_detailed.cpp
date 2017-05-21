#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "ls_detailed.h"
using namespace boost::filesystem;
using namespace std;

void file_details(const string& f_name){
    if(exists(f_name)){
        if (is_regular_file(f_name)){
            time_t t = last_write_time(f_name) ;
            cout << f_name << " size:"<< file_size(f_name)<< " bytes, last modified: " << ctime(&t);
        }
        else{
            cout << f_name << "(have not last modified time and size)" << endl;
        }
    }
    else{
        cout<< "No such file or directory" << endl;

    }

}
