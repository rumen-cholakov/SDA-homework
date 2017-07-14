/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Rumen Cholakov
* @task 4
* @compiler GCC
*
*/
#include<iostream>
#include<fstream>
#include<cstdio>
#include<climits>
#include "BST.h"

using namespace std;

int main(int argc, char * argv[]){

    //Creating the tree from the .bin file
    BST<Data> bst;
    ifstream myFile1 (argv[1], ios::in | ios::binary);
    dataInfo q;
    while(myFile1.read ((char*)&q, sizeof (dataInfo))){

        char* tempBuff = new char[q.size + 1];
        tempBuff[q.size] = '\0';
        myFile1.read (tempBuff, q.size);
        Data d(q.key, q.size + 1, tempBuff);
        bst.add(d);
        //cout << d.getKey()<<d.getTxt()<<endl;
        delete []tempBuff;
    }
    myFile1.close();
    //Balancing the tree
    bst.DSW();
    //Getting and executing commands from the command line
    char command[10];
    int key;
    while(strcmp(command,"^Z") && strcmp(command,"^D"))
    {
        cin>>command;
        cin>>key;
        if(strcmp(command,"removeall"))
        {
            char *data=new char[100];
            cin >> data;
            if(!strcmp(command,"add"))
            {
                cout <<"add:";
                Data tmp(key, 100, data);
                bst.add(tmp);
            }
            else if(!strcmp(command,"remove"))
            {
                cout <<"rem:";
                Data tmp(key, 100, data);
                cout << bst.remove(tmp) << endl;
            }
            else if(!strcmp(command,"search"))
            {
                cout <<"ser:";
                Data tmp(key, 100, data);
                cout << bst.search(tmp) << endl;
            }
            else
            {
                cout<<"Invalid command!" << endl;
            }
            delete []data;
        }
        else if(!strcmp(command,"removeall"))
        {
            cout <<"ra:";
            int counter = 0;
            Data tmp(key, 1, '\0');
            while( bst.removeall(tmp)) {++counter;}
            cout << counter << endl;
        }
        else
        {
            cout<<"Invalid command!" << endl;
        }

    }
    return 0;
}
