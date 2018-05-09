#include "stdafx.h"
#include <stdlib.h>
#include "locale.h"
#include < string.h > 
#include "Book.h"
#define MAX_LEN 20

// Конструктор по умолчанию
Book::Book()
{
}

// Конструктор с параметрами(ну не совсем)
Book::Book(int num, char InfoString[100])//здесь происходит парс строки из Source по сиволам '/' и заполнение соответствующих полей
{
	itsNum = num;
	int i = 0;
	char curr = InfoString[i];
	while (curr!='/')
	{
		author[i] = curr;
		curr = InfoString[i+1];
		i++;
	}
	author[i] = '\0';
	curr = InfoString[i + 1];
	i++;
	int j = 0;
	for (j = 0; (curr != '/');)
	{
		title[j] = curr;
		curr = InfoString[i + 1];
		i++;j++;
	}
	title[j] = '\0';
	curr = InfoString[i + 1];
	i++;
	for (j = 0; (curr != '/');)
	{
		publishingHouse[j] = curr;
		curr = InfoString[i + 1];
		i++;j++;
	}
	publishingHouse[j] = '\0';
	curr = InfoString[i + 1];
	i++;
	char yearToCast[4];
	for (j = 0; (curr != '/')&&(j<4);)
	{
		yearToCast[j] = curr;
		curr = InfoString[i + 1];
		i++;j++;
	}
	yearOfPublishing = atoi(yearToCast);
	curr = InfoString[i + 1];
	i++;
	char pagesToCast[5];
	for (j = 0; (curr != '/') && (j<4);)
	{
		pagesToCast[j] = curr;
		curr = InfoString[i + 1];
		i++;j++;
	}
	pagesToCast[j] = '\0';
	numOfPages = atoi(pagesToCast);
}

void Book::printInfo()
{
	printf("%3d %20s %20s %20s %4d %5d\n",itsNum, author, title, publishingHouse, yearOfPublishing, numOfPages);
}

void Book::printByPublished(char nameQ[MAX_LEN])
{
	setlocale(LC_ALL, "RUS");
	int len = strlen(publishingHouse);
	if (strlen(nameQ) == len)//условие на допуск к сравнению
	{
		bool mark = true;
		for (int i = 0;i < len;i++) mark &= nameQ[i] == publishingHouse[i];//посимвольное сравнение
		if (mark) printInfo();
	}
}
void Book::printByYear(int yearQ)
{
	if (yearQ <= yearOfPublishing) printInfo();
}
void Book::printByAuthor(char nameQ[MAX_LEN])
{
	setlocale(LC_ALL, "RUS");
	int len = strlen(author);
	if (strlen(nameQ) == len)
	{
		bool mark = true;
		for (int i = 0;i < len;i++) mark &= nameQ[i] == author[i];//посимвольное сравнение
		if (mark) printInfo();
	}
}


//Деструктор
Book::~Book()
{
}
