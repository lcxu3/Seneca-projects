Milestone 3
Milestone 3 implements and tests the Workstation and LineManager modules.

The LineManager module first configures the assembly line and then moves CustomerOrders along it (from start to finish). The LineManager object configures the Workstation objects identified by the user, and moves orders along the line one step at a time. A Workstation is a Station that the LineManager has activated on the user's request. At each step, every Workstation fills one item in a Customer Order, if possible. The manager moves orders from station to station. Once an order has reached the end of the line, it is either complete or incomplete. An order is incomplete if one or more stations had an insufficient number of items in stock to cover that order's requests.

Workstation Module
The Workstation module consists of three double-ended queues of CustomerOrder and the Workstation class. The queues (global variables) hold the orders at either end of the assembly line:

g_pending holds the orders to be placed onto the assembly line at the first station.
g_completed holds the orders that have been removed from the last station and have been completely filled.
g_incomplete holds the orders that have been removed from the last station and could not be filled completely.
Each queue is accessible outside this module's translation unit.

The Workstation class defines the structure of an active station on the assembly line and contains all the functionality for filling customer orders with station items. Each Workstation is-a-kind-of Station. A Workstation object manages order processing for a single Item on the assembly line. Since a Workstation object represents a single location on the assembly line for filling customer orders with items, the object cannot be copied or moved. Make sure that this capability is deleted in your definition of the Workstation class.

The Workstation class includes the following additional information:

Instance Variables

m_orders – is a double-ended-queue with CustomerOrders entering the back and exiting the front. These are orders that have been placed on this station to receive service (or already received service).
m_pNextStation – a pointer to the next Workstation on the assembly line.
Member Functions

a custom 1-argument constructor -- receives a reference to an unmodifiable reference to std::string and passes it to the Station base class.

void fill(std::ostream& os) – this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.

bool attemptToMoveOrder() – attempts to move the order order at the front of the queue to the next station in the assembly line:

if the order requires no more service at this station or cannot be filled (not enough inventory), move it to the next station; otherwise do nothing
if there is no next station in the assembly line, then the order is moved into g_completed or g_incomplete queue
if an order has been moved, return true; false otherwise.
void setNextStation(Workstation* station) – this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation. Parameter defaults to nullptr.

Workstation* getNextStation() const – this query returns the address of next Workstation

void display(std::ostream& os) const – this query inserts the name of the Item for which the current object is responsible into stream os following the format: ITEM_NAME --> NEXT_ITEM_NAME

if the current object is the last Workstation in the assembly line this query inserts: ITEM_NAME --> End of Line.
in either case, the message is terminated with \n
Workstation& operator+=(CustomerOrder&& newOrder) – moves the CustomerOrder referenced in parameter newOrder to the back of the queue.

LineManager Module
The LineManager class manages an assembly line of active stations and contains the following information:

Instance Variables

std::vector<Workstation*> m_activeLine – the collection of workstations for the current assembly line.
size_t m_cntCustomerOrder – the total number of CustomerOrder objects
Workstation* m_firstStation - points to the first active station on the current line
Member Functions

LineManager(const std::string& file, const std::vector<Workstation*>& stations) - this constructor receives the name of the file that identifies the active stations on the assembly line (example: AssemblyLine.txt) and the collection of workstations available for configuring the assembly line.

The file contains the linkage between workstation pairs. The format of each record in the file is WORKSTATION|NEXT_WORKSTATION. The records themselves are not in any particular order.

This function stores the workstations in the order received from the file in the m_activeLine instance variable. It loads the contents of the file, stores the address of the next workstation in each element of the collection, identifies the first station in the assembly line and stores its address in the m_firstStation attribute. This function also updates the attribute that holds the total number of orders in the g_pending queue. If something goes wrong, this constructor reports an error.

Note: to receive full marks, use STL algorithms throughout this function, except for iterating through the file records (one while loop); marks will be deducted if you use any of for, while or do-while loops except for iterating through the file records.

