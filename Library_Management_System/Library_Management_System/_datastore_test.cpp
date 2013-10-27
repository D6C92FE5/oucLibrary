
#include <iostream>
//using namespace std;

#include "datastore.h"
using namespace Datastore;

bool test(const Book* book) {
    std::cout << book->Name << std::endl;
    return true;
}

bool where(const User* user) {
    return strcmp(user->Type, "”√ªß") == 0;
}

int main() {
    //Book* book = Select<Book>(1);
    //Traverse<Book>(test);
    //int a = Test(new User());
    //auto book = Create<Book>();
    //cout << _GenerateFilePathByType<Book>() << endl;
    //_OpenFile<Book>();
    Init();
    auto users = Select<User>(where);
    return 0;
}
