#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <list>
#include<vector>
#include <iomanip>
#include <crtdbg.h>
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"


using namespace std;

template<typename T> void printElement(T t, const int& width);
void printTableHeaders();

bool fillTable();

void AddVehicleOption();
void RemoveVehicleOption();
void CarSearchOption();
void BikeSearchOption();
void RegSortOption();
void CostSortOption();
void CarRegSearch();
void CarSeatSearch();
void CarDoorSearch();
void BikeRegSearch();
bool sortOnReg(const Vehicle* lhs, const Vehicle* rhs);

const char separator = ' ';
const int bigWidth = 23;
const int midWidth = 16;

int main() {	

#ifdef _DEBUG
	//_CrtSetBreakAlloc(299);
	_onexit(_CrtDumpMemoryLeaks);
#endif

	cout << "Vehicle Rental System\n";
	cout << "---------------------\n\n";

	printTableHeaders();
	fillTable();
	cout << "\n\n";

	char option = ' ';

	do {	
		cout << "1) Add Vehicle\n"
			<< "2) Remove Vehicle\n"
			<< "3) Search For Car\n"
			<< "4) Search For Bike\n"
			<< "5) Sort By Registration Number\n"
			<< "6) Sort By Cost/Day\n"
			<< "9) Exit\n\n";
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

void printTableHeaders() {
	printElement("Vehicles Num", midWidth);	
	printElement("Registration Number", bigWidth);
	printElement("Cost Per Day", midWidth);
	printElement("Vehicle Type", midWidth);
	
	cout << endl;

	printElement("------------", midWidth);
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
	if (regNum.length() == 7) return true;
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
		<< "----------\n\n";
	char option = ' ';
		do {
			cout << "1) Registration Number\n"
				<< "2) Number of Seats\n"
				<< "3) Number of Doors\n"
				<< "4) Return to Main Menu\n\n"
				<< "Select Option: ";
			cin >> option;
			switch (option) 
			{
			case '1': CarRegSearch(); break;
			case '2': CarSeatSearch(); break;
			case '3': CarDoorSearch(); break;
			case '4': break;
			default: cout << "Invalid Input\n\n"; break;				
			}
		} while (option != '4');
		
}

void BikeSearchOption() {
	cout << "\n\nBike Search\n"
		<< "-----------\n\n";
		char option = ' ';
		do {
			cout << "1) Registration Number\n"
				<< "2) Engine Size\n"
				<< "3) Number of Wheels\n"
				<< "4) Return to Main Menu\n\n"
				<< "Select Option: ";
			cin >> option;
			switch (option)
			{
			case '1': BikeRegSearch();  break;
			case '2': break;
			case '3': break;
			case '4': break;
			default: cout << "Invalid Input\n\n"; break;
			}
		} while (option != '4');
}

void RegSortOption() {
	cout << "\n\nSort By Registration Number\n"
		<<"---------------------------\n\n";

	string line;
	vector<Vehicle*> vehicles;
	int count = 1;

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open())
	{
		while (getline(vehicleFile, line)) {		
			string cRegNum;
			int cost;
			string vType;
			int age;
			int doors = 0;
			int seats = 0;
			int eSize = 0;
			int wheels = 0;
			string make;
			string model;

			replace(line.begin(), line.end(), ',', '\n');
			stringstream ss(line);

			ss >> cRegNum;
			ss >> cost;
			ss >> vType;
			if (vType == "Car") {
				ss >> doors;
				ss >> seats;
			}
			else {
				ss >> eSize;
				ss >> wheels;
			}			
			ss >> age;
			ss >> make;
			ss >> model;

			if (vType == "Car") {
				Car* car = new Car(cRegNum, make, model, age, doors, seats);
				vehicles.push_back(car);
			}
			else {
				Bike* bike = new Bike(cRegNum, make, model, age, eSize, wheels);
				vehicles.push_back(bike);
			}

			sort(vehicles.begin(), vehicles.end(), sortOnReg);
			vector<Vehicle*>::iterator it(vehicles.begin());
			int count = 1;
			cout << "\n\n";
			printTableHeaders();
			while (it != vehicles.end()) {
				(*it)->printDetails(count, (*it)->getCostPerDay());
				it++; count++;
			}
		}
		
	}

}

bool sortOnReg(const Vehicle* lhs, const Vehicle* rhs) {
	return lhs->getRegNum() < rhs->getRegNum();
}

void CostSortOption() {
	cout << "\n\nSort By Cost Per Day\n"
		<< "--------------------\n\n";
}

bool fillTable() {
	string line;
	int count = 1;
	
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
			printElement(count, midWidth);
			printElement(regNum, bigWidth);
			printElement(cost, midWidth);
			printElement(VehType, midWidth);	
			cout << endl;
			count++;
		}
		return true;
	}
	else return false;
}

