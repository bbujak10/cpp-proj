#ifndef controller_hpp
#define controller_hpp

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "matrix.hpp"

using namespace std;

class CSparseController{
    public:
    ~CSparseController();

    int getDim(int matOff);

    /*void addMat();
    void addMat(string name);*/
    void addMat(int dim, int* range, int defVal);
    void addMat(int dim, int* range, int defVal, string name);

    int del(int matOff); //-1:matrixOOB
    void delAll();

    int def(int matOff, int* coord, int val);//0:OK -1:matrixOOB -2:coordOOB

    string print(int matOff);

    string list();

    int rename(int matOff, string newName);//-1:matrixOOB

    int clone(int matOff);//-1:matrixOOB

    private:
    vector<CSparseMatrix*> ctMatrixes;
};

#endif 