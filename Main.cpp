#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <crtdbg.h>
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"


using namespace std;

template<typename T> void printElement(T t, const int& width);
void printTableHeaders();
void printOptions();

bool fillTable();

void AddVehicleOption();
void RemoveVehicleOption();
void CarSearchOption();
void BikeSearchOption();
void RegSortOption();
void CostSortOption();




const char separator = ' ';
const int bigWidth = 23;
const int midWidth = 16;

int main() {	

#ifdef _DEBUG
	//_CrtSetBreakAlloc(95);
	_onexit(_CrtDumpMemoryLeaks);
#endif

	cout << "Vehicle Rental System\n";
	cout << "---------------------\n\n";

	printTableHeaders();
	fillTable();
	cout << "\n\n";

	char option = ' ';

	do {	
		printOptions();
		cin >> option;

		switch (option) {
			case '1': AddVehicleOption(); break;
			case '2': RemoveVehicleOption(); break;
			case '3': CarSearchOption(); break;
			case '4': BikeSearchOption(); break;
			case '5': RegSortOption(); break;
			case '6': CostSortOption(); break;
			case '9': break;
			default: cout << "Invalid Input\n\n"; break;
		}
	} while (option != '9');


	return 0;
}

void printOptions() {
	cout << "1) Add Vehicle\n"
		<< "2) Remove Vehicle\n"
		<< "3) Search By Car\n"
		<< "4) Search By Biken\n"
		<< "5) Sort By Registration Number\n"
		<< "6) Sort By Cost/Day\n"
		<< "9) Exit\n\n";
}

void printTableHeaders() {

	printElement("Registration Number", bigWidth);
	printElement("Cost Per Day", midWidth);
	printElement("Vehicle Type", midWidth);
	
	cout << endl;

	printElement("-------------------", bigWidth);
	printElement("------------", midWidth);
	printElement("------------", midWidth);

	cout << endl << endl;
}

template<typename T> void printElement(T t, const int& width)
{	
	cout << left  << setw(width) << setfill(separator) << t;			//using templates to repeatedly format table printing
}

void AddCar() {

	cout << "\n\nCreating Car\n"
		 << "------------\n\n";

	string regNum;
	cout << "Enter Registration Number:\n";
	cin >> regNum;
	string make;
	cout << "\nEnter Vehicle's Make:\n";
	cin >> make;
	string model;
	cout << "\nEnter Vehicle's Model:\n";
	cin >> model;	
	int age;
	cout << "\nEnter Vehicle's Age:\n";
	if (!(cin >> age))	throw - 1;
	int noDoors;
	cout << "\nEnter Number of Doors:\n";
	if (!(cin >> noDoors))	throw - 1;
	int noSeats;
	cout << "\nEnter Number of Seats:\n";
	if (!(cin >> noSeats))	throw - 1;

	Car* car = new Car(regNum, make, model, age, noDoors, noSeats);			//Creating new Car object

	car->addVehicle();	
}

void AddBike() {
	cout << "\n\nCreating Bike\n"
		 << "-------------\n\n";

	string regNum;
	cout << "Enter Registration Number:\n";
	cin >> regNum;
	string make;
	cout << "\nEnter Vehicle's Make:\n";
	cin >> make;
	string model;
	cout << "\nEnter Vehicle's Model:\n";
	cin >> model;
	int age;
	cout << "\nEnter Vehicle's Age:\n";
	if (!(cin >> age))	throw - 1;
	int engineSize;
	cout << "\nEnter Size of Engine:\n";
	if (!(cin >> engineSize))	throw - 1;
	int noWheels;
	cout << "\nEnter Number of Wheels:\n";
	if (!(cin >> noWheels))	throw - 1;

	Bike* bike = new Bike(regNum, make, model, age, engineSize, noWheels);		//Creating new bike object

	bike->addVehicle();
}

bool checkRegNum(string regNum) {
	if (sizeof(regNum) == 7) return true;
	cout << "Invalid Registration Number.\n\n";
	return false;
}

void AddVehicleOption() {
	cout << "\n\nAdd Vehicle\n"
		<< "-----------\n";

	cout << "1) Add Car\n";
	cout << "2) Add Bike\n\n";

	try {
		int input;
		cout << "Select Vehicle Type:\n";
		if (!(cin >> input))	throw - 1;

		if (input == 1) AddCar();
		else if (input == 2) AddBike();
		else throw - 1;
	}
	catch (int) {
		cerr << "\nInvalid Input\n"
			<< "Returning To Options. \n\n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void RemoveVehicleOption() {
	cout << "\n\nRemove Vehicle\n"
		<< "--------------\n\n";
}

void CarSearchOption() {
	cout << "\n\nCar Search\n"
		<<"----------\n\n"
		<< "1) Registration Number\n"
		<< "2) Number of Seats\n"
		<< "3) Number of Doors\n"
		<< "4)Return to Main Menu\n\n"
		<< "Select Option: ";
}

void BikeSearchOption() {
	cout << "\n\nBike Search\n"
		<< "-----------\n\n"
		<< "1) Registration Number\n"
		<< "2) Engine Size\n"
		<< "3) Number of Wheels\n"
		<< "4)Return to Main Menu\n\n"
		<< "Select Option: ";
}

void RegSortOption() {
	cout << "\n\nSort By Registration Number\n"
		<<"---------------------------\n\n";
}

void CostSortOption() {
	cout << "\n\nSort By Cost Per Day\n"
		<< "--------------------\n\n";
}

bool fillTable() {
	string line;

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open())
	{	
		while (getline(vehicleFile, line)) {		//Read Each line of file return true if there is a line.
			string regNum;
			int cost;
			string VehType;			

			replace(line.begin(), line.end(), ',', '\n');		// Set the start and end of each element of the line.

			stringstream ss(line);		//Using a string stream to split each element.

			ss >> regNum;				//Assigning each element of the string stream to the correct Var ready for output.
			ss >> cost;
			ss >> VehType;
			
			printElement(regNum, bigWidth);
			printElement(cost, midWidth);
			printElement(VehType, midWidth);	
			cout << endl;
		}
		return true;
	}
	else return false;
}


