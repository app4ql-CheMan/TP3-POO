#ifndef EVALT_HPP
#define EVALT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "expression.hpp"
#include "make_factory.hpp"
#include "visiteur.hpp"
#include "Visiteureval.hpp"

class expression_t;
class expression_t_;
class constant_t;
class operator_t;
class variable_t;

class eval_t:  public Visiteureval
{
	public :
	
	std::map<std::string,double> vars;
	
	public:
	
	eval_t(std::vector<expression_t_> &v);
	
	double visiteval(constant_t &c);
	
	double visiteval(operator_t &o);
	
	double visiteval(variable_t &v);

};
	
#endif

