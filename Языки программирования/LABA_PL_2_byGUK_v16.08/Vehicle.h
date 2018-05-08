#pragma once

#include <string>
#include <iostream>
#include "math.h"
#include "locale.h"

#define ST_LINE "---------------------------------------------------------\n"

class Vehicle
{
public:
	virtual void PrintAllAboutTransit(int km, int kg);//��������� �����, ������ �� ���� ������ ����
	virtual void PrintRequiredTime(int km);// ���������� ����� ��������
	void ShowSpeed();
	void ShowLiftingCapacity();
	virtual void ShowModel();//�������������� ��� ����� � �������
	void SetSpeed(int speed);
	void SetLiftingCapacity(int value);
	void SetFactorOfSafety(int value);//����� ���������
	virtual void PrintCostOfTransit(int km, int kg);// ���������� ��������� ��������
	Vehicle();
	virtual ~Vehicle();// �����������!!!
protected:
	int GetPathLength(int km, int kg); //� ������ ���������������� ���������� ������ ����� ���� (����� ������ ����-�������)
	int costOfServices;//���� ��������� �� ��
	int RepairSelf(int km);
	int costOfRepair;//���� �������
	int averageSpeed;
	int liftingCapacity;//���������������� � ��
	int factorOfSafety;//����� ��������� � ��
	std::string model;//�������� ������
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
	std::cout << "���� " << kg << " �� �� " << km << " �� \n";
	int finalCost = costOfServices * pathLength;
	std::cout << "��������� ��������� ��������� " << finalCost << " �����\n";
}

void Vehicle::PrintRequiredTime(int km)
{
	std::cout << "��������� �������: " << ceil(km / averageSpeed) << " �\n";
}

int Vehicle::GetPathLength(int km, int kg)
{
	// 10 �� 100 �� ��� ��-�� 50�� �������� 30 ��?
	// 100 �� 10 �� ��� ��-�� 50�� �������� 100 ��
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
	std::cout << "��� " << model << "\n";
}

void Vehicle::ShowLiftingCapacity()
{
	std::cout << "���������������� " << liftingCapacity << " ��\n";
}

void Vehicle::ShowSpeed()
{
	std::cout << "������� �������� " << averageSpeed << " ��/�\n";
}

int Vehicle::RepairSelf(int km)
{
	int x = (int)km / factorOfSafety;
	std::cout << "�������� � �������� :" << x << "\n";
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
