#include "Rental.h"

Rental::Rental(Vehicle* vehicle) : vehicle(vehicle), noDays(CalcNoDays()), start(CreateStartDate()), end(CreateEndDate()), customer(CreateCustomer())  {}
Rental::~Rental() {
	delete(start);
	delete(end);
}

Customer Rental::CreateCustomer() {
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

RentalDate* Rental::CreateStartDate() {
	string date;
;
	cout << "Enter Start Date: (DD/MM/YY)\n";
	getline(cin, date);

	
}

RentalDate* Rental::CreateEndDate() {
	string date;

	cout << "Enter End Date: (DD/MM/YY)\n";
	getline(cin, date);

	
}

double Rental::CalcTotalCost() {
	return noDays * vehicle->getCostPerDay();
}

int Rental::CalcNoDays() {
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
	printElement(1/1, 1);
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