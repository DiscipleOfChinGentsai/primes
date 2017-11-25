#ifndef LLIST1D_H
#define LLIST1D_H

#include "Item1d.h"

//template<typename typeA>;

template<typename T> class LList_1d
{
public:
	//LList_1d();
	~LList_1d();
	LList_1d(const T &);

	bool moveN();
	bool moveP();
	bool moveN_(item_1d<T> *t);
	bool moveP_(item_1d<T> *t);
	bool moveN(int num);
	bool moveP(int num);
	bool moveN_(item_1d<T> *t, int num);
	bool moveP_(item_1d<T> *t, int num);
	bool move(int num);
	bool moveTo(T thisData);

	void addToHead(const T &);
	void addToTail(const T &);
	void addNext(const T &);
	void addPrev(const T &);

	void remHead();
	void remTail();
	void remNext();
	void remPrev();
	bool remThis();
	
	bool remNodeFromHead(const T &);
	bool remNodeFromTail(const T &);
	bool remNodeFromHead(const T *, int n); //number of times
	bool remNodeFromTail(const T *, int n); //number of times
	bool remAll(const T &);
	void remAllEmptyNodes();

	
	item_1d<T> *getTail();
	item_1d<T> *getHead();
	item_1d<T> *getCurr();
	item_1d<T> *getNext();
	item_1d<T> *getPrev();
	item_1d<T> *getNode(int num); // node number starting 0

	T getHeadItem();
	T getTailItem();
	T getCurrItem();
	T getNextItem();
	T getPrevItem();
	T getItemAt(int num); // node number starting 0

	void setCurr(item_1d<T> *t);

	bool isEmpty();
	bool inList(T data_comp); // item is in the list

	int getCount();
private:
	bool setTail();
	bool setHead();
	
	void renumerate();
	void count();
	void recalculateAll();

	item_1d<T> *headPtr;
	item_1d<T> *tailPtr;
	item_1d<T> *currPtr;

	int count_;
};


//===============================
//||      implementation       ||
//===============================

//======================================================

template<typename T> void LList_1d<T>::renumerate()
{
	item_1d<T> *temp_ = headPtr;

		for(int i = headPtr->getCoord()+1; moveN_(temp_); i++)
		{			
			temp_->setCoord(i);
		}
		count_ = temp_->getCoord() + 1;
}

template<typename T> void LList_1d<T>::recalculateAll()
{
	setHead();
	setTail();
	//count();
	renumerate();
}

//======================================================

template<typename T> LList_1d<T>::LList_1d(const T &info)
{
	headPtr = tailPtr = currPtr = new item_1d<T>(info);
	currPtr->setCoord(0);
	
	recalculateAll();
}

template<typename T> LList_1d<T>::~LList_1d()
{
//	delete tailPtr;
//	delete headPtr;
//	delete currPtr;
}

//===================================================

template<typename T> bool LList_1d<T>::moveN()
{
	if(currPtr->getNext())
		currPtr = currPtr->getNext();
	else
		return false;
	return true;
}

template<typename T> bool LList_1d<T>::moveP()
{
	if(currPtr->getPrev())
		currPtr = currPtr->getPrev();
	else
		return false;
	return true;
}


template<typename T> bool LList_1d<T>::moveN(int num)
{
	for( i = 0; i < num ; i++)
	{
	if(!currPtr->getNext())
		return false;
	else
		currPtr = currPtr->getNext();
	}
	return true;
}

template<typename T> bool LList_1d<T>::moveP(int num)
{
	for( i = 0; i < num ; i++)
	{
	if(!currPtr->getPrev())
		return false;
	else
		currPtr = currPtr->getPrev();
	}
	return true;
}

template<typename T> bool LList_1d<T>::moveTo(T thisData)
{
	setCurr(headPtr);
	while(currPtr->getData() != thisData)
	{
		if(!moveN())
			return false;
	}
	return true;
}


template<typename T> bool LList_1d<T>::moveN_(item_1d<T> *t)
{
	if(t->getNext())
		t = (t->getNext());
	else
		return false;
	return true;
}

template<typename T> bool LList_1d<T>::moveP_(item_1d<T> *t)
{
	if(t->getPrev())
		t = (t->getPrev()); 
	else
		return false;
	return true;
}

//=========================================================================
template<typename T> bool LList_1d<T>::setHead()
{
	if(!headPtr || headPtr->getPrev())
	{
		item_1d<T> *temp_ = headPtr;
		while(moveP_(temp_))
		{
			temp_ = temp_->getPrev();
		}
		headPtr = temp_;

		return true;
	}
	
	return false;
}

template<typename T> bool LList_1d<T>::setTail()
{
	if(!tailPtr  || tailPtr->getNext())
	{
		item_1d<T> *temp_ = currPtr;
		while(moveN_(temp_))
		{
			temp_ = temp_->getNext();
		}
		tailPtr = temp_;

		return true;
	}
	return false;
}

