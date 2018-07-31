/*
Implementation C++ source code for B+ index tree
*/

#include <vector>
#include <fstream>

#include "Index.h"



using namespace std;

int BPNode::isLeaf()
{
    return leaf;
}

void BPNode::setIsLeaf(int x)
{
    switch (x) {
        case 0:
            leaf = 0;
            break;
        case 1:
            leaf = 1;
            break;
    }
}

int BPNode::getPosition()
{
    return positionInFile;
}

void BPNode::setPosition(int x)
{
    positionInFile = x;
}

bool BPNode::hasKey(int x)
{
    // key is smaller than all elements in this node
    if (x < keys[0]) {
        return false;
    }

    // key is larger than largest element in this node
    if (x > keys[keys.size()-1]) {
        return false;
    }

    // key is larger than first(smallest) element in this node
    for (int i = 0; i < keys.size(); i++) {
        if (keys[i] == x) {
            return true;
        }
    }

    // key not found
    return false;
}

/*
int BPNode::searchKeyWithCheck(int x)
{
    int index = 0;

    if (!hasKey(x)) {
        return -1;
    }

    for (index; index < keys.size(); index++) {
        if (keys[index] >= x) {
            break;
        }
    }

    return index;
}
*/

int BPNode::searchKey(int x)
{
    int index = 0;

    for (index; index < keys.size(); index++) {
        if (keys[index] >= x) {
            break;
        }
    }

    return index;
}

void BPNode::insertKey(int x, int y, int z, int t)
{
    if (noOfKeys == 0) { // if the current node is empty
        keys.push_back(x);
        value.push_back(Data(y, z));
        children.push_back(t);
        children.push_back(t);
        noOfKeys++;
        return;
    } else { // if there is element inside node
        int index = searchKey(x);
        keys.insert(keys.begin() + index, x);
        value.insert(value.begin() + index, Data(y, z));
        children.insert(children.begin() + index + 1, t);
        noOfKeys++;
        return;
    }
}

vector<int> BPNode::removeKey(int x)
{
    // this method assumes key is available in this node. Use hasKey() to determine if not sure

    vector<int> info;

    // get the index of key to be deleted
    int index = searchKey(x);
    int offset = value[index].offset;
    int length = value[index].length;
    info.push_back(offset);
    info.push_back(length);

    // perform deletion
    keys.erase(keys.begin() + index);
    value.erase(value.begin() + index);
    (index == 0) ? (children.erase(children.begin())) : (children.erase(children.begin() + index + 1));

    noOfKeys--;

    return info;
}

int BPNode::getNoOfKeys()
{
    return noOfKeys;
}

void BPNode::setNoOfKeys(int x)
{
    noOfKeys = x;
}

bool BPNode::isOverflow()
{
    if (noOfKeys > MAXNODE) {
        return true;
    }

    return false;
}

/*
This is a special function to write into index file following the order of:
> leaf
> number of key
> keys
> children
> value.position
> value.length
> next node position
*/
void write(BPNode& obj, fstream& file)
{
    int leaf = obj.isLeaf(); // 1 if leaf. 0 otherwise
    int numberOfKey = obj.getNoOfKeys();

    // write state and number of key of the current node
    file.write((char*)&leaf, sizeof(int));
    file.write((char*)&numberOfKey, sizeof(int));

    // write existing keys of node into index file
    for (int i = 0; i < numberOfKey; i++) {
        file.write((char*)&(obj.keys[i]), sizeof(int));
    }

    // write children pointer into index file
    for (int i = 0; i < numberOfKey + 1; i++) {
        file.write((char*)&(obj.children[i]), sizeof(int));
    }

    // write position and length of the key into index file
    for (int i = 0; i < numberOfKey; i++) {
        file.write((char*)&(obj.value[i].offset), sizeof(int));
        file.write((char*)&(obj.value[i].length), sizeof(int));
    }

    // write position of next node into index file
    int nextNode = obj.nextNode;
    file.write((char*)&nextNode, sizeof(int));
}

void Index::open(string x, int y)
{
    switch (y) {
        case CREATE: // create new index file
            file.open(x, ios::binary | ios::out);
            break;
        case READANDWRITE: // read and ammend index file
            file.open(x, ios::binary | ios::out | ios::in);
            
            bool tf = true;
            file.seekp(0, ios::end);
	        (file.tellp() == 0) ? tf = true : tf = false;

            if (tf) {
                empty = true;
                break; // prevent change of boolean value
            }

            empty = false;
            file.seekg(0, ios::beg);
            file.read((char*)&rootPosition, sizeof(int));
            break;
    }

    return; // do nothing if wrong commands
}

void Index::close()
{
    file.close();
}

BPNode Index::searchKey(int x)
{
    BPNode temp = getKey(rootPosition);
    
    // iteratively search for the node in leaves
    while (temp.isLeaf() == 0) {
        int index = temp.searchKey(x);
        temp = getKey(temp.children[index]);
    }

    return temp;
}

BPNode Index::searchWithInsertKey(int x)
{
    BPNode temp = getKey(rootPosition);
    parents.push_back(temp);

    // iteratively search for the node in leaves
    while (temp.isLeaf() == 0) {
        int index = temp.searchKey(x);
        temp = getKey(temp.children[index]);
        parents.push_back(temp);
    }

    return temp;
}

