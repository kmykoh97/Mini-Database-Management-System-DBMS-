/*
Header source file of B+ Tree whole tree. It is used for database indexing
*/

#ifndef INDEX_H
#define INDEX_H

#include <fstream>
#include <string>
#include <vector>

#include "Data.h"



/*
MAXNODE is the maximum number of keys in B+ tree nodes
MAXSPACES is the spaces needed to write a node to Index
MAXSPACES:
> state of node (leaf or not leaf)
> number of keys available in this node
> keys * n times
> children * n+1 times
> value.offset * n times
> value.length * n times
> positon of next node
*/
const int MAXNODE = 100;
const int MAXSPACES = (MAXNODE * 4 + 4) * 4 + 1;

class BPNode
{
    private:
        int leaf = 1; // 1 if node is leaf node, 0 otherwise
        int positionInFile = -1; // -1 if position no yet determined, real positive number otherwise. It will be proportionate with position of this node in index file
        int noOfKeys = 0; // number of keys available in this node
    
    public:
        // These elements are put in public so that index.cpp can use them to write into index file
        std::vector<int> keys; // list of keys in this node
        std::vector<Data> value; // information of value pointed by the key
        std::vector<int> children; // position of children nodes
        int nextNode = -1; // linked list of leaves
        
        BPNode() {};
        
        int isLeaf(); // checks whether node is leaf node
        void setIsLeaf(int state); // sets the node to be leaf of not
        int getPosition(); // return position of this node in index file
        void setPosition(int setter); // sets this node's position
        bool hasKey(int key); // checks if key is available in this node
        int searchKey(int key); // return index of key position if available
        void insertKey(int key, int offset, int length, int childPosition); // inserts new key into this node
        std::vector<int> removeKey(int key); // removes key from this node
        int getNoOfKeys(); // return the number of keys in this node
        void setNoOfKeys(int number); // sets the number of keys in this node
        bool isOverflow(); // checks whether the node has been filled
};

class Index
{
    private:
        std::fstream file; // used for read, modify, close file
        int rootPosition = -1; // note the starting position of root in index file
        bool empty = true; // state of index file
        std::vector<BPNode> reserved; // store changed nodes for rewrite

    public:
        Index() {};

        std::vector<BPNode> parents; // store parents of node for better overflow management

        void open(std::string filePath, int method); // open an index file and read its content
        void close(); // close an index file
        BPNode searchKey(int key); // search the appropriate node that will contain a key and return
        BPNode searchWithInsertKey(int key); // search the appropriate node that will contain a key and return while filling path
        BPNode getKey(int position); // get the node from index file
        bool hasKey(int key, BPNode& obj); // determine if the node has key
        bool isEmpty(); // determine if index file is empty
        void writeRoot(); // write into root position
        int writeNode(BPNode& obj); // write a node into index file
        void insertKey(int key, int valuePosition, int length, int childPosition, BPNode& obj); // insert new key-value data into this program
        std::vector<int> removeKey(int key, BPNode& obj); // remove a key from a node and write to index file
        void overflow(BPNode& obj); // take care of overflow
        void reload(); // rewrite changed nodes stored in reserved
};



#endif