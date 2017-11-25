#ifndef PRIMES_H
#define PRIMES_H

#include "LList1D.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>

using namespace std;

class number_base
{
	
public:
	~number_base();
	int num;
	LList_1d<int> *factors;
	int factor_unique;
	int factor_count;
	int factor_sum;
	bool isPrime;

	number_base();
	number_base(int x);

	void setNum(int i);
	int getNum();
};

class number: public number_base
{
public:
	number();
	number(int i);
};

class prime: public number_base
{
public:
	prime(int i);
	prime();
};

class num_set
{
	LList_1d<number> *number_set;
	LList_1d<prime> *prime_set;

public:
	~num_set();
	num_set(int head, int tail, int divisor);
	num_set(int head, int tail);
	num_set(int tail);
	num_set(int head, int tail, string primeFile);
	int getNumber();

	bool loadPrimes();
	bool loadPrimes(string id);

	bool writeFrom(int from_, int to_);
	bool writeTo(int x);
	void writeAll();
	void write(int f, int t);
	void writeAll(string id);
	void write(int f, int t, string id);
	void writePrimes();
	void writeBAint(int divisor);


	bool printFrom(int from_, int to_);
	bool printTo(int x);
	void printAll();
	void print(int f, int t);
	void printPrimes();

	bool isPrimeChecker(int i, LList_1d<prime> p_s);
	int calcFactor(int n, int p);
	bool inList(int n, LList_1d<number> *list_);
	bool inList(LList_1d<prime> *list_,int n);
};

//============================

num_set::~num_set()
{
	number_set = nullptr;
	prime_set = nullptr;
}

number_base::~number_base()
{
	isPrime = false;
	factors = nullptr;
	factor_unique = 0;
	factor_count = 0;
	num = 0;
}


//===========================

number_base::number_base()
{
}

number_base::number_base(int x)
{
	num = x;
}

void number_base::setNum(int i)
{
	num = i;
}
int number_base::getNum()
{
	return num;
}

//======================

number::number(){}

number::number(int i)
{
	num = i;
}

//-----------------

prime::prime(){}

prime::prime(int i)
{
	num = i;
}

//----------------

int num_set::getNumber()
{
	return number_set->getCurrItem().getNum();
}

//========================================================

void num_set::writeBAint(int divisor)
{
}

//---------------------------------------

void num_set::writeAll(string id)
{
	write(2,number_set->getCount()+2, id);
}

void num_set::write(int f, int t, string id)
{
	ofstream ofile, ofile2, ofile3, ofile4;
	ofile.open("composites/factor_list"+id+".txt",ios::out);
	ofile2.open("primes/prime_list"+id+".txt",ios::out);
	ofile3.open("composites/factor_stats"+id+".txt",ios::out);
	ofile4.open("composites/factor_list_short"+id+".txt",ios::out);

	prime_set->setCurr(prime_set->getHead());
	int prime_num;
	int prime_count = prime_set->getCount();
	for(int i = 0; i<prime_count;i++)
	{
		prime_num = prime_set->getCurrItem().getNum();
		ofile<< prime_num <<"|";
		ofile2<<prime_num;
		cout<<prime_num<<"|";
		if(i<(prime_count-1))
			ofile2<<endl;
		prime_set->moveN();
	}
	ofile2.close();
	ofile<<endl;
	ofile<<"------------------------------------------------------------\n";
	cout<<"\n------------------------------------------------------------\n";
	number_set->setCurr(number_set->getHead());
	int prevPrime = 2;
	while(prevPrime < f)
	for(int i = f; i < t; i++)
	{
		ofile<<number_set->getCurrItem().getNum()<<": ";
		ofile4<<number_set->getCurrItem().getNum()<<": ";
		ofile3<<number_set->getCurrItem().getNum()<<": "<<
			number_set->getCurrItem().factor_unique<<"uniques | "<<
			number_set->getCurrItem().factor_count<<"count | "<<
			number_set->getCurrItem().factor_sum<<"sum\n";
		cout<<number_set->getCurrItem().getNum()<<": ";

		LList_1d<int> *this_factors = number_set->getCurrItem().factors;
		this_factors->setCurr(this_factors->getHead());
		int factor_count_ = this_factors->getCount();
		prime_set->setCurr(prime_set->getHead());
	
		for(int j = 0; j < factor_count_; j++)
		{
			if(this_factors->getCurrItem()!=0)
			{
				ofile<<this_factors->getCurrItem()<<" ";
				ofile4<<"{"<<prime_set->getCurrItem().getNum()<<":"<<this_factors->getCurrItem()<<"} ";
				cout<<"{"<<prime_set->getCurrItem().getNum()<<":"<<this_factors->getCurrItem()<<"} ";

				if(prime_set->getCurrItem().getNum()==number_set->getCurrItem().getNum())
				{
					ofile4<<" <<-- PRIME [Last prime was: "<<prevPrime;
					cout<<" <<-- PRIME";
					prevPrime = prime_set->getCurrItem().getNum();
				}
				
			}else
			{
				ofile<<"_ ";
				//cout<<".";
			}
			prime_set->moveN();
			this_factors->moveN();
		}
		number_set->moveN();
		ofile<<endl;
		ofile4<<endl;
		cout<<endl;
	}
	ofile<<"------------------------------------------------------------\n";
	cout<<"----------------------END-------------------------------\n";
	ofile3.close();
	ofile.close();
	ofile4.close();

}

