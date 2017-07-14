/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Rumen Cholakov
* @task 5
* @compiler GCC
*
*/
#include<iostream>
#include<fstream>
#include<stdio.h>
#include "Hash.h"

using namespace std;

void writeIntersection(Hash& h, int n)
{
    ofstream result("result.bin", ios::binary);

    int hsize = h.getSize();
    Node** table = h.getTable();
    for( int i = 0; i < hsize; ++i)
    {
        if(table[i])
        {
            Node* current = table[i];
            while(current)
            {
                if(h.getCounter(current) == n)
                {
                    long long data = h.getData(current);
                    result.write((char*)&data, 8);
                }

                current = h.getNext(current);
            }
        }
    }

    result.close();
}

int main (int argv, char* argc[])
{
    Hash h;
    int numFiles;
    sscanf(argc[1], "%d", &numFiles);

    long long data;
    for(int i = 0; i < numFiles; ++i)
    {
        ifstream file(argc[ i + 2 ], ios::binary);
        while(file.read((char*)&data, 8))
        {
            h.add(data);
        }
    }

    writeIntersection(h, numFiles);

    return 0;
}
