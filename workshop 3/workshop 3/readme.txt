w3 Module (supplied)
Do not modify this module! Look at the code and make sure you understand how to instantiate a templated class.

Pair Module
This module represents a value-key pair (like the words and their definition in a dictionary).

class Pair
{
	std::string m_key{};
	std::string m_value{};
public:
	const std::string& getKey() { return m_key; }
	const std::string& getValue() { return m_value; }
	Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};

	// TODO: Add here the missing prototypes for the members
	//           that are necessary if this class is to be used
	//           with the template classes described below.
	//       Implement them in the Pair.cpp file.
}
Two objects of type Pair are considered to be equal if they have the same key.

🗎 In the reflection justify why it was necessary to add each one of the members you have decided to add.

Collection Module
This module represents a family of collections of elements of any data type (for example, collection of ints, or collection of Pairs, etc.).

Design and code a class template named Collection. Your template manages a statically allocated array of any datatype. The template parameters in order of their specification are:

T: the type of any element in the collection
CAPACITY: the capacity of the collection (a non-type parameter; an integer without sign). This is the maximum number of elements that can be added to the collection
Your design keeps track of the current number of elements stored in the collection (which may differ from the capacity of the collection). Initially the collection has no elements.

Class Members

An object of type T (a dummy object). This object will be returned by member-functions when the client requests an object that is not in the collection.
Public Members

size(): a query that returns the current number of elements in the collection
display(): a query that receives as the parameter an output stream (with default value std::cout) and inserts into the stream all items from the collection (see the sample output for formatting hints).
bool add(const T& item): a mutator that adds a copy of the parameter to the collection if there still is capacity. If the item has been added, this function return true; false otherwise.
operator[]: a query that receives an index as parameter and returns a copy of the element stored in the collection at the specified index. If the index is not valid (outside the boundaries of the collection), this query returns the dummy object.
Add any other private members that your design requires (without changing the specs above)!

Specialize the dummy object when type T = Pair and CAPACITY = 100 so the key is "No Key" and the value is "No Value".

adding a collection named Set that doesn't allow duplicates.

Collection Module
Modify the add() member function in the Collection module to enable inclusion polymorphism on the hierarchy. For the same purpose, add an empty body destructor.

No other changes are necessary to this module.

Set Module
Add to your project a new module called Set that represents a Collection where no item appears more than once.

Derive the Set class template from Collection<T, 100> (the Set will always have a capacity of 100 items). The Set will have only one template parameter T.

Public Members

override the inherited function add to prevent adding an item if it already exists in the Set.
No other members need to be added to this class.

Specializations

for T = double, the function add() should consider that two numbers are the same if their difference in the absolute value is smaller or equal to 0.01.

When implementing this specialization, consider the function std::fabs().

main.cpp file 
#include <iostream>
#include <iomanip>
#include "Set.h"
#include "Collection.h"
#include "Pair.h"

