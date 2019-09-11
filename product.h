#ifndef __PRODUCT_H
#define __PRODUCT_H
#include <iostream>

class Product
{
	protected:
		std::string _name;
		double _price;
		double _cost;
	public:
		Product(std::string name,double price, double cost);
		std::string name();
        double profit();
		virtual std::string to_string();
		
};
#endif
