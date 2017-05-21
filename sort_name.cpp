#include "ls_detailed.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <algorithm>
#include "sort_name.h"
using namespace boost::filesystem;
using namespace std;

void ls_sort_by_name(const string& pa){
    path p(pa);
    try{
        if (exists(p)) {
            typedef vector<path> vec; // store paths,
            vec v; // so we can sort them later
            copy(directory_iterator(p), directory_iterator(), back_inserter(v));
            sort(v.begin(), v.end()); // sort, since directory iteration
            // is not ordered on some file systems
            for (vec::const_iterator it (v.begin()); it != v.end(); ++it){
                cout  << *it << endl;
            }
        }
        else
            cout << p << " does not exist\n";
    }

    catch (const filesystem_error& ex)
    {
        cout << ex.what() << '\n';
    }
}
