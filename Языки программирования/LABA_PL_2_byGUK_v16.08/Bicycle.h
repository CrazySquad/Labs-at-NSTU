#pragma once

#include "Vehicle.h"

#define DEFAULT_FACTOR_OF_SAFITY_BIKE 200   // км без ремонта
#define DEFAULT_LIFTING_CAPACITY_BIKE 27    // кг перевозит
#define DEFAULT_AVERAGE_SPEED_BIKE 25       // км/ч
#define DEFAULT_COST_OF_REPAIR_BIKE 110     // монет за разовую починку
#define DEFAULT_COST_OF_SERVICE_BIKE 2      // монет за км
#define RELAX_TIME 24                       // часа

class Bicycle :
	public Vehicle
{
public:
	void PrintAllAboutTransit(int km, int kg) override;
	void ShowModel() override;
	void SetFriends(unsigned int num);
	void PrintCostOfTransit(int km, int kg) override;
	void PrintRequiredTime(int km,int kg) ;
	Bicycle(std::string name);
	~Bicycle();
private:
	int RelaxInTown(int km,int kg);
	unsigned int amountOfFriends;   // у велосипедиста есть друзья-единомышленники, деньги делят поровну, зато зависают в разных городах
};

void Bicycle::PrintAllAboutTransit(int km, int kg)
{
	std::cout << ST_LINE;
	ShowModel();
	ShowSpeed();
	ShowLiftingCapacity();
	PrintCostOfTransit(km, kg);
	PrintRequiredTime(GetPathLength(km, kg),kg);
	std::cout << ST_LINE;
}

void Bicycle::PrintCostOfTransit(int km, int kg)
{
	int pathLength = GetPathLength(km, kg);
	std::cout << "Груз " << kg << " кг на " << km << " км \n";
	int finalCost = costOfServices * pathLength + amountOfFriends*RepairSelf(pathLength);
	std::cout << "Стоимость перевозки составила " << finalCost << " монет\n";
}

void Bicycle::PrintRequiredTime(int km,int kg)
{
	std::cout << "Затрачено времени: " << ceil(km / averageSpeed) + RelaxInTown(km,kg)<< " ч\n";
}

int Bicycle::RelaxInTown(int km,int kg)
{
	int times = round(GetPathLength(km, kg) / km)-1;
	std::cout<<"Отдыхов в городах : "<<times<<"\n";
	return (int)(sqrt(1 + amountOfFriends)*RELAX_TIME*times);
}

void Bicycle::SetFriends(unsigned int num)
{
	amountOfFriends = num;
	liftingCapacity *= 1 + amountOfFriends;
}

void Bicycle::ShowModel()
{
	std::cout << "Это велосипедист " << model<<" и его "<<amountOfFriends<<" друзей\n";
}

Bicycle::Bicycle(std::string name)
{
	model = name;
	factorOfSafety = DEFAULT_FACTOR_OF_SAFITY_BIKE;
	liftingCapacity = DEFAULT_LIFTING_CAPACITY_BIKE;
	averageSpeed = DEFAULT_AVERAGE_SPEED_BIKE;
	costOfRepair = DEFAULT_COST_OF_REPAIR_BIKE;
	costOfServices = DEFAULT_COST_OF_SERVICE_BIKE;
	amountOfFriends=0;
}

Bicycle::~Bicycle()
{
}
