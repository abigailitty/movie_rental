#include "dvd.h"
#include<iostream>

using namespace std;

Dvd::Dvd(const string& n, int c)
{
	name = n;
	copies = c;
	copies_checked_out = 0;
}

void Dvd::print(std::ostream &ostr)
{
	ostr << name << ":" << endl;

	if(copies_checked_out == 1)
		ostr << "  " << copies_checked_out << " copy checked out";
	else if(copies_checked_out > 1)
		ostr << "  " << copies_checked_out << " copies checked out";
	else //copies_checked_out
		ostr << "  ";

	if(copies - copies_checked_out == 0)
		ostr << endl;

	if(copies != copies_checked_out)
	{
		if(copies_checked_out > 0)
			ostr << " and ";

		if((copies - copies_checked_out) == 1)
			ostr << 1 << " copy available" << endl;
		else
			ostr << copies - copies_checked_out << " copies available" << endl;
	}
}