void reorderStations() - this modifier reorders the workstations present in the instance variable m_activeLine (loaded by the constructor) and stores the reordered collection in the same instance variable. The elements in the reordered collection start with the first station, proceeds to the next, and so forth until the end of the line.

bool run(std::ostream& os) – this modifier performs one iteration of operations on all of the workstations in the current assembly line by doing the following:

keeps track of the current iteration number (use a local variable)
inserts into stream os the iteration number (how many times this function has been called by the client) in the format Line Manager Iteration: COUNT<endl>
moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue. This function moves only one order to the line on a single iteration.
for each station on the line, executes one fill operation
for each station on the line, attempts to move an order down the line
return true if all customer orders have been filled or cannot be filled, otherwise returns false.
void display(std::ostream& os) const -- this query displays all active stations on the assembly line in their current order

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
=                Orders                =
========================================
Cornel B. - 1-Room Home Office
[000000] Office Chair                   - TO BE FILLED
[000000] Desk                           - TO BE FILLED
[000000] Bookcase                       - TO BE FILLED
[000000] Bookcase                       - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
Chris S. - Bedroom
[000000] Bed                            - TO BE FILLED
[000000] Armchair                       - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Dresser                        - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
John M. - Kids Bedroom
[000000] Bed                            - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Dresser                        - TO BE FILLED
[000000] Desk                           - TO BE FILLED
Hong H. - 1-Room Office
[000000] Desk                           - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Filing Cabinet                 - TO BE FILLED
[000000] Bookcase                       - TO BE FILLED
Rania A. - 2-Room Home Office and Bedroom
[000000] Desk                           - TO BE FILLED
[000000] Desk                           - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Bed                            - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Office Chair                   - TO BE FILLED
[000000] Nighttable                     - TO BE FILLED
[000000] Armchair                       - TO BE FILLED
[000000] Dresser                        - TO BE FILLED


========================================
=       Display Stations (loaded)      =
========================================
Nighttable --> Desk
Dresser --> Armchair
Filing Cabinet --> Bookcase
Bookcase --> End of Line
Bed --> Dresser
Office Chair --> Filing Cabinet
Armchair --> Nighttable
Desk --> Office Chair


========================================
=      Display Stations (ordered)      =
========================================
Bed --> Dresser
Dresser --> Armchair
Armchair --> Nighttable
Nighttable --> Desk
Desk --> Office Chair
Office Chair --> Filing Cabinet
Filing Cabinet --> Bookcase
Bookcase --> End of Line


========================================
=           Filling Orders             =
========================================
Line Manager Iteration: 1
Line Manager Iteration: 2
    Filled Chris S., Bedroom [Bed]
    Filled Cornel B., 1-Room Home Office [Desk]
Line Manager Iteration: 3
    Filled John M., Kids Bedroom [Bed]
    Filled Chris S., Bedroom [Dresser]
    Filled Cornel B., 1-Room Home Office [Office Chair]
Line Manager Iteration: 4
    Filled John M., Kids Bedroom [Bed]
    Filled Chris S., Bedroom [Armchair]
    Filled Cornel B., 1-Room Home Office [Filing Cabinet]
Line Manager Iteration: 5
    Filled John M., Kids Bedroom [Bed]
    Filled Chris S., Bedroom [Nighttable]
    Filled Cornel B., 1-Room Home Office [Bookcase]
Line Manager Iteration: 6
    Filled John M., Kids Bedroom [Bed]
    Filled Chris S., Bedroom [Nighttable]
    Filled Cornel B., 1-Room Home Office [Bookcase]
Line Manager Iteration: 7
    Filled John M., Kids Bedroom [Dresser]
Line Manager Iteration: 8
    Unable to fill Rania A., 2-Room Home Office and Bedroom [Bed]
    Filled John M., Kids Bedroom [Nighttable]
