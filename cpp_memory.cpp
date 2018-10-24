#include <iostream>
#include <sstream>

using namespace std;

//ZARZADZANIE TABLICAMI
int* newArray(int len){
    int* temp = new int[len];
    return temp;
}
int* enlargeArray(int& aRealLength, int*& tab){
    int* temp = new int[aRealLength*2];
    for(int i=0; i<aRealLength; i++){
        temp[i] = tab[i];
    }
    delete tab;
    return temp;
}
int* shrinkArray(int& aRealLength, int& aLength, int*& tab){
    int* temp = new int[aRealLength/2];
    for(int i=0; i<aLength; i++){
        temp[i] = tab[i];
    }
    delete tab;
    return temp;
}
//sortuje obie tablice values i offsets rosnąco wedlug offsetow
void sortArraysByOffsets(int*& values, int*& offsets, int& aLength){
    int temp, tempV, j;
    for(int i = 1; i < aLength; i++){
        temp = offsets[i];
        tempV = values[i];
        for(j = i-1; j >= 0 && offsets[j] > temp; j--){
             offsets[j+1] = offsets[j];
             values[j+1] = values[j];
        }
        offsets[j+1] = temp;
        values[j+1] = tempV;
    }
}

//OBSLUGA VECTORA
//utworzenie wektora - lub usuniecie starego utworzenie nowego
void makeVector(int*& values, int*& offsets, int& aRealLength, int& aLength, bool& vExists){
    if(vExists){
        delete values;
        delete offsets;
    }
    aRealLength = 1;
    aLength = 0;
    vExists = true;
    values = newArray(aRealLength);
    offsets = newArray(aRealLength);
}

//zmiana wartosci domyslnej - tylko jesli wektor jest pusty
void changeDefVal(int& aLength, int& DEF_VAL, int newVal){
    if(aLength != 0) cout << "Wektor nie jest pusty" << endl;
    else DEF_VAL = newVal;
}

//zwraca id dla danego offsetu
int findOffset(int*& offsets, int& aLength, int findOff){
    for(int i=0; i<aLength; i++)
        if (offsets[i]==findOff) return i;
    return -1;
}

//zwraca wartosc dla danego offsetu(elementu wektora)
int elementValue(int DEF_VAL, int vLength, int*& values, int*& offsets, int aLength, int findOff){
    if(vLength<=findOff) cout << "Indeks wykracza poza wektor" << endl;
    else{
        int foundOffId = findOffset(offsets, aLength, findOff);
        if(foundOffId == -1) return DEF_VAL;
        else return values[foundOffId];
    }
    return -1;
}

//usuwa wartosc spod danego id w tablicy
void deleteId(int*& values, int*& offsets, int& aRealLength, int& aLength, int delId){
    if(delId<aLength && delId>=0){
        for(int i=delId; i<(aLength-1); i++){
            offsets[i] = offsets[i+1];
            values[i] = values[i+1];
        }  
        aLength--;
        if((aRealLength/2)>aLength){
            values = shrinkArray(aRealLength, aLength, values);
            offsets = shrinkArray(aRealLength, aLength, offsets);
            aRealLength = aRealLength/2;
        }
    }
}

//usuwa wartosc znajdujaca sie w wektorze pod dannym offsetem
void deleteOffset(int*& values, int*& offsets, int& aRealLength, int& aLength, int delOff){
    int found = -1;
    for(int i=0; i<aLength; i++)
        if(offsets[i] == delOff) found = i;
    deleteId(values, offsets, aRealLength, aLength, found);
}

//definiuje nowa wartosc
void defineValue(int*& values, int*& offsets, int& aRealLength, int& aLength, int DEF_VAL, int vLength, int newVal, int newOff){
    if(newOff>=vLength) cout << "Wartosc wykracza poza dlugosc wektora" << endl;    //czy nie wykracza poza wektor
    else{
        int foundOffId = findOffset(offsets, aLength, newOff);                      //czy taki offset juz istnieje(jesli nie to -1)

        if(newVal != DEF_VAL){                                                      //czy rozne od domyslnej
            if(foundOffId!=-1) values[foundOffId] = newVal;
            else{
                if(aRealLength<=aLength){
                    values = enlargeArray(aRealLength, values);
                    offsets = enlargeArray(aRealLength, offsets);
                    aRealLength = aRealLength*2;
                }
                offsets[aLength] = newOff;
                values[aLength] = newVal;
                aLength++;
                sortArraysByOffsets(values, offsets, aLength);
            }
        }
        else{
            if(foundOffId!=-1) deleteOffset(values, offsets, aRealLength, aLength, newOff);
        }
    }
}

