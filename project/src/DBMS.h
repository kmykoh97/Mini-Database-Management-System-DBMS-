/*
C++ header file for main API for this database
*/

#ifndef DBMS_H
#define DBMS_H

#include <string>
#include <vector>

#include "DataFile.h"
#include "Index.h"



class DBMS
{
    private:
        Index key;
        DataFile value;
        std::string keyPath; // stores the file path to index file
        std::string valuePath; // stores the file path to data file

    public:
        DBMS (std::string path) {
            keyPath = path + "index";
            valuePath = path + "value";
        };

        void openDB(int method); // do required initialization to open index and data files
        void closeDB(); // do required ending procedures
        bool insertDB(int key, std::string value); // insert key-value data into this database
        bool changeDB(int key, std::string newValue); // change value of a value based on key given
        bool deleteDB(int key); // delete unwanted data
        std::string getDB(int key); // search for data
        std::vector<int> getRangeDB(int key1, int key2); // search for range of keys
};



#endif