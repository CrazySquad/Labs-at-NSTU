#pragma once

#include "Vehicle.h"
#include <string>
#include <iostream>
#include "math.h"
#include "locale.h"
#define STOP_TIME 2

struct Animal  //возможные животные( у каждого свои параметры)
{
	char Camel = 'c';
	char Horse = 'h';
	char Donkey = 'd';
};

class Wain :
	public Vehicle
{
private:
	int MakeStopes(int km);
	int stamina;
public:
	void PrintRequiredTime(int km) override;
	Wain(char code) ;
	~Wain();
};

int Wain::MakeStopes(int km)
{
	int x = (int)(km / averageSpeed)/stamina;
	std::cout << "Сделано остановок :" << x << "\n";
	return x;
}

void Wain::PrintRequiredTime(int km) 
{
	std::cout << "Затрачено времени: " << ceil(km / averageSpeed) + MakeStopes(km)*STOP_TIME << " ч\n";
}

Wain::Wain(char code)
{
	costOfRepair = 0;
	factorOfSafety = INT_MAX;
	switch (code)
	{
	case 'c':
	{
		costOfServices = 6;
		averageSpeed = 7;
		liftingCapacity = 350;
		stamina = 16;
		model = "Верблюд Пётр Сергеевич Кароедов";
		break;
	}
	case 'h':
	{
		costOfServices = 10;
		averageSpeed = 7;
		liftingCapacity = 700;
		stamina = 7;
		model = "Запряженная лошадь Лариса Ивановна";
		break;
	}
	case 'd':
	{
		costOfServices=3;
		averageSpeed=5;
		liftingCapacity=150;
		stamina = 10;
		model="Ишак Андрей Малахов";
		break;
	}
	default:
	{
		break;
	}
	}
}

Wain::~Wain()
{
}
