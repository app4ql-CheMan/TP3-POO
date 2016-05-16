#ifndef VISITEUREVAL_HPP
#define VISITEUREVAL_HPP

class operator_t;
class constant_t;
class variable_t;



class Visiteureval
{
  public:
    
    virtual double visiteval(operator_t &) = 0;
    virtual double visiteval(variable_t &) = 0;
    virtual double visiteval(constant_t &) = 0;
 
};

#endif
