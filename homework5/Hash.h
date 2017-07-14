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
#ifndef HASH_H
#define HASH_H

struct Node
{
    Node(unsigned int key, long long data, size_t c = 1, Node* next = nullptr )
    {
        nkey = key;
        ndata = data;
        nnext = next;
        ncounter = c;
    }

    unsigned int nkey;
    long long ndata;
    size_t ncounter;
    Node* nnext;
};

class Hash
{
    public:
        Hash();
        Hash(Hash&);
        Hash& operator=(Hash& other);
        ~Hash();

        void add(long long data);
        void remove(long long data);
        Node* search(long long data) const;

        size_t getCounter(Node* node) const { return node->ncounter; };
        long long getData(Node* node) const { return node->ndata; };
        Node* getNext(Node* node) const { return node->nnext; };
        int getSize() const { return size; }
        Node** getTable() { return this->hashTable; }

     private:
        unsigned int  hashFunctin(long long data) const { return data % size; }

        void clear(Node*);
        Node* copy(Node*);

        int size = 5011;
        Node* hashTable[5011];


};

Hash::Hash()
{
    int i = 0;
    while(i != size)
    {
        hashTable[i] = nullptr;
        ++i;
    }
}

Hash::Hash(Hash& other)
{
    int i = 0;
    while(i != size)
    {
        clear(hashTable[i]);
        ++i;
    }

    i = 0;
    while(i != size)
    {
        hashTable[i] = copy(other.getTable()[i]);
        ++i;
    }
}

Hash& Hash::operator=(Hash& other)
{
    if(this != &other)
    {
        int i = 0;
        while(i != size)
        {
            clear(hashTable[i]);
            ++i;
        }

        i = 0;
        while(i != size)
        {
            hashTable[i] = copy(other.getTable()[i]);
            ++i;
        }
    }

    return *this;
}

Hash::~Hash()
{
    int i = 0;
    while(i != size)
    {
        clear(hashTable[i]);
        ++i;
    }
}

Node* Hash::copy(Node* start)
{
    if(start)
    {
        Node *result, *temp;
        result = new Node(start->nkey, start->ndata, start->ncounter);
        temp = result;

        while(start->nnext)
        {
            start = start->nnext;
            temp->nnext = new Node(start->nkey, start->ndata, start->ncounter);
            temp = temp->nnext;
        }

        return result;
    }
    else
    {
        return nullptr;
    }
}

void Hash::clear(Node* start)
{
    while(start)
    {
        Node* temp = start;
        start = start->nnext;
        delete temp;
    }
}

void Hash::add(long long data)
{
    unsigned int key = hashFunctin(data);
    if(!hashTable[key])
    {
        hashTable[key] = new Node(key,data);
    }
    else
    {
        Node* current = hashTable[key];
        while(current)
        {
            if(current->ndata == data)
            {
                current->ncounter++;
                break;
            }
            else if(!current->nnext)
            {
                current->nnext = new Node(key, data);
                break;
            }
            else
            {
                current = current->nnext;
            }
        }
    }

}

void Hash::remove(long long data)
{
    unsigned int key = hashFunctin(data);
    if(!hashTable[key])
    {
        std::cout << "No such element!" << std::endl;
    }
    else
    {
        Node* current = hashTable[key];
        Node* help = current;
        while(current)
        {
            if(current->ndata == data)
            {
                if(current->ncounter - 1 == 0)
                {
                    if(!current->nnext)
                    {
                        delete current;
                        help != hashTable[key] ? help->nnext = nullptr : hashTable[key] = nullptr;
                    }
                    else
                    {
                        help->nnext = current->nnext;
                        delete current;
                    }
                }
                else
                {
                    current->ncounter--;
                }

                break;
            }
            else if(!current->nnext)
            {
                std::cout << "No such element!" << std::endl;
                break;
            }
            else
            {
                help = current;
                current = current->nnext;
            }
        }
    }
}

Node* Hash::search(long long data) const
{
    unsigned int key = hashFunctin(data);
    if(!hashTable[key])
    {
        std::cout << "No such element!" << std::endl;
    }
    else
    {
        Node* current = hashTable[key];
        while(current)
        {
            if(current->ndata == data)
            {
                return current;
            }
            else if(!current->nnext)
            {
                std::cout << "No such element!" << std::endl;
                return nullptr;
            }
            else
            {
                current = current->nnext;
            }
        }
    }
}

#endif // HASH_H
