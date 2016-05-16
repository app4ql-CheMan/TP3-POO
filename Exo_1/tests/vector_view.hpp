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

#ifndef VECTOR_VIEW_HPP
#define VECTOR_VIEW_HPP

#include <iostream>
#include <vector>

#include <hopp/memory/view_ptr.hpp>


// NOTE: T is a container like std::vector http://en.cppreference.com/w/cpp/container/vector
template <class T>
class vector_view
{
public:
	
	// NOTE: Public types like std::vector
	
	/// Value type
	using value_type = typename T::value_type;
	
	/// Const reference type
	using const_reference = typename T::const_reference;
	
	/// Reference type
	using reference = typename T::reference;
	
	/// Const pointer type
	using const_pointer = typename T::const_pointer;
	
	/// Pointer type
	using pointer = typename T::pointer;
	
	/// Const iterator type
	using const_iterator = typename T::const_iterator;
	
	/// Iterator type
	using iterator = typename T::iterator;
	
	/// Const reverse iterator type
	using const_reverse_iterator = typename T::const_reverse_iterator;
	
	/// Reverse iterator type
	using reverse_iterator = typename T::reverse_iterator;
	
	/// Difference type
	using difference_type = typename T::difference_type;
	
	/// Size type
	using size_type = typename T::size_type;
	
private:
	
	// NOTE: is like T * with the following semantic: hopp::view_ptr<T> does not manage memory
	hopp::view_ptr<T> p_vector; //
	
	size_t m_begin;
	
	size_t m_end;
	
public:
	
	// Default constructor
	vector_view() : p_vector(nullptr), m_begin(0), m_end(0) { }
	
	// Constructor from T
	vector_view(T & vector, size_t const i_begin, size_t const i_end) :
		p_vector(vector), m_begin(i_begin), m_end(i_end)
	{ }
	
	// TODO: member function size() const
	//taille = fin - début
	size_type size() const
	{
		return (m_end - m_begin);
	}
	
	// TODO: member operator [](size_t const) const
	//lecture
	const_reference operator[](size_type i) const
	{
		return (*p_vector)[i+m_begin];
	}
	
	// TODO: member operator [](size_t const)
	//affectation
	reference operator[](size_type i)
	{
		return (*p_vector)[i+m_begin];
	}
	
	// TODO: member function begin() const
	//itérateur de début = début + (iterator)(début vue)
	const_iterator begin() const
	{
		return (*p_vector).begin() + std::ptrdiff_t(m_begin);
	}
	
	// TODO: member function begin()
	//itérateur de début = début + (iterator)(début vue)
	iterator begin()
	{
		return (*p_vector).begin() + std::ptrdiff_t(m_begin);
	}
	
	// TODO: member function end() const
	//itérateur de fin = début + (iterator)(taille)
	const_iterator end() const
	{
		return this->begin() + std::ptrdiff_t(m_end-m_begin);
	}
	
	// TODO: member function end()
	//itérateur de fin = début + (iterator)(taille)
	iterator end()
	{
		return  this->begin() + std::ptrdiff_t(m_end-m_begin);
	}
};

// Operator << between a std::ostream and a vector_view<T>
template <class T>
std::ostream & operator <<(std::ostream & out, vector_view<T> const & vector_view)
{
	/// TODO
	out << "{ ";
	for(auto it=vector_view.begin();it!=vector_view.end();++it)
	{
		if(it != vector_view.end() - std::ptrdiff_t(1)) out << *it << ", "; 
		else out << *it << " "; //avant dernier : on affiche pas la virgule
	}
	out << "}";
	return out;
}

// make_view (it is convenient to let the compiler determine vector_view<T> type)
template <class T>
vector_view<T> make_view(T & vector, size_t const i_begin, size_t const i_end)
{
	return vector_view<T>(vector, i_begin, i_end);
}

#endif
