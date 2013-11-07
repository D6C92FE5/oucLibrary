#pragma once
namespace Config {

    //用户类型
    extern const bool ADMIN_USER;
    extern const bool NORMAL_USER;

    //用户权限
    struct USER_ACCESS {
        bool SEARCH_BOOK;       ///检索图书
        bool CHANGE_PASSWORD;   ///修改密码
        bool ADD_USER;          ///添加用户
        bool DELETE_USER;       ///删除用户
        bool RESET_PASSWORD;    ///重置用户密码
        bool BOLLOW_BOOK;       ///借阅图书
        bool RETURN_BOOK;       ///归还图书
        bool RENEW_BOOK;        ///续借图书
        bool BOLLOW_HISTORY;    ///查看借阅历史
    };
    extern const USER_ACCESS ADMIN_ACCESS;
    extern const USER_ACCESS NORMAL_ACCESS;

    //借阅期限
    extern const int MAX_BOLLOW_TIME;

    //借阅上限
    extern const int MAX_BOLLOW_NUM;
}