#ifndef tree_hpp
#define tree_hpp

#define FIX_VAL 1

#define FUNC_VAR -1
#define FUNC_CON 0
#define FUNC_SIN 1
#define FUNC_ADD 2
#define FUNC_MIN 3
#define FUNC_TIM 4
#define FUNC_DIV 5
#define FUNC_COS 6

#define WAR_NOTENOUGHARG -10
#define WAR_TOOMANYARG -11

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

bool strToDouble(string &s, double &d);
int stringToInt(string &s);

class CNode{
    friend class CTree;
    public:
    CNode(stringstream& ss, bool &fixed);
    CNode(CNode &pcOther);
    ~CNode();

    void print(stringstream& ss);
    void getVars(vector<string> &v);
    double eval(vector<string> &var, vector<double> &val, int &err);
    void nodesOfLevel(int findLevel, int currentLevel, int &result);

    private:
    int iNodeType;              //typ: operacja/funkcja(jaka)/zmienna/stala
    vector<CNode*> vpcChild;    //dzieci

    double dVal;                //wartosc jesli stała
    string sName;               //nazwa jesli zmienna
};

class CTree{
    public:
    CTree();
    CTree(CTree &pcOther);
    ~CTree();

    CTree & operator=(CTree &pcOther);
    CTree & operator+(CTree &pcOther);

    int enter(stringstream &ss);
    vector<string> getVars();
    string print();
    double comp(vector<double> &val, int &err);
    int countNodesOfLevel(int findLevel);

    private:
    CNode* pcRoot;              //korzen
};

#endif