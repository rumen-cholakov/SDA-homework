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
#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include<cstring>

struct dataInfo{
    dataInfo(__int32 k = 0, __int32 s = 0): key(k), size(s){}
    __int32 key;
    __int32 size;
};

class Data{
public:
    Data() {key = 0; size = 1; txt = '\0';};
    Data(int, size_t, char*);
    Data(const Data&);
    Data& operator=(const Data&);
    ~Data();

    bool friend operator==(const Data&, const Data&);
    bool friend operator<=(const Data&, const Data&);
    bool friend operator>=(const Data&, const Data&);

    char* getTxt() const { return this->txt; }
    int getKey() const { return this->key; }
    size_t getSize() const { return this->size; }

private:
    void clear();
    void copy(const Data&);
    void setTxt(char* buff) { strcpy(this->txt, buff); }
    int key;
    size_t size;
    char* txt;
};


void Data::clear()
{
    delete []this->txt;
}


void Data::copy(const Data& other)
{
    this->key = other.getKey();
    this->size = other.getSize();
    this->txt = new char[size];
    this->setTxt(other.getTxt());
}


Data::Data(int k, size_t l, char* ntxt){
    key = k;
    size = l;
    txt = new char[l];
    this->setTxt(ntxt);
}


Data::Data(const Data& other){
    clear();
    copy(other);
}


Data& Data::operator=(const Data& other){
    if(this != &other){
        clear();
        copy(other);
    }

    return *this;
}


Data::~Data(){
    clear();
}

bool operator==(const Data& a, const Data& b)
{
    return (a.getKey() == b.getKey() && !strcmp(a.getTxt(), b.getTxt()));
}

bool operator<=(const Data& a, const Data& b)
{
    return (a.getKey() <= b.getKey());
}

bool operator>=(const Data& a, const Data& b)
{
    return (a.getKey() >= b.getKey());
}

#endif // DATA_H_INCLUDED
