#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split

#include "mkdir.h"
#include "ls.h"
#include "ls_detailed.h"
#include "remove.h"


using namespace boost::filesystem;
using namespace std;



void change_path(string p){
    try{
        if(p.find("/home") != -1){
            current_path(p);
        }
        else{
            string p1 = current_path().string() + "/" + p;
            current_path(p1);
        }
    }
    catch (const filesystem_error& e){
        cout << "No such file or directory" << endl;
    }
}

/*void cp(string src_path, string dst_path){
    if (exists(dst_path)){
        boost::filesystem::remove(dst_path);
        boost::filesystem::copy_file(src_path, dst_path);
    }
    else{
            cout << "Error" << endl;
    }
}

void cp(vector<string> files, string dir){
    for( auto &i : files){
        boost::filesystem::copy_file(i, dir);
        }
}*/

void rname(string old, string newn){
    if(exists(old)){
        rename(old,newn);
        cout<<"renamed"<<endl;
      }
    else{
        cout << "file: "<< old << " does not exist" << endl;
    }
}



int main(){
    map<string, string> help_data;

    help_data["ls -h"] = "Information about files in directory.";
    help_data["ls --help"] = "Information about files in directory.";
    help_data["pwd -h"] = "Information about current path.";
    help_data["pwd --help"] = "Information about current path";
    help_data["cd -h"] = "Go to path.";
    help_data["cd --help"] = "Go to path.";
    help_data["exit -h"] = "Exit from shell.";
    help_data["exit --help"] = "Exit from shell.";
    help_data["cp -h"] = "Copy from one file to another.";
    help_data["cp --help"] = "Copy from one file to another.";
    help_data["mv -h"] = "Rename or remove.";
    help_data["mv --help"] = "Rename or remove.";
    help_data["rm -h"] = "Delete file.";
    help_data["rm --help"] = "Delete file.";
    help_data["mkdir -h"] = "Create new directory.";

    while(1){
        cout << "cat@ ";
        string command;
        getline(cin,command);

        if(help_data.find(command) != help_data.end()){
           cout << help_data.find(command) -> second << endl;
        }
        else if (command == "pwd") {
            cout << current_path() << endl;
        }
        else if (command == "ls"){
            files(".");
        }
        else if(command.find("mkdir") != -1){
            string name  = command.substr(6,command.length());
            makeDir(name);
        }
        else if (command.length() > 5 && command.find("ls -l") != -1){
            string path  = command.substr(6,command.length());
            file_details(path);
        }
        else if (command.length() > 2 && command.find("ls") != -1){
            string path  = command.substr(3,command.length());
            files(path);
        }

        else if (command.length() > 4 && command.find("mkdir") != -1){
            string path  = command.substr(6,command.length());
            makeDir(path);
        }
        else if (command.find("rm") != -1 && command.find("-R") == -1){
            cout << "Can not delete without '-R'" << endl;
        }
        else if (command.find("rm") != -1 && command.find("-f") != -1 && command.find("-R") != -1){
            string path  = command.substr(9,command.length());
            vector<string> words;
            boost::split(words, path, boost::is_any_of(" "), boost::token_compress_on);
            rm(words);
        }
        else if (command.find("rm") != -1 && command.find("-f") == -1 && command.find("-R") != -1){
            cout << "Are you sure? [Y/N]" << endl;
            string answer;
            cin >> answer;
            if (answer == "Y" || answer == "y"){
                string path  = command.substr(7,command.length());
                vector<string> words;
                boost::split(words, path, boost::is_any_of(" "), boost::token_compress_on);
                rm(words);
            }
        }
        else if (command.find("mv") != -1){
            string path  = command.substr(3,command.length());
            vector<string> words;
            boost::split(words, path, boost::is_any_of(" "), boost::token_compress_on);
            rname(words[0], words[1]);
        }
        else if(command.find("cd") != -1){
            string path  = command.substr(3,command.length());
            change_path(path);
        }
        else if(command == "exit"){
            break;
            return 0;
        }
        else{
            cout << "No such command"<<endl;
        }
    }
    return 0;
}
