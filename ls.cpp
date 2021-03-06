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
#include "sort_type.h"
using namespace boost::filesystem;
using namespace std;


int files(vector<string>& param){
    param.erase(remove(param.begin(), param.end(), "ls"), param.end());

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

    path p(str_path);
    int len_of_path = str_path.length();
    directory_iterator end_itr;

    //Sorts!!!
    vector<string> sorted;

    for(string i: param){
        if(i == "--sort" || i == "--sort=N"|| i == "--sort=n"){
            sorted = ls_sort_by_name(str_path);
        }
        if( i == "--sort=T"|| i == "--sort=t"){
            sorted = ls_sort_by_date(str_path); 
        }
        if( i == "--sort=X"|| i == "--sort=x"){
            sorted = ls_sort_by_type(str_path);
        }
        if(i == "--sort=S"|| i == "--sort=s"){
            sorted = ls_sort_by_size(str_path);
        }
    }

    if(find(param.begin(),param.end(),"-l") != param.end()){
        param.erase(remove(param.begin(), param.end(), "-l"), param.end());
        if(sorted.size() != 0 && find(param.begin(),param.end(),"-r") != param.end()){
            for(auto ent = sorted.rbegin(); ent != sorted.rend(); ent ++){
                file_details(*ent);
            }
            return 0;
        }
        else if(sorted.size() != 0){
            for(string ent1 : sorted){
                file_details(ent1);
            }
            return 0;
        }

        if(param.size() == 0){
            for (directory_iterator itr(p); itr != end_itr; ++itr)
            {
                // If it's not a directory
                if (is_regular_file(itr->path())) {
                    // assign current file name to current_file and echo it out to the console.
                    string current_file = itr->path().string();
                    //cout << current_file.substr(len_of_path+1,current_file.length()) << endl;
                    file_details(current_file);
                }
                else{
                    string current_file = itr->path().string();
                    cout << current_file.substr(len_of_path,current_file.length()) << endl;
                }
            }
        }
        for (vector<string>::iterator it = param.begin() ; it != param.end(); ++it){
            file_details(*it);
        }
        return 0;
    }



    else if(sorted.size() != 0){
        for(string ent1 : sorted){
            cout <<ent1 << endl;
        }
        return 0;
    }
    if(sorted.size() != 0 && find(param.begin(),param.end(),"-r") != param.end()){
        for(auto ent = sorted.rbegin(); ent != sorted.rend(); ent ++){
            cout << *ent<< endl;
        }
        return 0;
    }

    if(param.size() == 2){
        mask = param[1];
    }


    try{


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

