#include "World_Planes.h"
#include <utility> // std::move

void Building::Name()
{
	std::cout << "I am a BUILDING!\n\n";
}

/* AIRPORT ===============================================

This class will store airport info, such as city and code

Can be used in mapQueue (a vector of pointers)
*/

// Default Constructor
airPort::airPort(): airName("DogWood Shining"), cityName("Phoenicia"), airCode("PNA")  {}

// Constructor
airPort::airPort(std::string placeName, std::string placeCity, std::string placeCode) : airName(placeName), cityName(placeCity), airCode(placeCode) {}

// Destructor
airPort::~airPort() {
	/*setCityName("");
	setAirCode("");*/
	displayNullAir();
}

// Copy Constructor
airPort::airPort(const airPort& other) : airName(other.airName), cityName(other.cityName), airCode(other.airCode)
{
	std::cout << "Copy constructor.." << std::endl;
	//airPort* ptr = new airPort(obj.getCityName(), obj.getCode());
	*this = other;

}

// Move Constructor (This will move the pointer of other to this and then makes other nullptr)
airPort::airPort(airPort&& other) noexcept {
	std::cout << "Move constructor.." << std::endl;
	*this = std::move(other);
	other.airCode = nullptr;
	other.cityName = nullptr;
	other.airName = nullptr;
}

// Copy Assignment operator
airPort& airPort::operator=(const airPort& other) {
	if (this == &other)
		return *this;
	PlaneNumber = other.PlaneNumber;
	return *this;
}

// Move Assignment operator
airPort& airPort::operator=(airPort&& other)	{
	this->PlaneNumber = std::move(other.PlaneNumber);
	//this->cityName = std::move(other.cityName);
	//this->airCode = std::move(other.airCode);
	//other.PlaneNumber = nullptr;
	return *this;
}

// This will display the plane number through a function (airPort())
int airPort::operator()() const {	return this->PlaneNumber;	}

// ---------------------------------------------------
// Setting name of the airport
void airPort::setName(std::string name) {	airName = name;	}

// Show the name of the airport
void airPort::getName()	{	std::cout << GetAir();	}

std::string airPort::GetAir() const	{	return airName;	}
// ---------------------------------------------------
// +++++++++++++++++++++++++++++++++++++++++++++++++++
// Setting name of city where airport is located
void airPort::setCityName(std::string place) {	cityName = place;	}

// Getting name of city where airport is located
void airPort::getCityName() {
	std::cout << GetCityName();
}

std::string airPort::GetCityName() const {	return cityName;	}
// +++++++++++++++++++++++++++++++++++++++++++++++++++
int airPort::PlaneNumber = 4423;

//static function
void airPort::printPlane() {
	std::cout << "Plane # is " << airPort::PlaneNumber << '\n';
}

//Operations regarding airCode
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void airPort::setAirCode(std::string code) {	airCode = code;	}

void airPort::getAirCode() {
	std::cout << GetCode();
}

std::string airPort::GetCode() const {	return airCode;	}
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void airPort::displayAir() {
	std::cout << "\nAirport currently:\n";
	getName();
	getCityName();
	getAirCode();
	std::cout << "\\\n";
}

void airPort::freeAirSpace() {
	setAirCode("");
	setCityName("");
	setName("");
	delete this;
}

// Only used for the destructor (for future memory purpose)
void airPort::displayNullAir() {
	std::cout << "The airport in " << cityName << " does not exist\n" << std::endl;
}

// ==============================================================
/* MAP QUEUE ****************************************************

This will store a list of airports that can be used
*/

mapQueue::mapQueue()	{
	std::cout << "A map is being created...\n\n";
	size = 0;
}

mapQueue::~mapQueue() {
	std::cout << '\n';
	/*cities.erase(cities.begin(), cities.begin() + cities.size());*/
	for (auto & elem : cities) {
		if (elem == nullptr) {
			delete elem;
		}
		else
		{
			elem->~airPort();
			elem->freeAirSpace();
			elem = nullptr;
			delete elem;
		}	
	}
	cities.shrink_to_fit();
	std::cout << "The map is being closed...\n";
	size = 0;
}

void mapQueue::display()	{
	std::vector<airPort*>::iterator it;

	std::cout << '\n';

	for (it = cities.begin(); it != cities.end(); it++) {
		(*it)->getName();
		std::cout << " airport @ ";
		(*it)->getCityName();
		std::cout << " (";
		(*it)->getAirCode();
		std::cout << ")\n";
	}
	std::cout << '\n';
}

// Adding to the vector
void mapQueue::add(airPort** newPlace) {
	//currentAir = new airPort();
	currentAir = *newPlace;
	cities.push_back(currentAir);
	currentAir->getCityName();
	std::cout << " has been added!\n";
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

*/

void mapQueue::remove(airPort** oldPlace)	{

	bool found = false;
	unsigned pos = 0;
	

	// iterate over all elements in vector
	for (auto & elem : cities)	{
		if (elem == *oldPlace && !found)
		{
			found = true;
			std::cout << elem->GetCityName() <<" found!\n";
			elem = nullptr;
			delete elem;
			std::cout << "This airport is deleted\n";
			//currentAir = nullptr;
			break;
		}
		else
			pos++;
	}
	for (unsigned i = pos; i < cities.size(); i++)	{
		if (i == cities.size() - 1) 
		{
			cities.resize(i);
			size = i;
			cities.shrink_to_fit();
			break;
		}
			cities[i] = cities[i + 1];
	}
	*oldPlace = nullptr;
	delete *oldPlace;
}

// Sorting functions @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Sort by city 
void mapQueue::sortByCity(bool flag)	{
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
void mapQueue::sortByCode(bool flag)	{
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
