#include "Bike.h"

Bike::Bike(string regNum, string make, string model, int age, int engineSize, int noWheels) : engineSize(engineSize), noWheels(noWheels) {
	this->regNum = regNum;
	this->make = make;
	this->model = model;
	this->age = age;
	vehicleType = "Bike";
}

Bike::~Bike(){}

const double Bike::getCostPerDay() const{
	double dailyCost;
	dailyCost = 1500 + roundEngineSize();
	return dailyCost;
}

const int Bike::roundEngineSize() const {
	int n = engineSize % 100;
	n = 100 - n;
	return engineSize + n;
}

void Bike::addVehicle() {

	ofstream vehicleFile("VehicleList.txt", ios::app);
	if (vehicleFile.is_open())
	{
		vehicleFile << regNum << "," << getCostPerDay() << "," << vehicleType << "," << engineSize << "," << noWheels << "," << age << "," << make << "," << model << "\n";
		vehicleFile.close();
		cout << "\nVehicle Successfully Added - " << regNum << "\n\n";
	}
	else cout << "Unable to Add Vehicle"
		<< "<No File Error>\n\n";
}


