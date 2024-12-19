the instructions 
Toy Module
This module includes the definition of a class that manages information about a single toy. A multiple number of this toy can be ordered.

Design and code a class named Toy that can store the following information (for each attribute, choose any type that you think is appropriate--you must be able to justify the decisions you make):

order id the order id of the toy (a positive number)
the name the name of the toy
the number of items the number of toys of this type to be ordered
the price the price of this toy
the harmonized sales tax assume the HST is equal to 13%
Private Members

Add as many private members as your design requires
Public Members

a default constructor

void update(int numItems): a modifier that receives as a parameter the number of toys of this type to be ordered and updates the number of items attribute with the received value. Assume the parameter is correct and doesn't require validation.

Toy(const std::string& toy): A constructor that receives the toy attributes as a string; this constructor is responsible for extracting information about the toy from the string and storing the tokens in the instance's attributes. The string will always have the following format:

ID:NAME:NUM:PRICE
This constructor should remove all leading and trailing spaces from the beginning and end of any token extracted from the string.

When implementing the constructor, consider this following functions:

std::string::substr()
std::string::find()
std::string::erase()
std::stoi()
Friend Helpers

overload the insertion operator to insert the contents of a toy object into an ostream object:
The word Toy ("Toy")
the ID of the toy should display on a field of size 8 followed by a colon (':')
The name of the toy should display on a field of size 18, aligned to the right
The number of items should display on a field of size 3,
The word items preceded by a space (" items"),
The price of the toy should display on a field of size 8
The words "/item subtotal:" should follow
The subtotal should display on a field of size 7 (the price times the number of items)
The word tax: should follow preceded by a space (" tax:")
The tax should display on a field of size 6 (the amount of tax paid on the subtotal)
The word total: should follow preceded by a space (" total:")
The total should display on a field of size 7 (the subtotal plus the tax)
Look in the sample output file for hints about formatting

The module Toy doesn't need any change.

Child Module
Add a Child module to your project that defines a class named Child. This class should have attributes to store a name and an age, and maintain a dynamically allocated array of pointers of type Toy: const seneca::Toy** (each element of the array points to an object of type Toy).

Private Members

An attribute of type const seneca::Toy** representing the dynamically allocated array of pointers
Add as many private members as your design requires
🗎 Explain in the reflection what is the relationship between Child and Toy, and what is the relationship between Child and the array of pointers.
Public Members

Child(std::string name, int age, const Toy* toys[], size_t count): a constructor that receives as a parameter a name and an age, and an array of pointers to objects of type Toy (i.e., each element of the array is a pointer). If you need a refresh on arrays of pointers, re-read the material from the last term (chapter Abstract Base Classes, section Array of Pointers).

this constructor should store copies of all toys
add any other special members that are necessary to manage the toys stored

size_t size() const: a query that returns the number of toys stored in the array attribute.

Friend Helpers

overload the insertion operator to insert the content of a Child object into an ostream object. This operator should use a local to function variable to count how many times this operator has been called (CALL_CNT below). It should also insert the child's name (NAME below) and the child's age (AGE below):
if there are no toys:
--------------------------
Child CALL_CNT: NAME AGE years old:
--------------------------
This child has no toys!
--------------------------
if there are toys:
--------------------------
Child CALL_CNT: NAME AGE years old:
--------------------------
TOY
TOY
...
--------------------------
ConfirmOrder Module
Add a ConfirmOrder module to your project. The purpose of this module is to receive all the toys from multiple children, and contact the recipients with a confirmation message.

This module should maintain a dynamically allocated array of pointers to objects of type Toy: const seneca::Toy** (each element of the array is a pointer to an object of type Toy).

This class should have attributes to store and manage a dynamically-allocated array of pointers to objects of type Toy: const sdds::Toy** (each element of the array points to an object of type Toy). Very Important: This class is responsible for managing the array of pointers but is not managing the life of Toy objects.


Private Members

An attribute of type const seneca::Toy** representing the dynamically allocated array of pointers
Add as many private members as your design requires
🗎 Explain in the reflection what is the relationship between ConfirmOrder and Toy, and what is the relationship between ConfirmOrder and the array of pointers.
Public Members

add any special members that are necessary to manage the resource (the resource is an array of pointers; your class must manage this array, but the objects at the addresses stored in the array are managed outside this class)

ConfirmOrder& operator+=(const Toy& toy): adds the toy toy to the array by adding its address.

if the address of toy is already in the array, this operator does nothing
resizes the array to make room for toy if necessary
stores the address of toy in the array (your function should not make copies of the toy itself)
ConfirmOrder& operator-=(const Toy& toy): removes the toy toy from the array by removing its address

