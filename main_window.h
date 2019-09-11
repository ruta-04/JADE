 #ifndef __MAIN_WINDOW_H
#define __MAIN_WINDOW_H
//#include "view.h"
#include "store.h"
#include <gtkmm.h>
//#include "rental_site.h"
//#include "vehicle.h"
//#include "controller.h"


class Main_window : public Gtk::Window
{
    public:
        Main_window();
        virtual ~Main_window();
    protected:

    void on_quit_click();           // Exit the game
	void on_create_coffee_click();
    void on_create_order_click();
   	void on_create_donut_click();
   	void on_view_all_click();
    void on_new_customer_click();
    void on_list_customers_click();
      void on_about_click();
    void on_view_order_click();
    void on_fill_order_click();
     void on_pay_order_click();
     void on_discard_order_click();
    private:
    
    Store _store{"ParksMall JADE"};
    //Order _order;
    static int order_counter;
    //Store *p=NULL;
//		View  v;
//        void set_sticks();                    // Update display, robot move
	//	Rental_site rental_site;
	//Controller c;

//
//        Gtk::Label *sticks;                   // Display of sticks on game board
//        Gtk::Label *msg;                      // Status message display
       Gtk::ToolButton *button1;             // Button to select 1 donut
        Gtk::Image *button1_on_image;         //   Image when active
//        Gtk::Image *button1_off_image;        //   Image when inactive
       Gtk::ToolButton *button2;             // Button to select 2 coffee
       Gtk::Image *button2_on_image;
//        Gtk::Image *button2_off_image;
        Gtk::ToolButton *button3;             // Button to select 3 sticks
       Gtk::Image *button3_on_image;
    Gtk::ToolButton *button4;
    Gtk::Image *button4_on_image;
    Gtk::ToolButton *button5;
    Gtk::Image *button5_on_image;
    Gtk::ToolButton *button6;
    Gtk::Image *button6_on_image;
    Gtk::ToolButton *button7;
    Gtk::Image *button7_on_image;
    Gtk::ToolButton *button8;
    Gtk::Image *button8_on_image;
    Gtk::ToolButton *button9;
    Gtk::Image *button9_on_image;
    Gtk::ToolButton *button10;
    Gtk::Image *button10_on_image;
    Gtk::Label *msg;  
//        Gtk::Image *button3_off_image;
//        Gtk::ToggleToolButton *computer_player;  // Button to enable robot
};
#endif 

