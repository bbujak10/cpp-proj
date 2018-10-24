#ifndef matrix_hpp
#define matrix_hpp
#define DEF_VAL 0
#define DEF_DIM 2
#define DEF_RAN 5
#define DEF_NAME "def_name"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class CSparseCell{
    friend class CSparseMatrix;
    public:
    CSparseCell(int* coord, int val, int dim);
    CSparseCell(CSparseCell &pcOther);
    ~CSparseCell();

    string toString();

    private:
    int iCoordSize;
    int* itCoord;
    int iVal;
};

class CSparseMatrix{
    public:
    CSparseMatrix();
    CSparseMatrix(string name);
    CSparseMatrix(int dim, int* range, int defVal);
    CSparseMatrix(int dim, int* range, int defVal, string name);

    CSparseMatrix(CSparseMatrix &pcOther);

    ~CSparseMatrix();

    void init(int dim, int* range, int defVal, string name);

    //przypisanie tablicy z innego obiektu - jezeli wymiary i zakresy sa rowne
    int operator=(CSparseMatrix &pcOther);//-2:pcOther==this -1:dim/range dont match

    //gettery/settery
    void setName(string name);
    string getName();
    int getDim();
    void setDefVal(int defVal);

    //zarzadzanie tablicami
    void enlargeArray();
    void shrinkArray();

    int findCellByCoord(int* coord);//-1:not found
    void delCell(int id);
    void addCell(int* coord, int val);
    void addCell(CSparseCell &pcOther);
    int defCell(int* coord, int val);//-2:index out of bounds
    int readCell(int* coord);//-1:index out of bounds

    void printHelper(int* t, int pos, ostringstream& s);
    string printM();

    string toString();
    string info();

    private:
    int iDim;
    int *itRange;
    int iDefVal;
    string sName;

    int iCellsLength;       //uzywany rozmiar
    int iCellsRealLength;   //rzeczywisty rozmiar
    CSparseCell **ctCells;
};
#endif