Line Manager Iteration: 9
    Filled Rania A., 2-Room Home Office and Bedroom [Dresser]
    Filled John M., Kids Bedroom [Nighttable]
Line Manager Iteration: 10
    Filled Rania A., 2-Room Home Office and Bedroom [Armchair]
    Filled John M., Kids Bedroom [Desk]
Line Manager Iteration: 11
    Filled Rania A., 2-Room Home Office and Bedroom [Nighttable]
    Unable to fill Hong H., 1-Room Office [Desk]
Line Manager Iteration: 12
    Unable to fill Rania A., 2-Room Home Office and Bedroom [Desk]
    Unable to fill Rania A., 2-Room Home Office and Bedroom [Desk]
    Filled Hong H., 1-Room Office [Office Chair]
Line Manager Iteration: 13
    Filled Hong H., 1-Room Office [Office Chair]
Line Manager Iteration: 14
    Filled Rania A., 2-Room Home Office and Bedroom [Office Chair]
    Filled Hong H., 1-Room Office [Filing Cabinet]
Line Manager Iteration: 15
    Filled Rania A., 2-Room Home Office and Bedroom [Office Chair]
    Filled Hong H., 1-Room Office [Filing Cabinet]
Line Manager Iteration: 16
    Filled Rania A., 2-Room Home Office and Bedroom [Office Chair]
    Filled Hong H., 1-Room Office [Filing Cabinet]
Line Manager Iteration: 17
    Filled Hong H., 1-Room Office [Bookcase]
Line Manager Iteration: 18


========================================
=      Processed Orders (complete)     =
========================================
Cornel B. - 1-Room Home Office
[147852] Office Chair                   - FILLED
[459214] Desk                           - FILLED
[000987] Bookcase                       - FILLED
[000988] Bookcase                       - FILLED
[987654] Filing Cabinet                 - FILLED
Chris S. - Bedroom
[123456] Bed                            - FILLED
[654323] Armchair                       - FILLED
[000887] Nighttable                     - FILLED
[056789] Dresser                        - FILLED
[000888] Nighttable                     - FILLED
John M. - Kids Bedroom
[123457] Bed                            - FILLED
[123458] Bed                            - FILLED
[123459] Bed                            - FILLED
[123460] Bed                            - FILLED
[000889] Nighttable                     - FILLED
[000890] Nighttable                     - FILLED
[056790] Dresser                        - FILLED
[459215] Desk                           - FILLED


========================================
=     Processed Orders (incomplete)    =
========================================
Hong H. - 1-Room Office
[000000] Desk                           - TO BE FILLED
[147853] Office Chair                   - FILLED
[147854] Office Chair                   - FILLED
[987655] Filing Cabinet                 - FILLED
[987656] Filing Cabinet                 - FILLED
[987657] Filing Cabinet                 - FILLED
[000989] Bookcase                       - FILLED
Rania A. - 2-Room Home Office and Bedroom
[000000] Desk                           - TO BE FILLED
[000000] Desk                           - TO BE FILLED
[147855] Office Chair                   - FILLED
[000000] Bed                            - TO BE FILLED
[147856] Office Chair                   - FILLED
[147857] Office Chair                   - FILLED
[000891] Nighttable                     - FILLED
[654324] Armchair                       - FILLED
[056791] Dresser                        - FILLED


========================================
=          Inventory (full)            =
========================================
001 | Armchair       | 654325 |    7 | Upholstered Wing Chair
002 | Bed            | 123461 |    0 | Queen size bed with headboard
003 | Dresser        | 056792 |    4 | 6-Drawer Unit
004 | Nighttable     | 000892 |    0 | Nightstand with 2 drawers
005 | Filing Cabinet | 987658 |    1 | 3-drawer filing cabinet
006 | Office Chair   | 147858 |   14 | High-back carpet-rollers
007 | Bookcase       | 000990 |    2 | 5-shelf open bookcase
008 | Desk           | 459216 |    0 | 6-foot worktable