BPNode Index::getKey(int x)
{
    file.seekg(x);
    BPNode temp;
    int leaf, noOfKey, key, children, offset, length, nextNode;
    temp.setPosition(x);
    
    // read leaf status
    file.read((char*)&leaf, sizeof(int));
    temp.setIsLeaf(leaf);

    // read number of keys
    file.read((char*)&noOfKey, sizeof(int));
    temp.setNoOfKeys(noOfKey);

    // read keys
    for (int i = 0; i < noOfKey; i++) {
        file.read((char*)&key, sizeof(int));
        temp.keys.push_back(key);
    }

    // read children pointers
    for (int i = 0; i < noOfKey + 1; i++) {
        file.read((char*)&children, sizeof(int));
        temp.children.push_back(children);
    }

    // read data of keys
    for (int i = 0; i < noOfKey; i++) {
        file.read((char*)&offset, sizeof(int));
        file.read((char*)&length, sizeof(int));
        temp.value.push_back(Data(offset, length));
    }

    // read next node
    file.read((char*)&nextNode, sizeof(int));
    temp.nextNode = nextNode;

    return temp;
}

bool Index::hasKey(int x, BPNode& o)
{
    if (empty) {
        return false;
    }

    int index = o.searchKey(x);
    if (o.keys[index] == x) {
        return true;
    }

    return false;
}

bool Index::isEmpty()
{
    return empty;
}

void Index::writeRoot()
{
    file.seekp(0, ios::beg);
    file.write((char*)&rootPosition, sizeof(int));
}

int Index::writeNode(BPNode& o)
{
    BPNode temp = o;
    int noOfKeys = o.getNoOfKeys();
    int requiredLength;

    // determine how much space needed to contain the node in index file
    if (noOfKeys == 0) {
        requiredLength = 0;
    } else {
        requiredLength = (4 + noOfKeys * 4) * 4;
    }

    // fill unused spaces with \0 (but giving appropriate space to enable them to be usable when needed or node expands)
    char* content = new char[MAXSPACES - requiredLength];
    for (int i = 0; i < MAXSPACES - requiredLength - 1; i++) {
        content[i] = '\0';
    }

    if (noOfKeys == 0) {
        file.seekp(o.getPosition());
        file.write(content, MAXSPACES - 1);
        delete content;
        return o.getPosition();
    }

    if (o.getPosition() == -1) {
        file.seekp(0, ios::end); // writes at end of file
        int position = file.tellp();
        write(o, file); // write content of node into index file
        file.write(content, MAXSPACES - requiredLength - 1); // fills remaining spaces with '\0'
        delete content;
        return position;
    } else {
        file.seekp(o.getPosition());
        write(o, file); // write content of node into index file
        file.write(content, MAXSPACES - requiredLength - 1); // fills remaining spaces with '\0'
        delete content;
        return o.getPosition();
    }
}

void Index::insertKey(int x, int y, int z, int t, BPNode& o)
{
    // if empty straight away write into node
    if (isEmpty()) {
        writeRoot();
        BPNode temp;
        temp.insertKey(x, y, z, 0);
        rootPosition = writeNode(temp);
        temp.setPosition(rootPosition);
        empty = false;
        writeRoot();
        return;
    }

    o.insertKey(x, y, z, t);
    parents.pop_back();
    parents.push_back(o);

    if (o.isOverflow()) {
        overflow(o);
    } else {
        writeNode(o);
    }
    parents.clear();
    empty = false;
}

vector<int> Index::removeKey(int x, BPNode& o)
{
    vector<int> info;
    info = o.removeKey(x);
    writeNode(o);

    return info;
}

void Index::overflow(BPNode& o)
{
    BPNode newNode;
    int add;
    parents.pop_back();
    int indexSplit = MAXNODE / 2;
    int nodeSplit = o.keys[indexSplit];

    if (o.isLeaf() == 1) { // node is leaf
        for (int i = indexSplit + 1; i < MAXNODE + 1; i++) {
            int key = o.keys[indexSplit+1];
            int offset = o.value[indexSplit+1].offset;
            int space = o.value[indexSplit+1].length;

            newNode.insertKey(key, offset, space, 0);
            o.removeKey(key);
        }
    } else { // inner node
        newNode.children.push_back(o.children[indexSplit+1]); // first, push first child

        for (int i = indexSplit+1; i < MAXNODE+1; i++) {
            int key = o.keys[indexSplit+1];
            int childPosition = o.children[indexSplit+2];
            newNode.insertKey(key, 0, 0, childPosition);
            o.removeKey(key);
        }

        o.removeKey(nodeSplit);
    }

    newNode.setNoOfKeys(newNode.keys.size());
    newNode.setIsLeaf(o.isLeaf());
    file.seekg(0, ios::end);
    newNode.setPosition(file.tellg());
    add = writeNode(newNode);
    if (newNode.isLeaf() == 1) {
        o.nextNode = add;
    } else {
        o.nextNode = -1;
    }

    if (o.getPosition() == rootPosition) { // node is root
        BPNode temp;
        temp.setIsLeaf(0);
		temp.setNoOfKeys(1);
        temp.keys.push_back(nodeSplit);
		temp.value.push_back(Data(0, 0));
		temp.children.push_back(o.getPosition()); // set children pointer
		temp.children.push_back(newNode.getPosition());
        file.seekg(0, ios::end);
		temp.setPosition(file.tellg());
		rootPosition = writeNode(temp);
		writeRoot();
		temp.setPosition(rootPosition);
		reserved.push_back(o);
    } else { // node is middle node
        BPNode parent = parents[parents.size()-1];
        parent.insertKey(nodeSplit, 0, 0, add);
        reserved.push_back(o);

        if (parent.isOverflow()) {
            overflow(parent);
        } else {
            reserved.push_back(parent);
        }
    }

    reload(); // rewrite changed nodes
}

void Index::reload()
{
    // reorient pointer
    writeRoot();
    
    // rewrite changed nodes in index file
    for (int i = 0; i < reserved.size(); i++) {
        writeNode(reserved[i]);
    }

    reserved.clear();
}