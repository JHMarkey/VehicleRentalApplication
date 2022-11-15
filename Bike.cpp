#include "Bike.h"

Bike::Bike(string regNum, string make, string model, int age, int engineSize, int noWheels) : engineSize(engineSize), noWheels(noWheels) {
	this->regNum = regNum;
	this->make = make;
	this->model = model;
	this->age = age;
	vehicleType = "Bike";
}

Bike::~Bike(){}

double Bike::getCostPerDay() {
	double dailyCost;
	dailyCost = 1500 + roundEngineSize();
	return dailyCost;
}

int Bike::roundEngineSize() {
	int n = engineSize % 100;
	n = 100 - n;
	return engineSize + n;
}

void Bike::addVehicle() {
	if (this->isNew()) {
		ofstream vehicleFile("VehicleList.txt",ios::app);
		if (vehicleFile.is_open())
		{
			vehicleFile << regNum << "," << getCostPerDay() << "," << vehicleType << "," << engineSize << "," << noWheels << "," << age << "," << make << "," << model << "\n";
			vehicleFile.close();
			cout << "\nVehicle Successfully Added - " << regNum << "\n\n";
		}
		else cout << "Unable to Add Vehicle"
				  << "<No File Error>\n\n";
	}
	else cout << "\nUnable to Add Vehicle\n"
			  << "<Unable to Verify Error>\n\n";

}