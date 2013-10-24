#ifndef _DATASTORE_H_
#define _DATASTORE_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Datastore {

	struct Book
	{
		int Index;
		char Isbn[13];
		char Name[100];
		char Author[100];
		char Pulisher[100];
		int Total;
		int Remain;
		bool IsDeleted;
	};

	struct User
	{
		int Index;
		char Name[100];
		char Password[40];
		char Type[10];
	};

	struct Record
	{
		int Index;
		int BookIndex;
		int UserIndex;
		int Datetime;
		bool IsRenew;
	};

	template <typename T>
	T* Create() {
		auto item = new T();
		memset(item, 0, sizeof T);
		item->Index = -1;
		return item;
	}

	template <typename T>
	T* Select(const int index) {
		return new T();
	}

	template <typename T>
	T** Select(bool(*where)(T*), const int beginIndex = 0, const int maxCount = 0) {
		auto array = new T[10];
		return array;
	}

	template <typename T>
	void InsertOrUpdate(T* item) {
		;
	}

	template <typename T>
	void Delete(const int index) {
		;
	}

	template <typename T>
	void Traverse(bool(*func)(T*), const int beginIndex = 0, const int endIndex = 0) {
		if (endIndex <= 0) {
			;
		}
	}

}

#endif // _DATASTORE_H_