template<typename T> void LList_1d<T>::setCurr(item_1d<T> *t)
{
	currPtr = t;
}


template<typename T> item_1d<T> *LList_1d<T>::getHead()
{	
	return headPtr;
}

template<typename T> item_1d<T> *LList_1d<T>::getTail()
{	
	return tailPtr;
}

template<typename T> item_1d<T> *LList_1d<T>::getNext()
{	
	return currPtr->getNext();
}

template<typename T> item_1d<T> *LList_1d<T>::getPrev()
{	
	return currPtr->getPrev();
}

template<typename T> item_1d<T> *LList_1d<T>::getCurr()
{
	return currPtr;
}

template<typename T> item_1d<T> *LList_1d<T>::getNode(int num)
{
	if(currPtr->getCoord()>num)
		while(currPtr->getCoord()>num)
			moveP();
	else if(currPtr->getCoord()<num)
		while(currPtr->getCoord()<num)
			moveN();
	//else
		//return currPtr->getData();
	return currPtr;
}

//----------------------------------------

template<typename T> bool LList_1d<T>::inList(T data_comp)
{
	item_1d<T> *temp = currPtr;

	for(setCurr(headPtr); currPtr->getLoc() <= tailPtr->getLoc(); moveN())
	{
		if(data_comp == currPtr->getData())
		{
			currPtr = temp;
			return true;
		}
	}
	currPtr = temp;
	return false;
}

//--------------------------------------

template<typename T> T LList_1d<T>::getCurrItem()
{
	return currPtr->getData();
}

template<typename T> T LList_1d<T>::getHeadItem()
{
	return getHead()->getData();
}

template<typename T> T LList_1d<T>::getTailItem()
{
	return getTail()->getData();
}

template<typename T> T LList_1d<T>::getNextItem()
{
	return getNext()->getData();
}

template<typename T> T LList_1d<T>::getPrevItem()
{
	return getPrev()->getData();
}

template<typename T> T LList_1d<T>::getItemAt(int num)
{
	item_1d<T> *temp = currPtr;
	if(currPtr->getCoord()>num)
		while(currPtr->getCoord()>num)
			moveP();
	else if(currPtr->getCoord()<num)
		while(currPtr->getCoord()<num)
			moveN();

	T this_data = currPtr->getData();

	currPtr = temp;

	return this_data;
}

//==========================================================================

template<typename T> void LList_1d<T>::count()
{
	item_1d<T> *temp_ = getHead();
	
	int i = 0;
	while(temp_->getNext())
	{
		i++;
		
		temp_ = temp_->getNext();
		temp_->setCoord(i);
		
	}
	count_ = i+1;
	
}

template<typename T> int LList_1d<T>::getCount()
{
	return count_;
}

//===================================================================================

template<typename T> void LList_1d<T>::addToHead(const T &itemPtr)
{
		setCurr(headPtr);
	addPrev(itemPtr);
}

template<typename T> void LList_1d<T>::addToTail(const T &itemPtr)
{

	setCurr(tailPtr);
	addNext(itemPtr);
	
}

template<typename T> void LList_1d<T>::addNext(const T &itemPtr)
{
	item_1d<T> *temp_ = new item_1d<T>(itemPtr);
	
	if(this->currPtr->getNext())
	{
		item_1d<T> *_next_ = this->currPtr->getNext();
		_next_->setPrev(temp_);
		temp_->setNext(_next_);
		temp_->setCoord(_next_->getCoord());
		_next_->setCoord(temp_->getCoord()+1);
	}else
		temp_->setCoord(currPtr->getCoord()+1);
		
		
		temp_->setPrev(this->currPtr);
		this->currPtr->setNext(temp_);

		setCurr(currPtr->getNext());
		setHead();
		setTail();
		count();
}

template<typename T> void LList_1d<T>::addPrev(const T &itemPtr)
{
	item_1d<T> *temp_ = new item_1d<T>(itemPtr);
	
	if(this->currPtr->getPrev())
	{
		item_1d<T> *_prev_ = this->currPtr->getPrev();
		_prev_->setNext(temp_);
		temp_->setPrev(_prev_);
		temp_->setCoord(_prev_->getCoord()+1);
		currPtr->setCoord(temp_->getCoord()+1);
	}else
		temp_->setCoord(currPtr->getCoord());
		
		
		temp_->setNext(this->currPtr);
		this->currPtr->setPrev(temp_);
	

		setCurr(currPtr->getPrev());
		setHead();
		setTail();
		count();
	
}

//===================================================================================

template<typename T> void LList_1d<T>::remHead()
{
	if(currPtr=headPtr)
		moveN(); //currPtr=currPtr->getNext();

	item_1d<T> *del_this = headPtr;
	//headPtr=nullptr;
	delete del_this;
	del_this = nullptr;

	currPtr->setPrev(nullptr);
	headPtr = currPtr;

	item_1d<T> *temp_ = headPtr;
	temp_->setCoord(0);
	for(int i = 1; moveN(temp_); i++)
		temp_->setCoord(i);

	recalculateAll();
}

