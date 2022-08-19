#pragma once
#include <glib-2.0/glib.h>
#include <gtk-3.0/gtk/gtk.h>

using namespace std;

class Context;
class FileManagerState{
    protected:
    Context*context;
    GArray*arrIP;
    GArray*arrTTyFiles;
    const gchar*str;
    public:
    void setContext(Context*context){
        this->context=context;
    }
    virtual void writeIpToFileGString(const gchar*fileName,const gchar*stringIp)=0;
    virtual GArray*readGStringsFromFile(const gchar*fileName)=0;
    virtual void removeGStringFromFile(const gchar*fileName,const gchar*gString)=0;
    virtual GArray*readFilesNameFromDir(const gchar*pathToFiles)=0;
    virtual ~FileManagerState(){
    }
};