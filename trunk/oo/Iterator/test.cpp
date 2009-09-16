#include <iostream>
#include <vector>

using namespace std;

class Observer {

  void Update() {};

};


main() {
vector<Observer*> *myIntVector;
vector<Observer*>::iterator myIntVectorIterator;


 myIntVectorIterator = myIntVector->begin();




for(myIntVectorIterator = myIntVector->begin(); 
        myIntVectorIterator != myIntVector->end();
        myIntVectorIterator++)
{
#if 0
    cout<<*myIntVectorIterator<<" ";
    //Should output 1 4 8
#endif
}


}
