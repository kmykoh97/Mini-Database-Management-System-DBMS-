/*
C++ implementation file for value storage
*/

#include <string>
#include <fstream>

#include "DataFile.h"



using namespace std;

void DataFile::open(string x, int y)
{
    switch (y) {
        case CREATE:
            dataFile.open(x, ios::binary | ios::out);
            break;
        case READANDWRITE:
            dataFile.open(x, ios::binary | ios::in | ios::out);
            break;
    }
}

void DataFile::close()
{
    dataFile.close();
}

int DataFile::insertValue(string x)
{
    spaces.sortDataDel();
    x += '\0';
    int position = spaces.getSpace(x.size()); // try to get unused dangling space first

    if (position == -1) { // if can't get any free dangling space
        dataFile.seekp(0, ios::end); // moves pointer to the end
        position = dataFile.tellp();
        dataFile.write(x.c_str(), x.size());
        return position;
    } else { // if can get spaces from DataDel
        dataFile.seekp(position); // move pointer to the position
        dataFile.write(x.c_str(), x.size());
        return position;
    }
}

int DataFile::changeValue(int x, int y, string z)
{
    deleteValue(x, y);
    return insertValue(z);
}

void DataFile::deleteValue(int x, int y)
{
    spaces.insertSpace(x, y);
}

string DataFile::getValue(int x, int y)
{
    dataFile.seekg(x);
    char* temp = new char[y];
    dataFile.read(temp, y);
    string value(temp); //perform deep copy before free memory
    delete temp;

    return value;
}