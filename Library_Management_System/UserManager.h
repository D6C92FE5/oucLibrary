#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;
#include "datastore.h"
extern string Type;
extern Datastore::User * IUser;
namespace UserManager{
	//
	bool Login(string Name, string Password);
	void Logout();
	bool UpLevel(string Name, string Password);
	void UpdataOnesPassword(string Password);
	void UpdataOnesInfo(string Info);
	//管理员所有
	void InsertUser(string Name, string Password);
	Datastore::User * SelectUser(string Name);
	void DeleteUser(string Name);
	void UpdataUserPassword(string Name, string Password = "");
	void UpdataUserInfo(string Name, string Info = "");
}