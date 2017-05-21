#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <algorithm>
#include "sort_size.h"
#include <map>
using namespace boost::filesystem;
using namespace std;

#include "ls_detailed.h"

void ls_sort_by_size(const string& pa){
    path someDir(pa);
    directory_iterator end_iter;

    typedef multimap<size_t, path> result_set_t;
    result_set_t result_set;

    if ( exists(someDir) && is_directory(someDir))
    {
        for( directory_iterator dir_iter(someDir) ; dir_iter != end_iter ; ++dir_iter)
        {
            if (is_regular_file(dir_iter->status()) )
            {
                result_set.insert(result_set_t::value_type(file_size(dir_iter->path()), *dir_iter));
            }
            else{
                cout << *dir_iter << "(has not last modified time and size)" << endl;
            }
        }
    }
    for(auto const &ent1 : result_set){
        file_details(ent1.second.string());
    }

}
