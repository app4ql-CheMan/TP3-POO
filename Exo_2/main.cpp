#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

template<class T> class observer_ptr;

template<typename T> 
class observable_ptr
{
	std::unique_ptr<T> membre;
	std::vector<std::reference_wrapper<observer_ptr<T>>> observers;
	
public:
	observable_ptr(std::unique_ptr<T> &&t) : membre(std::move(t))
	{
		
	}
	
	T * get()
	{
		return membre.get();
	}
	
	observable_ptr<T>& operator= (std::unique_ptr<T> && t)
	{
		membre = t;
		notify();
		return *this;
	}
	
	
	
	observable_ptr<T>& operator* ()
	{
		return *this;
	}
	
	void notify()
	{
		for(auto o : observers)
		{
			o.update();
		}
	}
	
	void add_observer(observer_ptr<T>& o)
	{
		observers.push_back(o);
	}
	
	void remove_observer(observer_ptr<T>& o)
	{
		observers.erase(std::find_if(observers.begin(),observers.end(),[&](auto & e)->bool{ return &o == &*e; }));
	}
};

template<typename T> 
std::ostream& operator<<(std::ostream & os, observable_ptr<T> &t)
{
	os << *t.get();
	return os;
}

template<typename T> 
std::ostream& operator<<(std::ostream & os, observer_ptr<T> &t)
{
	os << *t.get();
	return os;
}
	
template<typename T> 
class observer_ptr
{
	T* membre;
	//hopp::view_ptr<observable_ptr<T>> p;
	observable_ptr<T> *p;
	
public:
	observer_ptr(observable_ptr<T> &o)
	{
		p = &o;
		p->add_observer(*this);
	}
	
	observer_ptr<T>& operator* ()
	{
		return *this;
	}
	
	observer_ptr<T>& operator= (T && t)
	{
		membre = &t;
		return *this;
	}
	
	T* get()
	{
		return membre;
	}
	
	void update()
	{
		membre = p.get();
	}
};

int main() {
observable_ptr<int> p0 = std::make_unique<int>(7);

observer_ptr<int> v0(p0); // add_observer
observer_ptr<int> v1(p0); // add_observer

std::cout << "p0 = " << p0 << std::endl; // p0 = 7
std::cout << "v0 = " << v0 << std::endl; // v0 = 7
std::cout << "v1 = " << v1 << std::endl; // v1 = 7
*v1 = 42;
std::cout << "p0 = " << p0 << std::endl; // p0 = 42
std::cout << "v0 = " << v0 << std::endl; // v0 = 42
std::cout << "v1 = " << v1 << std::endl; // v1 = 42
}
