/*
C++ header source file for value storage
*/

#ifndef DATAFILE_H
#define DATAFILE_H

#include <fstream>
#include <string>

#include "Data.h"



class DataFile
{
    private:
        std::fstream dataFile; // mechanism variable to open and modified files
        DataDel spaces; // to keep extra spaces after user deletes some datas

    public:
        DataFile() {};

        void open(std::string path, int method); // open data file, if none, create it
        void close(); // close data file
        int insertValue(std::string value); // insert new value into data file
        int changeValue(int offset, int length, std::string newValue); // change content of value in data file
        void deleteValue(int offset, int length); // delete value in data file
        std::string getValue(int offset, int length); // get content of value in an offset
};



#endif