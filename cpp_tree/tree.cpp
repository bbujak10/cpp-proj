#include "tree.hpp"

bool strToDouble(string &s, double &d){
    const char* str = s.c_str();
    char* endptr = 0;
    double temp = strtod(str, &endptr);

    if(*endptr != '\0' || endptr == str)
        return false;
    d = temp;
    return true;
}
int find(vector<string> &v, string &s){
    for(int i=0; i<v.size(); i++){
        if(v[i] == s) return i;
    }
    return -1;
}

//
//
//____________TREE______________
//
//


CTree::CTree(){
    pcRoot = NULL;
    //cout << "c: Tree\n";
}

CTree::CTree(CTree &pcOther){
    pcRoot = new CNode(*(pcOther.pcRoot));
}

CTree::~CTree(){
    delete pcRoot;
    //cout << "d: Tree\n";
}

CTree & CTree::operator=(CTree &pcOther){
    if (pcRoot != NULL)
        delete pcRoot;
    pcRoot = pcOther.pcRoot;
    return (*this);
}

CTree & CTree::operator+(CTree &pcOther){
    CTree* baseTree = new CTree(*(this));
    CNode* prevNode = NULL;
    CNode* currNode = baseTree->pcRoot;
    //wyszukiwanie miejsca do dolaczenia drzewa(skrajnie prawy lisc)
    while(currNode->vpcChild.size() != 0){
        prevNode = currNode;
        currNode = currNode->vpcChild[(currNode->vpcChild.size())-1];
    }
    //drzewo podstawowe: wiecej niz 1 wezel
    if(prevNode != NULL){ 
        delete prevNode->vpcChild[(prevNode->vpcChild.size())-1];
        prevNode->vpcChild.pop_back();
        prevNode->vpcChild.push_back(new CNode(*(pcOther.pcRoot)));
    }
    //drzewo podstawowe: dokladnie 1 wezel
    else{   
        delete baseTree->pcRoot;
        baseTree->pcRoot = new CNode(*(pcOther.pcRoot));
    }
    return *baseTree;
}

int CTree::enter(stringstream &ss){
    bool fixed = false;

    if(pcRoot != NULL){
        delete pcRoot;
    }
        
    pcRoot = new CNode(ss, fixed);
    
    if(fixed)
        return WAR_NOTENOUGHARG;
    else if (!(ss.eof())) 
        return WAR_TOOMANYARG;
    return 0;
}

string CTree::print(){
    stringstream ss;
    pcRoot->print(ss);
    ss << "\n";
    return ss.str();
}

vector<string> CTree::getVars(){
    vector<string> v;
    pcRoot->getVars(v);
    return v;
}

double CTree::comp(vector<double> &val, int &err){
    vector<string> var;
    double temp = pcRoot->eval(var, val, err);
    if(var.size() < val.size()) err = WAR_TOOMANYARG;
    return temp;
}

int CTree::countNodesOfLevel(int findLevel){
    int result = 0;
    pcRoot->nodesOfLevel(findLevel, 1, result);
    return result;
}

//
//
//____________NODE______________
//
//

CNode::CNode(stringstream &ss, bool &fixed){
    string func;
    ss >> func;

    //cout << "c: " << func << endl;

    if(func == "+"){
        iNodeType = FUNC_ADD;
        vpcChild.push_back(new CNode(ss, fixed));
        vpcChild.push_back(new CNode(ss, fixed));
    }
    else if(func == "-"){
        iNodeType = FUNC_MIN;
        vpcChild.push_back(new CNode(ss, fixed));
        vpcChild.push_back(new CNode(ss, fixed));
    }
    else if(func == "*"){
        iNodeType = FUNC_TIM;
        vpcChild.push_back(new CNode(ss, fixed));
        vpcChild.push_back(new CNode(ss, fixed));
    }
    else if(func == "/"){
        iNodeType = FUNC_DIV;
        vpcChild.push_back(new CNode(ss, fixed));
        vpcChild.push_back(new CNode(ss, fixed));
    }
    else if(func == "sin"){
        iNodeType = FUNC_SIN;
        vpcChild.push_back(new CNode(ss, fixed));
    }
    else if(func == "cos"){
        iNodeType = FUNC_COS;
        vpcChild.push_back(new CNode(ss, fixed));
    }
    else if(strToDouble(func, dVal)){
        iNodeType = FUNC_CON;
    }
    else if(func.empty()){
        iNodeType = FUNC_CON;
        dVal = FIX_VAL;
        fixed = true;
    }
    else{
        iNodeType = FUNC_VAR;
        sName = func;
    }
}

CNode::CNode(CNode &pcOther){
    iNodeType = pcOther.iNodeType;
    dVal = pcOther.dVal;
    sName = pcOther.sName;
    for(int i = 0; i < pcOther.vpcChild.size(); i++){
        vpcChild.push_back(new CNode(*(pcOther.vpcChild[i])));
    }
}

CNode::~CNode(){
    for(int i = 0; i<vpcChild.size(); i++){
        delete vpcChild[i];
    }

    //cout << "d: " << iNodeType << endl;
}

void CNode::print(stringstream &ss){
    if(iNodeType == FUNC_ADD)
        ss << "+ ";
    else if(iNodeType == FUNC_MIN)
        ss << "- ";
    else if(iNodeType == FUNC_TIM)
        ss << "* ";
    else if(iNodeType == FUNC_DIV)
        ss << "/ ";
    else if(iNodeType == FUNC_SIN)
        ss << "sin ";
    else if(iNodeType == FUNC_COS)
        ss << "cos ";
    else if(iNodeType == FUNC_CON)
        ss << dVal << " ";
    else if(iNodeType == FUNC_VAR)
        ss << sName << " ";
    
    for(int i = 0; i<vpcChild.size(); i++)
        vpcChild[i]->print(ss);
}

void CNode::getVars(vector<string> &v){
    if(iNodeType == FUNC_VAR){
        if(find(v, sName) == -1) v.push_back(sName);
    }
    for(int i = 0; i<vpcChild.size(); i++){
        vpcChild[i]->getVars(v);
    }
}

double CNode::eval(vector<string> &var, vector<double> &val, int &err){
    if(iNodeType == FUNC_ADD)
        return vpcChild[0]->eval(var, val, err) + vpcChild[1]->eval(var, val, err);
    else if(iNodeType == FUNC_MIN)
        return vpcChild[0]->eval(var, val, err) - vpcChild[1]->eval(var, val, err);
    else if(iNodeType == FUNC_TIM)
        return vpcChild[0]->eval(var, val, err) * vpcChild[1]->eval(var, val, err);
    else if(iNodeType == FUNC_DIV)
        return vpcChild[0]->eval(var, val, err) / vpcChild[1]->eval(var, val, err);
    else if(iNodeType == FUNC_SIN)
        return sin((vpcChild[0]->eval(var, val, err)));
    else if(iNodeType == FUNC_COS)
        return cos((vpcChild[0]->eval(var, val, err)));
    else if(iNodeType == FUNC_VAR){
        int found = find(var, sName);
        if(found != -1) return val[found];
        else{
            var.push_back(sName);
            if(val.size() < var.size()) {
                err = WAR_NOTENOUGHARG;
                return 1;
            }
            return val[var.size()-1];
        }
    }
    else{
        return dVal;
    }
}

void CNode::nodesOfLevel(int findLevel, int currentLevel, int &result){
    if(currentLevel == findLevel) result++;
    else{
        for(int i=0; i<vpcChild.size(); i++){
            vpcChild[i]->nodesOfLevel(findLevel, currentLevel+1, result);
        }   
    }
}