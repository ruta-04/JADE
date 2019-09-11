#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#include <iostream>
class Customer
{	
	private:
		std::string _customer;
		std::string _customer_phone;
	public:
		Customer(std::string customer,std::string customer_phone);
		Customer();
		std::string to_string(); 
		friend std::ostream& operator<< (std::ostream& ost, Customer &customer);
};

#endif

