#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
//a
template <typename T>
void printArray (T A[], int n) {
  for (int i = 0; i < n; i++)
 cout << A[i] << " ";
  cout << endl;
}

template <typename T>
class PriorityQueue {
    vector<T> A;

    int priority(string txt)
    {
        int txtASCII_Sum = 0;

    for(int i = 0; i < txt.size(); i++)
    {
        txtASCII_Sum = txtASCII_Sum + txt[i];
    }

        return txtASCII_Sum;
    }

    void heapify_enqueue (int index) {   // used in enqueue.

    if (priority(A[parent(index)]) <  priority(A[index]))
        {
            swap(A[index], A[parent(index)]);
            heapify_enqueue(parent(index));
        }
    }

    int parent(int child){
        return (child - 1 )/2;
    }

    int RIGHT(int parent)
    {
        return (2*parent + 2);
    }
    int LEFT(int parent)
    {
        return (2*parent + 1);
    }

    void heapify_dequeue (int index) {   // used in dequeue.
    // get left and right child of node at index `i`
        int left = LEFT(index);
        int right = RIGHT(index);
        int largest = index;
        // compare `A[i]` with its left and right child
        // and find the largest value
        if (left < size() && priority(A[left]) > priority(A[index])) {
            largest = left;
        }

        if (right < size() && priority(A[right]) > priority(A[largest])) {
            largest = right;
        }

        // swap with a child having greater value and
        // call heapify-down on the child
        if (largest != index)
        {
            swap(A[index], A[largest]);
            heapify_dequeue(largest);
        }
    }

public:
    void enqueue (T element) {
        A.push_back (element);
        heapify_enqueue (A.size()-1);  // start at last element.
    }

    T dequeue() { // make this function return T if we want to return the dequeud element
        T removed_element = A[0];       // pick the root
        A[0] = A[A.size()-1];          // copy last element to root.
        A.pop_back();                 // remove last element.
        heapify_dequeue(0);           // start at root.
        return removed_element;
      }

    int size() {
        return A.size();
    }

    void print(){
        cout<<left<<setw(2)<<"index"<<setw(5)<<""<<setw(25)<<"Emails"<<"Priority"<<endl;
        for (int i = 0; i<20; i++)
          cout<<left<<setw(2)<<i<<setw(5)<<":"<<setw(30)<<A[i]<<priority(A[i])<<endl;
      }
};