//--------------------------------------------------------

void num_set::writeAll()
{
	cout<<number_set->getCount()<<endl;
	write(2,number_set->getCount()+1);
}

void num_set::write(int f, int t)
{
	ofstream ofile, ofile2, ofile3, ofile4;
	ofile.open("composites/factor_list.txt",ios::out);
	ofile2.open("primes/prime_list.txt",ios::out);
	ofile3.open("composites/factor_stats.txt",ios::out);
	ofile4.open("composites/factor_list_short.txt",ios::out);

	prime_set->setCurr(prime_set->getHead());
	int prime_num;
	int prime_count = prime_set->getCount();
	int i,j;
	
	for(i = 0; i<prime_count;i++)
	{
		prime_num = prime_set->getItemAt(i).getNum();
		ofile<< prime_num <<"|";
		ofile2<<prime_num;
		cout<<prime_num<<"|";
		if(i<(prime_count-1))
			ofile2<<endl;
		prime_set->moveN();
	}
	ofile2.close();
	ofile<<endl;
	ofile<<"------------------------------------------------------------\n";
	cout<<"\n------------------------------------------------------------\n";
	number_set->setCurr(number_set->getHead());
	
	LList_1d<int> *this_factors;
	int factor_count_;
	
	int compA, compB, powa, powb;
	int current_num, thisPrime, currFactor;
	number curr_num;
	int checker;//	int k;
	for(i = f; i <= t; i++)
	{
		curr_num = number_set->getCurrItem();
		current_num = curr_num.getNum();
		ofile<<current_num<<": ";
		ofile4<<current_num<<": ";
		ofile3<<current_num<<": "<<
			curr_num.factor_unique<<"unique | "<<
			curr_num.factor_count<<"count | "<<
			curr_num.factor_sum<<"sum\n";
		cout<<current_num<<": ";
		checker = 1;

		this_factors = curr_num.factors;
		this_factors->setCurr(this_factors->getHead());
		factor_count_ = this_factors->getCount();
		prime_set->setCurr(prime_set->getHead());
		//if(!inList(prime_set,current_num))
		{
			for(j = 0; j < factor_count_; j++)
			{

				thisPrime = prime_set->getItemAt(j).getNum();//->getCurrItem().getNum();

				currFactor = this_factors->getCurrItem();
			//	cout<<thisPrime<<" : "<<currFactor<<endl;
				if(currFactor!=0)
				{
					//for(k = 0; k<currFactor; k++)
			//		cout<<"test 1"<<endl;
					checker *= pow(thisPrime,currFactor);


					ofile<<currFactor<<" ";
					ofile4<<"{"<<thisPrime<<":"<<currFactor<<"} ";
					cout<<"{"<<thisPrime<<":"<<currFactor;
					cout<<"} ";		
		
					if(checker==current_num)
						break;
				}else
				{
					ofile<<"_ ";
					//cout<<".";
				}

		//		cout<<"test 1"<<endl;
				this_factors->moveN();
				//prime_set->moveN();
			}
		}

		if(current_num>3)
		{
		 compA = this_factors->getItemAt(0);
		 compB = this_factors->getItemAt(1);
		}
		 powa, powb;
		// cout<<endl<<"testing -- -- "<<current_num<<" -- -- testing"<<endl;		current_num==2|| current_num==3 ||
		 if(current_num==2||  (curr_num.factor_sum == current_num && curr_num.factor_count==1))//inList(prime_set,current_num))//prime_set->getCurrItem().getNum()==current_num)
		{
			ofile4<<" <<-- PRIME";
			cout<<" <<-- PRIME";
		}else if(compA > 0 && compB > 0)
		{
			ofile4<<" <<-- 6 {";
			cout<<" <<-- 6 {";
			if(compA > compB)
			{
				powb = pow(6,compB);
				ofile4<<compB<<"} "<<powb;
				cout<<compB<<"} "<<powb;
			}
			else
			{
				powa = pow(6,compA);
				ofile4<<compA<<"} "<<powa;
				cout<<compA<<"} "<<powa;
			}

		}
		
		number_set->moveN();
		ofile4<<endl;
		ofile<<endl;
		cout<<endl;
	}
	ofile<<"------------------------------------------------------------\n";
	cout<<"----------------------END-------------------------------\n";
	ofile3.close();
	ofile.close();
	ofile4.close();

}

