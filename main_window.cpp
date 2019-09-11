#include "main_window.h"
#include "dialogs.h"
#include "store.h"
#include "product.h"
#include <regex>
#include <gtkmm.h>
#include "customer.h"
#include "order.h"

//#include "view.h"

int Main_window::order_counter=0;
Main_window::Main_window() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(400, 200);
 
    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //   F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
   Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);
    
    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_quit_click));
    filemenu->append(*menuitem_quit);
    
    //View
    //Create a view
    Gtk::MenuItem *menuitem_view=Gtk::manage(new Gtk::MenuItem("View",true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu=Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);
    
    // All products
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_products = Gtk::manage(new Gtk::MenuItem("All products", true));
    menuitem_products->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_view_all_click));
    viewmenu->append(*menuitem_products);
    
    //list customers
    Gtk::MenuItem *menuitem_customers = Gtk::manage(new Gtk::MenuItem("List all customers", true));
    menuitem_customers->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_list_customers_click));
    viewmenu->append(*menuitem_customers);
    
    //view order
    Gtk::MenuItem *menuitem_orders = Gtk::manage(new Gtk::MenuItem("View order", true));
    menuitem_orders->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_view_order_click));
    viewmenu->append(*menuitem_orders);
    
    //Create
    //Create a menu
    Gtk::MenuItem *menuitem_create=Gtk::manage(new Gtk::MenuItem("Create",true));
    menubar->append(*menuitem_create);
    Gtk::Menu *createmenu=Gtk::manage(new Gtk::Menu());
    menuitem_create->set_submenu(*createmenu);
    
    //     Coffee
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_java = Gtk::manage(new Gtk::MenuItem("Java", true));
    menuitem_java->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_create_coffee_click));
    createmenu->append(*menuitem_java);
    
    //        Donut
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_donut = Gtk::manage(new Gtk::MenuItem("Donut", true));
    menuitem_donut->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_create_donut_click));
    createmenu->append(*menuitem_donut);
    
    //customer
    Gtk::MenuItem *menuitem_customer = Gtk::manage(new Gtk::MenuItem("Customer", true));
    menuitem_customer->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_new_customer_click));
    createmenu->append(*menuitem_customer);
    
    //customer
    Gtk::MenuItem *menuitem_order = Gtk::manage(new Gtk::MenuItem("Order", true));
    menuitem_order->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_create_order_click));
    createmenu->append(*menuitem_order);
    
    //STATE OF ORDERS
    //Create a process
    Gtk::MenuItem *menuitem_process=Gtk::manage(new Gtk::MenuItem("Process",true));
    menubar->append(*menuitem_process);
    Gtk::Menu *processmenu=Gtk::manage(new Gtk::Menu());
    menuitem_process->set_submenu(*processmenu);
    
    //        FILL
    Gtk::MenuItem *menuitem_fill = Gtk::manage(new Gtk::MenuItem("Fill", true));
    menuitem_fill->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_fill_order_click));
    processmenu->append(*menuitem_fill);
    
    //        PAY
    Gtk::MenuItem *menuitem_pay = Gtk::manage(new Gtk::MenuItem("Pay", true));
    menuitem_pay->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_pay_order_click));
    processmenu->append(*menuitem_pay);
    
    //        DISACRD
    Gtk::MenuItem *menuitem_discard = Gtk::manage(new Gtk::MenuItem("Discard", true));
    menuitem_discard->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_discard_order_click));
    processmenu->append(*menuitem_discard);
    
    
    
    
    //help
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);
    
    //about help
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_about_click));
    helpmenu->append(*menuitem_about);
    
    

