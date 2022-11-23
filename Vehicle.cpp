#include "Vehicle.h"

const string Vehicle::getRegNum() const{
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

void const Vehicle::display() const{
	
	printElement("Registration Number", bigWidth);
	printElement("Cost Per Day", midWidth);
	printElement("Vehicle Type", midWidth);
	printElement("Vehicle Make", midWidth);
	printElement("Vehicle Model", midWidth + 1);

	cout << endl;

	printElement("-------------------", bigWidth);
	printElement("------------", midWidth);
	printElement("------------", midWidth);
	printElement("------------", midWidth);
	printElement("-------------", midWidth + 1);

	cout << endl << endl;

	printElement(regNum, bigWidth);
	printElement(getCostPerDay(), midWidth);
	printElement(vehicleType, midWidth);
	printElement(make, midWidth);
	printElement(model, midWidth + 1);

	cout << endl << endl;
	
}


void Vehicle::addVehicle() {
	if (this->isNew()) {
		ofstream vehicleFile("VehicleList.txt");
		if (vehicleFile.is_open())
		{
			vehicleFile << regNum << "," << getCostPerDay() << "," << vehicleType << "\n";
			vehicleFile.close();
			cout << "\nVehicle Successfully Added - " << regNum << "\n\n";
			vehicleFile.close();
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
			
			if (cRegNum == regNum) vehicleFile.close(); return false;	 //if the current line's RegNum is the same as the RegNum Trying to be added return false.
		}
		vehicleFile.close();
		return true;
	}
	else return false;

}

void const Vehicle::printDetails(int count, double cost) const {
	printElement(count, 4);
	printElement(regNum, bigWidth);	
	printElement(cost, midWidth);
	printElement(vehicleType, midWidth);
	cout << "\n";
}



