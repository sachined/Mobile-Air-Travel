#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
	Building - a base class that will be used as foundation for other classes,
	such as airPort class below
*/
struct Building {
	void Name();
	// Set up pure virtual class function
	virtual void getName() = 0;
	virtual ~Building() {}
};

/*
	Airport class - this will define an airport with name, city & assoc. air code
	This will inherit the Building class (hence polymorphism)
*/
class airPort : public Building {
	// Name of airport
	std::string airName;
	// City where airport located
	std::string cityName;
	// Airport code (three letters in length)
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
	airPort& operator=(airPort&& other) noexcept;

	// This will display the plane number through a function (airPort())
	int operator()() const;

	//Operations regarding airName
	// ---------------------------------
	void setName(std::string name);
	virtual void getName();
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

protected:
	// Only used for the destructor (for future memory purpose)
	void displayNullAir();
};

/*
*	airPort_deleter - Helper class that will remove pointer from mapQueue's vector
*					  of airPort pointers
*	Necessary since airPort class does not have any memory/pointer management
*/
struct airPort_deleter {
	void operator()(airPort*& e); // important to take pointer by reference
};


/*
	mapQueue class - Hold a vector of airPort pointers, size(amount) of pointers,
					 and internal airPort pointer
	This will hold pointers to airPort containers
*/
class mapQueue : public airPort_deleter {
	std::vector<airPort*> cities;
	int size;
	airPort* currentAir;

public:
	mapQueue();
	~mapQueue();

	// Shows the contents of vector
	void display();
	// Add via reference of airPort pointer
	void add(airPort*&);
	// Add via reference of Building pointer
	void add(Building*&);
	// Add via default airPort constructor
	void add();
	// Add via string parameters
	void add(std::string, std::string, std::string);
	// Remove via reference of airPort pointer
	void remove(airPort*&);
	// Remove via reference of Building pointer
	void remove(Building*&);

	// Sorting functions by city, code, and name
	void sortByCity(bool);
	void sortByCode(bool);
	void sortByName(bool);
};