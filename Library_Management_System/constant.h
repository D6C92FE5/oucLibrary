#pragma once
namespace Constant
{
	//用户类型
	const bool ADMIN_USER = true;
	const bool NORMAL_USER = false;

	//用户权限
	struct USER_ACCESS{
		bool SEARCH_BOOK;		///检索图书
		bool CHANGE_PASSWORD;	///修改密码
		bool ADD_USER;			///添加用户
		bool DELETE_USER;		///删除用户
		bool RESET_PASSWORD;	///重置用户密码
		bool BOLLOW_BOOK;		///借阅图书
		bool RETURN_BOOK;		///归还图书
		bool RENEW_BOOK;		///续借图书
		bool BOLLOW_HISTORY;	///查看借阅历史
	}ADMIN_ACCESS, NORMAL_ACCESS;

	//借阅期限
	const int MAX_BOLLOW_TIME = 30;

	//借阅上限
	const int MAX_BOLLOW_NUM = 5;

	void Init();
}