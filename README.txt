HOMEWORK 4: DVD LISTS


NAME:  Abby Itty


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Lec notes, DS Discord, Makenna Noel

Remember: Your implementation for this assignment must be done on your
Maown, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >


ORDER NOTATION:
For each function, using the variables:
  d = number of different movie DVD titles
  k = average or maximum copies of each DVD
  c = number of customers
  p = average or maximum movies ranked on each customer’s preference list
Include a short description of your order notation analysis.

dvd: O(d) -> the function goes only goes through the inventory to check for repeats

customer: O( p*(d+p) + c ) ->for each preference, the funciton goes though the inventory and preference list
	  		     it also goes through the customers after

add_preference: O(c+d+p) -> the function goes through the inventory
			    it also goes the customer list
			    the function findMovie() goes the preferences of the customer

ship: O(cpd) -> the function goes through the inventory for each preference for each customer

return_oldest: O(c+d) -> the function goes through the customers
			 it also goes through the inventory to return the movie

return_newest: O(c+d) -> same as return_oldest

print_customer: O(c+p+3) -> function goes through customers
			    goes through movies the customer has (max 3)
			    goes through preferences for a specific customer

print_dvd: O(d) -> function goes through inventory, other variables are members so O(1)



EXTRA CREDIT:
Describe the analysis you performed on customer satisfaction.  Paste
in a small amount of sample analysis output and/or specify a sample
output file.  Describe your improved algorithm and compare the
analysis results of your new algorithm.  Please be concise!



MISC. COMMENTS TO GRADER:  
Hello :D






