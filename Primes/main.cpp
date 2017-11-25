
#include <iostream>
#include "Primes.h"
#include <string>
#include <time.h>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	ofstream ofile;
	ofile.open("compileTime.txt",ios::out);
	if(!ofile)
		exit(1);

	time_t start;
	struct tm  startTimeInfo;
	time(&start);
	localtime_s(&startTimeInfo,&start);
	char strStart[26];
	asctime_s(strStart,sizeof strStart,&startTimeInfo);
	cout<<strStart<<endl;
	ofile<<strStart<<endl;

	//num_set set_a = num_set(13);
	//num_set set_a = num_set(2, 65000, 6);
	num_set set_a = num_set(2, 75000, 6);
	//num_set set_a = num_set(2, 48000, 6);
	//num_set set_a = num_set(48001, 75000, 6);
	//num_set set_a = num_set(75001, 95000, 6);
	//num_set set_a = num_set(95000, 110000, 6);
	//num_set set_a = num_set(110000, 120001, 6);
	//num_set set_a = num_set(120002, 135000, 6);
	//num_set set_a = num_set(135001, 160000, 6);
	
	time_t mid;
	struct tm  midTimeInfo;
	char strMid[26];
	
	time(&mid);
		localtime_s(&midTimeInfo,&mid);
		asctime_s(strMid,sizeof strMid,&midTimeInfo);
		cout<<strStart<<endl<<strMid<<endl;
		ofile<<")--> "<<strMid<<endl;

	set_a.writeAll();

	/*
	time_t mid;
	struct tm  midTimeInfo;
	char strMid[26];
	
	num_set set_a = num_set(2);
	string prime_file;

	for(int i = 0; i<=20; i++)
	{
		set_a = num_set(2);

		if(i>0)
			set_a = num_set(2+2000*i, 2001+2000*i,"prime_list"+ prime_file);
		else
			set_a = num_set(2001+2000*i);
		
		prime_file = "_" + to_string(i);
		set_a.writeAll(prime_file);

		time(&mid);
		localtime_s(&midTimeInfo,&mid);
		asctime_s(strMid,sizeof strMid,&midTimeInfo);
		cout<<strStart<<endl<<strMid<<endl;
		ofile<<i<<")--> "<<strMid<<endl;
	}
	*/
	
	time_t endtime;
	struct tm  endTimeInfo;
	time(&endtime);
	localtime_s(&endTimeInfo,&endtime);
	char strEnd[26];
	asctime_s(strEnd,sizeof strEnd,&endTimeInfo);
	cout<<strStart<<endl<<strEnd<<endl;
	ofile<<"COMPLETED"<<endl<<strEnd<<endl;
	ofile.close();

	return 0;
}


/*
int main()
{
	time_t start;
	struct tm  startTimeInfo;
	time(&start);
	localtime_s(&startTimeInfo,&start);
	char strStart[26];
	asctime_s(strStart,sizeof strStart,&startTimeInfo);
	cout<<strStart<<endl;

	num_set set_a = num_set(32767, 41249,"OLD-prime_list");
	
	time_t mid;
	struct tm  midTimeInfo;
	time(&mid);
	localtime_s(&midTimeInfo,&mid);
	char strMid[26];
	asctime_s(strMid,sizeof strMid,&midTimeInfo);
	cout<<strStart<<endl<<strMid<<endl;
	
	set_a.writeAll("_a_");
	
	time_t endtime;
	struct tm  endTimeInfo;
	time(&endtime);
	localtime_s(&endTimeInfo,&endtime);
	char strEnd[26];
	asctime_s(strEnd,sizeof strEnd,&endTimeInfo);
	cout<<strStart<<endl<<strMid<<endl<<strEnd<<endl;
	return 0;
}
*/