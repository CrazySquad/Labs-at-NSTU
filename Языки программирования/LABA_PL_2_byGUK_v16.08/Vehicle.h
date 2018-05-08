#pragma once

#include <string>
#include <iostream>
#include "math.h"
#include "locale.h"

#define ST_LINE "---------------------------------------------------------\n"

class Vehicle
{
public:
	virtual void PrintAllAboutTransit(int km, int kg);//финальный метод, сборка из всей нужной инфы
	virtual void PrintRequiredTime(int km);// рассчитает время доставки
	void ShowSpeed();
	void ShowLiftingCapacity();
	virtual void ShowModel();//перепопределен для машин и великов
	void SetSpeed(int speed);
	void SetLiftingCapacity(int value);
	void SetFactorOfSafety(int value);//запас прочности
	virtual void PrintCostOfTransit(int km, int kg);// рассчитает стоимость доставки
	Vehicle();
	virtual ~Vehicle();// виртуальный!!!
protected:
	int GetPathLength(int km, int kg); //с учетом грузоподъемности рассчитает полную длину пути (может гонять туда-обратно)
	int costOfServices;//цена перевозки на км
	int RepairSelf(int km);
	int costOfRepair;//цена ремонта
	int averageSpeed;
	int liftingCapacity;//грузоподъёмность в кг
	int factorOfSafety;//запас прочности в км
	std::string model;//название модели
};

void Vehicle::PrintAllAboutTransit(int km, int kg)
{
	std::cout << ST_LINE;
	ShowModel();
	ShowSpeed();
	ShowLiftingCapacity();
	PrintCostOfTransit(km, kg);
	PrintRequiredTime(GetPathLength(km, kg));
	std::cout << ST_LINE;
}

void Vehicle::PrintCostOfTransit(int km, int kg)
{
	int pathLength = GetPathLength(km, kg);
	std::cout << "Груз " << kg << " кг на " << km << " км \n";
	int finalCost = costOfServices * pathLength;
	std::cout << "Стоимость перевозки составила " << finalCost << " монет\n";
}

void Vehicle::PrintRequiredTime(int km)
{
	std::cout << "Затрачено времени: " << ceil(km / averageSpeed) << " ч\n";
}

int Vehicle::GetPathLength(int km, int kg)
{
	// 10 км 100 кг при гр-ти 50кг получаем 30 км?
	// 100 км 10 кг при гр-ти 50кг получаем 100 км
	return ceil((double)kg / liftingCapacity) * 2 * km - km;
}

void Vehicle::SetSpeed(int speed)
{
	averageSpeed = speed;
}

void Vehicle::SetFactorOfSafety(int value)
{
	factorOfSafety = value;
}

void Vehicle::SetLiftingCapacity(int value)
{
	liftingCapacity = value;
}

void Vehicle::ShowModel()
{
	std::cout << "Это " << model << "\n";
}

void Vehicle::ShowLiftingCapacity()
{
	std::cout << "Грузоподъемность " << liftingCapacity << " кг\n";
}

void Vehicle::ShowSpeed()
{
	std::cout << "Средняя скорость " << averageSpeed << " км/ч\n";
}

int Vehicle::RepairSelf(int km)
{
	int x = (int)km / factorOfSafety;
	std::cout << "Ремонтов в процессе :" << x << "\n";
	return x * costOfRepair;
}

Vehicle::Vehicle()
{
	averageSpeed = 0;
	liftingCapacity = 0;
	factorOfSafety = 0;
}

Vehicle::~Vehicle()
{
}
