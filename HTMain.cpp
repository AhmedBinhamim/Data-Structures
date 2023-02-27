#include <iostream>
#include "HashTable.cpp"
#include <fstream>
#include <chrono> // c++11
#include <cstdlib> // This line is required in Code:: Blocks 13.12.


int main(){

    char set;
    //Getting the desired set from the user
    while (true)
    {
        cout <<"Enter The Set Letter: ";
        cin >> set;
        set=tolower(set);

        if (set == 'a' || set == 'b' || set == 'c')
            break;
        else
            cout <<"Wrong Set Detected, Please Enter either 'A/a','B/b','C/c'"<<endl;
    }

    int hashTableSize;
    string targetFile;
    //Getting size of hash table & file to read from
    if (set == 'a')
    {
        hashTableSize = 90;
        targetFile = "setA.txt";
    }
    else if (set == 'b')
    {
        hashTableSize = 900000;
        targetFile = "setB.txt";
    }
    else
    {
        hashTableSize = 4500000;
        targetFile = "setC.txt";
    }

    HashTable<string> hashTable(hashTableSize);

    //Reading emails from txt file and inserting them into the Hashtable
    ifstream txtFile(targetFile);
    string email;

    auto startTime = chrono::system_clock::now();
    while (getline(txtFile,email))
        hashTable.insert(email);
    auto endTime = chrono::system_clock::now();
    chrono::duration<double> duration = endTime - startTime;
    //cout << hashTable << endl;     //Displaying the Hashtable
    cout<<"Time taken to insert emails into the Hashtable: "<<duration.count() << "s\n";
    cout << hashTable << endl;

    //Testing the search data
    string targetEmail;
    txtFile.open("setFound.txt");

    startTime = chrono::system_clock::now();
    while(getline(txtFile, targetEmail))
        hashTable.retrieve(targetEmail);

    endTime = chrono::system_clock::now();
    duration = endTime - startTime;
    cout <<"Time taken to search for found data: "<<duration.count() <<"s"<<endl;
    txtFile.close();

    txtFile.open("setNotFound.txt");
    startTime = chrono::system_clock::now();
    while(getline(txtFile, targetEmail))
        hashTable.retrieve(targetEmail);

    endTime = chrono::system_clock::now();
    duration = endTime - startTime;
    cout <<"Time taken to search for not found data: "<<duration.count() <<"s"<<endl;
    txtFile.close();

    //Searching for  a specific email
    // cout<<"Enter an email to see if it is in the Hashtable: ";
    // cin >> targetEmail;
    // startTime = chrono::system_clock::now();

    // if(hashTable.retrieve(targetEmail))
    //     cout<< "The email exists in the Hashtable"<<endl;
    // else
    //     cout<<"The email does not exist in the Hashtable"<<endl;

    // endTime = chrono::system_clock::now();
    // duration = endTime - startTime;
    // cout <<"Time taken to search for the email: "<<duration.count() <<"s\n"<<endl;

    //Asking User if they want to restart or terminate program
    while (true){
        int choice;
        cout<<"Enter 1 to restart the program "<<endl;
        cout<<"Enter any other key to terminate the program "<<endl;
        cout<<"=> ";
        cin >> choice;

        if(choice ==1)
            main();
        else
            break;
    }
    return 0;
}