//    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);
    
    // Add a donut
    button1_on_image = Gtk::manage(new Gtk::Image{"donut.png"});
    //button1_off_image = Gtk::manage(new Gtk::Image{"button1_off.png"});
    button1 = Gtk::manage(new Gtk::ToolButton(*button1_on_image));
    button1->set_tooltip_markup("Create donut");
    button1->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_create_donut_click));
    toolbar->append(*button1);

    
    // Add a coffee
    button2_on_image = Gtk::manage(new Gtk::Image{"coffee.png"});
    //button2_off_image = Gtk::manage(new Gtk::Image{"button2_off.png"});
    button2 = Gtk::manage(new Gtk::ToolButton(*button2_on_image));
    button2->set_tooltip_markup("Add coffee");
    button2->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_create_coffee_click));
    toolbar->append(*button2);

    
   
    // Add a list of donut and coffee
    button3_on_image = Gtk::manage(new Gtk::Image{"d_c.png"});
   // button3_off_image = Gtk::manage(new Gtk::Image{"button3_off.png"});
    button3 = Gtk::manage(new Gtk::ToolButton(*button3_on_image));
    button3->set_tooltip_markup("List all Donut and Coffee");
    button3->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_view_all_click));
    toolbar->append(*button3);
    
    // Add a list of donut and coffee
    button4_on_image = Gtk::manage(new Gtk::Image{"customer.png"});
    // button3_off_image = Gtk::manage(new Gtk::Image{"button3_off.png"});
    button4 = Gtk::manage(new Gtk::ToolButton(*button4_on_image));
    button4->set_tooltip_markup("Create Customer");
    button4->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_new_customer_click));
    toolbar->append(*button4);

    // Add a list of customer
    button5_on_image = Gtk::manage(new Gtk::Image{"list_c.png"});
    // button3_off_image = Gtk::manage(new Gtk::Image{"button3_off.png"});
    button5 = Gtk::manage(new Gtk::ToolButton(*button5_on_image));
    button5->set_tooltip_markup("List all Customers");
    button5->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_list_customers_click));
    toolbar->append(*button5);
    
    //create order
    button6_on_image = Gtk::manage(new Gtk::Image{"create_order.png"});
    // button3_off_image = Gtk::manage(new Gtk::Image{"button3_off.png"});
    button6 = Gtk::manage(new Gtk::ToolButton(*button6_on_image));
    button6->set_tooltip_markup("Create order");
    button6->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_create_order_click));
    toolbar->append(*button6);
    
    //view order
    button7_on_image = Gtk::manage(new Gtk::Image{"list_orders.png"});
    // button3_off_image = Gtk::manage(new Gtk::Image{"button3_off.png"});
    button7 = Gtk::manage(new Gtk::ToolButton(*button7_on_image));
    button7->set_tooltip_markup("List orders");
    button7->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_view_order_click));
    toolbar->append(*button7);
    
    //FILL ORDER
    button8_on_image = Gtk::manage(new Gtk::Image{"fill.png"});
    // button3_off_image = Gtk::manage(new Gtk::Image{"button3_off.png"});
    button8 = Gtk::manage(new Gtk::ToolButton(*button8_on_image));
    button8->set_tooltip_markup("Fill orders");
    button8->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_fill_order_click));
    toolbar->append(*button8);
    
    
    //PAY ORDER
    button9_on_image = Gtk::manage(new Gtk::Image{"pay.png"});
    // button3_off_image = Gtk::manage(new Gtk::Image{"button3_off.png"});
    button9 = Gtk::manage(new Gtk::ToolButton(*button9_on_image));
    button9->set_tooltip_markup("Pay orders");
    button9->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_pay_order_click));
    toolbar->append(*button9);
    
    //DISCARD ORDER
    button10_on_image = Gtk::manage(new Gtk::Image{"del.png"});
    // button3_off_image = Gtk::manage(new Gtk::Image{"button3_off.png"});
    button10 = Gtk::manage(new Gtk::ToolButton(*button10_on_image));
    button10->set_tooltip_markup("Disacrd orders");
    button10->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_discard_order_click));
    toolbar->append(*button10);
    
    // M A I N   A R E A
    Gtk::Label* main_area = Gtk::manage(new Gtk::Label);
    main_area->set_hexpand(true);
    main_area->set_vexpand(true);
    vbox->add(*main_area);
    
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for program messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);
    
    // Make the box and everything in it visible
    vbox->show_all();

}

