#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
#include "UserManager.h"
#include "datastore.h"
string Type;
Datastore::User * IUser;
//维护
namespace UserManager
{
	bool Login(string Name, string Password)
	{
		IUser = new Datastore::User;
		char name[LEN_USER_NAME], password[LEN_USER_PASSWORD];
		for (int i = 0; Name[i] != 0; i++){ name[i] = Name[i]; }
		for (int i = 0; Password[i] != 0; i++){ password[i] = Password[i]; }
		strcpy(IUser->Name, name);
		auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
			return user->Name==Name;
		});
		if (user == NULL) return false;
		if (strcmp(user->Password,password)){
			Type = user->Type;
			IUser->Index = user->Index;
			IUser->IsDeleted = user->IsDeleted;
			strcpy(IUser->Info, user->Info);
			strcpy(IUser->Password, user->Password);
			strcpy(IUser->Type, user->Type);
			delete user;
			return true;
		}
		else strcpy(IUser->Name, "");
		delete user;
		return false;
	}


	void Logout()
	{ 
		delete IUser;
		IUser=NULL;
		Type.clear();
	}


	bool UpLevel(string Name, string Password)
	{
		UserManager::Logout();
		return UserManager::Login(Name, Password);
	}
	//一般用户
	//用户成功登入下可用
	void UpdataOnesPassword(string Password)
	{
		if (Type.size() == 0)return;
		int length = Password.size();
		for (int i = 0; i < length ; i++)
		{
			IUser->Password[i]=Password[i];
		}
		Datastore::InsertOrUpdate(IUser);
	}
	void UpdataOnesInfo(string Info)
	{
		if (Type.size() == 0)return;
		int length = Info.size();
		for (int i = 0; i < length; i++)
		{
			IUser->Password[i] = Info[i];
		}
		Datastore::InsertOrUpdate(IUser);
	}


	
	//管理员
	//所有操作在管理员未登入的情况下无法进行
	//搜索返回NULL
	void InsertUser(string Name, string Password)
	{
		if (Type != "管理员")return;
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
		if (Type != "管理员")return NULL;
		auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
			return user->Name == Name;
		});
		return user;
	}
	void DeleteUser(string Name)
	{
		if (Type != "管理员")return;
		auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
			return user->Name == Name;
		});
		Datastore::Delete<Datastore::User>(user->Index);
		delete user;
	}
	void UpdataUserPassword(string Name, string Password)
	{
		if (Type != "管理员")return;
		if (Password == "")return;
		else {
			auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
				return user->Name == Name;
			});
			user->Password == Password;
			Datastore::InsertOrUpdate(user);
			delete user;
		}
	}
	void UpdataUserInfo(string Name, string Info)
	{
		if (Type != "管理员")return;
		if (Info == "")return;
		else {
			auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
				return user->Name == Name;
			});
			user->Info == Info;
			Datastore::InsertOrUpdate(user);
			delete user;
		}
	}
}