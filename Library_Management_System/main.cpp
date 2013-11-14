
#include "UserManager.h"
#include <stdlib.h>
#include <fstream>

void printLine(char * content){
	cout << content << endl;
}
void printLine(){
	cout << endl;
}

void printVisitorMenu(){
	printLine("---------菜单---------");
	printLine("1.检索书目");
	printLine("2.登陆");
	printLine("0.退出系统");
	printLine("----------------------");
	printLine();
}

void printUserMenu(){
	printLine("---------菜单---------");
	printLine("1.检索书目");
	printLine("2.修改个人信息");
	printLine("3.权限提升（管理员）");
	printLine("0.注销");
	printLine("----------------------");
	printLine();
}

void printAdminMenu(){
	printLine("-------图书管理-------");
	printLine("1.检索书目");
	printLine("2.删除书目");
	printLine("3.修改书目信息");
	printLine("4.新书入馆");
	printLine("5.图书借阅");
	printLine("6.图书归还");
	printLine("7.图书续借");
	printLine("-------用户管理-------");
	printLine("8.检索用户");
	printLine("9.移除用户");
	printLine("10.重置用户密码");
	printLine("11.注册新用户");
	printLine("0.注销");
	printLine("----------------------");
	printLine();
}

void printInfoChangeMenu(){
	printLine("-----修改个人信息-----");
	printLine("1.修改密码");
	printLine("2.修改简介");
	printLine("0.返回");
	printLine("----------------------");
}

void printWrongTypeWarning(){
	printLine("数据不合法，请重新输入！");
}

//验证字符串每一位都是数字且没有先导0
bool allNumric(const char * str){
	if(str[0] == '0'){
		return false;
	}
	int i = 1;
	while(str[i]!='\0'){
		if(str[i] < '0' || str[i] >'9'){
			return false;
		}
		i++;
	}
	return true;
}

//重复请求一个整数输入，直到输入正确，参数指定上限，默认没有
int getInputPosNum(int maxNum = 0){
	int num = -1;
	string input;
	while(num < 0 || cin <= 0){
		getline(cin, input);
		if(!allNumric(input.c_str())){
			printWrongTypeWarning();
		}else{
			num	= atoi(input.c_str());
			if(num < 0 || (maxNum && num > maxNum)){
				printWrongTypeWarning();
			}
		}
	};
	return num;
}



int main(){
    Datastore::Init();
	printAdminMenu();
	printUserMenu();
	printVisitorMenu();
	int a;
	a = getInputPosNum(11);
	a = getInputPosNum();
	return 0;
	printf("sf ");
}

//插入示例图书的代码
int __main ()
{
	Datastore::Init();
	ifstream infile("书目信息.txt");
	string temp;
	while (getline(infile, temp))
	{
		auto TmpBook = Datastore::Create<Datastore::Book>();
		strcpy(TmpBook->Name, temp.c_str());
		getline(infile, temp);
		strcpy(TmpBook->Author, temp.c_str());
		getline(infile, temp);
		strcpy(TmpBook->Publisher, temp.c_str());
		getline(infile, temp);
		strcpy(TmpBook->Isbn, temp.c_str());
		TmpBook->Total = rand() / 500;
		TmpBook->Remain = TmpBook->Total;
		Datastore::InsertOrUpdate(TmpBook);
		delete TmpBook;
	}
	return 0;
}