Main_window::~Main_window() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Main_window::on_create_donut_click() {
    //_store.add_java();
    //_store.add_product((Product*)(Java{"Java",5.00,2.00,0}));
    //_store.product_to_string(0);
    
//    Frosting frosting = (Frosting)(rand()%5);
//    Filling filling = (Filling)(rand()%5);
//    //Donut* d = new Donut{"Donut", 0.75, 0.25, frosting, true, filling};
//    Donut* d = new Donut{"Donut", 0.75, 0.25, frosting, true, filling};
//
//    _store.add_product(d);
    //std::cout<<d->to_string();
    
    //creating donut widget
    
    Gtk::Dialog *dialog=new Gtk::Dialog();
    dialog->set_title("Create a Donut");
    dialog->set_transient_for(*this);
    
    ///DONUT NAME
    Gtk::HBox name;
    
    Gtk::Label name_donut{"Name: "};
    name.pack_start(name_donut);
    
    Gtk::Entry entry_donut;
    entry_donut.set_max_length(50);
    name.pack_start(entry_donut);
    dialog->get_vbox()->pack_start(name);
    
    //price
    Gtk::HBox price;
    
    Gtk::Label price_donut{"Price: "};
    price.pack_start(price_donut);
    
    Gtk::Entry entry_price;
    entry_price.set_max_length(50);
    price.pack_start(entry_price);
    dialog->get_vbox()->pack_start(price);
    
    //cost
    Gtk::HBox cost;
    
    Gtk::Label cost_donut{"Cost: "};
    cost.pack_start(cost_donut);
    
    Gtk::Entry entry_cost;
    entry_cost.set_max_length(50);
    cost.pack_start(entry_cost);
    dialog->get_vbox()->pack_start(cost);

    //Frosting
    Gtk::HBox frosting;
    
    Gtk::Label frosting_donut{"Frosting: "};
    frosting.pack_start(frosting_donut);
    
    Gtk::ComboBoxText frosting_menu;
    frosting_menu.append("Unfrosted");
    frosting_menu.append("Chocolate_top");
    frosting_menu.append("Vanilla_top");
    frosting_menu.append("Pink_top");
    frosting.pack_start(frosting_menu);
    dialog->get_vbox()->pack_start(frosting);
    
    //filling
    Gtk::HBox filling;
    
    Gtk::Label filling_donut{"Filling: "};
    filling.pack_start(filling_donut);
    
    Gtk::ComboBoxText filling_menu;
    filling_menu.append("Unfilled");
    filling_menu.append("Creme");
    filling_menu.append("Bavarian");
    filling_menu.append("Strawberry");
    filling.pack_start(filling_menu);
    dialog->get_vbox()->pack_start(filling);
    
    Gtk::CheckButton sprinkles("Sprinkles", true);
    dialog->get_vbox()->pack_start(sprinkles);
    
    dialog->add_button("Cancel", 0);
    dialog->add_button("Create", 1);
    dialog->show_all();
    int result = dialog->run();
    
    std::string name_d=entry_donut.get_text();
    std::string price_d=entry_price.get_text();
    std::string cost_d=entry_cost.get_text();
    int frost_d=frosting_menu.get_active_row_number();
    int fill_d=filling_menu.get_active_row_number();
    bool flag_sprinkles=sprinkles.get_active();
    double price_final=0;
    double cost_final=0;
    
    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    if(result==1)
    {
        
        if(name_d.empty())
        {
            Dialogs::message("Name fiels is empty. Donut cannot be created.");
        }
        if(price_d.empty() || cost_d.empty())
        {
            Dialogs::message("Price/Cost field is empty. Donut cannot be created.");
        }
        else
        {
            try {
                //std::cout<<"gign\n";
                price_final=std::stod(price_d);
                //std::cout<<price_final<<"\n";
                cost_final=std::stod(cost_d);
                //std::cout<<cost_final;
                
                
            } catch (...) {
                
            }
        }
        if(price_final==0.0 || cost_final==0.0)
        {
           // std::cout<<"in loop";
            Dialogs::message("Invalid data in price/cost field. Donut cannot be created");
        }
        
        if(!name_d.empty() && !price_d.empty() && !cost_d.empty() && !(price_final==0.0) && !(cost_final==0.0) )
        {
            Donut *donut=new Donut(name_d,price_final,cost_final,(Frosting)frost_d,flag_sprinkles,(Filling)fill_d);
            _store.add_product(donut);
            msg->set_text("New donut product \"" + name_d + "\" created"+"\t\t\t\t\t\t\t\t\t"+_store.get_cash_register());
            
        }
       
    }
     delete dialog;
}

