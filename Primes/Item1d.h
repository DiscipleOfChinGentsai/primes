#ifndef ITEM1D_H
#define ITEM1D_H

#include <cstddef>

template<typename T> class LList_1d;
template<typename T> class item_1d;

template<typename T> class ptrPair
{
	friend class item_1d<T>;
	item_1d<T> *nextPtr;
	item_1d<T> *prevPtr;

	ptrPair()
	{
		nextPtr = nullptr;
		prevPtr = nullptr;
	}

	~ptrPair()
	{
		delete nextPtr;
		delete prevPtr;
	}
};

 class coord_1d
{
	//friend class item_1d<T>;
public:
	void setA(int i)
	{
		a=i;
	}
	int getA()
	{
		return a;
	}
private:
	int a;
};

template<typename T> class item_1d
{
	friend class LList_1d<T>;
	ptrPair<T> linear;
private:
	T data;
	coord_1d loc;
	
public:
	item_1d();
	item_1d( const T &);
	~item_1d();

	bool setNext(item_1d<T> *item);
	bool setPrev(item_1d<T> *item);

	bool addNext(item_1d<T> &item);
	bool addPrev(item_1d<T> &item);

	bool remNext();
	bool remPrev();

	item_1d<T> *getNext();
	item_1d<T> *getPrev();

	int getCoord();
	void setCoord(int num);

	void setData(const T &);
	T getData() const;
};


//=====================================================
//||     implementation  ||
//=================================

template<typename T> item_1d<T>::item_1d()
{
}

template<typename T> item_1d<T>::item_1d(const T &info)
{
	setData(info);
	setCoord(0);
	
}

template<typename T> item_1d<T>::~item_1d()
{

	//loc.setA(0);
	//delete loc;

}
template<typename T> T item_1d<T>::getData() const
{
	return data;
}

template<typename T> void item_1d<T>::setData(const T &info)
{
	data = info;
}

//==============================================

template<typename T> int item_1d<T>::getCoord()
{
	return loc.getA();
}

template<typename T> void item_1d<T>::setCoord(int num)
{
	loc.setA(num);
}


//============================================

template<typename T> bool item_1d<T>::setNext(item_1d<T> *item)
{
	if(linear.nextPtr= item)
	 return true;
	else return false;
}

template<typename T> bool item_1d<T>::setPrev(item_1d<T> *item)
{
	if(linear.prevPtr= item)
	 return true;
	else return false;
}

//================================================

template<typename T> item_1d<T> *item_1d<T>::getNext()
{
	return linear.nextPtr;
}

template<typename T> item_1d<T> *item_1d<T>::getPrev()
{
	return linear.prevPtr;
}

//===================================


#endif