#include "ls_detailed.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <algorithm>
#include "sort_name.h"
#include <map>
using namespace boost::filesystem;
using namespace std;

vector<string> ls_sort_by_name(const string& pa){
    path someDir(pa);
    directory_iterator end_iter;

    typedef multimap<path,int> result_set_t;
    result_set_t result_set;

    if ( exists(someDir) && is_directory(someDir))
    {
        for( directory_iterator dir_iter(someDir) ; dir_iter != end_iter ; ++dir_iter)
        {

           result_set.insert(result_set_t::value_type(*dir_iter,0));

        }
    }
    vector<string> sorted;
    for(auto const &ent1 : result_set){
       sorted.push_back(ent1.first.string());
    }
    return sorted;
}