void Main_window::on_create_coffee_click() {
    //_store.add_java();
    //_store.add_product((Product*)(Java{"Java",5.00,2.00,0}));
    //_store.product_to_string(0);
    
//    int darkness = rand() % 5;
//    double price = 5.00;
//    double cost = 2.00;
//    Java* c = new Java{"Coffee", price, cost, (Darkness)darkness};
//    int shot_clock = rand() % 4; // vary the number of shots
//    while (shot_clock>=0) {
//        Shot shot = (Shot)(rand()%4);
//        c->add_shot(shot);
//        shot_clock--;
//    }
//    _store.add_product(c);
    //std::cout<< c->to_string();
    
    
    //create java
   
    bool flag=true;
    double price_final=0.0;
    double cost_final=0.0;
    Gtk::Dialog *dialog=new Gtk::Dialog();
    dialog->set_transient_for(*this);
    dialog->set_title("Create Java");
    
    //Name
    
    Gtk::HBox name;
    
    Gtk::Label label_name{"Name: "};
    name.pack_start(label_name);
    
    Gtk::Entry entry_name;
    entry_name.set_max_length(50);
    name.pack_start(entry_name);
    dialog->get_vbox()->pack_start(name);
    
    //price
    
    Gtk::HBox price;
    
    Gtk::Label label_price{"Price: "};
    price.pack_start(label_price);
    
    Gtk::Entry entry_price;
    entry_price.set_max_length(50);
    price.pack_start(entry_price);
    dialog->get_vbox()->pack_start(price);
    
    //cost
    
    Gtk::HBox cost;
    
    Gtk::Label label_cost{"Cost: "};
    cost.pack_start(label_cost);
    
    Gtk::Entry entry_cost;
    entry_cost.set_max_length(50);
    cost.pack_start(entry_cost);
    dialog->get_vbox()->pack_start(cost);
    
    //Darkness

    Gtk::HBox darkness;
    
    Gtk::Label label_darkness{"Darkness: "};
    darkness.pack_start(label_darkness);
    
    Gtk::ComboBoxText darkness_menu;
    darkness_menu.append("Blond");
    darkness_menu.append("Light");
    darkness_menu.append("Medium");
    darkness_menu.append("Dark");
    darkness_menu.append("Extra_Dark");
    darkness.pack_start(darkness_menu);
    dialog->get_vbox()->pack_start(darkness);
    
    dialog->add_button("Cancel", 0);
    dialog->add_button("Next", 1);
    dialog->show_all();
    int result = dialog->run();
    
    std::string name_j=entry_name.get_text();
    std::string price_j=entry_price.get_text();
    std::string cost_j=entry_cost.get_text();
    int darkness_j=darkness_menu.get_active_row_number();
    
    if(result==1)
    {
        if(name_j.empty())
        {
            Dialogs::message("Name fiels is empty. Donut cannot be created.");
        }
        if(price_j.empty() || cost_j.empty())
        {
            Dialogs::message("Price/Cost field is empty. Donut cannot be created.");
        }
        else
        {
            try {
                //std::cout<<"gign\n";
                price_final=std::stod(price_j);
                //std::cout<<price_final<<"\n";
                cost_final=std::stod(cost_j);
                //std::cout<<cost_final;
                
                
            } catch (...) {
                
            }
        }
        if(price_final==0.0 || cost_final==0.0)
        {
            // std::cout<<"in loop";
            Dialogs::message("Invalid data in price/cost field. Donut cannot be created");
        }
        
        if(!name_j.empty() && !price_j.empty() && !cost_j.empty() && !(price_final==0.0) && !(cost_final==0.0) )
        {
            Java *java=new Java{name_j,price_final,cost_final,(Darkness)darkness_j};
            
            
            while(flag)
            {
                Gtk::Dialog shots;
                //shots.set_transient_for(this);
                shots.set_title("Add Shots");
                
                Gtk::ComboBoxText add_shots;
                add_shots.append("None");
                add_shots.append("Chocolate");
                add_shots.append("Vanilla");
                add_shots.append("Peppermint");
                add_shots.append("Hazlenut");
                shots.get_vbox()->pack_start(add_shots);
                
                shots.add_button("Cancel",0);
                shots.add_button("Create",1);
                shots.add_button("Add",2);
                
                shots.show_all();
                int result = shots.run();
                
                int shot_number=add_shots.get_active_row_number();
                
                if(result==2)
                {
                    java->add_shot((Shot)shot_number);
                    if(shot_number==0)
                    {
                        Dialogs::message("None of the shots are added");
                    }
                     if(shot_number==1)
                    {
                        Dialogs::message("Chocolate shot is added");
                    }
                    else if(shot_number==2)
                    {
                        Dialogs::message("Vanilla shot is added");
                    }
                    else if(shot_number==3)
                    {
                        Dialogs::message("Peppermint shot is added");
                    }
                    else if(shot_number==4)
                    {
                        Dialogs::message("Hazlenut shot is added");
                    }
                    
                    
                    flag=true;
                }
                
                if(result==1)
                {
                    _store.add_product(java);
                    msg->set_text("New java product \"" + name_j + "\" created"+"\t\t\t\t\t\t\t\t\t"+_store.get_cash_register());
                    flag=false;
                }
                
            }
            
            
        }
        
    }
    
    delete dialog;
    
}

