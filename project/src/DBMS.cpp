/*
Implementation source file for main API for database management system
*/

#include <string>
#include <vector>

#include "DBMS.h"



using namespace std;

void DBMS::openDB(int x)
{
    key.open(keyPath, x);
    value.open(valuePath, x);
}

void DBMS::closeDB()
{
    key.close();
    value.close();
}

bool DBMS::insertDB(int x, string y)
{
    // start from new
    if (key.isEmpty()) {
        int offset = value.insertValue(y);
        int length = y.size() + 1;
        BPNode temp = BPNode();
        key.insertKey(x, offset, length, 0, temp);
        return true;
    }

    // key already available
    BPNode temp = key.searchWithInsertKey(x);
    if (key.hasKey(x, temp)) {
        key.parents.clear();
        return false;
    }

    int offset = value.insertValue(y);
    int length = y.size() + 1;
    key.insertKey(x, offset, length, 0, temp);
    return true;
}

bool DBMS::changeDB(int x, string y)
{
    if (key.isEmpty()) {
        return false;
    }

    BPNode temp = key.searchKey(x);

    if (key.hasKey(x, temp)) {
        int index = temp.searchKey(x);
        int offset = temp.value[index].offset;
        int length = temp.value[index].length;
        offset = value.changeValue(offset, length, y);
        temp.value[index] = Data(offset, length);
        key.writeNode(temp);
        return true;
    }

    return false;
}

bool DBMS::deleteDB(int x)
{
    if (key.isEmpty()) {
        return false;
    }

    BPNode temp = key.searchKey(x);
    if (key.hasKey(x, temp)) {
        vector<int> info = key.removeKey(x, temp);
        value.deleteValue(info[0], info[1]);
        return true;
    }

    return false;
}

string DBMS::getDB(int x)
{
    string ans = "Invalid key!";
    
    if (key.isEmpty()) {
        return ans;
    }

    BPNode temp = key.searchKey(x);
    if (key.hasKey(x, temp)) {
        int index = temp.searchKey(x);
        int offset = temp.value[index].offset;
        int length = temp.value[index].length;
        ans = value.getValue(offset, length);

        return ans;
    }

    return ans;
}

vector<int> DBMS::getRangeDB(int x, int y)
{
    vector<int> result;
    BPNode temp = key.searchKey(x);
    int index = temp.searchKey(x);
    if (temp.getNoOfKeys() == 0) {
        return result;
    }
    int ans = temp.keys[index];
    result.push_back(ans);

    while (y > result[result.size()-1]) {
        index++;
        if (index > temp.getNoOfKeys()) {
            temp = key.getKey(temp.nextNode);
            index = 0;
        }
        ans = temp.keys[index];
        result.push_back(ans);
    }

    while (result[result.size()-1] > y) {
        result.pop_back();
    }

    return result;
}