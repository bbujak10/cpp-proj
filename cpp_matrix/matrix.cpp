#include "matrix.hpp"

CSparseCell::CSparseCell(int* coord, int val, int dim){
    iVal = val;
    iCoordSize = dim;
    itCoord = new int[dim];
    for(int i=0; i<dim; i++){
        itCoord[i] = coord[i];
    }

    cout << "create: cell\n";
}

CSparseCell::CSparseCell(CSparseCell &pcOther){
    iVal = pcOther.iVal;
    iCoordSize = pcOther.iCoordSize;
    itCoord = new int[iCoordSize];
    for(int i=0; i<iCoordSize; i++){
        itCoord[i] = pcOther.itCoord[i];
    }
}

CSparseCell::~CSparseCell(){
    delete[] itCoord;

    cout << "destroy: cell\n";
}

string CSparseCell::toString(){
    ostringstream s;
    s <<"[";;
    for(int i=0; i<iCoordSize; i++)
        s << (i==0?"":", ") << itCoord[i];
    s << "]:" << iVal;
    return s.str();
}

/*
CSPARSE MATRIX
*/

CSparseMatrix::CSparseMatrix(){
    int t[DEF_DIM];
    for(int i=0; i<DEF_DIM; i++) t[i] = DEF_RAN;
    init(DEF_DIM, t, DEF_VAL, DEF_NAME);
}
CSparseMatrix::CSparseMatrix(string name){
    int t[DEF_DIM];
    for(int i=0; i<DEF_DIM; i++) t[i] = DEF_RAN;
    init(DEF_DIM, t, DEF_VAL, name);
}
CSparseMatrix::CSparseMatrix(int dim, int* range, int defVal){
    init(dim, range, defVal, DEF_NAME);
}
CSparseMatrix::CSparseMatrix(int dim, int* range, int defVal, string name){
    init(dim, range, defVal, name);
}
//C++11: CSparseMatrix::CSparseMatrix() : CSparseMatrix(DEF_DIM, DEF_RAN, DEF_VAL, DEF_NAME){}
CSparseMatrix::CSparseMatrix(CSparseMatrix &pcOther){
    init(pcOther.iDim, pcOther.itRange, pcOther.iDefVal, pcOther.sName+"_copy");
    for(int i = 0; i < pcOther.iCellsLength; i++){
        addCell(*(pcOther.ctCells[i]));
    }
}

CSparseMatrix::~CSparseMatrix(){
    delete[] itRange;
    for(int i=0; i<iCellsLength; i++){
        delete ctCells[i];
    }
    delete[] ctCells;
    cout << "destroy: " << sName << "\n";
}

void CSparseMatrix::init(int dim, int* range, int defVal, string name){
    iDim = dim;
    itRange = new int[iDim];
    for(int i=0; i<iDim; i++){
        itRange[i] = range[i];
    }
    iDefVal = defVal;
    sName = name;

    iCellsLength = 0;
    iCellsRealLength = 2;
    ctCells = new CSparseCell*[iCellsRealLength];

    cout << "create: " << sName << "\n";
}

int CSparseMatrix::operator=(CSparseMatrix &pcOther){
    if(&pcOther != this){
        if(iDim == pcOther.iDim){
            for(int i=0; i<iDim; i++)
                if(itRange[i] != pcOther.itRange[i]) return -1;
        }
        else return -1;
        
        for(int i=0; i<iCellsLength; i++){
            delete ctCells[i];
        }
        while(iCellsRealLength < pcOther.iCellsRealLength){
            enlargeArray();
        }
        iCellsLength = 0;
        for(int i=0; i<pcOther.iCellsLength; i++){
            addCell(pcOther.ctCells[i]->itCoord, pcOther.ctCells[i]->iVal);
        }
    }
    else return -2;
    return 0;
}

void CSparseMatrix::setName(string name){sName = name;}
string CSparseMatrix::getName(){return sName;}
int CSparseMatrix::getDim(){return iDim;}
void CSparseMatrix::setDefVal(int defVal){if(iCellsLength==0) iDefVal=defVal;}

