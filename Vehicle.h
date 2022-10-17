#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Vehicle
{
public:

	virtual string getRegNum();
	virtual string getModel();
	virtual string getMake();
	virtual int getAge();

	virtual void display();

	virtual double getCostPerDay();

	virtual void addVehicle();

	virtual bool isNew();
	
	//virtual void removeVehicle();

	//virtual void regSearch();
	//virtual void costSearch();
	
protected:

	int age;
	string regNum, make, model, vehicleType;
	
};

