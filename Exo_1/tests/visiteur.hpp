#ifndef VISITEUR_HPP
#define VISITEUR_HPP

class operator_t;
class constant_t;
class variable_t;



class Visiteur
{
  public:

    virtual void visit(operator_t &) = 0;
    virtual void visit(variable_t &) = 0;
    virtual void visit(constant_t &) = 0;

 
};

#endif
