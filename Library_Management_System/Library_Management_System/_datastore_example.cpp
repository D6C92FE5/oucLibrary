
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

#include "datastore.h"

// 添加一种图书
void InsertBook() {
    auto book = Datastore::Create<Datastore::Book>();
    strcpy(book->Name, "C++ Primer中文版(第5版)");
    strcpy(book->Isbn, "9787121155352");
    strcpy(book->Author, "Stanley B. Lippman, Josee Lajoie, Barbara E. Moo");
    strcpy(book->Pulisher, "电子工业出版社");
    book->Total = 10;
    book->Remain = 10;
    Datastore::InsertOrUpdate(book);
}

// 修改图书信息
void UpdateBook() {
    auto book = Datastore::Select<Datastore::Book>(0);
    book->Remain = 5;
    Datastore::InsertOrUpdate(book);
}

// 删除图书信息
void DeleteBook() {
    Datastore::Delete<Datastore::Book>(0);
}


// 根据条件搜索图书
bool SearchBookCondition(const Datastore::Book* book) {
    return book->Remain > 0;
}
void SearchBook() {
    auto books = Datastore::Select<Datastore::Book>(SearchBookCondition);
}

// 根据条件搜索图书 第2种写法
void SearchBook2() {
    auto books = Datastore::Select<Datastore::Book>([](const Datastore::Book* book) {
        return book->Remain > 0;
    });
}

// 修改用户
void UpdateUser() {
    auto user = Datastore::Select<Datastore::User>(0);
    strcpy(user->Password, "123456");
    Datastore::InsertOrUpdate(user);
}

// 添加借阅记录
void InsertRecord() {
    auto record = Datastore::Create<Datastore::Record>();
    record->BookIndex = 0;
    record->UserIndex = 1;
    record->Datetime = time(NULL);
    Datastore::InsertOrUpdate(record);
}

// 注意初始化
int main() {
    Datastore::Init();
    InsertBook();
    UpdateBook();
    DeleteBook();
    SearchBook();
    SearchBook2();
    UpdateUser();
    InsertRecord();
    return 0;
}