if the address of toy is not in the array, this operator does nothing
searches the array for the address of toy, sets the pointer in the array to nullptr if toy is found.
To challenge yourself, try to actually resize the array.

add any other special members that are necessary to manage the resource.

Friend Helpers

overload the insertion operator to insert the content of a ConfirmOrder object into an ostream object:
if there are no toys to confirm:
--------------------------
Confirmations to Send
--------------------------
There are no confirmations to send!
--------------------------
if there are toys to confirm
--------------------------
Confirmations to Send
--------------------------
TOY
TOY
...
--------------------------

Add any private members that your design requires (without changing the specs above)!

main.cpp 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include "Child.h"
#include "Child.h"  // intentional
#include "ConfirmOrder.h"
#include "ConfirmOrder.h" // intentional
#include "Toy.h"
#include "Toy.h" // intentional

int cout = 0; // prevents compilation if headers don't follow convention

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n";

	const seneca::Toy** ppToys = nullptr;
	size_t count = 0;

	// Process the file
	if (argc > 1) {
		std::ifstream file(argv[1]);
		if (!file)
		{
			std::cerr << "ERROR: Cannot open file [" << argv[1] << "].\n";
			return 1;
		}

		std::string strToy;
		// count how many records are in the file
		do
		{
			std::getline(file, strToy);

			// if the previous operation failed, the "file" object is
			//   in error mode
			if (file)
			{
				// Check if this is a commented line.
				//   In the input file, commented lines start with '#'
				if (strToy[0] != '#')
					++count;
			}
		} while (file);

		ppToys = new const seneca::Toy * [count];
		count = 0;

		// read again from the file, but this time load and store data
		file.clear();
		file.seekg(std::ios::beg);
		do
		{
			std::getline(file, strToy);

			// if the previous operation failed, the "file" object is
			//   in error mode
			if (file)
			{
				// Check if this is a commented line.
				//   In the input file, commented lines start with '#'
				if (strToy[0] != '#')
				{
					ppToys[count] = new seneca::Toy(strToy);
					++count;
				}
			}
		} while (file);
		file.close();
	}
	std::cout << "\nToys\n--------------------------\n";
	for (auto i = 0u; i < count; ++i)
	{
		std::cout << *ppToys[i];
	}
	std::cout << "--------------------------\n\n";

	{
		std::cout << "C: Testing Constructor\n";
		std::cout << "==========================\n";
		seneca::Child child1("Kyle Patel", 8, ppToys, count);
		std::cout << child1;  // 1
		std::cout << "==========================\n\n";

		std::cout << "C: Testing Copy Constructor\n";
		std::cout << "==========================\n";
		seneca::Child child2(child1);
		std::cout << child1;  // 2
		std::cout << child2;  // 3
		std::cout << "==========================\n\n";

		{
			std::cout << "C: Testing Copy Assign\n";
			std::cout << "==========================\n";
			child2 = child2;
			std::cout << child1;  // 4
			std::cout << child2;  // 5
			seneca::Child child3("Paul Sakuraba", 11, ppToys + 3, 4);
			child2 = child3;
			std::cout << child2;  // 6
			std::cout << child3;  // 7
			std::cout << "==========================\n\n";
		}

		std::cout << "C: Testing Move Constructor\n";
		std::cout << "==========================\n";
		seneca::Child child3(std::move(child2));
		std::cout << child2;  // 8
		std::cout << child3;  // 9
		std::cout << "==========================\n\n";

		std::cout << "C: Testing Move Assign\n";
		std::cout << "==========================\n";
		seneca::Child& refChild3 = child3;
		refChild3 = std::move(child3);
		std::cout << child2;  // 10
		std::cout << child3;  // 11
		child2 = std::move(child3);
		std::cout << child2;  // 12
		std::cout << child3;  // 13
		std::cout << "==========================\n\n";
	}


	// Confirm Order
	{
		std::cout << "CS: Testing Constructor\n";
		std::cout << "==========================\n";
		seneca::ConfirmOrder order1;
		std::cout << order1;
		std::cout << "==========================\n\n";

		std::cout << "CS: Testing Operators\n";
		std::cout << "==========================\n";
		order1 += *ppToys[5];
		order1 += *ppToys[6];
		order1 += *ppToys[6];
		order1 += *ppToys[8];
		order1 += *ppToys[7];
		order1 += *ppToys[9];
		std::cout << order1;
		order1 -= *ppToys[8];
		order1 -= *ppToys[9];
		order1 -= *ppToys[7];
		std::cout << order1;
		std::cout << "==========================\n\n";

		std::cout << "CS: Testing Copy Constructor\n";
		std::cout << "==========================\n";
		seneca::ConfirmOrder order2(order1);
		std::cout << order1;
		std::cout << order2;
		std::cout << "==========================\n\n";

		order2 = order2;

		std::cout << "CS: Testing Move Constructor\n";
		std::cout << "==========================\n";
		seneca::ConfirmOrder order3(std::move(order1));
		std::cout << order1;
		std::cout << order3;
		std::cout << "==========================\n\n";

		seneca::ConfirmOrder& refOrder3 = order3;
		refOrder3 = std::move(order3);
	}

	{
		// Making a new array of pointers to toy.
		//   The toys in this array are not constant, so we must
		//   create copies of the original toy (which are constant)
		seneca::Toy* toys[]{
								new seneca::Toy(*ppToys[3]),
								new seneca::Toy(*ppToys[5]),
								new seneca::Toy(*ppToys[7]),
								new seneca::Toy(*ppToys[9])
		};

		std::cout << "C + CS: Testing Relations\n";
		std::cout << "==========================\n";
		seneca::Child child("Tom Chow", 7, const_cast<const seneca::Toy**>(toys), 4u);
		seneca::ConfirmOrder order;
		(order += *toys[0]) += *toys[1];
		(order += *toys[2]) += *toys[3];
		std::cout << child;
		std::cout << order;

		// updating some toys in main
		//   child should not be affected
		//   confirm order should be affected
		toys[0]->update(6);
		toys[2]->update(4);

		std::cout << "\nAfter main() updates some toys ...\n\n";

		std::cout << child;
		std::cout << order;
		std::cout << "==========================\n\n";

		// cleanup
		for (auto item : toys)
			delete item;

	}

	// cleanup
	for (auto i = 0u; i < count; ++i)
		delete ppToys[i];
	delete[] ppToys;

	return cout;
}

