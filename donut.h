#ifndef __DONUT_H
#define __DONUT_H

#include "product.h"
#include <iostream>

enum Frosting {Unfrosted, Chocolate_top, Vanilla_top, Pink_top};

enum Filling {Unfilled, Creme, Bavarian, Strawberry};

class Donut:public Product
{
	protected:
		bool _sprinkles;
		Frosting _frosting;
		Filling _filling;
	public:
		Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling);
		std::string to_string() override;
};
#endif


