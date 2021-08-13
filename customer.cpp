#include <iostream>

#include "customer.h"
//#include <string>
//#include <list>

using namespace std;

Customer::Customer(const string& n, const list<string> p)
{
	name = n;
	preferences = p;
	list<string> borrowing;
	movies_held = 0;
}

void Customer::borrowMovie(const string& n)
{
	borrowing.push_back(n);

	list<string>::iterator p = preferences.begin();
	while(*p != n)
		p++;

	preferences.erase(p); //p is invalidated, reset it if you try to use it again

	movies_held++;
}

string Customer::returnNewestMovie()
{
	movies_held--;
	
	list<string>::iterator b = borrowing.end();
	b--;

	string movie_name = *b;

	borrowing.pop_back();

	return movie_name;
}

string Customer::returnOldestMovie()
{
	movies_held--;
	
	list<string>::iterator b = borrowing.begin();
	string movie_name = *b;

	borrowing.pop_front();

	return movie_name;
}

bool Customer::findMovie(string& n) //Customer& cust
{
	//list<string> pref = cust.getPreferences();
	list<string>::iterator p = preferences.begin();
	bool found = false;

	while(p != preferences.end())
	{
		if(*p == n)
			found = true;
		p++;
	}
	return found;
}

void Customer::print(std::ostream &ostr)
{
	ostr << name << " has ";
	if(movies_held == 0)
		ostr << "no movies" << endl;
	else
	{
		if(movies_held == 1)
			ostr << movies_held << " movie:" << endl;
		else
			ostr << movies_held << " movies:" << endl;
		for(list<string>::iterator m = borrowing.begin(); m != borrowing.end(); m++)
			ostr << "    " << *m << endl;
	}

	if(!preferences.empty())
	{
		ostr << "  preference list:" << endl;
		for(list<string>::iterator s = preferences.begin(); s != preferences.end(); s++)
			ostr << "    " << *s << endl;
	}
}