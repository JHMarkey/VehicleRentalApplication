#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <list>
#include <vector>
#include <iomanip>
#include <crtdbg.h>
#include <cmath>
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"
#include "Rental.h"


using namespace std;

template<typename T> void printElement(T t, const int& width);
void printTableHeaders();

bool fillTable();
bool fillTable(vector<Vehicle*>);

vector<Vehicle*> AddVehicleOption(vector<Vehicle*>& vehicles);
vector<Vehicle*> RemoveVehicleOption(vector<Vehicle*>& vehicles);
void CarSearchOption();
void BikeSearchOption();
void RegSortOption(vector<Vehicle*>& vehicles);
void CostSortOption(vector<Vehicle*>& vehicles);
const vector<Vehicle*> getVehicleVector();;
const Car* CarRegSearch();
const Car* CarSeatSearch();
const Car* CarDoorSearch();
const Bike* BikeRegSearch();
const Bike* BikeWheelSearch();
const Bike* BikeEngineSearch();
bool sortOnReg(const Vehicle* lhs, const Vehicle* rhs);
bool sortOnCost(const Vehicle* lhs, const Vehicle* rhs);
const Bike* SelectVehicle(list<const Bike*> l);
const Car* SelectVehicle(list<const Car*> l);
char DisplayRentalOptions(const Vehicle* v);
list<const Rental*> GetRentals(const Vehicle* v);

const char separator = ' ';
const int bigWidth = 23;
const int midWidth = 16;

int main() {	

#ifdef _DEBUG
	//_CrtSetBreakAlloc(650);
	_onexit(_CrtDumpMemoryLeaks);
#endif	

	char option = ' ';
	vector<Vehicle*> vehicles = getVehicleVector();	
	
	do {
		cout << "Vehicle Rental System\n"
			<< "---------------------\n\n";

		printTableHeaders();
		fillTable(vehicles);
	
		vector<Vehicle*>::iterator it(vehicles.begin());		

		cout << "\n\n"
			<< "1) Add Vehicle\n"
			<< "2) Remove Vehicle\n"
			<< "3) Search For Car\n"
			<< "4) Search For Bike\n"
			<< "5) Sort By Registration Number\n"
			<< "6) Sort By Cost/Day\n"
			<< "9) Exit\n\n";
		cin >> option;
		ofstream vehicleFile;

		switch (option) {
		case '1': vehicles = AddVehicleOption(vehicles); break;			
		case '2': vehicles = RemoveVehicleOption(vehicles); break;
		case '3': CarSearchOption(); break;							//Searching is done using a new list created from data on the disk to prevent rentals been created for unconfirmed additions
		case '4': BikeSearchOption(); break;
		case '5': RegSortOption(vehicles); break;					//Sorting is done using the vector created everytime the main menu is loaded inorder to show the most recent changes in order.
		case '6': CostSortOption(vehicles); break;
		case '9': 	
			vehicleFile.open("VehicleList.txt");
			if (vehicleFile.is_open()) {
				vehicleFile << "";
			}
			while (it != vehicles.end()) {
				(*it)->addVehicle(); 
				delete(*it);
				it++;
			} 
			vehicleFile.close();
			break;
		default: cout << "Invalid Input\n\n"; break;
		}
		
	} while (option != '9');

	

	return 0;
}

bool fillTable() {
	string line;
	int count = 1;
	
	

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open())
	{
		while (getline(vehicleFile, line)) {		//Read Each line of file return true if there is a line.
			string regNum;
			double cost;
			string VehType;


			replace(line.begin(), line.end(), ',', '\n');		// Replaces Each ',' in the string with an new-line character so stringstream knows where to split.

			stringstream ss(line);		//Using a string stream to split each element on the new-line character.

			ss >> regNum;				//Assigning each element of the string stream to the correct Var ready for output.
			ss >> cost;
			ss >> VehType;

			char* c;
			string s(regNum);
			c = &s[0];
			for (int i = 0; i < sizeof(c); i++) c[i] = toupper(c[i]);
			regNum = c;
			printElement(count, 4);
			printElement(regNum, bigWidth);
			printElement('$' + to_string(cost / 100), midWidth);
			printElement(VehType, midWidth);
			cout << endl;
			count++;
		}
		vehicleFile.close();
		return true;
	}
	else {
		return false;
	}
}

