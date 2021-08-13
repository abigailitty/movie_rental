// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "dvd.h"
#include "customer.h"

using namespace std;

// several type defs to keep things neat
// (hint, these are STL lists)
typedef list<Dvd> inventory_type;
typedef list<Customer> customers_type;
typedef list<string> preference_type; //do i need this???


// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// ==================================================================


void usage(const char* program_name) {
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}


int main(int argc, char* argv[]) 
{

  if (argc < 3 || argc > 5) {
    usage(argv[0]);
  }

  // open input and output file streams
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]); 
  }
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
    usage(argv[0]); 
  }

  // optional parameters for extra credit
  bool use_improved_algorithm = false;
  bool print_analysis = false;
  for (int i = 3; i < argc; i++) {
    if (std::string(argv[i]) == "--improved") {
      use_improved_algorithm = true;
    } else if (std::string(argv[i]) == "--analysis") {
      print_analysis = true;
    } else {
      usage(argv[0]);
    }
  }


  // list of DVDs that stores information about the DVDs
  inventory_type inventory;
  // list of Customers that stores information about the customers
  customers_type customers;


  // read in and handle each of the 8 keyword tokens
  std::string token;
  while (istr >> token) 
  {
    if (token == "dvd") 
    {
      std::string dvd_name = read_dvd_name(istr);
      int copies;
      istr >> copies;

      if(inventory.empty()) //if inventory is empty, just add the movie
        inventory.push_back(Dvd(dvd_name, copies)); 
      else
      {
        inventory_type::iterator m = inventory.begin(); //I named my inevtory iterators m for movie

        while(m != inventory.end() && m->get_name() != dvd_name) //check if movie is in inventory
          m++;

        if(m == inventory.end()) //no? then add it in
          inventory.push_back(Dvd(dvd_name, copies));
        else //yes? add on the number of copies
          m->addCopies(copies);
      }

      if(copies == 1)
        ostr << copies << " copy of " << dvd_name <<" added" << std::endl;
      else
        ostr << copies << " copies of " << dvd_name << " added" << std::endl;
    }

    else if (token == "customer") 
    {
      std::string customer_name = read_customer_name(istr);

      int num_movies;
      istr >> num_movies;

      preference_type list_of_preferences;
      for (int i = 0; i < num_movies; i++) //read in all movie preferences for specific customer
      {
        std::string dvd_name = read_dvd_name(istr);
        bool dont_add_movie = false;

        inventory_type::iterator m = inventory.begin();
        while(m != inventory.end() && m->get_name() != dvd_name) //make sure dvd is in inventory
          m++;

        if(m == inventory.end())
        {
          dont_add_movie = true;
          ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << endl;
        }

        if(!dont_add_movie)  
        {
          if(list_of_preferences.empty())
            list_of_preferences.push_back(dvd_name);
          else
          {
            preference_type::iterator p = list_of_preferences.begin(); //I named my preferences iterators p for preferences

            while(p != list_of_preferences.end() && *p != dvd_name)
              p++;

            if(*p != dvd_name)
              list_of_preferences.push_back(dvd_name);
            else
              ostr << "WARNING: Duplicate movie " << *p << " on preference list!" << endl;
          }

        }

      }

      if(customers.empty()) //make the customer if they're valid
      {
        customers.push_back(Customer(customer_name, list_of_preferences));
        ostr << "new customer: " << customer_name << std::endl;
      }
      else
      {
        customers_type::iterator c = customers.begin(); //i named my customer iterators c for customer

        while(c != customers.end() && c->get_name() != customer_name)
          c++; //i get so excited whenever I get to type this line lol

        if(c == customers.end())
        {
          customers.push_back(Customer(customer_name, list_of_preferences));
          ostr << "new customer: " << customer_name << std::endl;
        }
        else
          ostr << "WARNING: Already have a customer named " << c->get_name() << endl;
      }

    }

    else if (token == "ship") 
    {
      shipping_algorithm(inventory,customers,ostr);
    }

    else if (token == "return_oldest") 
    {
      std::string customer_name = read_customer_name(istr);

      customers_type::iterator c = customers.begin();
      while(c != customers.end() && c->get_name() != customer_name)
        c++;

      if(c == customers.end())
        ostr << "WARNING: No customer named " << customer_name << endl;
      else
      {
        if(c->getMoviesHeld() == 0)
          ostr << "WARNING: " << c -> get_name() << " has no DVDs to return!" << endl;
        else
        {
          std::string movie_name = c -> returnOldestMovie();

          inventory_type::iterator m = inventory.begin();
          while(m->get_name() != movie_name)
            m++;

          m -> returnCopy();

          ostr << customer_name << " returns " << movie_name << std::endl;
        }
      }
    }

    else if (token == "return_newest") 
    {
      std::string customer_name = read_customer_name(istr);

      customers_type::iterator c = customers.begin();
      while(c != customers.end() && c->get_name() != customer_name)
        c++;

      if(c == customers.end())
        ostr << "WARNING: No customer named " << customer_name << endl;
      else
      {
        if(c->getMoviesHeld() == 0)
          ostr << "WARNING: " << c -> get_name() << " has no DVDs to return!" << endl;
        else
        {
          std::string movie_name = c -> returnNewestMovie();

          inventory_type::iterator m = inventory.begin();
          while(m->get_name() != movie_name)
            m++;

          m -> returnCopy();

          ostr << customer_name << " returns " << movie_name << std::endl;
        }
      }
      
    }

    else if (token == "print_customer") 
    {
      std::string customer_name = read_customer_name(istr);

      customers_type::iterator c = customers.begin();
      while(c != customers.end() && c -> get_name() != customer_name)
        c++;

      if(c == customers.end())
        ostr << "WARNING: No customer named " << customer_name << std::endl;
      else
        c -> print(ostr);

    }

    else if (token == "print_dvd") 
    {
      std::string dvd_name = read_dvd_name(istr);

      inventory_type::iterator m = inventory.begin();
      while(m != inventory.end() && m -> get_name() != dvd_name)
        m++;

      if(m == inventory.end())
        ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
      else
        m -> print(ostr);

    }

    else if (token == "add_preference") 
    {
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = read_dvd_name(istr);

      bool dont_do_it = false;

      inventory_type::iterator m = inventory.begin();
      while(m != inventory.end() && m -> get_name() != dvd_name)
        m++;

      if(m == inventory.end())
      {
        ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
        dont_do_it = true;
      }

      customers_type::iterator c = customers.begin();
      while(c != customers.end() && c -> get_name() != customer_name)
        c++;

      if(c == customers.end())
      {
        ostr << "WARNING: No customer named " << customer_name << std::endl;
        dont_do_it = true;
      }
      else
      {
        if(c -> findMovie(dvd_name))
        {
          dont_do_it = true;
          ostr << "WARNING: " << customer_name << " already has " << dvd_name << " on his/her preference list!" << std::endl;
        }

        /*preference_type cust_movies = c -> getBorrowing(); //movies that customer already has
        preference_type::iterator b = cust_movies.begin();
        while(b != cust_movies.end() && *b != dvd_name)
        {
            b++;
            dont_do_it = true;
            ostr << "WARNING: " << customer_name << " currently has " << dvd_name << endl;
        }*/
      }
        
        
      if(!dont_do_it)
        c -> addPreference(dvd_name);

    }

    else 
    {
      std::cerr << "ERROR: Unknown token " << token << std::endl;
      exit(1);
    }

  }
  ostr.close();
  istr.close();
  
}


