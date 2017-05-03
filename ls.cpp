#include "ls.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
using namespace boost::filesystem;
using namespace std;


int files(const string& str_path_mask){
    string str_path = ".";
    string mask;
    int i = str_path_mask.find("/");
    if(i != -1 || str_path_mask == "."){
        str_path = str_path_mask;
    }
    else{
        mask = str_path_mask;
    }
    try{
       path p(str_path);
       int len_of_path = str_path.length();
       directory_iterator end_itr;

       if(mask.length()==0){
       // cycle through the directory
           for (directory_iterator itr(p); itr != end_itr; ++itr)
           {
               // If it's not a directory
               if (is_regular_file(itr->path())) {
                   // assign current file name to current_file and echo it out to the console.
                   string current_file = itr->path().string();
                   cout << current_file.substr(len_of_path+1,current_file.length()) << endl;
               }
               else{
                   string current_file = itr->path().string();
                   cout << current_file.substr(len_of_path,current_file.length()) << endl;
               }
           }
       }
       else{
           if(mask.find("*") != -1){
               int ind = mask.find("*");
               for (directory_iterator itr(p); itr != end_itr; ++itr){
                   string current_file = itr->path().string().substr(len_of_path+1,current_file.length());
                   //cout<<current_file << endl;
                   //cout << current_file.substr(current_file.length()-(mask.length() - ind)+1,current_file.length()) << endl;
                   //cout << mask.substr(ind+1) << endl;
                   if (current_file.substr(0,ind) == mask.substr(0,ind)
                           && mask.substr(ind+1) ==
                           current_file.substr(current_file.length()-(mask.length() - ind)+1,current_file.length())){
                       cout<<current_file<<endl;
                   }
               }
           }
           else {
               for (directory_iterator itr(p); itr != end_itr; ++itr){
                   string current_file = itr->path().string().substr(len_of_path+1,current_file.length());
                   if( mask == current_file){
                       cout<<current_file<<endl;
                   }
               }

           }

       }
               return 1;
    }
    catch (const filesystem_error& e){
        cout << "No such file or directory" << endl;
        return 0;
    }
}