correct output 
Toys
--------------------------
Toy 1000121:          Red Bike  1 items   89.99/item  subtotal:  89.99 tax: 11.70 total: 101.69
Toy 1000122:           Pen Set  2 items    9.99/item  subtotal:  19.98 tax:  2.60 total:  22.58
Toy 1000123:    Colouring Book  1 items    8.99/item  subtotal:   8.99 tax:  1.17 total:  10.16
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000129: Skateboard Helmet  1 items   22.99/item  subtotal:  22.99 tax:  2.99 total:  25.98
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------

C: Testing Constructor
==========================
--------------------------
Child 1: Kyle Patel 8 years old:
--------------------------
Toy 1000121:          Red Bike  1 items   89.99/item  subtotal:  89.99 tax: 11.70 total: 101.69
Toy 1000122:           Pen Set  2 items    9.99/item  subtotal:  19.98 tax:  2.60 total:  22.58
Toy 1000123:    Colouring Book  1 items    8.99/item  subtotal:   8.99 tax:  1.17 total:  10.16
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000129: Skateboard Helmet  1 items   22.99/item  subtotal:  22.99 tax:  2.99 total:  25.98
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
==========================

C: Testing Copy Constructor
==========================
--------------------------
Child 2: Kyle Patel 8 years old:
--------------------------
Toy 1000121:          Red Bike  1 items   89.99/item  subtotal:  89.99 tax: 11.70 total: 101.69
Toy 1000122:           Pen Set  2 items    9.99/item  subtotal:  19.98 tax:  2.60 total:  22.58
Toy 1000123:    Colouring Book  1 items    8.99/item  subtotal:   8.99 tax:  1.17 total:  10.16
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000129: Skateboard Helmet  1 items   22.99/item  subtotal:  22.99 tax:  2.99 total:  25.98
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
--------------------------
Child 3: Kyle Patel 8 years old:
--------------------------
Toy 1000121:          Red Bike  1 items   89.99/item  subtotal:  89.99 tax: 11.70 total: 101.69
Toy 1000122:           Pen Set  2 items    9.99/item  subtotal:  19.98 tax:  2.60 total:  22.58
Toy 1000123:    Colouring Book  1 items    8.99/item  subtotal:   8.99 tax:  1.17 total:  10.16
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000129: Skateboard Helmet  1 items   22.99/item  subtotal:  22.99 tax:  2.99 total:  25.98
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
==========================

