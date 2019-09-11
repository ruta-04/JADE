#include "product.h"
#include <iomanip>
#include <iostream>

#include <sstream>

Product::Product(std::string name,double price, double cost):_name{name},_price{price},_cost{cost}{}

std::string Product::name()
{
	return _name;
}

std::string Product::to_string()
{
    
    //auto p=std::to_string(_price);
  //auto c=std::to_string(_cost);
    std::ostringstream oss;
    
    oss<< _name<<" ($"<<std::setprecision(2)<<std::fixed<<_price<<" / $"<<_cost<<" )";
    
  return oss.str();
  
}

double Product::profit()
{
    return _price-_cost;
}
