// BOOKER_H
#ifndef _BOOKER_H
#define _BOOKER_H

#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "datastore.h"

using namespace std;

namespace Booker{
///内部使用
	string Temp, AnotherTemp;
	int BookIndex, UserIndex;
	//Isbn搜索图书
	bool SearchBookCondition(Datastore::Book* book);
	
	//模糊搜索图书
	bool AnotherSearchBookCondition(Datastore::Book* book);

	//编辑距离,辅助搜索
	int DistanceBetweenThem(string a, string b);

	//Accout搜索记录
	bool SearchRecordCondition(Datastore::Record* record);

	//Account&Isbn搜索记录
	bool AnotherSearchRecordCondition(Datastore::Record* record);

	//Account&Isbn查找记录
	Datastore::Record** IsbnFindRecord(string Account, string Isbn);
	
///外部InterFace
	//增加图书
	bool AddBook(string Isbn, string Name, string Author, string Publisher, int Num);
	
	//删除图书
	bool DeleteBook(string Isbn, int Num);
	
	//更改图书信息
	bool ChangeBookIsbn(string Isbn, string NewIsbn);

	bool ChangeBookName(string Isbn, string Name);

	bool ChangeBookAuthor(string Isbn, string Author);

	bool ChangeBookPublisher(string Isbn, string Publisher);
	
	//Isbn查找图书
	Datastore::Book** IsbnFindBook(string Isbn);
	
	//Anything查找图书
	Datastore::Book** AnythingIsbnFindBook(string Anything);

	//借书
	bool BrowseBook(string Account, string Isbn);
	
	//1正常还书,-1超期还书,0还书失败
	int ReturnBook(string Account, string Isbn);

	//Account查找记录
	Datastore::Record** AccountFindRecord(string Account);
}

#endif  //BOOK_H