//=========================================================

bool num_set::printFrom(int from_, int to_)
{
	int i = number_set->getHeadItem().getNum();

	if(from_>to_ || from_<i || to_>(number_set->getCount()+i))
	{
		return false;
	}
	
	cout<<"=========//Print From ("<<from_<<", "<<to_<<")//=============\n n : ";

	printPrimes();
	print(from_,to_);
		return true;
}

bool num_set::printTo(int x)
{
	int i = number_set->getHeadItem().getNum();

	if(x>(number_set->getCount()+i))
	{
		return false;
	}
	
	cout<<"=========//Print To ("<<x<<")//=============\n n : ";

	printPrimes();
	print(i,x);
	
		return true;
}

void num_set::printAll()
{
	cout<<"=========//Print ALL ()//=============\n n : ";
	printPrimes();
	int i = number_set->getHeadItem().getNum();
	print(i,number_set->getCount()+i);
}

void num_set::printPrimes()
{
	prime_set->setCurr(prime_set->getHead());
	for(int i = 0; i<prime_set->getCount();i++)
	{
		cout<<prime_set->getCurrItem().getNum()<<"|";
		prime_set->moveN();
	}
	cout<<endl;
}

void num_set::print(int f, int t)
{
	cout<<"------------------------------------------------------------\n";
	number_set->setCurr(number_set->getHead());

	for(int i = f; i < t; i++)
	{
		cout<<number_set->getCurrItem().getNum()<<": ";
		LList_1d<int> *this_factors = number_set->getCurrItem().factors;
		this_factors->setCurr(this_factors->getHead());
		int factor_count_ = this_factors->getCount();
		for(int j = 0; j < factor_count_; j++)
		{
			if(this_factors->getCurrItem()!=0)
				cout<<this_factors->getCurrItem()<<" ";
			else
				cout<<". ";
			this_factors->moveN();
		}
		number_set->moveN();
		cout<<endl;
	}
	cout<<"------------------------------------------------------------\n";
}

//=====================================================


bool num_set::loadPrimes(string id)
{
	cout<<"opening Primes: "<<id<<".txt\n";
	ifstream infile;
	infile.open("primes/"+id+".txt", ios::in);
	if(!infile)
		return false;

	
	bool start = true;
	cout<<"loading Primes";
	while(!infile.eof())
	{
		cout<<".";
		int a;
		infile >> a;
		prime w(a);
		cout<<a;
		if(!start)
			prime_set->addToTail(w);
		else
			prime_set = new LList_1d<prime>(w);

		start= false;
			
	}
	cout<<"\nLoading Complete"<<endl;
	cout<<"Final Prime Loaded: "<<prime_set->getTailItem().getNum()<<endl;
	infile.close();
	return true;
}

