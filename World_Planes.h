#pragma once

#include <iostream>
#include <vector>
#include <string>

class airPort {
	// Name of airport
	std::string cityName;
	// Airport code
	std::string airCode;
public:
	//default constructor
	airPort();
	//constructor
	airPort(std::string placeName, std::string placeCode);

	// destructor
	~airPort();

	// copy constructor
	airPort(const airPort& other);
	//move constructor
	airPort(airPort&& other);

	//copy assignment operator
	airPort& operator=(const airPort& other);

	//move assignment operator
	airPort& operator=(airPort&& other);

	// This will display the plane number through a function (airPort())
	int operator()() const;

	//Operations regarding cityName
	// +++++++++++++++++++++++++++++++++
	void setAirName(std::string place);

	void getAirName();
	
	std::string getCityName() const;
	// ++++++++++++++++++++++++++++++

	static int PlaneNumber;

	static void printPlane();

	//Operations regarding airCode
	// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

	void setAirCode(std::string code);

	void getAirCode();

	std::string getCode() const;
	// $$$$$$$$$$$$$$$$$$$$$$$$$$
	
	void displayAir();
protected:
	// Only used for the destructor (for future memory purpose)
	void displayNullAir();
};

class mapQueue {
	std::vector<airPort*> cities;
	int size;
	airPort* currentAir;
public:
	mapQueue();
	~mapQueue();

	void add(airPort**);
	void remove(airPort**);

};