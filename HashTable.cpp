// HashTable.cpp
#include <vector>
#include "LinkedList.cpp"

template <typename T>
class HashTable {
  vector< LinkedList<T> > hashTable;
  int hashfunction (string email) { // hash function
    int hashVal = 0;
    for (int i =0; i<email.length();i++){
      hashVal = (hashVal << 5) + email[i];
    }
    return hashVal % hashTable.size();
  }
 public:
  HashTable (int size) {
    hashTable.resize (size); // resize vector to support size elements.
  }
  ~HashTable() {
    for (int i = 0; i < hashTable.size(); i++)
      hashTable[i].makeEmpty();
  }
  int size() {
    return hashTable.size();
  }

  void insert (T newEmail) {
    int hashKey = hashfunction(newEmail);
    hashTable[hashKey].insertFront(newEmail);
  }
  bool retrieve (T & target) {
    int hashKey = hashfunction(target);
    return hashTable[hashKey].find(target);
  }
  friend ostream& operator<< (ostream& os, HashTable<T>& ht) {
    for (int i = 0; i < 20; i++)
      os << i << " = " << ht.hashTable[i] << endl;
    return os;
  }
};
