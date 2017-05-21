#include "ls.h"
#include "ls_detailed.h"
#include <iostream>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <algorithm>
#include <boost/algorithm/string/replace.hpp>
#include "sort_name.h"
#include "sort_time.h"
#include "sort_size.h"
using namespace boost::filesystem;
using namespace std;


int files(vector<string>& param){
    param.erase(remove(param.begin(), param.end(), "ls"), param.end());
    if(find(param.begin(),param.end(),"-l") != param.end()){
        param.erase(remove(param.begin(), param.end(), "-l"), param.end());
        if(param.size() == 0){
            cout << "Set the name of file!!!" << endl;
            return 0;
        }
        for (vector<string>::iterator it = param.begin() ; it != param.end(); ++it){
            file_details(*it);
        }
        return 0;
    }

    string str_path = ".";
    string mask;

    if(param[0].find("/") != -1 || param[0] == "."){
        str_path = param[0];
    }
    else if(param.size() == 0 || param[0] == ".."){
        str_path = ".";
    }
    else{
        mask = param[0];
    }

    //Sorts!!!

    for(string i: param){
        if(i == "--sort" || i == "--sort=N"|| i == "--sort=n"){
            ls_sort_by_name(str_path);
            return 1;
        }
        if( i == "--sort=T"|| i == "--sort=t"){
            ls_sort_by_date(str_path);
            return 1;
        }
        if(i == "--sort=S"|| i == "--sort=s"){
            ls_sort_by_size(str_path);
            return 1;
        }
    }

    if(param.size() == 2){
        mask = param[1];
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

           boost::replace_all(mask,"*",".*");
           boost::replace_all(mask,"?","[a-z]");
           boost::regex expr{mask};

           for (directory_iterator itr(p); itr != end_itr; ++itr){
               string current_file = itr->path().string().substr(len_of_path+1,current_file.length());
               if(boost::regex_match(current_file, expr)){
                   cout<<current_file<<endl;
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

