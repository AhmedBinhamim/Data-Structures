#include <iostream>
#include <fstream>
#include <chrono>
#include "AVL.cpp"
using namespace std;

string getDataSetChoice()
{
    string set, dataFileName;

    while (true) {
        cout<< "Enter Data Set Letter (A/B/C): ";
        cin >> set;
        set[0] = toupper(set[0]);
        if (set[0] == 'A' ||  set[0] == 'B' || set[0] == 'C')
            break;
        else
          cout << "\nNo Such Data Set Exist Please Choose From (A/B/C)\n" << endl;
    }

    if (set[0] == 'A')
        dataFileName = "setA.txt";
    else if (set[0] == 'B')
        dataFileName = "setB.txt";
    else
        dataFileName = "setC.txt";

    return dataFileName;
}

int main()
{
    string choice, data, dataFileName, target;
    ifstream dataFile;
    AVL tree;

    while (true)
    {
        cout << "1. Insert Data Set Into AVL Tree" << endl;
        cout << "2. Delete Data Set From AVL" << endl;
        cout << "3. Search Data in AVL" << endl;
        cout << "4. Dequeue 10% of the data" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your Choice ==> ";
        cin >> choice;
        switch (choice[0]) //perform switch operation
        {
            case '1':
            {
                tree.root = NULL;
                dataFileName = getDataSetChoice();
                dataFile.open(dataFileName);
                auto startTime = chrono::system_clock::now();
                while(getline(dataFile, data))
                    tree.root = tree.insert(tree.root, data);
                auto endTime = chrono::system_clock::now();
                chrono::duration<double> duration = endTime - startTime;
                dataFile.close();
                cout << "Time To Insert Data Into AVL: " << duration.count() << " sec\n" << endl;
                tree.inOrder();
                break;
            }
            case '2':
            {
                cout << "Enter target to delete: ";
                cin >> target;
                auto startTime = chrono::system_clock::now();
                tree.root = tree.deleteItem(tree.root, target);
                auto endTime = chrono::system_clock::now();
                chrono::duration<double> duration = endTime - startTime;
                cout << "Time To Delete Target: " << duration.count() << " sec\n" << endl;
                tree.inOrder();
                break;
            }
            case '3':
            {
                dataFile.open("setFound.txt");
                auto startTime = chrono::system_clock::now();
                while(getline(dataFile, data))
                    tree.search(tree.root, data);
                auto endTime = chrono::system_clock::now();
                chrono::duration<double> duration = endTime - startTime;
                cout << "Search Process For Found Data Ended In: " << duration.count() * 1000000 << " us" << endl;
                dataFile.close();

                dataFile.open("setNotFound.txt");
                startTime = chrono::system_clock::now();
                while(getline(dataFile, data))
                    tree.search(tree.root, data);
                endTime = chrono::system_clock::now();
                duration = endTime - startTime;
                cout << "Search Process For Not Found Data Ended In: " << duration.count() * 1000000 << " us\n" << endl;
                dataFile.close();
                break;
            }
            case '4':
            {
                tree.maxOrder();
                int numOfElements = tree.emails.size() * 10/100;
                auto startTime = chrono::system_clock::now();
                for (int i = 0; i < numOfElements; i++)
                    tree.root = tree.dequeue(tree.root);
                auto endTime = chrono::system_clock::now();
                chrono::duration<double> duration = endTime - startTime;
                cout << "Time To Dequeue 10% of the data: " << duration.count() << " sec\n" << endl;
                tree.maxOrder();
                break;
            }
            case '5':
                exit(1);
                break;
            default:
                cout << "\nUnsupported Option, Please Choose Again\n" << endl;
        }
    }

    return 0;
}
