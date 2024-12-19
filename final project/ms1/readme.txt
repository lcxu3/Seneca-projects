Milestone 1
Utilities and Station classes
Milestone 1 implements and tests the Utilities and Station modules.

The Utilities module supports the parsing of input files, which contain information used to setup and configure the assembly line.
The Station module manages information about a station on the assembly line, which holds a specific item and fills customer orders.
The specifications of these two modules are defined below.

Utilities Module
Parsing string data from input files into tokens is performed uniformly for all objects within the simulation system. The Utilities type provides the basic functionality required for all objects in the system.

The Utilities class has the following structure:

Instance Variable

m_widthField -- specifies the length of the token extracted; used for display purposes; default value is 1.
Class Variable

m_delimiter -- separates the tokens in any given std::string object. All Utilities objects in the system share the same delimiter.
Member Functions

void setFieldWidth(size_t newWidth) -- sets the field width of the current object to the value of parameter newWidth

size_t getFieldWidth() const -- returns the field width of the current object

std::string extractToken(const std::string& str, size_t& next_pos, bool& more) -- extracts a token from string str referred to by the first parameter.

This function:

uses the delimiter to extract the next token from str starting at position next_pos.
If successful, return a copy of the extracted token found (without spaces at the beginning/end), update next_pos with the position of the next token, and set more to true (false otherwise).
reports an exception if a delimiter is found at next_pos.
updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
Note: in this application, str represents a single line that has been read from an input file.

Class Functions

static void setDelimiter(char newDelimiter) -- sets the delimiter for this class to the character received
static char getDelimiter() -- returns the delimiter for this class.
Station Module
A Station object manages a single station on the assembly line. Each station handles a specific item for filling customer orders.

The Station class has the following structure:

Instance Variables

the id of the station (integer)
the name of the item handled by the station (string)
the description of the station (string)
the next serial number to be assigned to an item at this station (non-negative integer)
the number of items currently in stock (non-negative integer)
Class Variables

m_widthField -- the maximum number of characters required to print to the screen the item name for any object of type Station. Initial value is 0.
id_generator -- a variable used to generate IDs for new instances of type Station. Every time a new instance is created, the current value of the id_generator is stored in that instance, and id_generator is incremented. Initial value is 0.
Public Functions

custom 1-argument constructor

upon instantiation, a Station object receives a reference to an unmodifiable std::string. This string contains a single record (one line) that has been retrieved from the input file specified by the user.
this constructor uses a Utilities object (defined locally) to extract each token from the record and populates the Station object accordingly.
this constructor assumes that the string contains 4 fields separated by the delimiter, in the following order:
name of the item
starting serial number
quantity in stock
description
the token delimiter is a single character, specified by the client and previously stored into the Utilities class of objects.
this constructor extracts name, starting serial number, and quantity from the string first
before extracting description, it updates Station::m_widthField to the maximum value of Station::m_widthField and Utilities::m_widthField.
Note: the display(...) member function uses this field width to align the output across all the records retrieved from the file.
const std::string& getItemName() const - returns the name of the current Station object

size_t getNextSerialNumber() – returns the next serial number to be used on the assembly line and increments m_serialNumber

size_t getQuantity() const – returns the remaining quantity of items in the Station object

void updateQuantity() – subtracts 1 from the available quantity; should not drop below 0.

void display(std::ostream& os, bool full) const -- inserts information about the current object into stream os.

if the second parameter is false, this function inserts only the ID, name, and serial number in the format: ID | NAME | SERIAL | 
if the second parameter if true, this function inserts the information in the following format: ID | NAME | SERIAL | QUANTITY | DESCRIPTION
the ID field uses 3 characters, the NAME field uses m_widthField characters, the QUANTITY field uses 4 characters, the SERIAL field uses 6 characters; the DESCRIPTION has no formatting options (see the sample output for other formatting options)
this function terminates the printed message with an endline

output 
========================================
=         Stations (summary)           =
========================================
001 | Armchair       | 654321 | 
002 | Bed            | 123456 | 
003 | Dresser        | 056789 | 
004 | Nighttable     | 000887 | 
005 | Filing Cabinet | 987654 | 
006 | Office Chair   | 147852 | 
007 | Bookcase       | 000987 | 
008 | Desk           | 459214 | 


========================================
=          Stations (full)             =
========================================
001 | Armchair       | 654321 |   10 | Upholstered Wing Chair
002 | Bed            | 123456 |    5 | Queen size bed with headboard
003 | Dresser        | 056789 |    7 | 6-Drawer Unit
004 | Nighttable     | 000887 |    5 | Nightstand with 2 drawers
005 | Filing Cabinet | 987654 |    5 | 3-drawer filing cabinet
006 | Office Chair   | 147852 |   20 | High-back carpet-rollers
007 | Bookcase       | 000987 |    5 | 5-shelf open bookcase
008 | Desk           | 459214 |    2 | 6-foot worktable


========================================
=          Manual Validation           =
========================================
getItemName(): Armchair
getNextSerialNumber(): 654321
getNextSerialNumber(): 654322
getQuantity(): 10
getQuantity(): 9

========================================
=              Utilities               =
========================================
Data: [a]    Delimiter: [a]
   ERROR: No token.
Data: [a]    Delimiter: [b]
   Token: [a] [1]
Data: [Hello]    Delimiter: [l]
   Token: [He] [2]
   ERROR: No token.
Data: [apple,orange,banana,kiwi,strawberry,yellow watermellon]    Delimiter: [,]
   Token: [apple] [5]
   Token: [orange] [6]
   Token: [banana] [6]
   Token: [kiwi] [6]
   Token: [strawberry] [10]
   Token: [yellow watermellon] [18]
Data: [Gengar|Arcanine|Bulbasaur|Blaziken|C h a r i z a r d|Umbreon|Lucario|Eevee]    Delimiter: [|]
   Token: [Gengar] [6]
   Token: [Arcanine] [8]
   Token: [Bulbasaur] [9]
   Token: [Blaziken] [9]
   Token: [C h a r i z a r d] [17]
   Token: [Umbreon] [17]
   Token: [Lucario] [17]
   Token: [Eevee] [17]



