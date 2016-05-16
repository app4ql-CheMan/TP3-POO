#ifndef VISITABLE_HPP
#define VISITABLE_HPP

class Visiteur;

class Visitable{
  public:
   virtual void accept(Visiteur &v) = 0;
};

#endif
