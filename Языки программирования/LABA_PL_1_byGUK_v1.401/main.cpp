// Lab_PL_2_byGUK.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdlib.h"
#include "locale.h"
#include "Book.h"
#include "BookList.h"
#define MAX_LEN 20
#define filename1 "C:/.../Source.txt" //поменять на актуальный!!!
#define amount_of_books 20  //тоже менять по необходимости
/**
* Опросник
*/
void TaskMethod(BookList* bL)
{
	printf("Ключи e - закончить работу,a - список по автору,p - список по издательству\n,i - получить весь список,y - сортировать по заданному году\n");
	char quest = NULL;
	scanf("%c", &quest);
	switch (quest)
	{
	case 'e':
	{
		getchar();
		break;
	}
	case 'a':
	{
		printf("Автор какой?   ");
		char popo[MAX_LEN];
		scanf("%s", &popo);
		bL->ListByAuthor(popo);
		getchar();
		TaskMethod(bL);
		break;
	}
	case 'p':
	{
		printf("Издательство какое?   ");
		char popo[MAX_LEN];
		scanf("%s", &popo);
		bL->ListByPublished(popo);
		getchar();
		TaskMethod(bL);
		break;
	}
	case 'i':
	{	
		bL->PrintAllInfo();
		getchar();
		TaskMethod(bL);
		break;
	}
	case 'y':
	{
		int year = 0;
		printf("Год какой?   ");
		scanf("%d", &year);
		bL->ListByYear(year);
		getchar();
		TaskMethod(bL);
		break;
	}
	default:
	{
		printf("Я верю в твои прямые ручки...\n"); 
		getchar();
		TaskMethod(bL);
		break;
	}
	}
}

// Точка входа
int main()
{
	setlocale(LC_ALL, "RUS");
	system("mode con cols=90 lines=60");
	FILE* SourceTEXT;
	SourceTEXT = fopen(filename1, "r");
	BookList* testBookList = new BookList(SourceTEXT);
	TaskMethod(testBookList);
	testBookList->~BookList();
	fclose(SourceTEXT);
	system("pause");
	return 0;
}