num_set::num_set(int head, int tail, string primeFile)
{
	if(loadPrimes(primeFile))
	{
		//=====initialize set with number 2========
	cout<<"\nBuilding: "<<head<<" to "<<tail;
	number *num_;
	prime *p_num;

	int checker;
	LList_1d<int> *factor;

	bool start = true;

	bool hasFactor;
	int i_factor_unique, i_factor_count, i_factor_sum;
	int factor_int, prime_curr;

	//=====continue list from number 3 onwards=======
	for(int i = head; i <= tail; i++)
	{
		cout<<"\nBuilding: "<<i;
		num_ = new number(i);
		
		 hasFactor = false;
		num_->isPrime = false;
		prime_set->setCurr(prime_set->getHead());
		 i_factor_unique = 0;
		 i_factor_count= 0;
		 i_factor_sum = 0;
		checker = 1;
		factor = new LList_1d<int>(calcFactor(num_->getNum(),2));
		factor_int = factor->getCurrItem();
		 prime_curr = prime_set->getCurrItem().getNum();
		if(factor_int>0)
		{
			i_factor_count += factor_int;
			i_factor_unique++;
			i_factor_sum += (factor_int*prime_curr);
			hasFactor = true;
			cout<<".";
		checker *= (prime_curr^factor_int);
		}

		while(prime_set->getCurrItem().getNum() <= prime_set->getItemAt(prime_set->getTail()->getCoord()/2+1).getNum() && checker != num_->getNum())
		{
			prime_set->moveN();

			factor->addNext(calcFactor(num_->getNum(),prime_set->getCurrItem().getNum()));
			factor_int = factor->getCurrItem();
			prime_curr = prime_set->getCurrItem().getNum();
			if(factor_int>0)
			{
				i_factor_count += factor->getCurrItem();
				i_factor_unique++;
				i_factor_sum += (factor_int*prime_curr);
				hasFactor = true;
				cout<<".";
				checker *= (prime_curr^factor_int);
			}
		}

		if(!hasFactor)
			num_->isPrime = true;
		

		if(num_->isPrime)
		{
			i_factor_count = 1;
			i_factor_unique = 1;
			i_factor_sum += num_->getNum();
			factor->addNext(1);
			p_num = new prime(num_->getNum());
			prime_set->addNext(*p_num);
		}
		num_->factors = factor;
		num_->factor_unique = i_factor_unique;
		num_->factor_count = i_factor_count;
		num_->factor_sum = i_factor_sum;

		if(!start)
			number_set->addNext(*num_);
		else
			number_set = new LList_1d<number>(*num_);
		
		start = false;
	}
	cout<<endl;
	}else
		cout<<"primes could not be loaded";
}


//-------------------------------------------

bool num_set::loadPrimes()
{
	ifstream infile;
	infile.open("primes/prime_list.txt", ios::in);
	if(!infile)
		return false;

	
	bool start = true;
	
	cout<<"LOADING PRIMES"<<endl;
	while(!infile.eof())
	{
		int a;
		infile >> a;
		cout<<a<<"|";
		prime w(a);
		if(!start)
			prime_set->addToTail(w);
		else
			prime_set = new LList_1d<prime>(w);

		start= false;
			
	}
	cout<<endl<<endl;
	
	infile.close();
	return true;
}

num_set::num_set(int head, int tail, int divisor)
{
	if(loadPrimes())
	{
		//=====initialize set with number 2========
		cout<<"\nBuilding: "<<head;
		number *num_;// = new number(head);
		prime *p_num;// = new prime();

		LList_1d<int> *factor;
		int checker;
		bool start = true;
		bool hasFactor;
		int i_factor_unique, i_factor_count, i_factor_sum;
		int factor_int, prime_curr, prime_tail;
		int compA, compB;
		int currNum;
		for(int i = head; i <= tail; i++)
		{
			if((i+1)%divisor==0 || i%divisor==0 || (i-1)%divisor==0)
			{
				cout<<"\nBuilding: "<<i;
				num_ = new number(i);
				currNum = num_->getNum();
				hasFactor = false;
				num_->isPrime = false;
				prime_set->setCurr(prime_set->getHead());
				i_factor_unique = 0;
				i_factor_count= 0;
				i_factor_sum = 0;
				checker = 1;
				factor = new LList_1d<int>(calcFactor(currNum,2));
				factor_int = factor->getCurrItem();
				prime_curr = prime_set->getCurrItem().getNum();
				prime_tail = prime_set->getTailItem().getNum();

				if(factor_int>0)
				{
					i_factor_count += factor_int;//->getHeadItem();
					i_factor_unique++;
					i_factor_sum += (factor_int*prime_curr);
					hasFactor = true;
					cout<<".";
					checker *= (prime_curr^factor_int);
				}

				while(prime_set->getCurrItem().getNum() <= prime_set->getItemAt(prime_set->getTail()->getCoord()/2).getNum() && checker != currNum)
				{
					prime_set->moveN();
					//=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.
					prime_curr = prime_set->getCurrItem().getNum();
					factor->addNext(calcFactor(currNum,prime_curr));
					factor_int = factor->getCurrItem();
					if(factor_int>0)
					{
						i_factor_count += factor_int;
						i_factor_unique++;
						i_factor_sum += (factor_int*prime_curr);
						hasFactor = true;
						cout<<".";
						checker *= (prime_curr^factor_int);
					}
				}

				if(!hasFactor)
					num_->isPrime = true;


				if(num_->isPrime)
				{
					cout<<" <<-- PRIME";
					if(!inList(prime_set,currNum))
					{
					i_factor_count = 1;
					i_factor_unique = 1;
					i_factor_sum += currNum;
					factor->addNext(1);
					p_num = new prime(currNum);
					prime_set->addToTail(*p_num);
					}
				}

				 compA = factor->getItemAt(0);
				 compB = factor->getItemAt(1);
		
				if(compA > 0 && compB > 0)
				{
					cout<<" <<-- 6 {";
					if(compA > compB)
					{
						cout<<compB<<"} "<<pow(6,compB);
					}
					else
					{
						cout<<compA<<"} "<<pow(6,compA);
					}
				}else if(inList(prime_set,currNum))
				{
					cout<<" <<-- PRIME";
				}

				num_->factors = factor;
				num_->factor_unique = i_factor_unique;
				num_->factor_count = i_factor_count;
				num_->factor_sum = i_factor_sum;
				if(!start)
					number_set->addToTail(*num_);
				else
					number_set = new LList_1d<number>(*num_);

				start = false;
			}else if(isPrimeChecker(i,*prime_set))
			{
				cout<<endl<<"new prime: "<<i<<" <<-- PRIME"<<endl;
				p_num = new prime(i);
				p_num->isPrime=true;
				prime_set->addToTail(*p_num);
			}
		}
		cout<<endl;
	}else
		cout<<"primes could not be loaded";
}

