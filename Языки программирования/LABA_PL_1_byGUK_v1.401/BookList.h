#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "Book.h"
#define MAX_LEN 20
#define amount_of_books 20  //поменять
class BookList
{
public:
	BookList();//не используется
	BookList(FILE * SourceFile);//конструктор от текстовго файла
	void PrintAllInfo();
	//void CleanList();
	void ListByAuthor(char nameQ[MAX_LEN]);//вывод книг, отстортированных по параметрам
	void ListByYear(int yearQ);
	void ListByPublished(char nameQ[MAX_LEN]);
	~BookList();
private:
	Book * arrPtr[amount_of_books]; 
};