//zmienia dlugosc wektora
void changeLength(int*& values, int*& offsets, int& aRealLength, int& aLength, int& vLength, int newLen){
    if(newLen < vLength) {
        for(int i = aLength-1; newLen<=offsets[i]; i--){
            deleteId(values, offsets, aRealLength, aLength, i);
        }
    }
    vLength = newLen;
}

//usuwa zmienne dynamiczne
void deleteDynamic(int*& values, int*& offsets, int& aRealLength, int& aLength, bool& vExists){
    delete values;
    delete offsets;
    aRealLength = 0;
    aLength = 0;
    vExists = false;
    cout << "Dealokacja dynamicznych tablic, by uzyc wektora ponownie uzyj mvec" << endl;
}

//dane vectora -> informacja typu string o dlugosci i zawartosci wektora
string infoVector(int DEF_VAL, int vLength, int*& values, int*& offsets, int& aLength){
    ostringstream s;
    s << "len: " << vLength << " values: ";
    int j = 0;
    for(int i=0; i<vLength; i++){
        s << (i==0 ? "" : ", ");
        int found = -1;
        int curOff = offsets[j];
        while(curOff<=i && found == -1 && j<aLength){
            if(curOff == i) found = j;
            j++;
        }
        if(found != -1){
            s << values[found];
        }
        else{
            s << DEF_VAL;
        }
    }
    return s.str();
}

void zamiana(int*& values, int*& offsets, int &aLength){
    int aId = findOffset(offsets, aLength, 0); // -1 gdy domyslna inaczej id
    int bId = findOffset(offsets, aLength, 1);

    if(aId != -1 && bId != -1){
        int temp = values[aId];
        values[aId] = values[bId];
        values[bId] = temp;
        //sortArraysByOffsets(values, offsets, aLength);
    }
    else if(aId == -1 && bId != -1)
        offsets[bId] = 0;
    else if(aId != -1 && bId == -1){
        offsets[aId] = 1;
    }
}



//STATUS
void variableStatus(int*& values, int*& offsets,int& aRealLength,int& aLength,bool& vExists,int& DEF_VAL,int& vLength){
    cout << "vExists: " << vExists << endl;
    cout << "aLength: " << aLength << " aRealLength: " << aRealLength << endl;
    cout << "values:  ";
    for(int i=0; i<aRealLength; i++) cout<<(i!=0?"*":"")<<values[i];
    cout << "\noffsets: ";
    for(int i=0; i<aRealLength; i++) cout<<(i!=0?"*":"")<<offsets[i];
    cout << endl << "vLength: " << vLength << " DEF_VAL: " << DEF_VAL << endl;
}

//MAIN
int main(){
    //Tablice wartosci roznych od domyslnych
    int* values;
    int* offsets;
    int aLength = 0;
    int aRealLength = 0;

    //Wlasciwosci wektora
    int vLength = 0;
    int DEF_VAL;
    bool vExists = false;

    //INTERFEJS
    bool active = true;
    while(active){
        string s;
        cin >> s;

        if(s == "mvec"){
            cin >> vLength >> DEF_VAL;
            makeVector(values, offsets, aRealLength, aLength, vExists);
        }
        else if(s == "len"){
            int newLen;
            cin >> newLen;
            changeLength(values, offsets, aRealLength, aLength, vLength, newLen);
        }
        else if(s == "def"){
            int newOff, newVal;
            cin >> newOff >> newVal;
            defineValue(values, offsets, aRealLength, aLength, DEF_VAL, vLength, newVal, newOff);
        }
        else if(s == "print"){
            cout << infoVector(DEF_VAL, vLength, values, offsets, aLength) << endl;
        }
        else if(s == "del"){
            deleteDynamic(values, offsets, aRealLength, aLength, vExists);
        }
        else if(s == "quit"){
            active = false;
        }
        else if(s == "zamiana"){
            zamiana(values, offsets, aLength);
        }
        
        /*
        else if(s == "delo"){
            int delOff;
            cin >> delOff;
            deleteOffset(values, offsets, aRealLength, aLength, delOff);
        }
        else if(s == "elv"){
            int findOff;
            cin >> findOff;
            cout << elementValue(DEF_VAL, vLength, values, offsets, aLength, findOff) << endl;
        }
        else if(s == "chdef"){
            int newDef;
            cin >> newDef;
            changeDefVal(aLength, DEF_VAL, newDef);
        }*/
        else if(s == "status"){
            variableStatus(values, offsets, aRealLength, aLength, vExists, DEF_VAL, vLength);
        }
        else{
            cout << "Bledna komenda" << endl;
        }
    }

    if(vExists){
        delete values;
        delete offsets;
    }

    return 0;
}