#include "order.h"

Order::Order():_is_paid{false}, _is_filled{false},_is_discarded{false} {}
Order::~Order(){}

void Order::add_product(Product* product)
{
	_products.push_back(product);
}


bool Order::pending()
{
    if(_is_paid==false && _is_filled==false && _is_discarded==false)
    {
        return true;
    }
    else{
        return false;
    }
}

bool Order::completed()
{
    if(_is_paid==true && _is_filled==true)
    {
        return true;
    }
    else{
        return false;
    }
}

bool Order::paid()
{
    return _is_paid;
}
void Order::pay()
{
   
        if(_is_paid==false && _is_discarded==false)
        {
            _is_paid = true;
        }
        else{
            throw std::runtime_error{" "};
        }
   
}

bool Order::filled()
{
    return _is_filled;
    
}
void Order::fill()
{
    if(_is_filled==false && _is_discarded==false )
    {
        _is_filled = true;
        std::cout<<"filled";
    }
    else{
        throw std::runtime_error{" "};
    }
    
}

bool Order::discarded()
{
    return _is_discarded;
}

void Order::discard()
{
    bool flag=completed();
    if(_is_discarded==false && flag==false)
    {
        _is_discarded=true;
    }
    else{
        throw std::runtime_error{" "};
    }
}



int Order::order_number()
{
	return _next_order_number;
}

void Order::add_order_number(int order_number)
{
    _order_number=order_number;
}
std::string Order::get_products()
{
    std::string products;
    for(auto e:_products)
    {
        products+=e->to_string();
    }
    return products;
}


///PROFIT

double Order::profit()
{
    double total=0.0;
    for(auto e:_products)
    {
        total+=e->profit();
    }
    return total;
}



bool operator<(const Order& lhs, const Order& rhs)
{
    return lhs._order_number<rhs._order_number;
}
