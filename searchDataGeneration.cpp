#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <chrono>
#include "AVL.cpp"

using namespace std;

// Generates random email based on given specific format
string gen_random() {

    string email; // Stores the generated email
    static const string domain[] = {".com", ".net", ".my"};
    static const char alphanum[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789";

    // [A-Z]{3}
    for (int i = 0; i < 3; ++i)
        email += alphanum[rand() % 26];
    // .
    email += ".";
    // [A-Za-z0-9]{5}
    for (int i = 0; i < 5; ++i)
        email += alphanum[rand() % 62];
    // .
    email += ".";
    // [0-9]{5}
    for (int i = 0; i < 5; ++i)
        email += alphanum[(rand() % 10) + 52];
    // @
    email += "@";
    // [A-Za-z0-9]{4}
    for (int i = 0; i < 4; ++i)
        email += alphanum[rand() % 62];
    // .(com|net|my)
    email += domain[rand() % 3];

    return email;
}

int main() {

    string data;
    ifstream file;
    ofstream foundFile, notFoundFile;
    AVL treeA, treeB, treeC;

    // Create the first AVL Tree to store set A data
    file.open("setA.txt");
    auto startTime = chrono::system_clock::now();
    while(getline(file, data))
        treeA.root = treeA.insert(treeA.root, data);
    auto endTime = chrono::system_clock::now();
    chrono::duration<double> durationTime = endTime - startTime;
    cout << "Time to Insert Set A: " << durationTime.count() << " sec\n";
    file.close();

    // Create the second AVL Tree to store set B data
    file.open("setB.txt");
    startTime = chrono::system_clock::now();
    while(getline(file, data))
        treeB.root = treeB.insert(treeB.root, data);
    endTime = chrono::system_clock::now();
    durationTime = endTime - startTime;
    cout << "Time to Insert Set B: " << durationTime.count() << " sec\n";
    file.close();

    // Create the third AVL Tree to store set C data
    file.open("setC.txt");
    startTime = chrono::system_clock::now();
    while(getline(file, data))
        treeC.root = treeC.insert(treeC.root, data);
    endTime = chrono::system_clock::now();
    durationTime = endTime - startTime;
    cout << "Time to Insert Set C: " << durationTime.count() << " sec\n";
    file.close();

    // Generate 10 data found and 10 data not found
    int foundCount = 0;
    int notFoundCount = 0;
    foundFile.open("setFound.txt");
    notFoundFile.open("setNotFound.txt");
    startTime = chrono::system_clock::now();
    while(foundCount != 10 || notFoundCount != 10) {
        data = gen_random();    // Generate random data
        // Search the three trees for the generated data
        if (foundCount != 10 && treeA.search(treeA.root, data) && treeB.search(treeB.root, data) && treeC.search(treeC.root, data))
        {
            foundFile << data << endl; // Add the data to found set if founded in the three trees
            foundCount++;
        }
        if (notFoundCount != 10 && (!treeA.search(treeA.root, data) && !treeB.search(treeB.root, data) && !treeC.search(treeC.root, data)))
        {
            notFoundFile << data << endl; // Add the data to not found set if not founded in the three trees
            notFoundCount++;
        }
    }
    endTime = chrono::system_clock::now();
    durationTime = endTime - startTime;
    cout << "Time to Generate Search Data Sets: " << durationTime.count() << " sec\n";
    foundFile.close();
    notFoundFile.close();

    return 0;
}
