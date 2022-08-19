#pragma once
#include <filesystem>
#include "../Interfaces/fileManagerState.hpp"

class ConcreteGetGArrayFilesNameFromDir:public FileManagerState{
    private:
    public:
    GArray*readFilesNameFromDir(const gchar*pathToFiles)override{
        const gchar*str=new gchar[32];
        arrTTyFiles=g_array_new(TRUE,TRUE,sizeof(gchar*));
        for(const auto&entry: std::filesystem::directory_iterator(pathToFiles)){
            str=entry.path().c_str();
            if(g_strrstr(str,"tty")==nullptr)continue;
            const gchar*normalizeGchar=g_utf8_normalize(str,32,G_NORMALIZE_DEFAULT);
            if(g_strcmp0(normalizeGchar,"")!=0 && g_strcmp0(normalizeGchar,"\n")!=0)
                g_array_append_val(arrTTyFiles,normalizeGchar);
        }
        return arrTTyFiles;
    }
    virtual void writeIpToFileGString(const gchar*fileName,const gchar*stringIp){
    }
    virtual GArray*readGStringsFromFile(const gchar*fileName){
        return nullptr;
    }
    virtual void removeGStringFromFile(const gchar*fileName,const gchar*gString){
    }
};