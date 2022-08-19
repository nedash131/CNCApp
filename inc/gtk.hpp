#pragma once
#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtkx.h>
#include <iostream>
#include <glib-2.0/glib.h>

using namespace std;

#include "./Interfaces/fileManagerState.hpp"
#include "./FileManager/Context.hpp"
#include "./FileManager/ConcreteWriteIpToFile.hpp"
#include "./FileManager/ConcreteReadGStringsFromFile.hpp"
#include "./FileManager/ConcreteRemoveGStringFromFile.hpp"
#include "./FileManager/ConcreteGetGArrayFilesNameFromDir.hpp"
#include "./model.hpp"

extern "C"
{
    class Gtk
    {
    private:
        GtkWidget *window;
        GtkBuilder *builder;
        //первая вкладка
        GtkWidget *btAdd;
        GtkWidget *btApply;
        GtkWidget *btRemove;
        GtkWidget *stackSwitcher;
        GtkWidget *entry0;
        GtkWidget *comboBoxTextIp;
        GtkWidget *textView;
        //вторая вкладка
        GtkWidget *comboBoxListTTY;

    public:
        void init(int argc, char *argv[])
        {
            gtk_init(&argc, &argv); // init gtk
            builder = gtk_builder_new();
            builder = gtk_builder_new_from_file("./CNC_1.glade");

            window = GTK_WIDGET(gtk_builder_get_object(builder, "windowMain"));
            g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
            gtk_builder_connect_signals(builder, NULL);
            //присваеваем указатели на виджеты
            stackSwitcher = GTK_WIDGET(gtk_builder_get_object(builder, "stackSwitcherMain"));
            btAdd = GTK_WIDGET(gtk_builder_get_object(builder, "btAdd0"));
            btApply = GTK_WIDGET(gtk_builder_get_object(builder, "btApply0"));
            entry0 = GTK_WIDGET(gtk_builder_get_object(builder, "entry0"));
            comboBoxTextIp = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxTextIP"));
            btRemove = GTK_WIDGET(gtk_builder_get_object(builder, "btRemove0"));
            textView = GTK_WIDGET(gtk_builder_get_object(builder, "textView0"));
            // Model::textBuf=GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer1"));
            Model::textBuffManager = new GtkTextBufferManager(
                GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer1")),
                10);
            //вторая вкладка
            comboBoxListTTY = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxListTTY"));

            ////////////////////////////
            gtk_widget_show(window);
            printf("Окно загружено!\n");
        }
        GtkBuilder *getBuilder()
        {
            return builder;
        }
    };
    void on_btApply0_clicked()
    {
        g_print("Button Apply clicked!\n");
    }
    void on_btAdd0_clicked()
    {
        g_print("Button Add clicked!\n");
        Model::context->changeState(new ConcreteWriteIpToFile());
        Model::context->writeIpToFileGString(IP_FILE_NAME, Model::ipToAdd);
        Model::textBuffManager->addGStringToTextBuffer("ip added!\n");
    }
    void on_entry0_changed(GtkEntry *e)
    {
        Model::ipToAdd = gtk_entry_get_text(e);
    }
    void on_stackMain_set_focus_child()
    {
        g_print("Stack set focus!\n");
    }
    void on_comboBoxTextIP_changed(GtkComboBoxText *box)
    {
        //когда выбрали другую позицию
        gchar *str = gtk_combo_box_text_get_active_text(box);
        if (str != nullptr)
            Model::currentIP = str;
        g_print("Model::currentIP: %s!\n", Model::currentIP);
    }
    void on_comboBoxTextIP_set_focus_child(GtkComboBoxText *box)
    {
        g_print("ComboBoxTextIP set focus child!\n");
        Model::context = new Context(new ConcreteReadStringsFromFile());
        Model::arrIP = Model::context->readGStringsFromFile(IP_FILE_NAME);
        gtk_combo_box_text_remove_all(box);

        for (guint i = 0; i < Model::arrIP->len - 1; i++)
        {
            gtk_combo_box_text_append_text(box,
                                           g_array_index(Model::arrIP, gchar *, i));
        }
        if (Model::arrIP == nullptr)
            gtk_combo_box_text_append_text(box, "none1");
        else if (Model::arrIP == NULL)
            gtk_combo_box_text_append_text(box, "none2");
        else if (!Model::arrIP)
            gtk_combo_box_text_append_text(box, "none3");
        else if (Model::arrIP == 0)
            gtk_combo_box_text_append_text(box, "none4");
    }

    void on_btRemove0_clicked(GtkButton *bt)
    {
        g_print("Remove str: %s\n", Model::currentIP);
        Model::context = new Context(new ConcreteRemoveGStringFromFile());
        Model::context->removeGStringFromFile(IP_FILE_NAME, Model::currentIP);
        Model::textBuffManager->addGStringToTextBuffer("ip был удален!\n");
    }
    void on_textbuffer1_changed(GtkTextBuffer *buff)
    {
        g_print("on_textbuffer1_changed!\n");
    }
    void on_textbuffer1_insert_text(GtkTextBuffer *buff)
    {
        g_print("on_textbuffer1_insert_text\n");
    }
    void on_comboBoxTextListTTY_set_focus_child(GtkComboBoxText *box)
    {
        g_print("on_comboBoxTextListTTY_focus\n");
        Model::context->changeState(new ConcreteGetGArrayFilesNameFromDir());
        Model::context->readFilesNameFromDir(TTY_DIRECTORY);
        Model::arrTTyFiles = Model::context->readFilesNameFromDir(TTY_DIRECTORY);
        for (guint i = 0; i < Model::arrTTyFiles->len; i++)
            gtk_combo_box_text_append_text(box, g_array_index(Model::arrTTyFiles, gchar *, i));
    }
    void on_comboBoxTextListTTY_changed(GtkComboBoxText *box)
    {
        // g_print("on_comboBoxTextListTTY_changed\n");
        gchar *str = gtk_combo_box_text_get_active_text(box);
        if (str != nullptr)
            Model::currentTTyFileName = str;
        //g_print("Model::currentTTyFileName: %s\n", Model::currentTTyFileName);
        Model::textBuffManager->addGStringToTextBuffer("\n");
        Model::textBuffManager->addGStringToTextBuffer(Model::currentTTyFileName);
        Model::textBuffManager->addGStringToTextBuffer("Выбран текущий COM port:");
        
        
    }
}