//order creation

void Main_window::on_create_order_click()
{
    Order _order;
    
    bool flag=true;
    bool order_placed=false;
    std::string o="Order #"+std::to_string(order_counter);
    while(flag)
    {
        Gtk::Dialog *dialog=new Gtk::Dialog();
        dialog->set_title("create a order");
        dialog->set_transient_for(*this);
        
        
        
        Gtk::Label order_label{o};
        dialog->get_vbox()->pack_start(order_label);
        Gtk::HBox order;
        
        Gtk::Label label{"Product: "};
        order.pack_start(label);
        
        Gtk::ComboBoxText product_menu;
        
        int size=_store.number_of_products();
        
        for(int i=0;i<size;i++)
        {
            product_menu.append(_store.product_to_string(i));
        }
        order.pack_start(product_menu);
        
        dialog->get_vbox()->pack_start(order);
        dialog->add_button("Cancel",0);
        dialog->add_button("Add",1);
        dialog->add_button("Next",2);
        
        dialog->show_all();
        int result= dialog->run();
        
        int row=product_menu.get_active_row_number();
        //std::cout<<row;
        
        dialog->close();
        while (Gtk::Main::events_pending())  Gtk::Main::iteration();
        
        
        
        if(result==0)
        {
            //flag=false;
            break;
        }
        else if(result==1)
        {
                    _order.add_product(_store.get_vector(row));
                   // flag=true;
        }
        else if(result==2)
        {
            
            Gtk::Dialog *d=new Gtk::Dialog();
            d->set_transient_for(*this);
            d->set_title("Select Customer");
            
            Gtk::ComboBoxText customer_menu;
            int size=_store.number_of_customers();
            
            for(int i=0;i<size;i++)
            {
                customer_menu.append(_store.get_customer_string(i));
            }
            d->get_vbox()->pack_start(customer_menu);
            
            std::string place_order="Place Order "+std::to_string(order_counter);
            d->add_button("Cancel",0);
            d->add_button(place_order,1);
           
            
            
            d->show_all();
            int r=d->run();
            
            
            if(r==0)
            {
                flag=false;
                break;
            }
            else if(r==1)
            {
                int row_number= customer_menu.get_active_row_number();
                _store.place_order(_order,row_number);
                _store.add_order_to_vectors(_order);
                order_placed=true;
                
            }
            
            d->close();
            while (Gtk::Main::events_pending())  Gtk::Main::iteration();
            delete d;
            //flag=false;
            break;
        }
        else{
            break;
        }
         delete dialog;
    }
    if(order_placed)
    {
        //std::cout<<_store.order_to_string(order_counter);
        _order.add_order_number(order_counter);
         msg->set_text("Order " + std::to_string(order_counter) + " placed"+"\t\t\t\t"+_store.get_cash_register());
        order_counter++;
    }
    else{
        msg->set_text("Order " + std::to_string(order_counter) + " canceled"+"\t\t\t\t\t\t\t\t\t"+_store.get_cash_register());
        order_counter++;
    }
    
  
}


