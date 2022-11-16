#include "Vehicle.h"

string Vehicle::getRegNum() {
	return regNum;
}

string Vehicle::getMake() {
	return make;
}

string Vehicle::getModel() {
	return model;
}

int Vehicle::getAge(){
	return age;
}

void Vehicle::display() {
	cout << regNum << "\t\t\t" << getCostPerDay() << "\t\t\t" << vehicleType << "\n";	
}


void Vehicle::addVehicle() {
	if (this->isNew()) {
		ofstream vehicleFile("VehicleList.txt");
		if (vehicleFile.is_open())
		{
			vehicleFile << regNum << "," << getCostPerDay() << "," << vehicleType << "\n";
			vehicleFile.close();
			cout << "\nVehicle Successfully Added - " << regNum << "\n\n";
		}
		else cout << "\nUnable to Add Vehicle\n"
				  << "<No File Error>\n\n";
	}	
	else cout << "\nUnable to Add Vehicle\n"
			  << "<Not Unique Error>\n\n";
}

const double Vehicle::getCostPerDay() const {
	return 1200;
}

bool Vehicle::isNew() {
	string line;

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open())
	{
		while (getline(vehicleFile, line, ',')) {		//iterates through all of the reg numbers in the "VehicleList.txt" file.
			string cRegNum;

			replace(line.begin(), line.end(), ',', '\n');
			stringstream ss(line);

			ss >> cRegNum;			

			if (cRegNum == regNum) return false;	 //if the current line's RegNum is the same as the RegNum Trying to be added return false.
		}
		return true;
	}
	else return false;

}

void const Vehicle::printDetails(int count, int cost) const {
	printElement(count, midWidth);
	printElement(regNum, bigWidth);	
	printElement(cost, midWidth);
	printElement(vehicleType, midWidth);
	cout << "\n\n";
}


