#ifndef DISPLAYT_HPP
#define DISPLAYT_HPP

#include <iostream>

#include "visiteur.hpp"

class expression_t;
class constant_t;
class operator_t;
class variable_t;

class display_t : public Visiteur
{
	public:
	

	void visit(constant_t &c);
	
	void visit(operator_t &o);
	
	void visit(variable_t &v);

};

#endif
