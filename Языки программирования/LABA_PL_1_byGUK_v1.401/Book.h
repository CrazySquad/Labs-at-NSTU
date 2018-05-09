#pragma once
#include <iostream>

#define MAX_LEN 20  // ���� � ��������
class Book
{
private:
	unsigned short itsNum; // ���������� �����
	unsigned short yearOfPublishing; //��� �������
	char author[MAX_LEN];//����� ���������� "string" � ������������ std::string ������ char[ ] � �� ����� ����������� �� �����
	char title[MAX_LEN];//��������
	char publishingHouse[MAX_LEN];// ������������ ���
	unsigned short numOfPages; //���-�� �������
public:
	//����������� �� ���������
	Book();
	//����������� � �����������(�� �� ������)
	Book(int num,char InfoString[100]);
	//����
	void printInfo();
	void printByPublished(char nameQ[MAX_LEN]); //������� �� ������������ ������������
	void printByYear(int yearQ);//������� �� ������������ ����
	void printByAuthor(char nameQ[MAX_LEN]);//������� �� ������������ ������
	//�����������
	~Book();
};

