#include "World_Planes.h"

int main() {

	mapQueue mainMap = mapQueue();

	airPort* firstAir = new airPort();

	mainMap.add(&firstAir);

	airPort* secondAir = new airPort("Orange Promenade","Tuscaloosa", "TSC");

	airPort* thirdAir = new airPort("Thunder Sonics","Oklahoma City", "OKC");

	mainMap.add(&secondAir);

	mainMap.add(&thirdAir);

	std::cout << "\nSecond ";
	
	secondAir->printPlane();

	// Copy constructor was done!!
	airPort* fourthAir(secondAir);

	// MOve constructor was done!!
	airPort* fifth (std::move(firstAir));

	/*mainMap.add(&fourthAir);*/

	mainMap.sortByCity(false);

	mainMap.display();

	/*mainMap.add(&fifth);*/

	mainMap.sortByCode(true);

	mainMap.display();

	mainMap.remove(&secondAir);

	mainMap.sortByName(true);

	mainMap.display();

	Building* a = new airPort();

	a->Name();

	a->getName();

	std::cout << '\n';
	
	mainMap.sortByCity(true);

	mainMap.display();

	return 0;
}
