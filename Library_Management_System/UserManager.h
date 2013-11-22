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
	//登入
	bool Login(string Name, string Password);
	//登出
	void Logout();
	//用户升级
	bool UpLevel(string Name, string Password);
	//用户修改密码
	bool UpdataOnesPassword(string Password);
	//用户修改INFO
	bool UpdataOnesInfo(string Info);
	//管理员所有
	//创建新用户
	bool InsertUser(string Name, string Password);
	//选择用户
	Datastore::User * SelectUser(string Name);
	//删除用户
	bool DeleteUser(string Name);
	//更新用户密码
	bool UpdataUserPassword(string Name, string Password);
	//更新用户INFO
	bool UpdataUserInfo(string Name, string Info = "");
}