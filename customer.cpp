#include "customer.h"

Customer::Customer(std::string customer,std::string customer_phone):_customer{customer},_customer_phone{customer_phone} {}

Customer::Customer() {}

std::string Customer::to_string()
{
	return _customer+",  "+_customer_phone;
}

std::ostream& operator<< (std::ostream& ost, Customer &customer)
{
	ost<< customer.to_string();
	return ost;
}