num_set::num_set(int head, int tail)
{
	if(loadPrimes())
	{
		//=====initialize set with number 2========
	cout<<"\nBuilding: "<<head;
	number *num_;// = new number(head);
	prime *p_num;// = new prime();

	LList_1d<int> *factor;
	int checker;
	bool start = true;

	//=====continue list from number 3 onwards=======
	for(int i = head; i <= tail; i++)
	{
		cout<<"\nBuilding: "<<i;
		num_ = new number(i);
		
		bool hasFactor = false;
		num_->isPrime = false;
		prime_set->setCurr(prime_set->getHead());
		int i_factor_unique = 0;
		int i_factor_count= 0;
		int i_factor_sum = 0;
		checker = 1;
		factor = new LList_1d<int>(calcFactor(num_->getNum(),2));
		if(factor->getHeadItem()>0)
		{
			i_factor_count += factor->getHeadItem();
			i_factor_unique++;
			i_factor_sum += (factor->getCurrItem()*prime_set->getCurrItem().getNum());
			hasFactor = true;
			cout<<".";
		checker *= (prime_set->getCurrItem().getNum()^factor->getHeadItem());
		}
		
		while(prime_set->getCurrItem().getNum() <= prime_set->getItemAt(prime_set->getTail()->getCoord()/2).getNum() && checker != num_->getNum())
		{
			prime_set->moveN();
//=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.=-.
			factor->addNext(calcFactor(num_->getNum(),prime_set->getCurrItem().getNum()));
			if(factor->getCurrItem()>0)
			{
				i_factor_count += factor->getCurrItem();
				i_factor_unique++;
				i_factor_sum += (factor->getCurrItem()*prime_set->getCurrItem().getNum());
				hasFactor = true;
				cout<<".";
				checker *= (prime_set->getCurrItem().getNum()^factor->getCurrItem());
			}
		}

		if(!hasFactor)
			num_->isPrime = true;
		

		if(num_->isPrime)
		{
			cout<<" <<-- PRIME ";
			if(!inList(prime_set,num_->getNum()))
			{
			i_factor_count = 1;
			i_factor_unique = 1;
			i_factor_sum += (num_->getNum());

			factor->addNext(1);
			p_num = new prime(num_->getNum());
			prime_set->addNext(*p_num);
			}
		}
		num_->factors = factor;
		num_->factor_unique = i_factor_unique;
		num_->factor_count = i_factor_count;
		num_->factor_sum = i_factor_sum;
		if(!start)
			number_set->addNext(*num_);
		else
			number_set = new LList_1d<number>(*num_);
		
		start = false;
	}
	cout<<endl;
	}else
		cout<<"primes could not be loaded";
}

