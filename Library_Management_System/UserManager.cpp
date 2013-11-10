#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
#include "UserManager.h"
extern string Type;
extern Datastore::User * IUser;
//Î¬»¤
namespace UserManager
{
	bool Login(string Name, string Password)
	{
		auto user=Datastore::Select<Datastore::User>(UserManager::SearchUserName);
		//if (User[1] != NULL) return false;
		if (user->Name == Name && user->Password == Password){
			Type = user->Type;
			IUser->Index = user->Index;
			IUser->IsDeleted = user->IsDeleted;
			strcpy(IUser->Info, user->Info);
			strcpy(IUser->Name, user->Name);
			strcpy(IUser->Password, user->Password);
			strcpy(IUser->Type, user->Type);
			delete user;
			return true;
		}
		delete user;
		return false;
	}


	void Logout()
	{ 
		IUser=NULL;
		Type = "";
	}


	Datastore::User * InsertUser(string Name, string Password)
	{
		auto user = Datastore::Create<Datastore::User>();
		char name[LEN_USER_NAME];
		char password[LEN_USER_PASSWORD];
		char type[LEN_USER_TYPE];
		char info[LEN_USER_INFO];
		for (int i = 0; Name[i] != 0; i++){ name[i] = Name[i]; }
		for (int i = 0; Password[i] != 0; i++){ password[i] = Password[i]; }
		strcpy(user->Name, name);
		strcpy(user->Password, password);
		strcpy(user->Info, info);
		strcpy(user->Type, type);
		user->IsDeleted = false;
		Datastore::InsertOrUpdate(user);
		delete user;
	}
	Datastore::User * SelectUser(string Name)
	{
		auto user = Datastore::Select<Datastore::User>(SearchUserName);
		return user;
	}
	void DeleteUser(string Name)
	{
		auto user = Datastore::Select<Datastore::User>(SearchUserName);
		Datastore::Delete<Datastore::User>(user->Index);
		delete user;
	}
	void UpdataUserPassword(string Name, string Password)
	{
		if (Password == "")return;
		else {
			auto user = Datastore::Select<Datastore::User>(SearchUserName);
			user->Password == Password;
			Datastore::InsertOrUpdate(user);
			delete user;
		}
	}
	void UpdataUserInfo(string Name, string Info)
	{
		if (Info == "")return;
		else {
			auto user = Datastore::Select<Datastore::User>(SearchUserName);
			user->Info == Info;
			Datastore::InsertOrUpdate(user);
			delete user;
		}
	}
}