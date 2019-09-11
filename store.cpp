#include "store.h"
#include <sstream>
#include <iomanip>
Store::Store(std::string store_name):_name{store_name},_cash_register{1000}{}
Store::~Store() { }

std::string Store::name()
{
	return _name;
}

void Store::add_product(Product *product)
{
	_products.push_back(product);
    //std::cout<<"product successful";
}

int Store::number_of_products()
{
	return _products.size();
}

std::string Store:: product_to_string(int product)
{	
	std::string s;
	s = _products[product]->to_string();
    return s;
}
std::string Store::get_info()
{
    int i=0;
    std::string str;
    for(i=0;i<number_of_products();i++)
    {
        str=str+product_to_string(i);
    }
    std::string full= _name+"\n\n"+"Products: \n\n"+str;
    return full;


}
//std::ostream& operator<<(std::ostream& ost, Store& store) {
//    ost << "Store " << store._name << std::endl << std::endl;
//    ost << "Products: " << std::endl;
//    for (auto p : store._products) ost << "  " << p->to_string() << std::endl;
//    return ost;
//}

void Store::add_customer(Customer *customer)
{
  _customers.push_back(customer);
}

int Store::number_of_customers()
{
  return _customers.size();
}

std::string Store::customer_to_string(int customer)
{
    std::ostringstream oss;
    for(int i=0;i<customer;i++)
    {
      oss<<*_customers[i]<<"\n";
    }
  return oss.str();
}

void Store:: place_order(Order order, int customer)
{
    _orders[order]=_customers[customer];
}

int Store::number_of_orders()
{
    return _orders.size();
}

void Store::add_order_to_vectors(Order order)
{
    _order_numbers.push_back(order);
}
std::string Store::order_to_string(int order_number)
{
    std::string data="\n";
    //std::cout<<_orders[_order_numbers[order_number]]->to_string();
    data+=status(order_number)+"\n"+ _order_numbers[order_number].get_products()+"\n"+_orders[_order_numbers[order_number]]->to_string();
    return data;
}

Product* Store::get_vector(int number)
{
    return _products[number];
}

std::string Store::get_customer_string(int number)
{
    return _customers[number]->to_string();
}

void Store::fill_order(int order_number)
{
    _order_numbers[order_number].fill();
}
bool Store::order_is_filled(int order_number)
{
    return _order_numbers[order_number].filled();
}

void Store::pay_order(int order_number)
{
    _order_numbers[order_number].pay();
}
bool Store::order_is_paid(int order_number)
{
    return _order_numbers[order_number].paid();
}

bool Store::order_is_pending(int order_number)
{
    return _order_numbers[order_number].pending();
}

void Store::discard_order(int order_number)
{
    _order_numbers[order_number].discard();
}

bool Store::order_is_discarded(int order_number)
{
    return _order_numbers[order_number].discarded();
}

bool Store::order_is_completed(int order_number)
{
    return _order_numbers[order_number].completed();
}


//CASH REGISTER

std::string Store::get_cash_register()
{
    std::ostringstream oss;
    oss<<std::fixed << std::setprecision(2) << " $" <<_cash_register;
    return oss.str();
}

std::string Store::add_cash(int order_number)
{
    double total=0;
    if(order_is_paid(order_number))
    {
        total+=_order_numbers[order_number].profit();
    }
    
    if(order_is_paid(order_number) && order_is_discarded(order_number) )
    {
        _cash_register-=total;
    std::ostringstream oss;
    oss<<std::fixed << std::setprecision(2) << " $" <<_cash_register;
    return oss.str();
    }
    else{
        
        _cash_register+=total;
        std::ostringstream oss;
        oss<<std::fixed << std::setprecision(2) << " $" <<_cash_register;
        return oss.str();
    }
}

std::string Store::status(int order_number)
{
    if(order_is_discarded(order_number))
    {
        return "(DISCARDED)";
    }
    else if(order_is_completed(order_number))
    {
        return "(COMPLETED)";
    }
    else if(order_is_paid(order_number))
    {
        return "(PAID)";
    }

    else if(order_is_filled(order_number))
    {
        return "(FILLED)";
    }
    else if(order_is_pending(order_number))
    {
        return "(PENDING)";
    }
    else{
        return " ";
    }
}
