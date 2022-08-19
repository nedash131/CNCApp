#pragma once

#include <gtk-3.0/gtk/gtk.h>
#include <glib-2.0/glib.h>

class GtkTextBufferManager{
    private:
    GtkTextBuffer*buff;
    GtkTextIter*startIter; 
    GtkTextIter*endIter;
    gint max;
    gint counter;
    public:
    GtkTextBufferManager(GtkTextBuffer*b,gint m):
        buff(b),max(m){
            this->counter=0;
            this->startIter=new GtkTextIter();
            this->endIter=new GtkTextIter();
    }
    GtkTextBuffer*getTextBuffer(){
        return buff;
    }
    GtkTextIter*getStartTextIter(){
        return startIter;
    }
    GtkTextIter*getEndTextIter(){
        return endIter;
    }
    void addGStringToTextBuffer(const gchar*str){
        if(counter<max){
            gtk_text_buffer_get_start_iter(buff,startIter);
            gtk_text_buffer_insert(buff,startIter,str,-1);
            counter++;
        }else{
            //вставить текст
            gtk_text_buffer_get_start_iter(buff,startIter);
            gtk_text_buffer_insert(buff,startIter,str,-1);
            //удалить текст
            gtk_text_buffer_get_iter_at_line(buff,startIter,counter);
            gtk_text_buffer_get_end_iter(buff,endIter);
            gtk_text_buffer_delete(buff,startIter,endIter);
        }
    }

    ~GtkTextBufferManager(){
        if(startIter!=nullptr)
            delete startIter;
        if(endIter!=nullptr)
            delete endIter;
    }
};