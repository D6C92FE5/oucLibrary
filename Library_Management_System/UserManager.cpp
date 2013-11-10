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
	}
}