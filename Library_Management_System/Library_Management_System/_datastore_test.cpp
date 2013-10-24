
#include <iostream>
using namespace std;

#include "datastore.h"
using namespace Datastore;

bool test(Book* book) {
	cout << book->Name << endl;
	return true;
}

int main() {
	//Book* book = Select<Book>(1);
	//Traverse<Book>(test);
	//int a = Test(new User());
	//auto book = Create<Book>();
	//cout << _GenerateFilePathByType<Book>() << endl;
	//_OpenFile<Book>();
	Init();
	return 0;
}

