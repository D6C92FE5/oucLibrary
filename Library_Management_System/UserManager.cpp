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
		auto User=Datastore::Select<Datastore::User>(UserManager::SearchUserName);
		//if (User[1] != NULL) return false;
		if (User->Name == Name && User->Password == Password){
			Type = User->Type;
			IUser->Index = User->Index;
			IUser->IsDeleted = User->IsDeleted;
			strcpy(IUser->Info, User->Info);
			strcpy(IUser->Name, User->Name);
			strcpy(IUser->Password, User->Password);
			strcpy(IUser->Type, User->Type);
			delete User;
			return true;
		}
		delete User;
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
		;
	}
	void DeleteUser(string Name)
	{
		;
	}
	void UpdataUser(string Name)
	{
		;
	}

}