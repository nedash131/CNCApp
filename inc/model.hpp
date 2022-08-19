#pragma once
#include <string>
#include <gtk-3.0/gtk/gtk.h>

using namespace std;

#include "./FileManager/Context.hpp"
#include "./Interfaces/fileManagerState.hpp"
#include "./GtkTextBufferManager.hpp"

#define IP_FILE_NAME "ip.txt"
#define TTY_DIRECTORY "/dev"





class Model{
    private:
    public:
    static Context*context;
    static FileManagerState*fmState;
    static const gchar* ipToAdd;
    static GArray*arrIP;
    static const gchar* currentIP;
    static GtkTextBufferManager*textBuffManager;
    //com ports
    static GArray*arrTTyFiles;
    static const gchar* currentTTyFileName;
};
const gchar* Model::ipToAdd;
GArray* Model::arrIP;
Context* Model::context;
FileManagerState* Model::fmState;
const gchar* Model::currentIP;
GtkTextBufferManager* Model::textBuffManager;
//com ports
GArray*Model::arrTTyFiles;
const gchar* Model::currentTTyFileName;

   