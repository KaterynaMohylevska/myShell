#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "rename.h"
using namespace boost::filesystem;
using namespace std;

void rn(const string& old, const string& newn){
    if(exists(old)){
        rename(old,newn);
        puts ( "File successfully renamed" );
    }
    else{
        perror( "Error renaming file" );
    }
}
