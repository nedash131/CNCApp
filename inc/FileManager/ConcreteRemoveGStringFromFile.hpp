#pragma once
#include <fstream>

using namespace std;

#include "../Interfaces/fileManagerState.hpp"

class ConcreteRemoveGStringFromFile:public FileManagerState{
    public:
    void writeIpToFileGString(const gchar*fileName,const gchar*stringIp)override{
    }
    GArray*readGStringsFromFile(const gchar*fileName)override{
        return arrIP;
    }
    void removeGStringFromFile(const gchar*fileName,const gchar*gString)override{
        if(gString==nullptr || g_strcmp0(gString,"")==0)return;
        gString=g_utf8_normalize(gString,32,G_NORMALIZE_DEFAULT);
        g_print("%s\n",gString);

        gchar*str=new gchar[32];
        ifstream fin(fileName,ios::ios_base::in);
        if(!fin.is_open())return;
        ofstream fout("temp.txt");
        while(!fin.eof()){
            fin>>str;
            if(g_strcmp0(str,gString)!=0 && g_strcmp0(str,"") && g_strcmp0(str,"\n")){
                fout<<g_utf8_normalize(str,32,G_NORMALIZE_DEFAULT);
                fout<<"\n";
            }
                
        }
        fin.close();
        fout.close();
        remove(fileName);
        rename("temp.txt",fileName);
    }
    GArray*readFilesNameFromDir(const gchar*pathToFiles)override{
        return nullptr;
    }
};