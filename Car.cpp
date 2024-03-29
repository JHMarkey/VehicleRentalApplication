#include "Car.h"
#include "Rental.h"

Car::Car(const string regNum, const string make, const string model, const int age, const int noDoors, const int noSeats) : noDoors(noDoors), noSeats(noSeats) {
	this->regNum = regNum;
	this->make = make;
	this->model = model;
	this->age = age;
	const string c = "Car";
	vehicleType = c;
}

Car::~Car(){}

const double Car::getCostPerDay() const{
	double dailyCost;
	dailyCost = (2500 - (age * 150 - noDoors * 200));
	if (dailyCost < 1000) dailyCost = 1000;
	
	return dailyCost;	
}

void Car::addVehicle() {
	ofstream vehicleFile("VehicleList.txt", ios::app);
	if (vehicleFile.is_open())
	{
		vehicleFile << regNum << "," << getCostPerDay() << "," << vehicleType << "," << noDoors << "," << noSeats << "," << age << "," << make << "," << model << "\n";
		vehicleFile.close();
		cout << "\nVehicle Successfully Added - " << regNum << "\n\n";
	}
	else cout << "Unable to Add Vehicle - " << regNum
		<< "<No File Error>\n\n";
}


