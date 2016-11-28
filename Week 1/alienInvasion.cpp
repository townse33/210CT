#include <iostream> 
#include <vector>
#define INVASION_LENGTH 30 //define will be used for code versatility as invasion length was not a specified parameter

using namespace std;

int alienInvasion(int eggsX, int daysY) { 
//Alien Invasion Function: Takes arguments for X number of days for aliens to hatch, Y number of eggs produced per alien

	vector<int> hatchery; //Vector to contain data about eggs to hatch
	int totalAliens = 1;

	for (int i = 0; i < INVASION_LENGTH; i++) {
		hatchery.push_back(totalAliens * eggsX); //Each alien lays X eggs per day, thus the number to hatch is the product of alien no. and X

		if (hatchery.size() > daysY) {
			totalAliens += hatchery[0];
			hatchery.erase(hatchery.begin()); //To save space, hatchery is used as a FIFO that deletes obsolete data
		}

	}
	
	return totalAliens;

}


int main() {

	cout << "Total aliens: " << alienInvasion(3, 5) << endl; //Sample data provided by question

	system("pause");

	return 0; //0 indicates normal termination of the program
}