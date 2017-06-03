#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <stdio.h>
#include <stdlib.h>
#include "mkdir.h"
#include "ls.h"
#include "remove.h"
#include "cp.h"
#include "copy_files.h"
#include "rename.h"
#include "move.h"
#include <iostream>
#include <sys/wait.h>

using namespace boost::filesystem;
using namespace std;



void change_path(const string& p){
    try{
        if(p.find("/home") != -1){
            current_path(p);
            cout<< current_path() << endl;
        }
        else{
            string p1 = current_path().string() + "/" + p;
            current_path(p1);
            cout << current_path() << endl;
        }
    }
    catch (const filesystem_error& e){
        cout << "No such file or directory" << endl;
    }
}


int startProcess(const char * args[])
{
    pid_t childPid;
    childPid = fork();
    if (childPid == 0)
    {
        execvp(args[0], const_cast<char * const *>(args) );
        cout << "error" << endl;
        cout << strerror(errno) << std::endl;
    } else if (childPid < 0)
    {
        exit(-1);
    } else {
        waitpid(-1, nullptr, 0);
    }
    return 0 ;
}

int callOuter(const std::vector<std::string>& args)
{
    const char * argv[args.size()+1];
    for (int i = 0; i < args.size(); i++) {
        argv[i] = args[i].c_str();
    }
    argv[args.size()] = nullptr;
    startProcess(argv);

    return 0 ;

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

        else if(command.find("mkdir") != -1){
            string name  = command.substr(6,command.length());
            makeDir(name);
        }
        else if (command.find("ls") != -1){
            vector<string> parametrs;
            boost::split(parametrs,command,boost::is_any_of("\t "));
            files(parametrs);

        }

        else if (command.length() > 4 && command.find("mkdir") != -1){
            string path  = command.substr(6,command.length());
            makeDir(path);
        }
        else if (command.find("mv") != -1){
            string path = command.substr(3,command.length());
            vector<string> words;
            boost::split(words, path, boost::is_any_of(" "), boost::token_compress_on);
            if(words.size() > 2){
                if(find(words.begin(), words.end(),"-f") != words.end()){
                    words.erase(remove(words.begin(),words.end(), "-f"), words.end());
                    words.erase(remove(words.begin(),words.end(), "mv"), words.end());
                    vector<string>::const_iterator f = words.begin();
                    vector<string>::const_iterator l = words.begin() + words.size() - 1;
                    vector<string> files(f,l);
                    mv(files,words[words.size()-1]);
                    cout << "Success/";
                }
                else{
                    cout << "Do you want to replace file if it exist? [Y/N]" << endl;
                    string command;
                    getline(cin,command);
                    if(command == "Y" || command == "y"){
                        words.erase(remove(words.begin(),words.end(), "-f"), words.end());
                        words.erase(remove(words.begin(),words.end(), "mv"), words.end());
                        vector<string>::const_iterator f = words.begin();
                        vector<string>::const_iterator l = words.begin() + words.size() - 1;
                        vector<string> files(f,l);
                        mv(files,words[words.size()-1]);
                    }
                }
            }

            else{
                cout << "Do you want to rename it? [Y/N]" << endl;
                string command;
                getline(cin,command);
                if(command == "Y" || command == "y"){
                    rn(words[0], words[1]);
                }
            }
        }

        else if(command.find("cp") != -1){
            string files = command;
            vector<string> dir;
            boost::split(dir, files, boost::is_any_of(" "), boost::token_compress_on);
            dir.erase(remove(dir.begin(),dir.end(), "cp"), dir.end());

            if (find(dir.begin(), dir.end(),"-f") != dir.end()){
                dir.erase(remove(dir.begin(),dir.end(), "-f"), dir.end());
                if(dir.size() > 2){
                    string d = dir[dir.size()-1];
                    dir.pop_back();
                    c_files(dir,d);
                }else{
                    cp(dir[0], dir[1]);}
            }
            else{
                if(dir.size() > 2){
                    string d = dir[dir.size()-1];
                    dir.pop_back();
                    for( auto &i : dir){
                        if(exists(d+"/"+i)){
                            cout << i <<  " already exists, do you want to copy it? [Y/N]" << endl;
                            string command;
                            getline(cin,command);
                            if(command != "Y" && command != "y"){
                                dir.erase(remove(dir.begin(),dir.end(), i), dir.end());
                            }
                        }
                    }
                    if(dir.size()!=0){
                    c_files(dir,d);}
                }
                else{
                    if(exists(dir[1])){
                        cout << dir[1]<< " already exists, do you want to copy it? [Y/N]" << endl;
                        string command;
                        getline(cin,command);
                        if(command == "Y" || command == "y"){
                            dir.erase(remove(dir.begin(),dir.end(), "cp"), dir.end());
                            cp(dir[0], dir[1]);
                        }
                    }else{
                        cp(dir[0], dir[1]);
                    }

                }

            }
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
        else if(command.find("cd") != -1){
            string path  = command.substr(3,command.length());
            change_path(path);
        }
        else if (command.find("exit") != -1 && command.length() >= 5) {
            int code;
            code = stoi(command.substr(4,command.length()));
            exit(code);
        }
        else if (command.find("exit") != -1 && command.length() == 4){
            exit(0);}
        else{
            try{
               vector<string> splitVec;
               boost::split(splitVec, command, boost::is_space(), boost::token_compress_on);
               callOuter(splitVec);
            }
            catch (const filesystem_error& e){
                cout << "No such command"<<endl;
            }
        }
    }
    return 0;
}
