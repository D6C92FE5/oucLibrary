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
	void UpdataOnesPassword(string Password);
	//用户修改INFO
	void UpdataOnesInfo(string Info);
	//管理员所有
	//创建新用户
	void InsertUser(string Name, string Password);
	//选择用户
	Datastore::User * SelectUser(string Name);
	//删除用户
	void DeleteUser(string Name);
	//更新用户密码
	void UpdataUserPassword(string Name, string Password = "");
	//更新用户INFO
	void UpdataUserInfo(string Name, string Info = "");
}