//create customer

void Main_window::on_new_customer_click()
{
    Gtk::Dialog *dialog=new Gtk::Dialog();
    dialog->set_title("Create a customer");
    dialog->set_transient_for(*this);
    
    Gtk::Label *label_1=new Gtk::Label("Name");
    dialog->get_content_area()->pack_start(*label_1);
    label_1->show();
    
    Gtk::Entry *entry_1= new Gtk::Entry();
    entry_1->set_max_length(50);
    //entry_1->set_text("abc");
    entry_1->show();
    dialog->get_vbox()->pack_start(*entry_1);
    
    Gtk::Label *label_2=new Gtk::Label("Phone Number");
    dialog->get_vbox()->pack_start(*label_2);
    label_2->show();
    
    Gtk::Entry *entry_2= new Gtk::Entry();
    entry_2->set_max_length(50);
    //entry_2->set_text("817-233-3456");
    entry_2->show();
    dialog->get_vbox()->pack_start(*entry_2);
    
    dialog->add_button("Cancel", 0);
    dialog->add_button("Create", 1);
    dialog->set_default_response(0);
    
    
    
    int result=dialog->run();
    std::string text_1=entry_1->get_text();
    //std::cout<<text_1;
    std::string text_2=entry_2->get_text();
    //std::cout<<text_2;
    
    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();
    
    delete label_1;
    delete entry_1;
    delete label_2;
    delete entry_2;
    
    
    if(result==1)
    {
        //std::cout<<"checking";
        std::regex phone{"((\\(\\d{3,3}\\))|(\\d{3,3}-))?\\d{3,3}-\\d{4,4}"};
        if(std::regex_match(text_2,phone))
        {
            //std::cout<<"correct";
            Customer *customer =new Customer{text_1,text_2};
            _store.add_customer(customer);
            msg->set_text("Created customer " + text_1+"\t\t\t\t\t\t\t\t\t"+_store.get_cash_register());
        }
        else{
            Dialogs::message("Wrong phone number format!");
            //exit(0);
        }
    }
    else
    {
        //std::cerr<<"error entering phone number";
    }
    delete dialog;
}

void Main_window::on_list_customers_click()
{
    Dialogs::message(_store.customer_to_string(_store.number_of_customers()),"List of customers");
}
void Main_window::on_view_all_click() {
    //_store.add_java();
    //_store.add_product((Product*)(Java{"Java",5.00,2.00,0}));
    //_store.product_to_string(0);
    
    Dialogs::message(_store.get_info());
}

void Main_window::on_view_order_click()
{
    bool flag=true;
    int number;
    while(flag)
    {
      Gtk::Dialog *dialog=new Gtk::Dialog();
        dialog->set_transient_for(*this);
        dialog->set_title("Select an order");
        
        Gtk::HBox order_menu;
        Gtk::Label label{"Order"};
        order_menu.pack_start(label);
        
        Gtk::ComboBoxText order;
        for(int i=0;i<order_counter;i++)
        {
            std::string a=std::to_string(i);
            order.append(a);
        }
        order_menu.pack_start(order);
        
        dialog->get_vbox()->pack_start(order_menu);
        
        dialog->add_button("Cancel",0);
        dialog->add_button("Show",1);
        
        dialog->show_all();
        int result=dialog->run();
        number=order.get_active_row_number();
        
        if(result==1)
        {
            std::string msg="Order #"+std::to_string(number)+'\n'+_store.order_to_string(number);
            Dialogs::message(msg,"Order Information");
            flag=true;
        }
        else
        {
           flag=false;
        }
        
        delete dialog;
    
    }
}

