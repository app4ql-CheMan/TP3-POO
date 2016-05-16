// Copyright © 2016 Université Paris-Sud, Written by Lénaïc Bagnères, lenaic.bagneres@u-psud.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "hopp/conversion/is_integer.hpp"
#include "visitable.hpp"
#include "display_t.hpp"
#include "eval_t.hpp"

// Expression

class expression_t_
{
public:
	
	virtual ~expression_t_() = default;
	
	virtual void display(std::ostream & out = std::cout) const = 0;
	
	virtual double eval() const = 0;
		
	virtual void accept(display_t &d)=0;
	
	virtual double accept(eval_t &d)=0;
};

inline
std::ostream & operator <<(std::ostream & out, expression_t_ const & expression)
{
	expression.display(out);
	return out;
}

// Expression (do not care about virtual & co)

class expression_t : public expression_t_
{
public:
	
	std::unique_ptr<expression_t_> expression;
	
public:
	
	expression_t() = default;
	
	template <class T> // T is an expression_t_
	expression_t(std::unique_ptr<T> && p) : expression(std::move(p)) { }
	
	template <class T> // T is an expression_t_
	expression_t(T && t) : expression(std::make_unique<T>(std::move(t))) { }
	
	expression_t release() { return std::unique_ptr<expression_t_>(expression.release()); }
	
	expression_t_ * get() { return expression.get(); }
	
	expression_t_ const * get() const { return expression.get(); }
	
	expression_t_ & operator *() { return *get(); }
	
	expression_t_ const & operator *() const { return *get(); }
	
	bool is_null() const { return expression == nullptr; }
	
	virtual void display(std::ostream & out = std::cout) const
	{
		if (expression) { expression->display(out); }
	}
	
	virtual double eval() const
	{
		if (expression) { return expression->eval(); }
		else { return 0.0; } // we can throw
	}
	
	void accept(display_t &d)
	{
		if (expression) { expression->accept(d); }
		
	}
	double accept(eval_t &d)
	{
		if (expression) { return expression->accept(d); }
		
	}
};


// Constant

class constant_t : public expression_t_
{
public:
	
	double value;
	
public:
	
	constant_t(int const value) : value(value) { }
	
	virtual void display(std::ostream & out = std::cout) const
	{
		out << value;
	}
	
	virtual double eval() const
	{
		return value;
	}
	
	void accept(display_t &d)
	{
		d.visit(*this);
	}
	double accept(eval_t &d)
	{
		d.visiteval(*this);
	}
};


// Variable

class variable_t : public expression_t_
{
public:
	
	std::string name;
	
	double value;
	
public:
	
	variable_t(std::string const & name, int const value) : name(name), value(value) { }
	
	virtual void display(std::ostream & out = std::cout) const
	{
		out << name;
	}
	virtual double eval() const
	{
		return value;
	}
	void accept(display_t &d)
	{
		d.visit(*this);
	}
	double accept(eval_t &d)
	{
		d.visiteval(*this);
	}
};


// Operator

class operator_t : public expression_t_
{
public:
	
	char symbol; // Operator
	
	expression_t a; // left
	
	expression_t b; // right
	
public:
	
	operator_t(char const symbol, expression_t && a, expression_t && b) :
		symbol(symbol), a(std::move(a)), b(std::move(b)) { }
	
	virtual void display(std::ostream & out = std::cout) const
	{
		out << "(";
		a.display();
		out << " " << symbol << " ";
		b.display();
		out << ")";
	}
	
	virtual double eval() const
	{
		if (symbol == '+') { return a.eval() + b.eval(); }
		if (symbol == '-') { return a.eval() - b.eval(); }
		if (symbol == '*') { return a.eval() * b.eval(); }
		if (symbol == '/') { return a.eval() / b.eval(); }
		if (symbol == '=') { return b.eval(); }
		return 0.0; // we can throw
	}
	
	void accept(display_t &d)
	{
		d.visit(*this);
	}
	double accept(eval_t &d)
	{
		d.visiteval(*this);
	}
};


void display_t::visit(operator_t &e)
{
		std::cout << "(";
		e.a.accept(*this);
		std::cout  << " " << e.symbol << " " ;
		e.b.accept(*this);
		std::cout  << ")";
}
void display_t::visit(variable_t &e)
{
		std::cout << e.name;
}
void display_t::visit(constant_t &e)
{
		std::cout << e.value;
}
		
		
/* eval_t  */
double eval_t::visiteval(operator_t &o){
	
		if (o.symbol == '+') { return o.a.accept(*this) + o.b.accept(*this);}
		if (o.symbol == '-') {return o.a.accept(*this) - o.b.accept(*this);}
		if (o.symbol == '*') {return o.a.accept(*this) * o.b.accept(*this);}
		if (o.symbol == '/') {return o.a.accept(*this) / o.b.accept(*this);}
		if (o.symbol == '=') {  return 0;}
		
		
}
double eval_t::visiteval(variable_t &o){
		
		return o.value;
		
}
double eval_t::visiteval(constant_t &o){
		
		return o.value;
}

eval_t::eval_t(std::vector<expression_t_> &v){
		for(auto & expression : v){
			expression.accept(*this);
		}
	}


#endif
