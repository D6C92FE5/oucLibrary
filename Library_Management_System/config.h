#pragma once

namespace Config {

    //数据实体属性长度，注意 extern const 不能作为数组长度
    #define LEN_BOOK_ISBN 14
    #define LEN_BOOK_NAME 100
    #define LEN_BOOK_AUTHOR 100
    #define LEN_BOOK_PUBLISHER 100
    #define LEN_USER_NAME 100
    #define LEN_USER_PASSWORD 40
    #define LEN_USER_TYPE 10
    #define LEN_USER_INFO 100
    
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

    //数据存储文件所在的目录
    extern const char* DATASTORE_PATH;

    //数据存储文件读取缓存，每次读取的记录条数
    extern const int FILE_READ_CACHE_COUNT;

    // 是否为调试版本
    extern const bool DEBUG;
}