bool fillTable(vector<Vehicle*> v) {
	
	int count = 1;
	
	vector<Vehicle*>::iterator it(v.begin());
	
	
	while (it != v.end()) {
		string rNum = (*it)->getRegNum();
		stringstream ss;
		ss << fixed << setprecision(2) << (*it)->getCostPerDay() / 100;
		string costStr = '$' + ss.str();
		printElement(count, 4);
		printElement(rNum, bigWidth);
		printElement(costStr, midWidth);
		printElement((*it)->getVehType(), midWidth);
		cout << endl;
		count++;
		it++;
	}
	return true;
}

const vector<Vehicle*> getVehicleVector() {
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

		}
		vehicleFile.close();
		return vehicles;
	}
}

void printTableHeaders() {
	printElement("#", 4);	
	printElement("Registration Number", bigWidth);
	printElement("Cost Per Day", midWidth);
	printElement("Vehicle Type", midWidth);
	
	cout << endl;

	printElement("-", 4);
	printElement("-------------------", bigWidth);
	printElement("------------", midWidth);
	printElement("------------", midWidth);

	cout << endl << endl;
}

template<typename T> void printElement(T t, const int& width)
{	
	cout << left  << setw(width) << setfill(separator) << t ;			//using templates to repeatedly format table printing
}

Car* AddCar() {

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

	Car* c = new Car(regNum, make, model, age, noDoors, noSeats);			//Creating new Car object
	if (c->isNew()) return c;
	else {
		cout << "Unable to Add Vehicle\n"
			<< "Vehicle already Exists.\n\n";
		return(new Car("failveh", "", "", 1, 1, 1));
	}
}

Bike* AddBike() {
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

	Bike* b = new Bike(regNum, make, model, age, engineSize, noWheels);		//Creating new bike object
	if (b->isNew()) return b;
	else {
		cout << "Unable to Add Vehicle\n"
			<< "Vehicle already Exists.\n\n";
		return(new Bike("failveh", "", "", 1, 1, 1));
	}
	
}

bool checkRegNum(string regNum) {
	if (regNum.length() == 7) return true;
	cout << "Invalid Registration Number.\n\n";
	return false;
}

