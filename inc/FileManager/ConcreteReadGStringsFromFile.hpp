#pragma once
#include <fstream>
#include <iostream>

using namespace std;

#include "../Interfaces/fileManagerState.hpp"


class ConcreteReadStringsFromFile:public FileManagerState{
    private:
    public:
    GArray* readGStringsFromFile(const gchar*fileName)override{
        gchar*gStr=new gchar[32];
        if(arrIP==nullptr)arrIP=g_array_new(TRUE,TRUE,sizeof(gchar*));
        ifstream fin(fileName,ios::ios_base::in);
        while(!fin.eof()){
            fin>>gStr;
            const gchar*normalizeGchar=g_utf8_normalize(gStr,32,G_NORMALIZE_DEFAULT);
            if(g_strcmp0(normalizeGchar,"")!=0 && g_strcmp0(normalizeGchar,"\n")!=0)
                g_array_append_val(arrIP,normalizeGchar);
        }
        fin.close();
        delete [] gStr;
        return arrIP;
    }
    void writeIpToFileGString(const gchar*fileName,const gchar*stringIp)override{
    }
    void removeGStringFromFile(const gchar*fileName,const gchar*gString)override{
    }
    GArray*readFilesNameFromDir(const gchar*pathToFiles)override{
        return nullptr;
    }
};