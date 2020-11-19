
#include "World_Planes.h"

int main() {
	mapQueue mainMap = mapQueue();

	airPort* firstAir = new airPort();

	mainMap.add(&firstAir);
	
	airPort* secondAir = new airPort("Tuscaloosa", "TSC");

	airPort* thirdAir = new airPort("Oklahoma City", "OKC");

	mainMap.add(&secondAir);

	mainMap.add(&thirdAir);

	firstAir->operator();
		
	secondAir->displayAir();

	thirdAir->displayAir();


	airPort* fourthAir = airPort(secondAir*);

	mainMap.remove(&secondAir);

	return 0;

}