vector<Vehicle*> AddVehicleOption(vector<Vehicle*>& vehicles) {
	cout << "\n\nAdd Vehicle\n"
		<< "-----------\n";

	cout << "1) Add Car\n";
	cout << "2) Add Bike\n\n";

	Vehicle* v = new Bike("failveh", "", "", 1, 1, 1);

	try {
		int input;
		cout << "Select Vehicle Type:\n";
		if (!(cin >> input))	throw - 1;

		if (input == 1) v = AddCar();
		else if (input == 2) v = AddBike();
		else throw - 1;
		if (v->getRegNum() != "failveh") vehicles.push_back(v);
		else throw - 1;
	}
	catch (int) {
		cerr << "\nInvalid Input\n"
			<< "Returning To Options. \n\n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return vehicles;
}

vector<Vehicle*> RemoveVehicleOption(vector<Vehicle*>& vehicles) {
	cout << "\n\nRemove Vehicle\n"
		<< "--------------\n\n";

	vector<Vehicle*>::iterator it(vehicles.begin());
	vector < Vehicle*> updated;

	string regNum;
	cout << "Enter Registration Number:\n";
	cin >> regNum;


	while (it != vehicles.end()) {
		if ((*it)->getRegNum() != regNum) {
			updated.push_back(*it);
		}
		else {
			cout << "Vehicle Removed - " << regNum << "\n\n";
		}
		it++;
	}
	return updated;
}

void CarSearchOption() {
	const Car* car;
	char option = ' ';
	do {
		cout << "\n\nCar Search\n"
			<< "----------\n\n";
		cout << "1) Registration Number\n"
			<< "2) Number of Seats\n"
			<< "3) Number of Doors\n"
			<< "4) Return to Main Menu\n\n"
			<< "Select Option: ";
		cin >> option;
		switch (option)
		{
		case '1': car = CarRegSearch(); if (car->getRegNum() != "FAILVEH") { car->display(); option = DisplayRentalOptions(car); }delete(car); break;			//Performs Requested Search, if the search is successful it displays details
		case '2': car = CarSeatSearch(); if (car->getRegNum() != "FAILVEH") { car->display(); option = DisplayRentalOptions(car); }delete(car); break;			//Related to the Selected Vehicle. It then deletes the Object and Returns to
		case '3': car = CarDoorSearch(); if (car->getRegNum() != "FAILVEH") { car->display(); option = DisplayRentalOptions(car); }delete(car); break;			//Car Search Menu.
		case '4': break;	
		default: cout << "Invalid Input\n\n"; break;
		}

	} while (option != '4');

}

void BikeSearchOption() {
	const Bike* bike;
	char option = ' ';
	do {
		cout << "\n\nBike Search\n"
			<< "-----------\n\n";
		cout << "1) Registration Number\n"
			<< "2) Engine Size\n"
			<< "3) Number of Wheels\n"
			<< "4) Return to Main Menu\n\n"
			<< "Select Option: ";
		cin >> option;
		switch (option)
		{
		case '1': bike = BikeRegSearch(); if (bike->getRegNum() != "FAILVEH") { bike->display(); option = DisplayRentalOptions(bike); } delete(bike);  break;
		case '2': bike = BikeEngineSearch(); if (bike->getRegNum() != "FAILVEH") { bike->display(); option = DisplayRentalOptions(bike); } delete(bike);  break;
		case '3': bike = BikeWheelSearch(); if (bike->getRegNum() != "FAILVEH") { bike->display(); option = DisplayRentalOptions(bike); } delete(bike);   break;
		case '4': break;
		default: cout << "Invalid Input\n\n"; break;
		}

		
		

	} while (option != '4');
	
}

bool FileExists(const string& name) {
	ifstream f(name.c_str());
	return f.good();
}

const int GetNoRentals(const Vehicle* v) {
	int count = 0;
	string line;

	ifstream rFile(v->getRegNum() + ".txt");

	if (rFile.is_open()) {
		while (getline(rFile, line)) {
			count++;
		}
	}
	return count;
}

int* CreateDate(string& date) {
	int* dateA = (int*)malloc(sizeof(int) * 3);
	replace(date.begin(), date.end(), '/', '\n');
	stringstream ss(date);
	ss >> dateA[0];
	ss >> dateA[1];
	ss >> dateA[2];
	return dateA;
}

list<const Rental*> GetRentals(const Vehicle* v) {
	string line;
	list<const Rental*> rentals;
	ifstream rFile(v->getRegNum() + ".txt");
	if (rFile.is_open()) {
		while (getline(rFile, line, '\n')) {
			string starts{};
			string ends{};
			int noDays{};
			string name;
			string address;
			string teleN;

			replace(line.begin(), line.end(), ',', '\n');
			replace(line.begin(), line.end(), ' ', '_');
			stringstream ss(line);

			ss >> starts;
			ss >> ends;
			ss >> noDays;
			ss >> name;
			ss >> address;
			ss >> teleN;

			int* startDates = CreateDate(starts);
			int* endDates = CreateDate(ends);

			const RentalDate* start = new RentalDate(startDates[0], startDates[1], startDates[2] );
			const RentalDate* end = new RentalDate(endDates[0], endDates[1], endDates[2]);

			const Rental* r = new Rental(v, name, address, teleN, start, end, noDays);
			
			free(startDates);
			free(endDates);

			rentals.push_back(r);
		}
		return rentals;
	}
	return rentals;
}

char DisplayRentalOptions(const Vehicle* v) {

	char option = ' ';
	do {
		cout << "\n\n"
			<< "1) Rent Vehicle\n"
			<< "2) View Rental History\n"
			<< "9) Return to Main Menu\n\n"
			<< "Please choose an option:\n";
		cin >> option;

		
		if (option == '1') {
			Rental* r = new Rental(v);
			if (!FileExists(v->getRegNum() + ".txt")) r->CreateRentalFile();
			r->AddRentalDetails();
			delete(r);
		}
		else if (option == '2') {
			cout << "Rental History\n"
				<< "--------------\n\n";
			list<const Rental*> rentals = GetRentals(v);
			list<const Rental*>::iterator it(rentals.begin());
			char c = '0';
			int no = 0;
			int count = 1;
			while (it != rentals.end() && c != '9') {
				c = '0';
				no = (*it)->GetNoRentals();

				(*it)->DisplayRentalDetails(count);
				while (c != '1' && c != '2' && c != '9') {
					cout << "\n\n1) View Next Record\n"
						<< "2) View Previous Record\n"
						<< "9) Return to Vehicle Information Screen\n\n"
						<< "Please Choose an Option:\n";
					cin >> c;
				}
				if (c == '1' && count < no) {
					count++;
					it++;
				}
				else if (c == '2' && count != 1) {
					count--;
					it--;
				}
				else if(c != '9') {
					cout << "\n\nUnable to Fetch Data. Rental was out of Range.\n\n";
				}

			}
			it = rentals.begin();

			while (it != rentals.end()) {
				delete(*it);
				it++;
			}
		}
		else if (option != '9') cout << "Invalid Input.";	

	} while (option != '9');
	return '4';
}

void RegSortOption(vector<Vehicle*>& vehicles) {
	cout << "\n\nSort By Registration Number\n"
		<<"---------------------------";
	
		sort(vehicles.begin(), vehicles.end(), sortOnReg);						// Sorts Vehicles using their regnum is alphabetical order.
		vector<Vehicle*>::iterator it(vehicles.begin());
		int count = 1;
		cout << "\n\n";
		printTableHeaders();
		while (it != vehicles.end()) {
			(*it)->printDetails(count, (*it)->getCostPerDay());					// Iterates through all vehicles and prints details.
			it++; count++;														// Iterator Increments onto next Vehicle and Vehicle Number also increments.
		}
		cout << "\n\n";
		system("pause");
		cout << "\n\n";	
	
}

void CostSortOption(vector<Vehicle*>& vehicles) {
	cout << "\n\nSort By Cost Per Day\n"
		<< "--------------------";
		sort(vehicles.begin(), vehicles.end(), sortOnCost);
		vector<Vehicle*>::iterator it(vehicles.begin());
		int count = 1;
		cout << "\n\n";
		printTableHeaders();
		while (it != vehicles.end()) {
			(*it)->printDetails(count, (*it)->getCostPerDay());
			it++; count++;
		}
		cout << "\n\n";
		system("pause");
		cout << "\n\n";	
}

bool sortOnReg(const Vehicle* lhs, const Vehicle* rhs) {
	return lhs->getRegNum() < rhs->getRegNum();								//Uses operator overloading to compare the strings.
}

bool sortOnCost(const Vehicle* lhs, const Vehicle* rhs) {
	return lhs->getCostPerDay() < rhs->getCostPerDay();						//Uses operator's standard operation to compare numbers (Doubles).
}



const Car* CarRegSearch() {
	string r;
	do {
		cout << "\n\nEnter Registration Number:";	
		cin >> r;
	} while (!checkRegNum(r));
	

	string line;
	const Car* car;
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
			cout << "\n\n";
			vehicleFile.close();
			return SelectVehicle(cars);
		}
		
	}
	vehicleFile.close();
	return new Car("failveh", "f", "f", 0, 0, 0);
}

