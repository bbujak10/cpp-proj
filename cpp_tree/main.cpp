#include <iostream>
#include "tree.hpp"

using namespace std;

int main(){
    CTree c_a;

    bool go = true;
    while(go){
        string line; 
        getline(cin, line);
        stringstream ss(line);

        string word;
        ss >> word;

        if(word == "enter"){
            int res = c_a.enter(ss);
            if(res == WAR_NOTENOUGHARG) cout << "Warning: Not enough arguments! FIXED: \n" << c_a.print();
            else if(res == WAR_TOOMANYARG) cout << "Warning: Too many arguments!\n";
        }
        else if(word == "print"){
            cout << c_a.print();
        }
        else if(word == "vars"){
            vector<string> vsVars = c_a.getVars();
            for(int i=0; i<vsVars.size(); i++){
                cout << (i!=0?", ":"") << vsVars[i];
            }
            cout << endl;
        }
        else if(word == "comp"){
            vector<double> val;
            double temp;
            while(ss >> temp) val.push_back(temp);
            int err = 0;
            double res = c_a.comp(val, err);
            if(err == WAR_NOTENOUGHARG) cout << "Error: Not enough arguments!\n";
            else if(err == WAR_TOOMANYARG) cout << "Error: Too many arguments!\n";
            else cout << res << "\n";
        }
        else if(word == "join"){
            CTree c_sum, c_b;
            int res = c_b.enter(ss);
            if(res == WAR_NOTENOUGHARG) cout << "Warning: Not enough arguments! Fixed.\n";
            else if(res == WAR_TOOMANYARG) cout << "Warning: Too many arguments!\n";
            else{
                c_sum = c_a + c_b;
                cout << "c_a: " << c_a.print();
                cout << "c_b: " << c_b.print();
                cout << "c_sum: " << c_sum.print();
            }
        }
        else if(word == "mod"){
            int l;
            ss >> l;
            cout << c_a.countNodesOfLevel(l) << "\n";
        }
        else if(word == "exit"){
            go = false;
        }
        else{
            cout << "Error: Invalid command!\n";
        }
    }
/*
    cout << t.enter(ss) << endl;

    cout << t.print() << endl;

    vector<double> val;
    val.push_back(1);
    val.push_back(2);
    val.push_back(3);

    int err = 0;
    cout << "res: " << t.comp(val, err) << " | " << err << endl;

    err = 0;
    vector<double> val2;
    val2.push_back(1);
    val2.push_back(2);

    cout << "res: " << t.comp(val2, err) << " | " << err << endl;

    getline(cin, line);
    stringstream sss(line);

    CTree tt;
    cout << tt.enter(sss) << endl;

    CTree c_sum;

    c_sum = t + tt;

    cout << c_sum.print() << endl;

    ____________
    CTree ttt(t);
    CTree tt(t);

    tt = t+ttt;

    cout << tt.print() << endl;

    vector<string> v = tt.getVars();

    for(int i = 0; i<v.size(); i++){
        cout << v[i] << ", ";
    }
    cout << endl;


    vector<double> val;
    val.push_back(2);
    //val.push_back(2);
    //val.push_back(2);

    int err = 0;
    cout << "res: " << tt.comp(val, err) << " | " << err;
    cout << endl;
    */
}