#pragma once
#include "../Interfaces/fileManagerState.hpp"

class Context
{
private:
    FileManagerState *state;
public:
    Context(FileManagerState *newState) : state(newState){
    }
    void changeState(FileManagerState *newState){
        this->state = newState;
    }
    void writeIpToFileGString(const gchar*fileName,const gchar*stringIp){
        state->writeIpToFileGString(fileName, stringIp);
    }
    GArray*readGStringsFromFile(const gchar*fileName){
        return state->readGStringsFromFile(fileName);
    }
    void removeGStringFromFile(const gchar*fileName,const gchar*gString){
        state->removeGStringFromFile(fileName,gString);
    }
    GArray*readFilesNameFromDir(const gchar*pathToFiles){
        return state->readFilesNameFromDir(pathToFiles);
    }
    ~Context()
    {
        delete state;
    }
};