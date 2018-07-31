/*
C++ implementation source file for Data values
*/

#include <algorithm>
#include <vector>

#include "Data.h"



using namespace std;

void DataDel::insertSpace(int x, int y)
{
    spaces.push_back(Data(x, y));
}

void DataDel::sortDataDel()
{
    sort(spaces.begin(), spaces.end());
}

int DataDel::getSpace(int x)
{
    if (spaces.size() == 0) {
        return -1;
    } else {
        int position;
        sortDataDel();
        if (spaces[spaces.size() - 1].length < x) {
            return -1;
        } else {
            position = spaces[spaces.size()-1].offset;
            if (spaces[spaces.size()-1].offset == x) {
                spaces.pop_back();
                return position;
            } else {
                int newPosition = spaces[spaces.size()-1].offset + x;
                int newLength = spaces[spaces.size()-1].length - x;
                spaces.pop_back();
                spaces.push_back(Data(newPosition, newLength));
                return position;
            }
        }
    }

    return -1;
}