#ifndef __STORE_H
#define __STORE_H
#include "order.h"
#include "product.h"
#include "java.h"
#include "customer.h"
#include "donut.h"
#include <iostream>
#include <vector>
#include <map>
class Store
{
	private:
		std::string _name;
    double _cash_register;
		std::vector<Product*>  _products;
		std::vector<Customer*> _customers;
        std::map<Order,Customer*> _orders;
        std::vector<Order> _order_numbers;
  
	public:
		Store(std::string store_name);
    ~Store();
		std::string name();
		void add_product(Product *product);
    		std::string get_info();
        	friend std::ostream &operator<<(std::ostream &ost, Store& store);
		int number_of_products();
		std::string product_to_string(int product);

	//sprint 2
		void add_customer(Customer *customer);
		int number_of_customers();
		std::string customer_to_string(int Customer);
		
    //sprint 3
        void  place_order(Order order, int customer);
        int number_of_orders();
    void add_order_to_vectors(Order order);
        std::string order_to_string(int order_number);
    
    //sprint 4
    void pay_order(int order_number);
    bool order_is_paid(int order_number);
    void fill_order(int order_number);
    bool order_is_filled(int order_number);
    void discard_order(int order_number);
    bool order_is_discarded(int order_number);
    bool order_is_completed(int order_number);
    bool order_is_pending(int order_number);
    std::string status(int order_number);
    std::string get_cash_register();
    std::string add_cash(int order_number);
    //extra
    Product* get_vector(int number);
    std::string get_customer_string(int number);
    
};

#endif

