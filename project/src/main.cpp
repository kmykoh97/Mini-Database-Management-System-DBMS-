//============================================================================
// Name        : main.cpp
// Author      : Meng Yit Koh
// Version     :
// Copyright   : 
// Description : Mini Database Management System (DBMS)
//============================================================================

#include <iostream>
#include <vector>
#include <string>

#include "DBMS.h"



using namespace std;

int printChoice()
{
    int choice;

    while (true) {
        cout << "Please select an option: " << endl;
        cout << "1. Save" << endl;
        cout << "2. Search" << endl;
        cout << "3. Search keys with given range" << endl;
		cout << "4. Search values with given range" << endl;
        cout << "5. Modify" << endl;
        cout << "6. Delete" << endl;
        cout << "7. Exit program" << endl;

        cout << "> ";
        cin >> choice;
        cout << endl;

        if (choice < 1 || choice > 7) {
            cout << "Invalid choice. Please choose again!" << endl;
            continue;
        }

        break;
    }

    return choice;
}

bool check(const int &number)
{
    // ensure int is in int range to be representable by 4 bytes
    if (number > 2000000000 || number < -2000000000) { // int range = [-2147483648, 2147483647]
        return false;
    }

    return true;
}

void startProgram(DBMS& program)
{
    int choice;

	while (true) {
		choice = printChoice();

    	switch (choice) {
    	    case 1:
    	        {
    	            int key;
    	            string value;
					
    	            while (true) {
    	                cout << "Please insert key: ";
    	                cin >> key;
    	                if (check(key)) {
    	                    break;
    	                } else {
    	                    cout << "Wrong input. Please reenter: " << endl;
    	                }
    	            }

    	            cout << "Please enter value: ";
    	            cin >> value;

    	            if (program.insertDB(key, value)) {
    	                cout << "Success!" << endl;
    	            } else {
    	                cout << "Key is alraedy available. Fail!" << endl;
    	            }

    	            break;
    	        }
    	    case 2:
    	        {
    	            int key;
    	            string result;

    	            while (true) {
    	                cout << "Please enter key: ";
    	                cin >> key;
    	                if (check(key)) {
    	                    break;
    	                } else {
    	                    cout << "Invalid key. Please reenter!" << endl;
    	                }
    	            }

    	            result = program.getDB(key);
    	            if (result != "Invalid key!") {
    	                cout << "Value is: " << result << endl;
    	            } else {
    	                cout << result << endl;
    	            }

    	            break;
    	        }
    	    case 3:
    	        {
    	            int key1;
    	            int key2;
    	            vector<int> result;

    	            while (true) {
    	                cout << "Please enter key 1: ";
    	                cin >> key1;
    	                if (check(key1)) {
    	                    break;
    	                } else {
    	                    cout << "Invalid key. Please reenter!" << endl;
    	                }
    	            }

    	            while (true) {
    	                cout << "Please enter key 2: ";
    	                cin >> key2;
    	                if (check(key2)) {
    	                    break;
    	                } else {
    	                    cout << "Invalid key. Please reenter!" << endl;
    	                }
    	            }

    	            result = program.getRangeDB(key1, key2);
    	            for (int i = 0; i < result.size(); i++) {
					    cout << result[i] << endl;
				    }

				    break;
    	        }
			case 4:
				{
					int key1;
    	            int key2;
    	            vector<int> result;

    	            while (true) {
    	                cout << "Please enter key 1: ";
    	                cin >> key1;
    	                if (check(key1)) {
    	                    break;
    	                } else {
    	                    cout << "Invalid key. Please reenter!" << endl;
    	                }
    	            }

    	            while (true) {
    	                cout << "Please enter key 2: ";
    	                cin >> key2;
    	                if (check(key2)) {
    	                    break;
    	                } else {
    	                    cout << "Invalid key. Please reenter!" << endl;
    	                }
    	            }

    	            result = program.getRangeDB(key1, key2);
					
					for (int i = 0; i < result.size(); i++) {
						cout << program.getDB(result[i]) << endl;
					}

					break;
				}
    	    case 5:
    	        {
    	            int key;
    	            string newValue;

    	            while (true) {
    	                cout << "Please enter key: ";
    	                cin >> key;
    	                if (check(key)) {
    	                    break;
    	                } else {
    	                    cout << "Invalid key. Please reenter!" << endl;
    	                }
    	            }

    	            cout << "Please enter new value: ";
    	            cin >> newValue;
    	            if (program.changeDB(key, newValue)) {
    	                cout << "Modified success!" << endl;
    	            } else {
    	                cout << "Failure!" << endl;
    	            }

    	            break;
    	        }
    	    case 6:
    	        {
    	            int key;

    	            while (true) {
    	                cout << "Please enter key: ";
    	                cin >> key;
    	                if (check(key)) {
    	                    break;
    	                } else {
    	                    cout << "Invalid key. Please reenter!" << endl;
    	                }
    	            }

    	            if (program.deleteDB(key)) {
    	                cout << "Delete success!" << endl;
    	            } else {
    	                cout << "No such key!" << endl;
    	            }

    	            break;
    	        }
    	    case 7:
    	        return;
			default:
				break;
    	}
	}
}

int main()
{
    DBMS program(""); // initiate API to database management system
    int choice;

    while (true) {
        cout << "This is a mini Database Management System. It can store key and value in an efficient way using multilevel B+ tree indexing. \nPlease select: \n1. Create \n2. Open existing \n3. Description of DBMS \n4. Exit" << endl;
        cout << "> ";
        cin >> choice;
        cout << endl;
        if (choice < 1 || choice > 2) {
            cout << "Invalid choice. Please choose again!" << endl;
            continue;
        }

        break;
    }

    switch (choice) {
        case 1:
			program.openDB(0);
			program.closeDB();
			program.openDB(1);
            startProgram(program);
            break;
		case 2:
			program.openDB(1);
			startProgram(program);
			break;
        case 3:
            cout << "This should be helping statement" << endl;
            cout << "exiting..." << endl;
            break;
        case 4:
            cout << "Thank you for using me. Hope you enjoy!" << endl;
            cout << "exiting..." << endl;
            break;
    }

    system("PAUSE");
    return 0;
}