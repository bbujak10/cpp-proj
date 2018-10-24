#include <iostream>
#include "controller.hpp"

using namespace std;

int main(){
    CSparseController c;

    bool go = true;
    while(go==true){
        stringstream iss;
	    string line;
	    getline(cin, line);
	    iss << line;
	
	    string word;
	    if(iss >> word){
            if(word == "addmat"){
                bool fail = false;
                int n;
                iss >> n;
                int t[n];
                for(int i=0; i<n; i++){
                    if(!(iss >> t[i])) fail = true;
                }
                int def;
                if(!(iss >> def)) fail = true;
                string name;
                iss >> name;
                if(fail != true){
                    if(name == "")
                        c.addMat(n, t, def);
                    else
                        c.addMat(n,t,def,name);
                }
                else cout << "Error: not enough arguments\n";
                
            }
            else if(word == "list"){
                cout << c.list();
            }
            else if(word == "del"){
                int off;
                iss >> off;
                if(c.del(off) == -1) cout << "Error: matrix index out of bounds\n";
            }
            else if(word == "delall"){
                c.delAll();
            }
            else if(word == "def"){
                int off;
                iss >> off;
                int dim = c.getDim(off);
                if(dim != -1){
                    int t[dim];
                    for(int i=0; i<dim; i++){
                        iss >> t[i];
                    }
                    int val;
                    iss >> val;
                    int res = c.def(off, t, val);
                    if(res == -2) cout << "Error: coordinates out of bounds\n";
                }
                else cout << "Error: matrix index out of bounds\n";
            }
            else if(word == "print"){
                int off;
                iss >> off;
                cout << c.print(off);
            }
            else if(word == "clone"){
                int off;
                iss >> off;
                if(c.clone(off) == -1) cout << "Error: matrix index out of bounds\n";
            }
            else if(word == "quit"){
                c.delAll();
                go=false;
            }
            else if(word == "rename"){
                int off;
                iss >> off;
                string s;
                iss >> s;
                if(c.rename(off, s) == -1) cout << "Error: matrix index out of bounds\n";
            }
            else cout << "Error: invalid command\n";
        }
        else cout << "Error: invalid command\n";


    }
/*
    int t[] = {3,3,3};
    c.addMat(3, t, 1, "pierwsza");
    int tt[] = {100};
    c.addMat(1, tt, 0, "wektor");
    int ttt[] = {100,100,100,100};
    c.addMat(4, ttt, 4);
    c.rename(2, "test");
    tt[0]=5;
    c.addMat(1,tt,0,"wektor2");
    c.del(1);

    tt[0] = 2;
    c.def(2, tt, 5);

    t[0] = 5;
    t[1] = 30;
    t[2] = 20;
    c.def(0, t, 67);

    t[0] = 5;
    t[1] = 29;
    t[2] = 20;
    c.def(0, t, 67);

    c.clone(2);
    cout << c.list();
    cout << c.print(3);

*/

    return 0;
}