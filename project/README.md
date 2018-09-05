# Mini Database

## Reimplementation of key-value database management system(DBMS) using B+ tree indexing

### C++ files functionalities
```
main.cpp
	Main connection and interface for Database.
DBMS.h
	Some useful and often used API for Database.
	Used to connect difficultly understandable classes in other modules.
	Main entrance to Index and Data query.
	Implementation in DBMS.cpp
Index.h
	To store index and enable multi-level indexing based on BPNode.
	Adapt the idea of B+ tree.
	Backbone for pointer search to get value’s offset.
	Implementation in Index.cpp
DataFile.h
	To store values and give position of disk’s offset to Index to save location.
	Gather extra unwanted spaces for use by extra data.
	Implementation in DataFile.cpp
Data.h
	Small structure to store offset and length of values for storage later.
	Helps DataFile to gather rubbish spaces for later use.
	Implementation in Data.cpp
```

### Important DBMS.h API
```
> void openDB(int method); // do requireinitialization to open index and data files
> void closeDB(); // do required ending procedures
> bool insertDB(int key, std::string value); // insert key-value data into this database
> bool changeDB(int key, std::string newValue); // change value of a value based on key given
> bool deleteDB(int key); // delete unwanted data
> std::string getDB(int key); // search for data
> std::vector<int> getRangeDB(int key1, int key2); // search for range of keys

```

### char and int size
```
int = 4
char = 1
```

### Index file saving sequence
```
> state of current node (leaf of not)  
> number of available keys in current node  
> key  
> children  
> value.position  
> value.length  
> position of next node in file
```

### Data file saving sequence  
```
> offset
> length
```

### Efficiency
According to test, functionalities run in O(log(n)) complexity  
Please refer to Documentation to see the test methods and results

Meng Yit Koh  
kmykoh97@gmail.com   
Shanghai Jiao Tong University  