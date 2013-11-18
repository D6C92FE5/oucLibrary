
#include "config.h"

namespace Config {

    const bool ADMIN_USER = true;
    const bool NORMAL_USER = false;

    const USER_ACCESS ADMIN_ACCESS = {
        true,   // SEARCH_BOOK;     ///检索图书
        true,   // CHANGE_PASSWORD; ///修改密码
        true,   // ADD_USER;        ///添加用户
        true,   // DELETE_USER;     ///删除用户
        true,   // RESET_PASSWORD;  ///重置用户密码
        true,   // BOLLOW_BOOK;     ///借阅图书
        true,   // RETURN_BOOK;     ///归还图书
        true,   // RENEW_BOOK;      ///续借图书
        true,   // BOLLOW_HISTORY;  ///查看借阅历史
    };

    const USER_ACCESS NORMAL_ACCESS = {
        true,   // SEARCH_BOOK;     ///检索图书
        true,   // CHANGE_PASSWORD; ///修改密码
        false,  // ADD_USER;        ///添加用户
        false,  // DELETE_USER;     ///删除用户
        false,  // RESET_PASSWORD;  ///重置用户密码
        false,  // BOLLOW_BOOK;     ///借阅图书
        false,  // RETURN_BOOK;     ///归还图书
        false,  // RENEW_BOOK;      ///续借图书
        true,   // BOLLOW_HISTORY;  ///查看借阅历史
    };

    const int MAX_BOLLOW_TIME = 30;
    const int MAX_BOLLOW_NUM = 5;

    const char* DATASTORE_PATH = ".\\Datastore\\";

    const int FILE_READ_CACHE_COUNT = 100;
}
