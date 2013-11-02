
#include "datastore.h"

namespace Datastore {

    const char* _PATH = ".\\Datastore\\";

    void Init(bool force) {
        _mkdir(_PATH);

        if (force || !_IsFileExist<Book>()) {
            fclose(fopen(_GenerateFilePathByType<Book>(), "wb"));
        }
        if (force || !_IsFileExist<User>()) {
            fclose(fopen(_GenerateFilePathByType<User>(), "wb"));

            User* user;
            
            user = Create<User>();
            strcpy(user->Name, "admin");
            strcpy(user->Password, "1");
            strcpy(user->Type, "管理员");
            InsertOrUpdate(user);
            delete user;

            user = Create<User>();
            strcpy(user->Name, "user");
            strcpy(user->Password, "2");
            strcpy(user->Type, "用户");
            InsertOrUpdate(user);
            delete user;
        }
        if (force || !_IsFileExist<Record>()) {
            fclose(fopen(_GenerateFilePathByType<Record>(), "wb"));
        }
    }

}