void  Main_window::on_fill_order_click()
{
    Gtk::Dialog *dialog=new Gtk::Dialog("Select an order to fill", *this);
    Gtk::HBox b_orders;
    
    Gtk::Label l_current;
    dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

    Gtk::Label l_orders{"Order:"};
    l_orders.set_width_chars(15);
    b_orders.pack_start(l_orders, Gtk::PACK_SHRINK);
    
    Gtk::ComboBoxText c_orders;
     for(int i=0;i<order_counter;i++) {
        c_orders.append(std::to_string(i));
    }
    b_orders.pack_start(c_orders, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_orders, Gtk::PACK_SHRINK);
    dialog->add_button("Close", 0);
    dialog->add_button("Show", 1);
    dialog->add_button("Fill", 2);
    dialog->show_all();
    
    while(true)
    {
        //std::cout<<"running";
        int result=dialog->run();
        
        //std::cout<<"running_1";
       if(result==1)
       {
           std::string a="Order#"+std::to_string(c_orders.get_active_row_number())+"\n"+_store.order_to_string(c_orders.get_active_row_number());
           Dialogs::message(a);
           break;
       }
        else if(result==2)
        {
            //std::cout<<"messgae clear";
            try {
                
                _store.fill_order(c_orders.get_active_row_number());
                 std::string b="Order#"+std::to_string(c_orders.get_active_row_number())+"\n"+_store.order_to_string(c_orders.get_active_row_number());
                l_current.set_text(b);
                 msg->set_text("Order " + std::to_string(c_orders.get_active_row_number()) + " filled"+"\t\t\t\t\t\t\t\t\t"+_store.get_cash_register());
            }
            //        catch(std::bad_alloc &ba)
            //        {
            //
            //        }
            catch(...)
            {
                Dialogs::message("not offering to fill an order that is already paid or that has been discarded");
            }
        }
        else
        {
            delete dialog; return;
        }
    }
    delete dialog;
}

void  Main_window::on_pay_order_click()
{
    Gtk::Dialog *dialog=new Gtk::Dialog("Select an order to pay", *this);
    Gtk::HBox b_orders;
    
    Gtk::Label l_current{"order"};
    dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);
    
    Gtk::Label l_orders{"Order:"};
    l_orders.set_width_chars(15);
    b_orders.pack_start(l_orders, Gtk::PACK_SHRINK);
    
    Gtk::ComboBoxText c_orders;
    for(int i=0;i<order_counter;i++) {
        c_orders.append(std::to_string(i));
    }
    b_orders.pack_start(c_orders, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_orders, Gtk::PACK_SHRINK);
    dialog->add_button("Close", 0);
    dialog->add_button("Show", 1);
    dialog->add_button("Pay", 2);
    dialog->show_all();
    
    while(true)
    {
        int result=dialog->run();
        if(result==1)
        {
            std::string a="Order#"+std::to_string(c_orders.get_active_row_number())+"\n"+_store.order_to_string(c_orders.get_active_row_number());
            Dialogs::message(a);
            break;
        }
        else
        if(result==2)
        {
           
            try {
                
                _store.pay_order(c_orders.get_active_row_number());
                std::string b="Order#"+std::to_string(c_orders.get_active_row_number())+"\n"+_store.order_to_string(c_orders.get_active_row_number());
                l_current.set_text(b);
                msg->set_text("Order " + std::to_string(c_orders.get_active_row_number()) + " paid"+"\t\t\t\t\t\t\t\t\t"+(_store.add_cash(c_orders.get_active_row_number())));

            }
            catch(...)
            {
                Dialogs::message("not offering to pay an order that is already paid or that has been discarded");
            }
        }
        else
        {
            delete dialog; return;
        }
    }
    delete dialog;
}

void  Main_window::on_discard_order_click()
{
    Gtk::Dialog *dialog=new Gtk::Dialog("Select an order to discard", *this);
    Gtk::HBox b_orders;
    
    Gtk::Label l_current{"order"};
    dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);
    
    Gtk::Label l_orders{"Order:"};
    l_orders.set_width_chars(15);
    b_orders.pack_start(l_orders, Gtk::PACK_SHRINK);
    
    Gtk::ComboBoxText c_orders;
    for(int i=0;i<order_counter;i++) {
        c_orders.append(std::to_string(i));
    }
    b_orders.pack_start(c_orders, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_orders, Gtk::PACK_SHRINK);
    dialog->add_button("Close", 0);
    //dialog->add_button("Show", 1);
    dialog->add_button("Discarded", 2);
    dialog->show_all();
    
