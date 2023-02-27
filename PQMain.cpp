#include <iostream>
#include <vector>
#include "PriorityQueue.cpp"
#include <fstream>
#include <chrono>

using namespace std;
int main () {
    char set;
    int priorityQueueSize;

    //get the specified set
    do{
        cout<< "Enter set (a, b, c): ";
        cin >> set;
        set=tolower(set);
        if (set == 'a' ||  set == 'b' || set == 'c')
          break;
        else
          cout <<"Please enter one of set(a, b, c)"<<endl;
    } while(true);
    string targetFile;
    if (set =='a'){
            priorityQueueSize = 100;
            targetFile = "setA.txt";
        }

    else if (set =='b'){
            priorityQueueSize = 1000000;
            targetFile = "setB.txt";
        }

    else{
            priorityQueueSize = 5000000;
            targetFile = "setC.txt";
        }
    //store all emails of set 'X' (a,b,c) emails array
	string* emails = new string[priorityQueueSize];
    ifstream file(targetFile);
    if (file.is_open()){
        string line;
        int lineNumber = 0;
        while (getline(file,line)){
            emails[lineNumber] = line;
            lineNumber++;
        }
        file.close();
  }

    PriorityQueue<string> priorityQueue;
    auto start = chrono::system_clock::now(); // start calculating time for enqueue operation
    for(int i = 0; i < priorityQueueSize; i++){
        priorityQueue.enqueue(emails[i]); //enqueue the elements to the priorityQueue
    }
    file.close();
    auto end = chrono::system_clock::now(); //stop calculating time for enqueue operation
    chrono::duration<double> duration = end - start; //calculate time taken
    cout << "Time taken to enqueue elements into Priority Queue: "<< duration.count() << "s\n";
    priorityQueue.print();

    int dequeueRate = priorityQueueSize*10/100;
    start = chrono::system_clock::now();
    for(int j = 0; j < dequeueRate;j++){
        if(j<=20)
            cout<<priorityQueue.dequeue()<<endl; //dequeue the elements of the priorityQueue
        else
            priorityQueue.dequeue();
    }
    cout<<endl;
    end = chrono::system_clock::now();
    duration = end - start;
    cout << "Time taken to dequeue: "<< duration.count() << "s\n";
    //priorityQueue.print();
    delete[] emails;

}