num_set::num_set(int tail)
{
	//=====initialize set with number 2========
	cout<<"\nBuilding: 2";
	number *num_ = new number(2);
	prime *p_num = new prime(2);

	LList_1d<int> *factor = new LList_1d<int>(1);
	
	num_->factors = factor;
	num_->factor_unique = 1;//factor_cnt;
	num_->factor_count = 1;//fac_count;
	num_->factor_sum = 2;

	number_set = new LList_1d<number>(*num_);
	prime_set = new LList_1d<prime>(*p_num);

	int i_factor_unique;
	int i_factor_count;
	int i_factor_sum;
	int checker;
	bool hasFactor;

	//=====continue list from number 3 onwards=======
	for(int i = 1; num_->getNum() < tail; i++)
	{
		cout<<"\nBuilding: "<<i+2;
		num_ = new number(i+2);
		
		 hasFactor = false;
		num_->isPrime = false;
		prime_set->setCurr(prime_set->getHead());
		 i_factor_unique = 0;
		 i_factor_count= 0;
		 i_factor_sum = 0;
		 checker = 1;

		factor = new LList_1d<int>(calcFactor(num_->getNum(),2));
		if(factor->getHeadItem()>0)
		{
			i_factor_count += factor->getHeadItem();
			i_factor_unique++;
			i_factor_sum += (factor->getCurrItem()*prime_set->getCurrItem().getNum());
			hasFactor = true;
			cout<<".";
			checker *= (prime_set->getCurrItem().getNum()^factor->getHeadItem());
		}

		while(prime_set->getCurrItem().getNum() < prime_set->getItemAt(prime_set->getTail()->getCoord()/2).getNum() && checker != num_->getNum())
		{
			cout<<"test"<<endl;
			prime_set->moveN();

			factor->addNext(calcFactor(num_->getNum(),prime_set->getCurrItem().getNum()));
			if(factor->getCurrItem()>0)
			{
				i_factor_count += factor->getCurrItem();
				i_factor_unique++;
				i_factor_sum += (factor->getCurrItem()*prime_set->getCurrItem().getNum());
				hasFactor = true;
				cout<<".";
				checker *= (prime_set->getCurrItem().getNum()^factor->getCurrItem());
			}
		}

		if(!hasFactor)
			num_->isPrime = true;
		
		if(i_factor_unique==1)
		{
			factor->addNext(0);
		}

		if(num_->isPrime)
		{
			i_factor_count = 1;
			i_factor_unique = 1;
			i_factor_sum += (num_->getNum());
			cout<<"this num is: "<<num_->getNum()<<endl;
			factor->addNext(1);
			p_num = new prime(num_->getNum());
			cout<<"adding this to prime: "<<p_num->getNum()<<endl;
			prime_set->addToTail(*p_num);
		}
		num_->factors = factor;
		num_->factor_unique = i_factor_unique;
		num_->factor_count = i_factor_count;
		num_->factor_sum = i_factor_sum;
		number_set->addNext(*num_);
		
		
	}
	cout<<endl;
}

//=============================================================

bool num_set::isPrimeChecker(int i, LList_1d<prime> p_s)
{
	int tailnum = p_s.getTailItem().getNum();
	int a = p_s.getHeadItem().getNum();
	for(p_s.setCurr(p_s.getHead()); a < tailnum; p_s.moveN())
	{
		a = p_s.getCurrItem().getNum();
		if(i==a || i%a==0)
			return false;
	}
	return true;
}

int num_set::calcFactor(int n, int p)
{

	if(n % p == 0)
	{
		int i;
		for(i = 0; n != 1 ; i++)
		{
			n /= p;

			if(n%p != 0)
			{
				i++;
				break;
			}
		}
			return i;
	}else
			return 0;
}

bool num_set::inList(int n, LList_1d<number> *list_)
{
	item_1d<number> *temp = list_->getCurr();
	for(list_->setCurr(list_->getHead());list_->getCurrItem().getNum() < n+1; list_->moveN())
	{
		if(list_->getCurrItem().getNum() == n)
		{
			list_->setCurr(temp);
			return true;
		}
	}
	list_->setCurr(temp);
	return false;
}

bool num_set::inList(LList_1d<prime> *list_,int n)
{
			

	item_1d<prime> *temp = list_->getCurr();
	int test = list_->getHeadItem().getNum();//int test = list_->getHeadItem().getNum();
	item_1d<prime> *end = list_->getTail();
	for(list_->setCurr(list_->getHead()); test<n && list_->getCurr() != end; list_->moveN())//list_->getCurr() != end; list_->moveN())
	{
		test = list_->getCurrItem().getNum();
		if(n%test>0)
			break;
		else if(test == n)
		{
			list_->setCurr(temp);
			return true;
		}
	}
	list_->setCurr(temp);
	return false;
}

//======================================================



#endif