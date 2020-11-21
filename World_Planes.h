#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Building {

public:
	void getName();
	// Set up virtual class function
	virtual void getName() = 0;
	virtual ~Building()	{}
};

/*
	Airport class - this will define an airport with name, city & assoc. air code

	This will inherit the Building class (hence polymorphism)
*/
class airPort {
	// Name of airport
	std::string airName;
	// Name of city
	std::string cityName;
	// Airport code
	std::string airCode;
public:
	//default constructor
	airPort();
	//constructor
	airPort(std::string, std::string, std::string);
	// destructor
	~airPort();

	// copy constructor
	airPort(const airPort& other);
	//move constructor
	airPort(airPort&& other) noexcept;

	//copy assignment operator
	airPort& operator=(const airPort& other);
	//move assignment operator
	airPort& operator=(airPort&& other);

	// This will display the plane number through a function (airPort())
	int operator()() const;
	
	//Operations regarding airName
	// ---------------------------------
	void setName(std::string name);
	void getName();
	std::string GetAir() const;

	//Operations regarding cityName
	// +++++++++++++++++++++++++++++++++
	void setCityName(std::string place);
	void getCityName();
	std::string GetCityName() const;
	
	// STATIC
	static int PlaneNumber;
	static void printPlane();

	//Operations regarding airCode
	// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	void setAirCode(std::string code);
	void getAirCode();
	std::string GetCode() const;
	
	// $$$$ Show info of airport $$$$
	void displayAir();
	// Free pointer to nullptr
	void freeAirSpace();
	
protected:
	// Only used for the destructor (for future memory purpose)
	void displayNullAir();
};

/*
	mapQueue class - Hold a vector of airPort pointers, size(amount) of pointers, 
					 and internal airPort pointer

	This will hold pointers to airPort containers

*/
class mapQueue {
	std::vector<airPort*> cities;
	int size;
	airPort* currentAir;
public:
	mapQueue();
	~mapQueue();
	
	void display();
	void add(airPort**);
	void remove(airPort**);
	
	void sortByCity(bool);
	void sortByCode(bool);
	void sortByName(bool);
};
