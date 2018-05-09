#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "Book.h"
#define MAX_LEN 20
#define amount_of_books 20  //��������
class BookList
{
public:
	BookList();//�� ������������
	BookList(FILE * SourceFile);//����������� �� ��������� �����
	void PrintAllInfo();
	//void CleanList();
	void ListByAuthor(char nameQ[MAX_LEN]);//����� ����, ���������������� �� ����������
	void ListByYear(int yearQ);
	void ListByPublished(char nameQ[MAX_LEN]);
	~BookList();
private:
	Book * arrPtr[amount_of_books]; 
};

