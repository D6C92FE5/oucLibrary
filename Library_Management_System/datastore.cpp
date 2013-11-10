
#include "config.h"
#include "datastore.h"

namespace Datastore {

    char* _GenerateFilePathByTypeName(const char* name) {
        auto lengthName = strlen(name);
        auto lengthPath = strlen(Config::DATASTORE_PATH);
        auto filepath = new char[lengthPath + lengthName + 1];

        strcpy(filepath, Config::DATASTORE_PATH);
        strcpy(filepath + lengthPath, name);

        for (auto i = lengthPath; i < lengthPath + lengthName; i++) {
            if (strchr("\\/:*?\"<>| ", filepath[i]) != NULL) {
                filepath[i] = '_';
            }
        }

        return filepath;
    }

    void Init(bool force) {
        _mkdir(Config::DATASTORE_PATH);

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