//    while(true)
//    {
    int result=dialog->run();
//        if(result==1)
//        {
//            std::string a="Order#"+std::to_string(c_orders.get_active_row_number())+"\n"+_store.order_to_string(c_orders.get_active_row_number());
//            Dialogs::message(a);
//            break;
//        }
//        else
        if(result==2)
        {
            //std::cout<<"messgae clear";
            try {
                
                _store.discard_order(c_orders.get_active_row_number());
//                std::string b="Order#"+std::to_string(c_orders.get_active_row_number())+"\n"+_store.order_to_string(c_orders.get_active_row_number());
//                l_current.set_text(b);
                msg->set_text("Order " + std::to_string(c_orders.get_active_row_number()) + " discarded"+"\t\t\t\t\t\t\t\t\t"+(_store.add_cash(c_orders.get_active_row_number())));
                Dialogs::message("Order is discarded successfully");
            }
            
            catch(...)
            {
                Dialogs::message("Order is already discarded or completed");
            }
        }
        else
        {
            delete dialog; return;
        }
   // }
    delete dialog;
}

void Main_window::on_about_click() {
    Gtk::AboutDialog dialog{};
    //dialog.set_transient_for(*this);
    dialog.set_program_name("Java and Donut Express");
    auto logo = Gdk::Pixbuf::create_from_file("jade.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 0.2.0");
    dialog.set_copyright("Copyright 2018");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"Ruta Vaghasia"};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {"JADE logo is licensed the creative Commons Attribuition Share-Alike 3.0 License by Saxdeux Flat \n Coffee Icon is licensed under the Creative Common Attribution 3.0 License by Superawesomevectors \n Donut Icon is public by Hazmat2 via Hyju \n Person Icon is licensed under The Creative Commons 0 (public domain) License by Ciker-Free-Vector-Images"};
    dialog.set_artists(artists);
    dialog.run();
}





void Main_window::on_quit_click() {
    hide();
}

//void Main_window::on_about_click() {
//
//  v.help();
//  // Glib::ustring s = "<span size='24000' weight='bold'>Nim</span>\n<span size='large'>Copyright 2017 by George F. Rice</span>\n<span size='small'>Licensed under Creative Commons Attribution 4.0 International\nRobot icon created by Freepik, used under free attribution license</span>";
//  // Gtk::MessageDialog dlg(*this, s, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
//  //dlg.run();
//}

// /////////////////
// U T I L I T I E S
// /////////////////

//void Main_window::set_sticks() {
//    // s collects the status message
//    Glib::ustring s = "";
//
//    // If the robot is enabled and it's their turn, move the robot
//    if (nim->sticks_left() > 0) {
//        if (computer_player->get_active() && nim->current_player() == 2) {
//           s += "Robot plays " + std::to_string(nim->optimal_move()) + ", ";
//           nim->take_sticks(nim->optimal_move());
//        }
//    }
//
//    // Report who's turn it is, or (if all sticks gone) who won
//    if (nim->sticks_left() > 0) {
//        s += "Player " + std::to_string(nim->current_player()) + "'s turn";
//    } else {
//        s += "<span size='16000' weight='bold'>Player "
//              +  std::to_string(3-nim->current_player())
//              +  " wins!</span>";
//    }
//
//    // Display the collected status on the status bar
//    msg->set_markup(s);
//
//    // Update the visual display of sticks
//    s = "<span size='24000' weight='bold'>";
//    for(int i=0; i<nim->sticks_left(); ++i) s.append("| ");
//    s.append("</span>  (" + std::to_string(nim->sticks_left()) + " sticks)");
//    sticks->set_markup(s);
//
//    // Set sensitivity of the human stick selectors so user can't make an illegal move
//    button1->set_sensitive(nim->sticks_left() > 0);
//    button2->set_sensitive(nim->sticks_left() > 1);
//    button3->set_sensitive(nim->sticks_left() > 2);
//}

