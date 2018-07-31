/*
Implementation of diffirent test methods based directly on DBMS.h API
*/
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

#include "DBMS.h"



using namespace std;

/*
// insert test
int main() {
    clock_t begin, end;
    double time_spent;
    begin = clock();

    DBMS test("");
    test.openDB(0);
    test.closeDB();
    test.openDB(1);
    
    vector<string> samples;
    samples.push_back("ioveu");
    samples.push_back("fu");
    samples.push_back("hi there!@#$\%^&*()_+");
    samples.push_back("haha");
    samples.push_back("Ratatouie");
    samples.push_back("This is a testing sample!!");

    int counter = 100000;
    while (counter != 0) {
        test.insertDB(counter, samples[rand()%(samples.size()-1)]);
        counter--;
    }

    test.closeDB();

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "timespent is: " << time_spent << endl;


    system("pause");
    return 0;
}
*/

/*
// deletion
int main()
{
    clock_t begin, end;
    double time_spent;
    begin = clock();

    DBMS test("");
    test.openDB(0);
    test.closeDB();
    test.openDB(1);

    int counter = 100000;
    while (counter != 0) {
        test.deleteDB(counter);
        counter--;
    }
    
    // cout << "size of range vector is: " << test.getRangeDB(0, 1000000)[0] << endl;

    test.closeDB();

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "timespent is: " << time_spent << endl;


    system("pause");
    return 0;
}
*/



/*
// search
int main() {
    // clock_t begin, end;
    // double time_spent;
    // begin = clock();

    DBMS test("");
    test.openDB(0);
    test.closeDB();
    test.openDB(1);

    int counter = 100000;
    while (counter != 0) {
        test.insertDB(counter, "unchanged");
        counter--;
    }

    clock_t begin, end;
    double time_spent;
    begin = clock();

    int counter2 = 100000;
    while (counter2 != 0) {
        test.changeDB(counter2, "changed info");
        counter2--;
    }

    test.closeDB();

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "timespent is: " << time_spent << endl;


    system("pause");
    return 0;
}
*/

// truth testing
int main() {
    clock_t begin, end;
    double time_spent;
    begin = clock();

    DBMS test("");
    test.openDB(0);
    test.closeDB();
    test.openDB(1);

    int counter = 1000;
    while (counter != 0) {
        test.insertDB(counter, "unchanged");
        counter--;
    }

    // clock_t begin, end;
    // double time_spent;
    // begin = clock();

    // int counter2 = 1000;
    // while (counter2 != 0) {
    //     test.changeDB(counter2, "changed info");
    //     counter2--;
    // }

    int counter3 = 50;
    while (counter3 != 0) {
        test.deleteDB(rand()%1000);
        counter3--;
    }

    test.changeDB(1, "a");
    test.changeDB(2, "b");
    test.changeDB(3, "c");
    test.changeDB(4, "d");
    test.changeDB(5, "e");
    test.changeDB(6, "f");
    test.changeDB(7, "g");
    test.changeDB(8, "h");
    test.changeDB(9, "i");
    test.changeDB(10, "j");
    vector<string> use;
    use.push_back("test");
    use.push_back("a");
    use.push_back("b");
    use.push_back("c");
    use.push_back("d");
    use.push_back("e");
    use.push_back("f");
    use.push_back("g");
    use.push_back("h");
    use.push_back("i");
    use.push_back("j");

    for (int i = 1; i <= 10; i++) {
        cout << test.getDB(i) << " && " << use[i] << endl;
        if (test.getDB(i) == use[i]) {
            cout << "same!" << endl;
        } else {
            cout << "different!" << endl;
        }
    }

    test.closeDB();

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "timespent is: " << time_spent << endl;


    system("pause");
    return 0;
}