void CSparseMatrix::enlargeArray(){
    CSparseCell** temp = new CSparseCell*[iCellsRealLength*2];
    for(int i=0; i<iCellsRealLength; i++){
        temp[i] = ctCells[i];
    }
    iCellsRealLength = iCellsRealLength*2;
    delete ctCells;
    ctCells = temp;
}
void CSparseMatrix::shrinkArray(){
    CSparseCell** temp = new CSparseCell*[iCellsRealLength/2];
    for(int i=0; i<iCellsLength; i++){
        temp[i] = ctCells[i];
    }
    iCellsRealLength = iCellsRealLength/2;
    delete ctCells;
    ctCells = temp;
}

int CSparseMatrix::findCellByCoord(int* coord){
    int found = -1;
    int i = 0;
    while(found == -1 && i<iCellsLength){
        int j = 0;
        bool match = true;
        while(match == true && j<iDim){
            if(ctCells[i]->itCoord[j] != coord[j]) match = false;
            j++;
        }
        if(match == true) found = i;
        i++;
    }

    return found;
}

void CSparseMatrix::delCell(int id){
    delete ctCells[id];
    for(int i = id; i<iCellsLength-1; i++){
        ctCells[i] = ctCells[i+1];
    }
    iCellsLength--;
    if((iCellsRealLength/2)>iCellsLength){
        shrinkArray();
    }
}

void CSparseMatrix::addCell(int* coord, int val){
    if(iCellsLength == iCellsRealLength) enlargeArray();
    ctCells[iCellsLength] = new CSparseCell(coord, val, iDim);
    iCellsLength = iCellsLength+1;
}
void CSparseMatrix::addCell(CSparseCell& pcOther){
    if(iCellsLength == iCellsRealLength) enlargeArray();
    ctCells[iCellsLength] = new CSparseCell(pcOther);
    iCellsLength = iCellsLength+1;
}
int CSparseMatrix::defCell(int* coord, int val){
    int outOfBounds = 0;
    for(int i=0; i<iDim; i++){
        if(coord[i] >= itRange[i]) outOfBounds = -2;
    }
    if(outOfBounds != -2){
        int found = findCellByCoord(coord);
        if(found != -1){
            if(val == iDefVal) delCell(found);
            else ctCells[found]->iVal = val;
        }
        else{
            if(val != iDefVal){
                addCell(coord, val);
            }
        }
    }
    return outOfBounds;
}

int CSparseMatrix::readCell(int* coord){
    for(int i=0; i<iDim; i++){
        if(coord[i] >= itRange[i]) return -1;
    }
    int found = findCellByCoord(coord);
    if(found == -1) return iDefVal;
    return ctCells[found]->iVal;
}

string CSparseMatrix::info(){
    ostringstream s;
    s << "\"" << sName << "\" size: " <<"[";;
    for(int i=0; i<iDim; i++)
        s << (i==0?"":", ") << itRange[i];
    s << "]";
    return s.str();
}

void CSparseMatrix::printHelper(int* t, int pos, ostringstream& s){
    if(pos>=0){
        if(t[pos] < itRange[pos] && pos==(iDim-1)){
            s <<" [";;
            for(int i=0; i<iDim; i++)
                s << (i==0?"":", ") << t[i];
            s << "]:" << readCell(t);
            t[pos] = t[pos]+1;
        }
        else if(t[pos] == itRange[pos]){
            t[pos] = 0;
            pos--;
        }
        else{
            if(t[pos]+1 < itRange[pos]){
                t[pos] = t[pos]+1;
                pos++;
            }
            else{
                t[pos] = 0;
                pos--;
            }
        }
        printHelper(t,pos,s);
    }
}

string CSparseMatrix::printM(){
    int t[iDim];
    for(int i =0;i<iDim;i++){
        t[i] = 0;
    }
    ostringstream s;
    s << info() << " values:";
    printHelper(t, iDim-1, s);
    s << endl;
    return s.str();
}

string CSparseMatrix::toString(){
    ostringstream s;
    s << info();
    s << " values: ";
    for(int i=0; i<iCellsLength; i++){
        s << (i==0?"":"; ") << ctCells[i]->toString();
    }
    s << "\n";
    return s.str();
}