int cout = 0; // won't compile if headers don't follow convention

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// Data to be used by the template classes
	long   iData[]{    16,    12,     9,      3,    21,    12, 23 };
	double dData[]{ 1.222, 5.777, 1.223, 51.333, 8.888, 1.221 };
	seneca::Pair pData[]{
		seneca::Pair("static memory", "memory allocated during the compilation time"),
		seneca::Pair("programmer", "a person who writes code"),
		seneca::Pair("dynamic memory", "memory allocated during the runtime"),
		seneca::Pair("client of a class", "a piece of code that uses the class"),
		seneca::Pair("dynamic memory", "memory allocated with 'new' operator"),
		seneca::Pair("user", "a person who runs and interracts with the program"),
		seneca::Pair("array", "a contiguous block of memory storing multiple objects"),
		seneca::Pair("client of a function", "a piece of code that uses the function"),
		seneca::Pair("user", "Just John!"),
	};

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Collection of Integers                 *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<long, 20> colIntegers;

		for (const auto& item : iData)
			colIntegers.add(item);

		std::cout << "Collection size: [" << colIntegers.size() << "]\n";
		colIntegers.display();

		std::cout << "Item [0]: " << colIntegers[0] << "\n";
		std::cout << "Item [5]: " << colIntegers[5] << "\n";
		std::cout << "Item [9]: " << colIntegers[9] << "\n";
		std::cout << "******************************************************\n\n";
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Set of Integers                        *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<long, 100>* setIntegers = new seneca::Set<long>();

		for (const auto& item : iData)
			setIntegers->add(item);

		std::cout << "Set size: [" << setIntegers->size() << "]\n";
		setIntegers->display();

		std::cout << "Item [0]: " << (*setIntegers)[0] << "\n";
		std::cout << "Item [5]: " << (*setIntegers)[5] << "\n";
		std::cout << "Item [9]: " << (*setIntegers)[9] << "\n";
		std::cout << "******************************************************\n\n";
		delete setIntegers;
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Collection of Floats                   *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<double, 30> colFloats;

		for (const auto& item : dData)
			colFloats.add(item);

		std::cout << "Collection size: [" << colFloats.size() << "]\n";
		colFloats.display();

		std::cout << "Item [0]: " << colFloats[0] << "\n";
		std::cout << "Item [5]: " << colFloats[5] << "\n";
		std::cout << "Item [9]: " << colFloats[9] << "\n";
		std::cout << "******************************************************\n\n";
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Set of Floats                          *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<double, 100>* setFloats = new seneca::Set<double>;

		for (const auto& item : dData)
			setFloats->add(item);
		
		std::cout << "Set size: [" << setFloats->size() << "]\n";
		setFloats->display();

		std::cout << "Item [0]: " << (*setFloats)[0] << "\n";
		std::cout << "Item [5]: " << (*setFloats)[5] << "\n";
		std::cout << "Item [9]: " << (*setFloats)[9] << "\n";
		std::cout << "******************************************************\n\n";
		delete setFloats;
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Collection of Pairs                    *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<seneca::Pair, 50> colDictionary;

		for (const auto& item : pData)
			colDictionary.add(item);

		std::cout << "Collection size: [" << colDictionary.size() << "]\n";
		colDictionary.display();

		std::cout << "Item [0]: [" << colDictionary[0].getKey()   << "]["
		                           << colDictionary[0].getValue() << "]\n";
		std::cout << "Item [8]: [" << colDictionary[8].getKey()   << "]["
		                           << colDictionary[8].getValue() << "]\n";
		std::cout << "Item [9]: [" << colDictionary[9].getKey()   << "]["
		                           << colDictionary[9].getValue() << "]\n";
		std::cout << "******************************************************\n\n";
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Set of Pairs                           *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<seneca::Pair, 100>* setDictionary = new seneca::Set<seneca::Pair>();

		for (const auto& item : pData)
			setDictionary->add(item);

		std::cout << "Set size: [" << setDictionary->size() << "]\n";
		setDictionary->display();

		std::cout << "Item [1]: ["  << (*setDictionary)[1].getKey()    << "]["
		                            << (*setDictionary)[1].getValue()  << "]\n";
		std::cout << "Item [4]: ["  << (*setDictionary)[4].getKey()    << "]["
		                            << (*setDictionary)[4].getValue()  << "]\n";
		std::cout << "Item [11]: [" << (*setDictionary)[11].getKey()   << "]["
		                            << (*setDictionary)[11].getValue() << "]\n";
		std::cout << "******************************************************\n\n";
		delete setDictionary;
	}

	return cout;
}


correct output
******************************************************
* Testing the Collection of Integers                 *
******************************************************
Collection size: [7]
----------------------
| Collection Content |
----------------------
16
12
9
3
21
12
23
----------------------
Item [0]: 16
Item [5]: 12
Item [9]: 0
******************************************************

******************************************************
* Testing the Set of Integers                        *
******************************************************
Set size: [6]
----------------------
| Collection Content |
----------------------
16
12
9
3
21
23
----------------------
Item [0]: 16
Item [5]: 23
Item [9]: 0
******************************************************

******************************************************
* Testing the Collection of Floats                   *
******************************************************
Collection size: [6]
----------------------
| Collection Content |
----------------------
1.222
5.777
1.223
51.333
8.888
1.221
----------------------
Item [0]: 1.222
Item [5]: 1.221
Item [9]: 0
******************************************************

******************************************************
* Testing the Set of Floats                          *
******************************************************
Set size: [4]
----------------------
| Collection Content |
----------------------
1.222
5.777
51.333
8.888
----------------------
Item [0]: 1.222
Item [5]: 0
Item [9]: 0
******************************************************

******************************************************
* Testing the Collection of Pairs                    *
******************************************************
Collection size: [9]
----------------------
| Collection Content |
----------------------
       static memory: memory allocated during the compilation time
          programmer: a person who writes code
      dynamic memory: memory allocated during the runtime
   client of a class: a piece of code that uses the class
      dynamic memory: memory allocated with 'new' operator
                user: a person who runs and interracts with the program
               array: a contiguous block of memory storing multiple objects
client of a function: a piece of code that uses the function
                user: Just John!
----------------------
Item [0]: [static memory][memory allocated during the compilation time]
Item [8]: [user][Just John!]
Item [9]: [][]
******************************************************

******************************************************
* Testing the Set of Pairs                           *
******************************************************
Set size: [7]
----------------------
| Collection Content |
----------------------
       static memory: memory allocated during the compilation time
          programmer: a person who writes code
      dynamic memory: memory allocated during the runtime
   client of a class: a piece of code that uses the class
                user: a person who runs and interracts with the program
               array: a contiguous block of memory storing multiple objects
client of a function: a piece of code that uses the function
----------------------
Item [1]: [programmer][a person who writes code]
Item [4]: [user][a person who runs and interracts with the program]
Item [11]: [No Key][No Value]
******************************************************