const Bike* BikeRegSearch() {
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
			vehicleFile.close();
			return SelectVehicle(bikes);
		}
		
	}
	vehicleFile.close();
	return new Bike("failveh","f", "f",0,0,0);
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

const Car* CarSeatSearch() {
	int noSeats = getNoSeats();

	string line;
	const Car* car;
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
			cout << "\n\n";

			vehicleFile.close();
			return SelectVehicle(cars);
		}

	}
	vehicleFile.close();
	return new Car("failveh", "f", "f", 0, 0, 0);
}

const Car* CarDoorSearch() {
	int noSeats = getNoDoors();

	string line;
	const Car* car;
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
		cout << "\n\n";
		vehicleFile.close();
		return SelectVehicle(cars);
	}
	vehicleFile.close();
	return new Car("failveh", "f", "f", 0, 0, 0);
}

const Bike* BikeWheelSearch() {
	int w;
	try {
		cout << "Enter Number of Wheels(2 or 3):\n";
		if (!(cin >> w))	throw - 1;
		if (w > 3)	throw - 1;
	}
	catch (int) {
		cerr << "\nInvalid Input\n"
			<< "Default Value is 2.\n\n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		w = 2;
	}


	string line;
	const Bike* bike;
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

			if (wheels == w && vType == "Bike") {
				bike = new Bike(cRegNum, make, model, age, eSize, wheels);
				bikes.push_back(bike);
			}
		}
		if (bikes.empty()) {
			cout << "\n\nNo Vehicle With This Number of Wheels Was Found.\n\n";
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

			vehicleFile.close();
			return SelectVehicle(bikes);
		}

	}
	vehicleFile.close();
	return new Bike("failveh", "f", "f", 0, 0, 0);
}

