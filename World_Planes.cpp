#include "World_Planes.h"
#include <utility> // std::move

/* BUILDING ----------------------------------------
	This is an identifier function (from Base class)
	Useful for derived pointers and references
*/
void Building::Name()
{
	std::cout << "\nI am a BUILDING!\n\n";
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
airPort::airPort(airPort&& other) noexcept {
	std::cout << "Move constructor.." << std::endl;
	*this = std::move(other);
}

// Copy Assignment operator
airPort& airPort::operator=(const airPort& other) {
	if (this == &other)
		return *this;
	*this = other;
	return *this;
}

// Move Assignment operator (BETA)
airPort& airPort::operator=(airPort&& other) noexcept {
	return *this;
}

// This will display the plane number through a function
int airPort::operator()() const { return this->PlaneNumber; }

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
	if (e == NULL)
		return;
	std::string airName = e->GetAir();
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
	// should seperate for function (too verbiose)
	cities.push_back(currentAir);
	currentAir->getCityName();
	std::cout << " has been added!\n";
	size++;
	currentAir = nullptr;
	// ..................
}

// Adding the vector with Building pointer via reference
void mapQueue::add(Building*& newBuilding) {
	// Must be casted via dynamic_cast to enable push into vector
	currentAir = dynamic_cast<airPort*>(newBuilding);
	// should seperate for function (too verbiose)
	cities.push_back(currentAir);
	currentAir->getCityName();
	std::cout << " has been added!\n";
	size++;
	currentAir = nullptr;
	// ..................
}

void mapQueue::add() {
	currentAir = new airPort();
	// should seperate for function (too verbiose)
	cities.push_back(currentAir);
	currentAir->getCityName();
	std::cout << " has been added!\n";
	size++;
	currentAir = nullptr;
	// ..................
}

void mapQueue::add(std::string name, std::string city, std::string code) {

	currentAir = new airPort(name, city, code);
	// should seperate for function (too verbiose)
	cities.push_back(currentAir);
	currentAir->getCityName();
	std::cout << " has been added!\n";
	size++;
	currentAir = nullptr;
	// ..................
}

// Removing from vector 
// still not completely BUGS FREE
/* Towards the end of the function, the vector is not properly populated
	For example, if there are 3 airports and one is removed,
	3rd airport has two places occupied...
	This is still an oncoming fix
	PLEASE BE CAREFUL!
	11/20/20 Fixed
*/
void mapQueue::remove(airPort*& oldPlace) {

	bool found = false;
	unsigned pos = 0;

	currentAir = oldPlace;
	// should seperate for function (too verbiose)
	// iterate over all elements in vector
	for (auto& elem : cities) {
		if ((elem == currentAir || elem->GetAir() == currentAir->GetAir()) && !found)
		{
			found = true;
			std::cout << elem->GetCityName() << " found!\n";
			currentAir = nullptr;
			delete currentAir;
			std::cout << "This airport is deleted\n";
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
	// ..................
	oldPlace = nullptr;
	delete oldPlace;
}

void mapQueue::remove(Building*& newBuilding) {
	bool found = false;
	unsigned pos = 0;

	currentAir = dynamic_cast<airPort*>(newBuilding);
	// should seperate for function (too verbiose)
	// iterate over all elements in vector
	for (auto& elem : cities) {
		if (elem == currentAir && !found)
		{
			found = true;
			std::cout << elem->GetCityName() << " found!\n";
			currentAir = nullptr;
			delete currentAir;
			std::cout << "This airport is deleted\n";
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
	// ..................
	newBuilding = nullptr;
	delete newBuilding;
}

// Sorting functions @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Sort by city 
void mapQueue::sortByCity(bool flag) {
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
void mapQueue::sortByName(bool flag)
{
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
// **************************************************************************