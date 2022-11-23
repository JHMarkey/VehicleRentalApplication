#include "Rental.h"

Rental::Rental(const Vehicle* vehicle) : vehicle(vehicle), customer(CreateCustomer()), start(CreateStartDate()), end(CreateEndDate()), noDays(CalcNoDays()) {}
Rental::~Rental() {
	delete(start);
	delete(end);
}

const Customer Rental::CreateCustomer() const{
	Customer c;
	cout << "Enter Customer Details\n"
		<< "----------------------\n\n";
	cout << "Enter Customer Name:\n";
	getline(cin, c.name);
	cout << "Enter Customer Address:\n";
	getline(cin, c.address);
	cout << "Enter Customer Number:\n";
	getline(cin, c.teleN);

	return c;
}

const RentalDate* Rental::CreateStartDate() const {
	string date = "";
	do {		
		try {
			int d, m, y;
			cout << "Enter Start Date: (DD/MM/YYYY)\n";
			getline(cin, date);
			if (date.length() != 10) throw - 1;

			replace(date.begin(), date.end(), '/', '\n');
			stringstream ss(date);
			ss >> d;
			ss >> m;
			ss >> y;
			if (d > 31 || d < 1) throw - 1;
			if (m > 12 || m < 1) throw - 1;
			if (y > 2023 || y < 0) throw - 1;

			return new RentalDate(d, m, y);
		}
		catch (int) {
			cerr << "\nInvalid Date\n";
			date = "";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (date == "");
	return nullptr;
}

const RentalDate* Rental::CreateEndDate() const {
	string date = "";
	do {
		try {
			int d, m, y;
			cout << "Enter End Date: (DD/MM/YYYY)\n";
			getline(cin, date);
			if (date.length() != 10) throw - 1;

			replace(date.begin(), date.end(), '/', '\n');
			stringstream ss(date);
			ss >> d; 
			ss >> m;
			ss >> y;
			if (d > 31 || d < 1) throw - 1;
			if (m > 12 || m < 1) throw - 1;
			if (y > 2050 || y < 0) throw - 1;
			return new RentalDate(d, m, y);
		}
		catch (int) {
			cerr << "\nInvalid Date\n";
			date = "";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (date == "");
	return nullptr;
}

double Rental::CalcTotalCost() {
	return noDays * vehicle->getCostPerDay();
}

const int Rental::CalcNoDays() const {
	return 5;
}

void Rental::CreateRentalFile() {
	ofstream rFile(vehicle->getRegNum());
	rFile.close();
}

void Rental::AddRentalDetails() {

}

void Rental::DisplayRentalDetails() {
	string title = vehicle->getRegNum() + ": " + vehicle->getMake() + " " + vehicle->getModel() + " Rental History";
	cout <<  "\n\n" << title << "\n"
		<< CreateRentalLine(title) << "\n\n";

	printElement("Rental:", 30);
	printElement("1/1", 1);
	cout << "\n";
	printElement("Date From:", 30);
	printElement(start->GetDate(), 1);
	cout << "\n";
	printElement("Date To:", 30);
	printElement(end->GetDate(), 1);
	cout << "\n";
	printElement("Rental Days:", 30);
	printElement(noDays, 1);
	cout << "\n";
	printElement("Total Cost:", 30);
	printElement(CalcTotalCost(), 1);
	cout << "\n";
	printElement("Customer Name:", 30);
	printElement(customer.name, 1);
	cout << "\n";
	printElement("Customer Address:", 30);
	printElement(customer.address, 1);
	cout << "\n";
	printElement("Customer Number:", 30);
	printElement(customer.teleN, 1);
	cout << "\n";

}

string Rental::CreateRentalLine(string t) {
	string line = "";
	for (int i = 0; i < t.length(); i++) {
		line += "-";
	}
	return line;
}