template<typename T> void LList_1d<T>::remTail()
{
	if(currPtr=tailPtr)
		currPtr=currPtr->getPrev();

	item_1d<T> *del_this = tailPtr;
	tailPtr=nullptr;

	del_this = nullptr;
	delete del_this;

	currPtr->setNext(nullptr);
	
	recalculateAll();
}

template<typename T> void LList_1d<T>::remNext()
{
	if(currPtr->getNext())
	{
		item_1d<T> *temp_ = currPtr->getNext();
		item_1d<T> *temp_2 = temp_->getNext();

		currPtr->setNext(temp_2);
		temp_2->setPrev(currPtr);
		temp_->setNext(nullptr);
		temp_->setPrev(nullptr);
		delete temp_;

		temp_2 = currPtr;
		for(int i = currPtr->getCoord()+1; moveN(temp_2); i++)
		{
			temp_2->setCoord(i);
		}

		recalculateAll();
	}
}

template<typename T> void LList_1d<T>::remPrev()
{
	if(currPtr->getPrev())
	{
		item_1d<T> *temp_ = currPtr->getPrev();
		item_1d<T> *temp_2 = temp_->getPrev();

		currPtr->setPrev(temp_2);
		temp_2->setNext(currPtr);
		temp_->setPrev(nullptr);
		temp_->setNext(nullptr);
		delete temp_;
		
		temp_2 = currPtr->getPrev();
		for(int i = temp_2->getCoord()+1; moveN(temp_2); i++)
		{
			temp_2->setCoord(i);
		}

		recalculateAll();
	}
}

template<typename T> bool LList_1d<T>::remThis()
{
	if(currPtr->getNext())
	{
		item_1d<T> *temp_prev = currPtr->getPrev();
		item_1d<T> *temp_del = currPtr;
		currPtr = currPtr->getNext();

		temp_del->setNext(nullptr);
		temp_del->setPrev(nullptr);
		delete temp_del;

		temp_prev->setNext(currPtr);
		currPtr->setPrev(temp_prev);

		recalculateAll();
		return true;
		
	}
	else if(currPtr->getPrev())
	{
		item_1d<T> *temp_next = currPtr->getNext();
		item_1d<T> *temp_del = currPtr;
		currPtr = currPtr->getPrev();

		temp_del->setNext(nullptr);
		temp_del->setPrev(nullptr);
		delete temp_del;

		temp_next->setPrev(currPtr);
		currPtr->setNext(temp_next);

		recalculateAll();

		return true;
	}
	else
	{
		return false;
	}
}

//===========================================================================

template<typename T> bool LList_1d<T>::remNodeFromHead(const T &)
{
	item_1d<T> *temp_ = headPtr;
	
	while(temp_->getData!=T)
	{
		temp_ = temp_->getNext();
		if(temp_ == tailPtr)
			return false;
	}
	currPtr = temp_;
	return remThis();
}

template<typename T> bool LList_1d<T>::remNodeFromTail(const T &)
{
	item_1d<T> *temp_ = tailPtr;
	
	while(temp_->getData!=T)
	{
		temp_ = temp_->getPrev();
		if(temp_ == headPtr)
			return false;
	}
	currPtr = temp_;
	return remThis();
}

template<typename T> bool LList_1d<T>::remNodeFromHead(const T *, int n)
{
	item_1d<T> *temp_ = headPtr;
	int i = 0;	int x = 0;

	do
	{
		if(temp_->getData==T)
		{
			currPtr=temp_;
			if(remThis())
			{
				i++;
			}
		}
		
		if(temp_ == tailPtr || i==n)
			return false;
		temp_ = temp_->getNext();
		x++;

	}while(i<n && x < count_);

	return true;

}//number of times

template<typename T> bool LList_1d<T>::remNodeFromTail(const T *, int n)
{
	item_1d<T> *temp_ = tailPtr;
	int i = 0;	int x = 0;

	do
	{
		if(temp_->getData==T)
		{
			currPtr=temp_;
			if(remThis())
			{
				i++;
			}
		}
		
		if(temp_ == headPtr || i==n)
			return false;
		temp_ = temp_->getPrev();
		x++;

	}while(i<n && x < count_);

	return true;
}//number of times

template<typename T> bool LList_1d<T>::remAll(const T &)
{
	item_1d<T> *temp_ = headPtr;
	int x = 0;

	do
	{
		if(temp_->getData==T)
		{
			currPtr=temp_;
			remThis();
		}
		
		if(temp_ == tailPtr)
			return false;
		temp_ = temp_->getNext();
		x++;

	}while(x < count_);

	return true;
}

template<typename T> void LList_1d<T>::remAllEmptyNodes()
{
}

//===============================================================
#endif