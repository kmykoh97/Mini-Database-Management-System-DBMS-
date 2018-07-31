/*
This is a header source file for value data for each key in leaf node
*/

#ifndef DATA_H
#define DATA_H

#include <vector>



const int CREATE = 0;
const int READANDWRITE = 1;

class Data  
{
    public:
        // placed in public so index.cpp can access them later during save and write
        int offset; // position of this token inside disk
        int length; // spaces needed by this Data value
        
        // constructor
        Data(int offset = 0, int length = 0) {
            this -> offset = offset;
            this -> length = length;
        };

        // for sort() algorithm
        bool operator < (const Data &obj) {
            return this -> length < obj.length;
        }
};

class DataDel
{
    private:
        std::vector<Data> spaces; // stores a vector of extra spaces

    public:
        DataDel() {};

        void insertSpace(int offset, int length); // give space to DataDel
        void sortDataDel(); // sort spaces in accending order of length
        int getSpace(int dataLength); // get space from spaces if space for the length is available
};



#endif