// ==================================================================


// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
  std::string token;
  istr >> token;
  assert (token[0] == '"');
  std::string answer = token;
  while (answer[answer.size()-1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}


// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name) {
  for (inventory_type::iterator inventory_itr = inventory.begin(); 
       inventory_itr != inventory.end(); inventory_itr++) {
    if (inventory_itr->get_name() == dvd_name) {
      return inventory_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return inventory.end();
}


// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr)
{

   ostr << "Ship DVDs" << std::endl;

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  customers_type::iterator customer_itr = customers.begin();
  while (customer_itr != customers.end())
  {
    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->getMoviesHeld() == 3 || customer_itr->getPreferences().empty()) 
    {
      // move on to the next customer
      customer_itr++;
      continue;
    }

    // a helper flag variable
    bool sent_dvd = false;
 
    // loop over the customer's preferences
    const preference_type &preferences = customer_itr->getPreferences(); //will const cause problems?
    for (preference_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) 
    {

      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = inventory.begin();//find_DVD(inventory,*preferences_itr);
      while(inventory_itr->get_name() != *preferences_itr)
        inventory_itr++;

      if (inventory_itr != inventory.end() && (inventory_itr->getCopies() != inventory_itr->getCopiesCheckedOut()) )
      { 

        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->get_name() << " receives " << *preferences_itr << std::endl;
        inventory_itr->borrowCopy();
        customer_itr->borrowMovie(*preferences_itr);
        
        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;        
        break;
      }
    }

    // if no DVD was sent to this customer, then we move on to the next customer 
    // (do not change this customer's priority for tomorrow's shipment)
    if (!sent_dvd) 
    {
      customer_itr++;
    }
  }
}

// ==================================================================
