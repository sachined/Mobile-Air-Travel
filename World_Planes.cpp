#include "World_Planes.h"
#include <utility> // std::move

/* BUILDING ----------------------------------------
	This is an identifier function (from Base class)
	Useful for derived pointers and references
*/
void Building::Name()
{
	std::cout << "I am a BUILDING!\n\n";
}
//--------------------------------------------------
/*=================  AIRPORT  ==============================
This class will store airport info, such as city and code.
Can be used in mapQueue (a vector of pointers)	*/

// Default Constructor
airPort::airPort() : airName("DogWood Shining"), cityName("Phoenicia"), airCode("PNA") {}

// Constructor
airPort::airPort(std::string placeName, std::string placeCity, std::string placeCode) : airName(placeName), cityName(placeCity), airCode(placeCode) {}

// Destructor
airPort::~airPort() { displayNullAir(); }

// Copy Constructor
airPort::airPort(const airPort& other) : airName(other.airName), cityName(other.cityName), airCode(other.airCode) {
	std::cout << "Copy constructor.." << std::endl;
	*this = other;
}

// Move Constructor (BETA)
// (This will move the pointer of other to this and then makes other nullptr)
airPort::airPort(airPort&& other) noexcept	{
	std::cout << "Move constructor.." << std::endl;
	// Copy data from source object
	airName = other.airName;
	cityName = other.cityName;
	airCode = other.airCode;

	other.airName = nullptr;
	other.cityName = nullptr;
	other.airCode = nullptr;
}

// Copy Assignment operator
airPort& airPort::operator=(const airPort& other) {
	std::cout << "Copy constructor.." << std::endl;
	if (this != &other) {
		airName = other.airName;
		cityName = other.cityName;
		airCode = other.airCode;
	}
	return *this;
}

// Move Assignment operator (BETA)
airPort& airPort::operator=(airPort&& other) noexcept {
	std::cout << "Move constructor.." << std::endl;
	if (this != &other) {
		airName = other.airName;
		cityName = other.cityName;
		airCode = other.airCode;

		other.airName = nullptr;
		other.cityName = nullptr;
		other.airCode = nullptr;
	}
	return *this;
}

// This will display the plane number through a function
int airPort::operator()() const { return this->PlaneNumber; }

void airPort::Name()
{
	std::cout << "I am an Airport!\n\n";
}

// ---------------- NAME of airport -------------------------
// Setting name
void airPort::setName(std::string name) { airName = name; }

// Show the name
void airPort::getName() { std::cout << GetAir(); }

// Get name
std::string airPort::GetAir() const { return airName; }
// -------------------- NAME end ------------------------
// +++++++++++++++++ CITY of airport ++++++++++++++++++++++++
// Setting city
void airPort::setCityName(std::string place) { cityName = place; }

// Show city
void airPort::getCityName() { std::cout << GetCityName(); }

// Get city
std::string airPort::GetCityName() const { return cityName; }
// ++++++++++++++++++++ CITY end ++++++++++++++++++++++++
int airPort::PlaneNumber = 4423;

//static function that show the static plane number (4423)
void airPort::printPlane() {
	std::cout << "Plane # is " << PlaneNumber << "\n\n";
}

//Operations regarding airCode
// $$$$$$$$$$$$$$$$ AIRCODE $$$$$$$$$$$$$$$$$$$$$
void airPort::setAirCode(std::string code) { airCode = code; }

void airPort::getAirCode() { std::cout << GetCode(); }

std::string airPort::GetCode() const { return airCode; }
// $$$$$$$$$$$$$$$$$ AIRCODE end $$$$$$$$$$$$$$$$$$$$$

// Show the properties of airport
void airPort::displayAir() {
	getName();
	std::cout << " airport @ ";
	getCityName();
	std::cout << " (";
	getAirCode();
	std::cout << ")\n";
}

// Only used for the destructor (for future memory purpose)
void airPort::displayNullAir() {
	std::cout << "The airport in " << cityName << " does not exist,\n";
}
//======================= AIRPORT end =============================
/*--------------------- AIRPORT_DELETER -----------------------
This class that will be used with mapQueue

This will be used for freeing pointers at end of
program to prevent memory leak	*/
void airPort_deleter::operator()(airPort*& e) {
	std::string airName;
	
	if (e == NULL)
		return;
	airName = e->GetAir();
	e->~airPort();
	e = NULL;
	delete e;
	std::cout << airName << " airport has been removed!\n\n";
}
//----------------- AIRPORT_DELETER end ---------------------
/************************ MAP QUEUE *************************
This will store a list of airports that can be used
*/
mapQueue::mapQueue() {
	std::cout << "A map is being created...\n\n";
	size = 0;
	currentAir = nullptr;
}

mapQueue::~mapQueue() {
	for_each(cities.begin(), cities.end(), airPort_deleter());
	std::vector<airPort*>::iterator new_end = std::remove(cities.begin(), cities.end(), static_cast<airPort*>(NULL));
	// Removes the null pointers
	cities.erase(new_end, cities.end());
	// Shrinks the capacity to 0 by this point
	cities.shrink_to_fit();
	size = 0;
	std::cout << "The map is being closed...\n";
}

