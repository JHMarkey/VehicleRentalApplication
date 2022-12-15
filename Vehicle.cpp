#include "Vehicle.h"

const string Vehicle::getRegNum() const{
	char* c;
	string s(regNum);
	c = &s[0];
	for (int i = 0; i < sizeof(c); i++) c[i] = toupper(c[i]);

	return c;
}

const string Vehicle::getMake() const{
	return make;
}

const string Vehicle::getModel() const {
	return model;
}

int Vehicle::getAge(){
	return age;
}

void Vehicle::addVehicle() {
	ofstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open())
	{
		vehicleFile << regNum << "," << getCostPerDay() << "," << vehicleType << "\n";

		cout << "\nVehicle Successfully Added - " << regNum << "\n\n";
		vehicleFile.close();
	}
	else cout << "\nUnable to Add Vehicle\n"
		<< "<No File Error>\n\n";
}	

const double Vehicle::getCostPerDay() const {
	return 1200;
}

const string Vehicle::getVehType() const
{
	return vehicleType;
}

bool Vehicle::isNew() {
	string line;

	ifstream vehicleFile("VehicleList.txt");
	if (vehicleFile.is_open())
	{
		while (getline(vehicleFile, line)) {		//iterates through all of the reg numbers in the "VehicleList.txt" file.
			string cRegNum;

			replace(line.begin(), line.end(), ',', '\n');
			stringstream ss(line);

			ss >> cRegNum;			
			
			if (cRegNum == regNum) { vehicleFile.close(); return false; }	 //if the current line's RegNum is the same as the RegNum Trying to be added return false.
		}
		vehicleFile.close();
		return true;
	}
	else return false;

}

void const Vehicle::printDetails(int count, double cost) const {
	char* c;
	string s(regNum);
	c = &s[0];
	for (int i = 0; i < sizeof(c); i++) c[i] = toupper(c[i]);

	stringstream ss;
	ss << fixed << setprecision(2) << cost / 100;
	string costStr = '$' + ss.str();
	printElement(count, 4);
	printElement(c, bigWidth);	
	printElement(costStr, midWidth);
	printElement(vehicleType, midWidth);
	cout << "\n";
}

const int Vehicle::GetNoRentals() const {
	int count = 0;
	string line;
	string fName = getRegNum() + ".txt";
	ifstream rFile(fName);

	while (getline(rFile, line)) {
		count++;
	}
	return count;
}


