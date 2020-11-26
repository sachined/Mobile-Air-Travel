#include "World_Planes.h"

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

	mainMap.sortByCity(false);
	mainMap.display();

	mainMap.add(fifth);

	mainMap.sortByCode(true);
	mainMap.display();

	mainMap.sortByName(true);
	mainMap.display();

	mainMap.add("Mineta", "San Jose", "SJC");

	Building* a = new airPort("Frogger", "Seattle", "STA");

	a->Name();
	a->getName();
	std::cout << "\n\n";

	mainMap.add(a);

	mainMap.sortByCity(true);
	mainMap.display();

	mainMap.remove(newHeart);
	mainMap.remove(fourthAir);
	mainMap.remove(fifth);

	mainMap.sortByCode(false);
	mainMap.display();

	mainMap.remove(a);

	mainMap.sortByName(false);
	mainMap.display();

	return 0;
}