// Shows the properties of airport through an iterator
void mapQueue::display() {
	std::vector<airPort*>::iterator it;
	std::cout << '\n';
	for (it = cities.begin(); it != cities.end(); it++) {
		(*it)->displayAir();
	}
	std::cout << '\n';
}

// Adding to the vector with airPort pointer via reference
void mapQueue::add(airPort*& newPlace) {
	currentAir = newPlace;
	push_ptr(currentAir);
}

// Adding the vector with Building pointer via reference
void mapQueue::add(Building*& newBuilding) {
	// Must be casted via dynamic_cast to enable push into vector
	currentAir = dynamic_cast<airPort*>(newBuilding);
	push_ptr(currentAir);
}

void mapQueue::add() {
	currentAir = new airPort();
	push_ptr(currentAir);
}

void mapQueue::add(std::string name, std::string city, std::string code) {
	currentAir = new airPort(name, city, code);
	push_ptr(currentAir);
}

// This replaces the same lines in various add functions (Made 11/26/20)
void mapQueue::push_ptr(airPort*& currentAir)	{
	cities.push_back(currentAir);
	currentAir->getCityName();
	std::cout << " has been added!\n\n";
	size++;
	currentAir = nullptr;
}

// Removing from vector 
// still not completely BUGS FREE
/* Towards the end of the function, the vector is not properly populated
	For example, if there are 3 airports and one is removed,
	3rd airport has two places occupied...
	This is still an oncoming fix
	PLEASE BE CAREFUL!
	11/20/20 Fixed
	11/26/20 Refactored
*/
void mapQueue::remove(airPort*& oldPlace) {
	bool found = false;
	
	currentAir = oldPlace;
	remove_ptr(currentAir, found);

	oldPlace = nullptr;
	delete oldPlace;
}

void mapQueue::remove(Building*& newBuilding) {
	bool found = false;
	
	currentAir = dynamic_cast<airPort*>(newBuilding);
	remove_ptr(currentAir, found);

	newBuilding = nullptr;
	delete newBuilding;
}

void mapQueue::remove_ptr(airPort*& currentAir, bool& found)	{
	unsigned pos = 0;
	// iterate over all elements in vector
	for (auto& elem : cities) {
		if (elem == currentAir && !found)
		{
			found = true;
			std::cout << elem->GetCityName() << " found! ";
			currentAir = nullptr;
			delete currentAir;
			std::cout << "This airport is deleted\n\n";
			break;
		}
		else
			pos++;
	}
	for (unsigned i = pos; i < cities.size(); i++) {
		if (i == cities.size() - 1)
		{
			cities.resize(i);
			size = i;
			cities.shrink_to_fit();
			break;
		}
		cities[i] = cities[i + 1];
	}
}

// Sorting functions @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Sort by city 
void mapQueue::sortByCity(bool flag) {
	std::string status = flag ? "(A - Z)" : "(Z - A)";
	std::cout << "Sorted by City "<< status;
	if (flag) {
		std::sort(cities.begin(), cities.end(), [](airPort* a, airPort* b)
			{	return a->GetCityName() < b->GetCityName(); });
	}
	else
	{
		std::sort(cities.begin(), cities.end(), [](airPort* a, airPort* b)
			{	return a->GetCityName() > b->GetCityName(); });
	}
}
// Sort by air code
void mapQueue::sortByCode(bool flag) {
	std::string status = flag ? "(A - Z)" : "(Z - A)";
	std::cout << "Sorted by Code " << status;
	if (flag) {
		std::sort(cities.begin(), cities.end(), [](airPort* a, airPort* b)
			{	return a->GetCode() < b->GetCode(); });
	}
	else
	{
		std::sort(cities.begin(), cities.end(), [](airPort* a, airPort* b)
			{	return a->GetCode() > b->GetCode(); });
	}
}
// Sort by airport name
void mapQueue::sortByName(bool flag)	{
	std::string status = flag ? "(A - Z)" : "(Z - A)";
	std::cout << "Sorted by Name " << status;
	if (flag) {
		std::sort(cities.begin(), cities.end(), [](airPort* a, airPort* b)
			{	return a->GetAir() < b->GetAir(); });
	}
	else
	{
		std::sort(cities.begin(), cities.end(), [](airPort* a, airPort* b)
			{	return a->GetAir() > b->GetAir(); });
	}
}
// Aggregate sort
void mapQueue::sort(bool flag, int choice) {
	
	switch (choice) {
		case NAME:
			sortByName(flag);
			break;
		case CITY:
			sortByCity(flag);
			break;
		case CODE:
			sortByCode(flag);
			break;
		default:
			std::cout << "This is not sorted";
			break;
	}
	display();
}
// ************************** MAP QUEUE END *****************************