const Bike* BikeEngineSearch() {
	int e;
	try {
		cout << "Enter Engine Size:\n";
		if (!(cin >> e))	throw - 1;
		
	}
	catch (int) {
		cerr << "\nInvalid Input\n"
			<< "Default Value is 1000cc.\n\n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		e = 1000;
	}


	string line;
	const Bike* bike;
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

			if (eSize == e && vType == "Bike") {
				bike = new Bike(cRegNum, make, model, age, eSize, wheels);
				bikes.push_back(bike);
			}
		}
		if (bikes.empty()) {
			cout << "\n\nNo Vehicle With This Engine Size Was Found.\n\n";
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

			vehicleFile.close();
			return SelectVehicle(bikes);
		}

	}
	
	vehicleFile.close();
	return new Bike("failveh", "f", "f", 0, 0, 0);
}





const Bike* SelectVehicle(list<const Bike*> l) {
	list<const Bike*>::iterator it(l.begin());
	try {
		int input;
		cout << "Select Vehicle:\n";
		if (!(cin >> input))	throw - 1;
		if (input > l.size())	throw - 1;

		for (int i = 0; i < input; i++) {
			delete(*it);
			(it++);
		}
		return *it;
	}
	catch (int) {
		cerr << "\nInvalid Input\n"
			<< "Returning To Options. \n\n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return new Bike("failveh", "f", "f", 0, 0, 0);
}

const Car* SelectVehicle(list<const Car*> l) {
	list<const Car*>::iterator it(l.begin());
	try {
		int input;
		cout << "Select Vehicle:\n";
		if (!(cin >> input))	throw - 1;
		if (input > l.size())	throw - 1;

		for (int i = 1; i < input; i++) {
			delete(*it);
			(it++);
		}

		return *it;
	}
	catch (int) {
		cerr << "\nInvalid Input\n"
			<< "Returning To Options. \n\n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return new Car("failveh", "f", "f", 0, 0, 0);
}