void CarRegSearch() {
	string r;
	do {
		cout << "\n\nEnter Registration Number:";	
		cin >> r;
	} while (!checkRegNum(r));
	

	string line;
	const Car* car = new Car("", "", "", 0, 0, 0);
	list<const Car*> cars;

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open()) {
		while (getline(vehicleFile, line)) {
			
			string cRegNum;
			int cost;
			string vType;
			int age;
			int doors;
			int seats;
			string make;
			string model;

			replace(line.begin(), line.end(), ',', '\n');
			stringstream ss(line);

			ss >> cRegNum;
			ss >> cost;
			ss >> vType;
			ss >> doors;
			ss >> seats;
			ss >> age;			
			ss >> make;
			ss >> model;			

			if (cRegNum == r && vType == "Car") {
				car = new Car(cRegNum, make, model, age, doors, seats);
				cars.push_back(car);
			}
		}
		if (cars.empty()) {
			cout << "\n\nNo Vehicle With This Registration Number Was Found.\n\n";
		}
		else {
			int count = 1;
			cout << "\n\n";			
			printTableHeaders();
			list<const Car*>::iterator it(cars.begin());
			while (it != cars.end()) {
				(*it)->printDetails(count, (*it)->getCostPerDay());
				it++; count++;
			}
		}
		delete(car);
	}
	
}

void BikeRegSearch() {
	string r;
	do {
		cout << "\n\nEnter Registration Number:";
		cin >> r;
	} while (!checkRegNum(r));


	string line;
	const Bike* bike = new Bike("", "", "", 0, 0, 0);
	list<const Bike*> bikes;

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open()) {
		while (getline(vehicleFile, line)) {

			string cRegNum;
			int cost;
			string vType;
			int age;
			int eSize;
			int wheels;
			string make;
			string model;

			replace(line.begin(), line.end(), ',', '\n');
			stringstream ss(line);

			ss >> cRegNum;
			ss >> cost;
			ss >> vType;
			ss >> eSize;
			ss >> wheels;
			ss >> age;
			ss >> make;
			ss >> model;

			if (cRegNum == r && vType == "Bike") {
				bike = new Bike(cRegNum, make, model, age, eSize, wheels);
				bikes.push_back(bike);
			}
		}
		if (bikes.empty()) {
			cout << "\n\nNo Vehicle With This Registration Number Was Found.\n\n";
		}
		else {
			int count = 1;
			cout << "\n\n";
			printTableHeaders();
			list<const Bike*>::iterator it(bikes.begin());					//Iterates through all of the vehicles that match the search criteria
			while (it != bikes.end()) {
				(*it)->printDetails(count, (*it)->getCostPerDay());
				it++; count++;
			}
		}
		delete(bike);
	}

}

int getNoSeats() {
	try {
		int input;
		cout << "Enter Number of Seats:\n";
		if (!(cin >> input))	throw - 1;
		else return input;
	}
	catch (int) {
		cerr << "\nInvalid Input\n"
			<< "Default Value is 5.\n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return 5;
	}
}

int getNoDoors() {
	try {
		int input;
		cout << "Enter Number of Doors:\n";
		if (!(cin >> input))	throw - 1;
		else return input;
	}
	catch (int) {
		cerr << "\nInvalid Input\n"
			<< "Default Value is 5.\n\n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return 5;
	}
}

void CarSeatSearch() {
	int noSeats = getNoSeats();

	string line;
	const Car* car = new Car("", "", "", 0, 0, 0);
	list<const Car*> cars;

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open()) {
		while (getline(vehicleFile, line)) {
			string cRegNum;
			int cost;
			string vType;
			int age;
			int doors;
			int seats;
			string make;
			string model;

			replace(line.begin(), line.end(), ',', '\n');
			stringstream ss(line);
			

			ss >> cRegNum;
			ss >> cost;
			ss >> vType;
			ss >> doors;
			ss >> seats;
			ss >> age;
			ss >> make;
			ss >> model;

			if (seats == noSeats && vType == "Car") {
				car = new Car(cRegNum, make, model, age, doors, seats);
				cars.push_back(car);
			}
		}
		if (cars.empty()) {
			cout << "\n\nNo Vehicle With This Number of Seats Was Found.\n\n";
		}
		else {
			int count = 1;
			cout << "\n\n";
			printTableHeaders();
			list<const Car*>::iterator it(cars.begin());
			while (it != cars.end()) {
				(*it)->printDetails(count, (*it)->getCostPerDay());
				it++; count++;
			}
		}

	}
	delete(car);
}

void CarDoorSearch() {
	int noSeats = getNoDoors();

	string line;
	const Car* car = new Car("", "", "", 0, 0 , 0);
	list<const Car*> cars;

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open()) {
		while (getline(vehicleFile, line)) {
			string cRegNum;
			int cost;
			string vType;
			int age;
			int doors;
			int seats;
			string make;
			string model;

			replace(line.begin(), line.end(), ',', '\n');
			stringstream ss(line);


			ss >> cRegNum;
			ss >> cost;
			ss >> vType;
			ss >> doors;
			ss >> seats;
			ss >> age;
			ss >> make;
			ss >> model;

			if (seats == noSeats && vType == "Car") {
				car = new Car(cRegNum, make, model, age, doors, seats);
				cars.push_back(car);				
			}
		}
		if (cars.empty()) {
			cout << "\n\nNo Vehicle With This Number of Doors Was Found.\n\n";
		}
		else {
			int count = 1;
			cout << "\n\n";
			printTableHeaders();
			list<const Car*>::iterator it(cars.begin());
			while (it != cars.end()) {
				(*it)->printDetails(count, (*it)->getCostPerDay());
				it++; count++;
			}			
		}
	}
	delete(car);
}