C: Testing Copy Assign
==========================
--------------------------
Child 4: Kyle Patel 8 years old:
--------------------------
Toy 1000121:          Red Bike  1 items   89.99/item  subtotal:  89.99 tax: 11.70 total: 101.69
Toy 1000122:           Pen Set  2 items    9.99/item  subtotal:  19.98 tax:  2.60 total:  22.58
Toy 1000123:    Colouring Book  1 items    8.99/item  subtotal:   8.99 tax:  1.17 total:  10.16
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000129: Skateboard Helmet  1 items   22.99/item  subtotal:  22.99 tax:  2.99 total:  25.98
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
--------------------------
Child 5: Kyle Patel 8 years old:
--------------------------
Toy 1000121:          Red Bike  1 items   89.99/item  subtotal:  89.99 tax: 11.70 total: 101.69
Toy 1000122:           Pen Set  2 items    9.99/item  subtotal:  19.98 tax:  2.60 total:  22.58
Toy 1000123:    Colouring Book  1 items    8.99/item  subtotal:   8.99 tax:  1.17 total:  10.16
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000129: Skateboard Helmet  1 items   22.99/item  subtotal:  22.99 tax:  2.99 total:  25.98
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
--------------------------
Child 6: Paul Sakuraba 11 years old:
--------------------------
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
--------------------------
Child 7: Paul Sakuraba 11 years old:
--------------------------
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
==========================

C: Testing Move Constructor
==========================
--------------------------
Child 8:  0 years old:
--------------------------
This child has no toys!
--------------------------
--------------------------
Child 9: Paul Sakuraba 11 years old:
--------------------------
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
==========================

C: Testing Move Assign
==========================
--------------------------
Child 10:  0 years old:
--------------------------
This child has no toys!
--------------------------
--------------------------
Child 11: Paul Sakuraba 11 years old:
--------------------------
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
--------------------------
Child 12: Paul Sakuraba 11 years old:
--------------------------
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000125:           Toy car 10 items    3.99/item  subtotal:  39.90 tax:  5.19 total:  45.09
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
--------------------------
Child 13:  0 years old:
--------------------------
This child has no toys!
--------------------------
==========================

CS: Testing Constructor
==========================
--------------------------
Confirmations to Send
--------------------------
There are no confirmations to send!
--------------------------
==========================

CS: Testing Operators
==========================
--------------------------
Confirmations to Send
--------------------------
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
Toy 1000129: Skateboard Helmet  1 items   22.99/item  subtotal:  22.99 tax:  2.99 total:  25.98
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
--------------------------
Confirmations to Send
--------------------------
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
==========================

CS: Testing Copy Constructor
==========================
--------------------------
Confirmations to Send
--------------------------
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
--------------------------
Confirmations to Send
--------------------------
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
==========================

CS: Testing Move Constructor
==========================
--------------------------
Confirmations to Send
--------------------------
There are no confirmations to send!
--------------------------
--------------------------
Confirmations to Send
--------------------------
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000127:     SpongeBob DVD  2 items   14.99/item  subtotal:  29.98 tax:  3.90 total:  33.88
--------------------------
==========================

C + CS: Testing Relations
==========================
--------------------------
Child 14: Tom Chow 7 years old:
--------------------------
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
--------------------------
Confirmations to Send
--------------------------
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------

After main() updates some toys ...

--------------------------
Child 15: Tom Chow 7 years old:
--------------------------
Toy 1000124:         Leggo Set  2 items   39.99/item  subtotal:  79.98 tax: 10.40 total:  90.38
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000128:        Skateboard  1 items  149.99/item  subtotal: 149.99 tax: 19.50 total: 169.49
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
--------------------------
Confirmations to Send
--------------------------
Toy 1000124:         Leggo Set  6 items   39.99/item  subtotal: 239.94 tax: 31.19 total: 271.13
Toy 1000126:       Bubble Bath  3 items   11.98/item  subtotal:  35.94 tax:  4.67 total:  40.61
Toy 1000128:        Skateboard  4 items  149.99/item  subtotal: 599.96 tax: 77.99 total: 677.95
Toy 1000130:       Bike Helmet  1 items   18.99/item  subtotal:  18.99 tax:  2.47 total:  21.46
--------------------------
==========================

data.txt
#ID:Name:NUM:PRICE
1000121  :  Red Bike:1  :  89.99
1000122: Pen Set:2: 9.99
1000123 :Colouring Book:1:8.99
1000124:Leggo Set :2:39.99
1000125: Toy car:10:3.99
1000126:Bubble Bath: 3:11.98
1000127:SpongeBob DVD:2:14.99 
1000128  :  Skateboard: 1 :149.99
1000129: Skateboard Helmet: 1: 22.99
1000130 :Bike Helmet :1 :18.99

