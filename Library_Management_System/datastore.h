#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>
#include <list>
#include <direct.h>

#include "config.h"

namespace Datastore {

    // 图书信息实体
    struct Book
    {
        int Index;
        bool IsDeleted;
        char Isbn[LEN_BOOK_ISBN];
        char Name[LEN_BOOK_NAME];
        char Author[LEN_BOOK_AUTHOR];
        char Publisher[LEN_BOOK_PUBLISHER];
        int Total;
        int Remain;
    };

    // 用户实体
    struct User
    {
        int Index;
        bool IsDeleted;
        char Name[LEN_USER_NAME];
        char Password[LEN_USER_PASSWORD];
        char Type[LEN_USER_TYPE];
        char Info[LEN_USER_INFO];
    };

    // 借阅记录实体
    struct Record
    {
        int Index;
        bool IsDeleted;
        int BookIndex;
        int UserIndex;
        time_t Datetime;
        bool IsRenew;
        bool IsReturned;
    };

    // 根据实体类型生成文件名
    char* _GenerateFilePathByTypeName(const char* name);
    template <typename T>
    char* _GenerateFilePathByType() {
        auto name = typeid(T).name();
        return _GenerateFilePathByTypeName(name);
    }

    // 打开存储某种类型的实体的文件
    template <typename T>
    FILE* _OpenFile() {
        FILE *file = fopen(_GenerateFilePathByType<T>(), "rb+");
        if (file == NULL) {
            throw new std::exception("文件打开失败");
        }
        return file;
    }

    // 检测存储某种类型的实体的文件是否存在
    template <typename T>
    bool _IsFileExist() {
        auto file = fopen(_GenerateFilePathByType<T>(), "rb");
        auto exist = true;
        if (file == NULL) {
            exist = false;
        } else {
            fclose(file);
        }
        return exist;
    }

    // 创建某种实体
    template <typename T>
    T* Create() {
        auto item = new T();
        memset(item, 0, sizeof T);
        item->Index = -1;
        return item;
    }

    // 根据 Index 选择某个实体
    template <typename T>
    T* Select(int index) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        auto item = new T();
        fseek(file, size * index, SEEK_SET);
        fread(item, size, 1, file);
        return item;
    }

    // 根据条件选择一些实体
    // 返回 NULL 结尾的数组
    // where: 搜索条件
    template <typename T>
    T** Selects(const std::function<bool(const T*)> where, int beginIndex = 0, int maxCount = -1) {
        auto temp = std::list<T*>();
        auto count = 0;
        Traverse<T>([&](const T* item) {
            if (where(item)) {
                T* t = new T();
                memcpy(t, item, sizeof T);
                temp.push_back(t);
                count++;
            }
            return count != maxCount;
        }, beginIndex);

        auto result = new T*[temp.size() + 1];
        int i = 0;
        for (auto it=temp.begin(); it != temp.end(); it++) {
            result[i] = *it;
            i++;
        }
        result[temp.size()] = NULL;
        return result;
    }

    // 根据条件选择一个实体
    // 返回符合条件的第一个实体，没有找到时返回 NULL
    // where: 搜索条件
    template <typename T>
    T* Select(const std::function<bool(const T*)> where, int beginIndex = 0) {
        auto results = Selects(where, beginIndex, 1);
        auto result = *results;
        delete results;
        return result;
    }

    // 插入或更新一个实体
    template <typename T>
    void InsertOrUpdate(T* item) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        if (item->Index == -1) {
            fseek(file, 0, SEEK_END);            
            auto offset = ftell(file);
            item->Index = offset / size;
        } else {
            fseek(file, size * item->Index, SEEK_SET);
        }
        fwrite(item, size, 1, file);
        fclose(file);
    }

    // 删除一个实体
    template <typename T>
    void Delete(int index) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        T* item = new T();
        fseek(file, size * index, SEEK_SET);
        fread(item, size, 1, file);
        item->IsDeleted = true;
        fseek(file, size * index, SEEK_SET);
        fwrite(item, size, 1, file);
        delete item;
        fclose(file);
    }

    // 遍历一种实体
    // func: 操作一个实体的函数
    template <typename T>
    void Traverse(const std::function<bool(const T*)> func, int beginIndex = 0, int endIndex = 0) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        T* item = new T();

        fseek(file, 0, SEEK_END);
        auto count = ftell(file) / size;

        if (endIndex <= 0) {
            endIndex += count;
        }

        fseek(file, beginIndex * size, SEEK_SET);        
        for (auto i = beginIndex; i < endIndex; i++) {
            fread(item, size, 1, file);
            if (!item->IsDeleted && !func(item)) {
                break;
            }
        }

        delete item;
    }

    // 数据存储初始化，创建相关目录和文件并添加初始信息
    // force: 为 true 时忽略现有文件强制初始化
    void Init(bool force = false);

}
