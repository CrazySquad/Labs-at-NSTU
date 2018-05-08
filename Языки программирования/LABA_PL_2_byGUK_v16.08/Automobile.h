#pragma once

#include "Vehicle.h"
#include <string>
#include <iostream>
#include "math.h"
#include "locale.h"

#define DEFAULT_FACTOR_OF_SAFITY_CAR 500    // км без ремонта
#define DEFAULT_LIFTING_CAPACITY_CAR 450    // кг перевозит без прицепа
#define DEFAULT_AVERAGE_SPEED_CAR 80        // км/ч
#define DEFAULT_COST_OF_REPAIR_CAR 300      // монет за разовую починку
#define DEFAULT_COST_OF_SERVICE_CAR 14      // монет за км


class Automobile :
	public Vehicle
{
public:
	void ShowModel() override;
	void LockTrailer();
	void UnlockTrailer();
	void PrintCostOfTransit(int km, int kg) override;
	Automobile(std::string modelS);
	~Automobile();
private:
	bool trailer;
};

void Automobile::LockTrailer()
{
	if (!trailer)
	{
		trailer = true;
		liftingCapacity += 800;
		averageSpeed -= 15;
	}
}

void Automobile::UnlockTrailer()
{
	if (trailer)
	{
		trailer = false;
		liftingCapacity -= 800;
		averageSpeed += 15;
	}
}

void Automobile::PrintCostOfTransit(int km, int kg) 
{
	int pathLength = GetPathLength(km, kg);
	std::cout << "Груз " << kg << " кг на " << km << " км \n";
	int finalCost = costOfServices * pathLength + RepairSelf(pathLength);
	std::cout << "Стоимость перевозки составила " << finalCost << " монет\n";
}

Automobile::Automobile(std::string modelS)
{
	model = modelS;
	factorOfSafety = DEFAULT_FACTOR_OF_SAFITY_CAR;
	liftingCapacity = DEFAULT_LIFTING_CAPACITY_CAR;
	averageSpeed = DEFAULT_AVERAGE_SPEED_CAR;
	costOfRepair = DEFAULT_COST_OF_REPAIR_CAR;
	costOfServices = DEFAULT_COST_OF_SERVICE_CAR;
	trailer = false;
}

void Automobile::ShowModel() 
{
	std::cout << "Это " << model;
	if (trailer) std::cout << " с прицепом";
	std::cout << "\n";
}

Automobile::~Automobile()
{
}
