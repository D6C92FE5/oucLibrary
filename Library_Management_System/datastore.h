#ifndef _DATASTORE_H_
#define _DATASTORE_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>
#include <list>
#include <direct.h>

namespace Datastore {

    // ���ݴ洢���ļ����ڵ�Ŀ¼
    extern const char* _PATH;
    
    // ͼ����Ϣʵ��
    struct Book
    {
        int Index;
        bool IsDeleted;
        char Isbn[14];
        char Name[100];
        char Author[100];
        char Pulisher[100];
        int Total;
        int Remain;
    };

    // �û�ʵ��
    struct User
    {
        int Index;
        bool IsDeleted;
        char Name[100];
        char Password[40];
        char Type[10];
        char Info[100];
    };

    // ���ļ�¼ʵ��
    struct Record
    {
        int Index;
        bool IsDeleted;
        int BookIndex;
        int UserIndex;
        int Datetime;
        bool IsRenew;
        bool IsReturned;
    };

    // ����ʵ�����������ļ���
    template <typename T>
    char* _GenerateFilePathByType() {
        auto name = typeid(T).name();

        auto lengthName = strlen(name);
        auto lengthPath = strlen(_PATH);
        auto filepath = new char[lengthPath + lengthName + 1];

        strcpy(filepath, _PATH);
        strcpy(filepath + lengthPath, name);

        for (auto i = lengthPath; i < lengthPath + lengthName; i++) {
            if (strchr("\\/:*?\"<>| ", filepath[i]) != NULL) {
                filepath[i] = '_';
            }
        }

        return filepath;
    }

    // �򿪴洢ĳ�����͵�ʵ����ļ�
    template <typename T>
    FILE* _OpenFile() {
        FILE *file = fopen(_GenerateFilePathByType<T>(), "rb+");
        if (file == NULL) {
            throw new std::exception("�ļ���ʧ��");
        }
        return file;
    }

    // ���洢ĳ�����͵�ʵ����ļ��Ƿ����
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

    // ����ĳ��ʵ��
    template <typename T>
    T* Create() {
        auto item = new T();
        memset(item, 0, sizeof T);
        item->Index = -1;
        return item;
    }

    // ���� Index ѡ��ĳ��ʵ��
    template <typename T>
    T* Select(int index) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        auto item = new T();
        fseek(file, size * index, SEEK_SET);
        fread(item, size, 1, file);
        return item;
    }

    // ��������ѡ��һЩʵ��
    // ���� NULL ��β������
    // where: ��������
    template <typename T>
    T** Select(const std::function<bool(const T*)> where, int beginIndex = 0, int maxCount = -1) {
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

    // ��������һ��ʵ��
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

    // ɾ��һ��ʵ��
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

    // ����һ��ʵ��
    // func: ����һ��ʵ��ĺ���
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

    // ���ݴ洢��ʼ�����������Ŀ¼���ļ������ӳ�ʼ��Ϣ
    // force: Ϊ true ʱ���������ļ�ǿ�Ƴ�ʼ��
    void Init(bool force = false);

}

#endif // _DATASTORE_H_