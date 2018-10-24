#include "controller.hpp"

CSparseController::~CSparseController(){
    for(int i=0; i<ctMatrixes.size(); i++){delete ctMatrixes[i];}
}

int CSparseController::getDim(int matOff){
    if(matOff >= ctMatrixes.size()) return -1;
    return ctMatrixes[matOff]->getDim();
}

/*void CSparseController::addMat(){
    ctMatrixes.push_back(new CSparseMatrix());
}
void CSparseController::addMat(string name){
    ctMatrixes.push_back(new CSparseMatrix(name));
}*/
void CSparseController::addMat(int dim, int* range, int defVal){
    ctMatrixes.push_back(new CSparseMatrix(dim, range, defVal));
}
void CSparseController::addMat(int dim, int* range, int defVal, string name){
    ctMatrixes.push_back(new CSparseMatrix(dim, range, defVal, name));
}

int CSparseController::del(int matOff){
    if(matOff >= ctMatrixes.size()) return -1;
    delete ctMatrixes[matOff];
    ctMatrixes.erase(ctMatrixes.begin()+matOff);
    return 0;
}

void CSparseController::delAll(){
    while(ctMatrixes.size() != 0){
        del(ctMatrixes.size()-1);
    }
}

int CSparseController::def(int matOff, int* coord, int val){
    if(matOff >= ctMatrixes.size()) return -1;
    return ctMatrixes[matOff]->defCell(coord, val);
}

string CSparseController::list(){
    ostringstream s;
    s << ctMatrixes.size() << " matrices:\n";
    for(int i=0; i<ctMatrixes.size(); i++){
        s << "[" << i << "] - "<< ctMatrixes[i]->info() << "\n";
    }
    return s.str();
}

string CSparseController::print(int matOff){
    if(matOff >= ctMatrixes.size()) return "Error: matrix index out of bounds\n";
    return ctMatrixes[matOff]->printM();
}

int CSparseController::rename(int matOff, string newName){
    if(matOff >= ctMatrixes.size()) return -1;
    ctMatrixes[matOff]->setName(newName);
    return 0;
}

int CSparseController::clone(int matOff){
    if(matOff >= ctMatrixes.size()) return -1;
    ctMatrixes.push_back(new CSparseMatrix(*(ctMatrixes[matOff])));
    return 0;
}
