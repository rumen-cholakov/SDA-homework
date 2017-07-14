#include <assert.h>
template <typename T>
class LStack {
    class node {
    public:
        T Data;
        node* pNext;
        node(T, node* = NULL);
    };

public:
    LStack();
    LStack(LStack const & Other);
    LStack& operator= (LStack const & Other);
    ~LStack();

public:
    void Push(const T & Element);
    bool Pop(T& Element);
    T& Peek();

    size_t GetSize() const;
    bool IsEmpty() const;

private:
    void Init();
    void Destroy();
    void CopyFrom(LStack const & Other);

    node* pTop;
    size_t Size;
};


template <typename T>
LStack<T>::node::node(T Data, node* pNext)
{
    this->Data = Data;
    this->pNext = pNext;
}

template <typename T>
LStack<T>::LStack()
{
    Init();
}

template <typename T>
LStack<T>::LStack(LStack const & Other)
{
	Init();
	CopyFrom(Other); 
}

template <typename T>
LStack<T>& LStack<T>::operator=(LStack<T> const & Other)
{
	if (this != &Other)
	{
		Destroy();
		CopyFrom(Other);
	}

	return *this;
}


template <typename T>
LStack<T>::~LStack()
{
    Destroy();
}

template <typename T>
void LStack<T>::Init()
{
    pTop = 0;
    Size = 0;
}

template <typename T>
void LStack<T>::Destroy()
{
    node* p;

    while (pTop)
    {
        p = pTop;
        pTop = pTop->pNext;
        delete p;
    }

    Init();
}

template <typename T>
void LStack<T>::CopyFrom(LStack const& Other)
{
	if (Other.IsEmpty())
		return;

	node *pNew;
	node *pOld;
	try
	{
		pTop = new node(Other.pTop->Data);

		pNew = pTop;
		pOld = Other.pTop->pNext;

		while (pOld)
		{
			pNew->pNext = new node(pOld->Data);
			pNew = pNew->pNext;
			pOld = pOld->pNext;
		}
	}
	catch (std::bad_alloc&)
	{
		Destroy();
		throw;
	}

	Size = Other.Size;
}

template <typename T>
void LStack<T>::Push(const T & Element)
{
    pTop = new node(Element, pTop);

    Size++;
}

template<typename T>
bool LStack<T>::Pop(T & Element)
{
    if (Size == 0)
        return false;

    Element = pTop->Data;

    node* p = pTop;
    pTop = pTop->pNext;
    delete p;

    Size--;

    return true;
}


template<typename T>
T& LStack<T>::Peek()
{
	assert(Size != 0);

    return pTop->Data;
}

template<typename T>
size_t LStack<T>::GetSize() const
{
    return Size;
}

template<typename T>
bool LStack<T>::IsEmpty() const
{
    return Size == 0;
}
