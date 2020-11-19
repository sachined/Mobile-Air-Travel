#include "World_Planes.h"
#include <utility> // std::move

/* AIRPORT ===============================================

This class will store airport info, such as city and code

Can be used in mapQueue (a vector of pointers)
*/

// Default Constructor
airPort::airPort(): cityName("Phoenix"), airCode("PHX")  {
	/*setAirName("Phoenix");
	setAirCode("PHX");*/
}

// Constructor
airPort::airPort(std::string placeName, std::string placeCode) {
	setAirName(placeName);
	setAirCode(placeCode);
}

// Destructor
airPort::~airPort() {
	setAirName("");
	setAirCode("");
	displayNullAir();
}

// Copy Constructor
airPort::airPort(const airPort& other) : cityName(other.cityName), airCode(other.airCode)
{
	std::cout << "Copy constructor.." << std::endl;
	//airPort* ptr = new airPort(obj.getCityName(), obj.getCode());
	*this = other;

}

// Move Constructor (This will move the pointer of other to this and then makes other nullptr)
airPort::airPort(airPort&& other) {
	std::cout << "Move constructor.." << std::endl;
	*this = std::move(other);
}

// Copy Assignment operator
airPort& airPort::operator = (const airPort& other) {
	if (this == &other)
		return *this;
	PlaneNumber = other.PlaneNumber;
	return *this;
}

// Move Assignment operator
airPort& airPort::operator = (airPort&& other)	{
	this->PlaneNumber = std::move(other.PlaneNumber);
	return *this;
}


// This will display the plane number through a function (airPort())
int airPort::operator()()const {	return this->PlaneNumber;	}

// +++++++++++++++++++++++++++++++++++++++++++++++++++
// Getting name of city where airport is located
void airPort::getAirName() {
	std::cout << "Airport located at " << getCityName() << '\n';
}

void airPort::setAirName(std::string place) {	cityName = place;	}

std::string airPort::getCityName() const {	return cityName;	}
// +++++++++++++++++++++++++++++++++++++++++++++++++++

int airPort::PlaneNumber = 4423;

//static function
void airPort::printPlane() {
	std::cout << "Plane # is " << airPort::PlaneNumber << '\n';
}


//Operations regarding airCode
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void airPort::getAirCode() {
	std::cout << "Code: " << getCode() << std::endl;
}

void airPort::setAirCode(std::string code) {
	airCode = code;
}

std::string airPort::getCode() const {	return airCode;	}
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void airPort::displayAir() {
	std::cout << "\nAirport currently:\n";
	getAirName();
	getAirCode();
	std::cout << "\\\n";
}

// Only used for the destructor (for future memory purpose)
void airPort::displayNullAir() {
	std::cout << "This airport does not exist\n" << std::endl;
}

/* MAP QUEUE 

This will store a list of airports that can be used
*/

mapQueue::mapQueue()	{
	std::cout << "A map is being created...\n";
	size = 0;
}

mapQueue::~mapQueue() {
	cities.clear();
	std::cout << "The map is being closed...\n";
	size = 0;
}

// Adding to the vector
void mapQueue::add(airPort** newPlace) {
	cities.push_back(*newPlace);
	std::cout << (*(newPlace))->getCityName() << " has been added!\n";
	size++;
}


// Removing from vector 
// still not completely BUGS FREE

/* Towards the end of the function, the vector is not properly populated

	For example, if there are 3 airports and one is removed,

	3rd airport has two places occupied...

	This is still an oncoming fix

	PLEASE BE CAREFUL!


*/

void mapQueue::remove(airPort** oldPlace)	{
		currentAir = *oldPlace;

		bool found = false;
		unsigned position = 0;

		// iterate over all elements in vector
		for (auto & elem : cities)
		{
			if (elem == currentAir)
			{
				found = true;
				std::cout << currentAir->getCityName() <<" has been found!" << std::endl;
				break;
			}
			else if (found == false)
			{
				position++;
			}
		}
		if (found) {
			currentAir->displayAir();

		}
		for (unsigned i = position; i < cities.size(); i++)
		{
			if (position == cities.size() - 1) {

				cities.resize(position);
				break;
			}
			cities[position] = cities[position + 1];
		}

	}
