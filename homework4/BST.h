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
#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include<algorithm>
#include<cmath>
#include "Data.h"


template <class T>
class BST
{
public:
    BST()
    {
        root = nullptr;
        size = 0;
    }

    BST(const BST& other)
    {
        root = copy(other.root);
        size = other.size;
    }

    ~BST()
    {
        clear(root);
    }

    BST& operator=(const BST& other)
    {
        if(this != &other){
            clear(root);
            root = copy(other.root);
            size = other.size;
        }

        return *this;
    }

    void add(T data) { add(root, data); ++size; }
    bool remove(T data) { return remove(root, data); }
    //The bool removeall(Data) function works only for the data type I use in this homework
    bool removeall(Data data) { return remove(root, data); }
    bool search(T data) const { return search(root, data); }

    void DSW()
	{
	    T emptyData;
        Node* froot = new Node(emptyData,nullptr,root);
        ttv(froot);
        vtt(froot,size);

        root = froot->rChild;

        delete froot;
	}

private:
    struct Node
    {
        Node(const T& ninfo, Node* left = nullptr , Node* right = nullptr )
            :mdata(ninfo), lChild(left), rChild(right){}

        T mdata;
        Node *lChild, *rChild;
    };
    Node* root;
    size_t size;

    void clear(Node* root)
    {
        if (root)
        {
            clear(root->lChild);
            clear(root->rChild);
            delete root;
        }
    }
    Node* copy(Node* root)
    {
        return root ?
            new Node(root->mdata, copy(root->lCild()), copy(root->rCild())) : root;
    }

    void add(Node*& root, const T& data)
    {
        if (!root)
            root = new Node(data);
        else{
            add( root->mdata >= data ? root->lChild : root->rChild, data);}

    }

    bool remove(Node*& root, const T& data)
    {
        if (!root) return false;
        if (root->mdata == data)
        {
            Node* del = root;
            if (!root->lChild)
            {
                root = root->rChild;
            }
            else if (!root->rChild)
            {
                root = root->lChild;
            }
            else
            {
                Node* minRight = getMin(root->rChild);
                minRight->lChild = root->lChild;
                minRight->rChild = root->rChild;
                root = minRight;
            }
            --size;
            delete del;
            return true;
        }
        else
        {
            return remove(root->mdata >= data ? root->lChild : root->rChild, data);
        }
    }

    bool removeall(Node*& root, const Data& data)
    {
        if (!root) return false;
        if (root->mdata.getKey() == data.getKey())
        {
            Node* del = root;
            if (!root->lChild)
            {
                root = root->rChild;
            }
            else if (!root->rChild)
            {
                root = root->lChild;
            }
            else
            {
                Node* minRight = getMin(root->rChild);
                minRight->lChild = root->lChild;
                minRight->rChild = root->rChild;
                root = minRight;
            }
            --size;
            delete del;
            return true;
        }
        else
        {
            return remove(root->mdata >= data ? root->lChild : root->rChild, data);
        }
    }

    Node* getMin(Node*& root)
    {
        if (root->lChild)
            return getMin(root->lChild);

        Node* n = root;
        root = root->rChild;
        return n;
    }

    bool search(const  Node* root, T& data) const
    {
        if (!root) return false;
        if (root->mdata == data) return true;
        return root->mdata >= data ? search(root->lChild, data) : search(root->rChild, data);
    }

    void ttv(Node* root)
    {
        Node* tail = root;
        Node* rest = tail->rChild;
        while(rest != nullptr)
        {
            if (rest->lChild == nullptr)
            {
                tail = rest;
                rest = rest->rChild;
            }
            else
            {
                Node* temp = rest->lChild;
                rest->lChild = temp->rChild;
                temp->rChild = rest;
                rest = temp;
                tail->rChild = temp;
            }
        }
    }

    void vtt(Node* root, size_t size)
    {
        size_t leaves = size + 1 - pow(2,log2(size+1));
        compress(root, leaves);
        size = size - leaves;
        while(size > 1)
        {
            int i = size/2;
            compress(root,i);
            size = size/2;
        }
    }

    void compress(Node* root, int count)
    {
        Node* scanner = root;
        for(int i = 1; i <= count; ++i)
        {
            Node* child = scanner->rChild;
            scanner->rChild = child->rChild;
            scanner = scanner->rChild;
            child->rChild = scanner->lChild;
            scanner->lChild = child;
        }
    }

};


#endif // BST_H_INCLUDED
