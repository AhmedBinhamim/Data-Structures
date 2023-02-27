#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <chrono>

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
    ofstream file_a, file_b, file_c;

    file_a.open("setA.txt");
    file_b.open("setB.txt");
    file_c.open("setC.txt");

    // Write the first 100 data to all three files
    cout << "Set A Data: " << endl;
    auto startTime = chrono::system_clock::now();
    for (int i = 0; i < 100; i++)
    {
        data = gen_random();
        file_a << data << endl;
        file_b << data << endl;
        file_c << data << endl;
        cout << data << endl;
    }
    auto endTime = chrono::system_clock::now();
    chrono::duration<double> durationTime = endTime - startTime;
    cout << "Time to Generate Set A: " << durationTime.count() << " sec\n" << endl;

    // Write the second 99900 data to file saving set B and file saving set C 
    cout << "Set B Last 20 Data: " << endl;
    startTime = chrono::system_clock::now();
    for (int i = 100; i < 1000000; i++)
    {
        data = gen_random();
        file_b << data << endl;
        file_c << data << endl;
        if (i >= 999980)
            cout << data << endl;
    }
    endTime = chrono::system_clock::now();
    durationTime = endTime - startTime;
    cout << "Time to Generate Set B: " << durationTime.count() << " sec\n" << endl;

    // Write the last 4000000 data to file saving set C
    cout << "Set C Last 20 Data: " << endl;
    startTime = chrono::system_clock::now();
    for (int i = 1000000; i < 5000000; i++)
    {
        data = gen_random();
        file_c << data << endl;
        if (i >= 4999980)
            cout << data << endl;
    }
    endTime = chrono::system_clock::now();
    durationTime = endTime - startTime;
    cout << "Time to Generate Set C: " << durationTime.count() << " sec\n" << endl;

    file_a.close();
    file_b.close();
    file_c.close();

    return 0;
}
