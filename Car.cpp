#include "Car.h"

Car::Car(string regNum, string make, string model, int age, int noDoors, int noSeats) {
	this->regNum = regNum;
	this->make = make;
	this->model = model;
	this->age = age;
	this->noDoors = noDoors;
	this->noSeats = noSeats;
	vehicleType = "Car";
}

Car::~Car(){}

double Car::getCostPerDay(){
	double dailyCost;
	dailyCost = (2500 - (age * 150 - noDoors * 200));
	if (dailyCost < 1000) dailyCost = 1000;
	
	return dailyCost;	
}

void Car::addVehicle() {
	if (this->isNew()) {
		ofstream vehicleFile("VehicleList.txt", ios::app);
		if (vehicleFile.is_open())
		{
			vehicleFile << regNum << "," << getCostPerDay() << "," << vehicleType << "," << noDoors << "," << noSeats << "," << age << "," << make << "," << model << "\n";
			vehicleFile.close();
			cout << "\nVehicle Successfully Added\n\n";
		}
		else cout << "Unable to Add Vehicle"
				  << "<No File Error>\n\n";
	}
	else cout << "\nUnable to Add Vehicle\n"
			  << "<Unable to Verify Error>\n\n";
}
