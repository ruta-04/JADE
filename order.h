#ifndef __ORDER_H
#define __ORDER_H
#include <iostream>
#include <vector>
#include "product.h"
class Order
{
	private:
		std::vector<Product*> _products;
		int _next_order_number;
		int _order_number;
    bool _is_paid;
    bool _is_filled;
    bool _is_discarded;
	public:
    void add_order_number(int order_number);
		Order();
    ~Order();
		int order_number();
		void add_product(Product* product);
        std::string get_products();
    bool paid() ;
    void pay();
    bool filled();
    void fill();
    bool discarded();
    void discard();
    bool completed();
    bool pending();
    double profit();
    friend bool operator<(const Order& lhs, const Order& rhs);
};
#endif
