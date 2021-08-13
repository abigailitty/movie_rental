//dvd class h file

#ifndef __dvd_h_
#define __dvd_h_

#include <string>

using namespace std;

class Dvd
{
	private:
		int copies;
		int copies_checked_out;
		string name;

	public:
		//constructor
		Dvd(const string& name, int copies);

		//accessors
		int getCopies() const { return copies;} //const?
		int getCopiesCheckedOut() const {return copies_checked_out;}
		string& get_name() { return name;} //const?

		

		//modifiers
		void setCopies(const int c){ copies = c; };
		void addCopies(const int c){ copies += c; };
		void returnCopy(){ copies_checked_out--; }
		void borrowCopy(){ copies_checked_out++; }

		//print
		void print(std::ostream &ostr);
};

#endif