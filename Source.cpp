#include "World_Planes.h"
#include "Goods.h"

int main() {

	mapQueue mainMap = mapQueue();

	mainMap.add();
	mainMap.add("Thunder Sonics", "Oklahoma City", "OKC");
	mainMap.add("Orange Promenade", "Tuscaloosa", "TSC");

	std::cout << "Third ";

	airPort* newHeart = new airPort();
	newHeart->printPlane();

	// Copy constructor was done!!
	airPort* fourthAir(newHeart);

	fourthAir->Name();
	// MOve constructor was done!!
	airPort* fifth(std::move(newHeart));

	mainMap.add(fourthAir);

	// Sorted by name of airport
	mainMap.sort(true, NAME);
	mainMap.sort(false, NAME);

	mainMap.add(fifth);

	// Sorted by city name
	mainMap.sort(true, CITY);
	mainMap.sort(false, CITY);

	// Sorted by aircode
	mainMap.sort(true, CODE);

	mainMap.add("Mineta", "San Jose", "SJC");

	Building* a = new airPort("Frogger", "Seattle", "STA");

	a->Name();
	a->getName();
	std::cout << "\n\n";

	mainMap.add(a);

	// Non-sorting (default)
	mainMap.sort(true, 3);

	mainMap.remove(newHeart);
	mainMap.remove(fourthAir);
	mainMap.remove(fifth);

	mainMap.sort(false, CODE);

	mainMap.remove(a);

	return 0;
}