
#include "../inc/gtk.hpp"
#include "../inc/model.hpp"
#include "../inc/FileManager/ConcreteReadGStringsFromFile.hpp"

        
         
int main(int argc,char*argv[]){   
  setlocale(0,"RU"); 
  Gtk gtk;       
  Model::fmState=new ConcreteReadStringsFromFile();  
  Model::context=new Context(Model::fmState);
  //Model::textBuf=GTK_TEXT_BUFFER(gtk_builder_get_object(gtk.getBuilder(), "textbuffer1"));
     
  gtk.init(argc,argv); 
  //gtk.addToListIp(Model::context->readStringsFromFile(Model::getIpFileName()));
               
  gtk_main();              
              
  delete Model::context; 
  delete Model::textBuffManager;
  return 0; 
}  
                 