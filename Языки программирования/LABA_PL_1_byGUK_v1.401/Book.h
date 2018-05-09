#pragma once
#include <iostream>

#define MAX_LEN 20  // поля в символах
class Book
{
private:
	unsigned short itsNum; // порядковый номер
	unsigned short yearOfPublishing; //год издания
	char author[MAX_LEN];//можно подключить "string" и использовать std::string вместо char[ ] и не будет ограничений по длине
	char title[MAX_LEN];//название
	char publishingHouse[MAX_LEN];// издательский дом
	unsigned short numOfPages; //кол-во страниц
public:
	//конструктор по умолчанию
	Book();
	//конструктор с параметрами(ну не совсем)
	Book(int num,char InfoString[100]);
	//инфа
	void printInfo();
	void printByPublished(char nameQ[MAX_LEN]); //вывести по соответствию издательству
	void printByYear(int yearQ);//вывести по соответствию года
	void printByAuthor(char nameQ[MAX_LEN]);//вывести по соответствию автора
	//декструктор
	~Book();
};

