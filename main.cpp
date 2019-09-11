//#include "controller.h"
#include <iostream>
#include <gtkmm.h>
#include "main_window.h"

int main(int argc,char *argv[])
{
  //Gtk::Main kit(argc,argv);
  //Rental_site rental_site;
  //Controller c(rental_site);
  //c.cli();

  auto app=Gtk::Application::create(argc, argv,"edu.uta.cse1325.example");
  Main_window win;
  win.set_title("Java and Donut Express (JADE)");
  

 
  return app->run(win);
}
