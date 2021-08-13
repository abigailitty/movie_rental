#ifndef __customer_h_
#define __customer_h_

#include <string>
#include <list>

using namespace std;

class Customer
{
	private:
		string name;
		list<string> preferences;
		list<string> borrowing;
		int movies_held;

	public:
		//constructor
		Customer(const string& n, const list<string> p);

		//accessors
		const string& get_name() { return name; }
		list<string>& getPreferences() { return preferences; }
		const list<string>& getBorrowing() { return borrowing; }
		int getMoviesHeld() const { return movies_held; } //const?

		//modifiers
		void addPreference(string& name) {preferences.push_back(name);} //do you need iterators for these next 3 bc you're traversing a list?
		void borrowMovie(const string& name);
		string returnNewestMovie();
		string returnOldestMovie();

		bool findMovie(string& name);

		//print
		void print(std::ostream &ostr);
};

//bool findMovie(Customer& cust, string& name);

#endif