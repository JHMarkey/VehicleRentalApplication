#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <list>
#include <iomanip>
#include <crtdbg.h>


using namespace std;

class Vehicle
{
public:

	virtual const string getRegNum() const;
	virtual string getModel();
	virtual string getMake();
	virtual int getAge();

	virtual void display();

	virtual const double getCostPerDay() const;

	virtual void addVehicle();

	virtual bool isNew();

	virtual const void printDetails(int count, int cost) const;
	
	//virtual void removeVehicle();

	//virtual void costSearch();
	
protected:

	template<typename T> const void printElement(T t, const int& width) const
	{
		cout << left << setw(width) << setfill(separator) << t;			//using templates to repeatedly format table printing
	}

	const char separator = ' ';
	const int bigWidth = 23;
	const int midWidth = 16;

	int age;
	string regNum, make, model, vehicleType;
	
};

