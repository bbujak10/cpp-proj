#include "myStack.hpp"
template <class T>
CMyStack::CMyStack(int stackSize):iSize(stackSize){ 
    tStack = new T[iSize];
}


int main(){
    CMyStack c(5);
}