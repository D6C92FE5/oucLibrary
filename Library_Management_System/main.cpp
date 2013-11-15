#include "UserManager.h"
#include <stdlib.h>
#include <fstream>
#include <conio.h>

void printLine(char * content){
	cout << content << endl;
}

void printLine(){
	cout << endl;
}

//打印游客菜单
void printVisitorMenu(){
	printLine("---------菜单---------");
	printLine("1.检索书目");
	printLine("2.登陆");
	printLine("0.退出系统");
	printLine("----------------------");
	printLine();
}

//打印普通用户菜单
void printUserMenu(){
	printLine("---------菜单---------");
	printLine("1.检索书目");
	printLine("2.修改个人信息");
	printLine("3.权限提升（管理员）");
	printLine("0.注销");
	printLine("----------------------");
	printLine();
}

//打印管理员菜单
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

//打印修改个人信息菜单
void printInfoChangeMenu(){
	printLine("-----修改个人信息-----");
	printLine("1.修改密码");
	printLine("2.修改简介");
	printLine("0.返回");
	printLine("----------------------");
}

//打印错误输入数据警告
void printWrongTypeWarning(){
	printLine("数据不合法，请重新输入！");
}

//获取一行字符串输入
string getInputString(){
	string input;
	getline(cin, input);
	return input;
}

//验证字符串每一位都是数字且没有先导0
bool allNumric(const char * str){
	if(str[0] == '0'){
		return false;
	}
	int i = 0;
	while(str[i]!='\0'){
		if(str[i] < '0' || str[i] >'9'){
			return false;
		}
		i++;
	}
	return true;
}

//ISBN合法性检测(仅检测长度以及是否由纯数字和末尾可能的X组成)
bool isbnCheck(string str){
	if((str.size() != 13 && str.size() != 10)){
		return false;
	}
	if(str.size() == 13){
		if(allNumric(str.c_str())){
			return true;
		}
	}else if(allNumric(str.c_str()) || (allNumric(str.substr(0,str.size() - 2).c_str()) && str.at(str.size() - 1) == 'X')){
		return true;
	}
	return false;
}

//提示并获取书名输入
string getInputBookName(){
	printLine("请输入书名：");
	return getInputString();
}

//提示并获取用户名输入
string getInputUserName(){
	cout << "用户名：";
	return getInputString();
}

//提示并获取不显示的密码输入（注：非C自带不具有可移植性，满20位自动截止返回）
string getInputPassword(){
	cout << "密码：";
	char buf[30];
	int pos = 0;
	buf[pos] = getch();
	while(buf[pos] != '\r' && pos < 20){
		pos++;
		buf[pos] = getch();
	}
	buf[pos] = '\0';
	return buf;
}

//重复请求一个正整数输入，直到输入正确，参数指定上限，默认没有
int getInputPosNum(int maxNum = 0){
	int num = -1;
	string input;
	while(num < 0 || cin <= 0){
		input = getInputString();
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

//重复请求一个合法ISBN输入，直到输入正确
string getInputIsbn(){
	string input = "";
	input = getInputString();
	while(isbnCheck(input)){
		printWrongTypeWarning();
		input = getInputString();
	}
	return input;
}

void visitorMenu(){
	int choice = 0;
	printVisitorMenu();
	choice = getInputPosNum(2);
	switch (choice)
	{
	case 1:
	default:
		break;
	}
}

int main(){
    Datastore::Init();
	printAdminMenu();
	printUserMenu();
	printVisitorMenu();
	string aa;
	int a ;
	cin >> a;

	return 0;
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