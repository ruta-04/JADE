#ifndef __JAVA_H
#define __JAVA_H

#include "product.h"
#include <vector>
#include <iostream>

enum Shot {None, Chocolate,Vanilla,Peppermint,Halenut};
enum Darkness {Blond, Light, Medium, Dark, Extra_dark};
class Java:public Product
{
	protected:
		Darkness _darkness;
		std::vector<Shot> _shots;
	public:
		Java(std::string name, double price, double cost,Darkness darkness);
		void add_shot(Shot shot);
		std::string to_string() override;

		
};

#endif
