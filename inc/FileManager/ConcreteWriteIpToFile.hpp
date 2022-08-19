#pragma once
#include <fstream>
#include <iostream>
#include <glib-2.0/glib.h>
using namespace std;
#include "../Interfaces/fileManagerState.hpp"


class ConcreteWriteIpToFile:public FileManagerState{
    public:
    void writeIpToFileGString(const gchar*fileName,const gchar*stringIp)override{
        if(stringIp==nullptr || g_strcmp0(stringIp,"")==0)return;
        str=stringIp;
        ofstream fout(fileName,ios_base::app);//добавляем в конец
        if(!fout.is_open()){
            g_print("Не удалось открыть файл %s.\n",fileName);
            return;
        }
        const gchar*normalizeGchar=g_utf8_normalize(stringIp,32,G_NORMALIZE_DEFAULT);
        fout<<normalizeGchar<<endl;
        fout.close();
    }
    GArray*readGStringsFromFile(const gchar*fileName)override{
        return arrIP;
    }
    void removeGStringFromFile(const gchar*fileName,const gchar*gString)override{
    }
    GArray*readFilesNameFromDir(const gchar*pathToFiles)override{
        return nullptr;
    }
};