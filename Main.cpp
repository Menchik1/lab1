#include<iostream>
#include "mainHeader.h"
using namespace std;
int main(){
    string request;
    while(true){
        cout<<"Enter SYBD (Massiv, Spisok, Queue, Stack, Hash-table, Tree, exit): ";
        cin>> request;
        if(request=="Massiv"){
            Massiv();
        }
        else if(request=="Spisok"){
            Spisokk();
        }
        else if(request=="Queue"){
            Queuee();
        }
        else if(request=="Stack"){
            Stackk();
        }
        else if(request=="Hash-table"){
            Hash();
        }
        else if(request=="Tree"){
            Tree();
        }
        else if(request=="exit"){
            cout<<"Goodbye!";
            return 0;
        }
        else {
            cout<<"Wrong request"<<endl;
        }
    }
}
