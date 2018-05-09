#include "stdafx.h"
#include "BookList.h"
#include <stdlib.h>
#include "Book.h"
#define amount_of_books 20  //поменять если надо

BookList::BookList()
{
}

BookList::BookList(FILE* SourceFile)
{
	for (int k = 0;k < amount_of_books;k++)
	{
		char InfoString[100];
		fscanf(SourceFile, "%s", &InfoString);
		arrPtr[k] = new Book(k, InfoString);
	}

}
void BookList::PrintAllInfo()
{
	for (int k = 0;k < amount_of_books;k++)
	{
		arrPtr[k]->printInfo();
	}
}
void BookList::ListByAuthor(char nameQ[MAX_LEN])
{
	setlocale(LC_ALL, "RUS");
	for (int i = 0; i  < amount_of_books;i ++)
	{
		arrPtr[i]->printByAuthor(nameQ);
	}
}
void BookList::ListByYear(int yearQ)
{
	for (int i = 0; i < amount_of_books;i++)
	{
		arrPtr[i]->printByYear(yearQ);
	}
}
void BookList::ListByPublished(char nameQ[MAX_LEN])
{
	setlocale(LC_ALL, "RUS");
	for (int i = 0; i < amount_of_books;i++)
	{
		arrPtr[i]->printByPublished(nameQ);
	}
}
BookList::~BookList()
{
}
