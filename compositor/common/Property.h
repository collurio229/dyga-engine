#ifndef PROPERTY_DYGA_H
#define PROPERTY_DYGA_H

#include <iostream>
#include <list>
#include "Visitor.h"

template <class T>
class Property
{
public:
	typedef typename std::list<Visitor<T>*>::iterator visitor_iterator;

	Property(T value, std::string id_ = "")
		: value_(value) {}
	~Property() {}

	void set(T new_val)
	{
		value_ = new_val;

		update_();
	}

	T get()
	{
		return value_;
	}

	std::string getId()
	{
		return id_;
	}

	visitor_iterator subscribe(Visitor<T>* visitor)
	{
		visitors_.push_front(visitor);

		return visitors_.begin();
	}

	void unsubscribe(visitor_iterator id)
	{
		visitors_.erase(id);
	}
private:
	void update_() {
		for (auto it = visitors_.begin(); it != visitors_.end(); it++) {
			(*it)->call(this);
		}
	}
	T value_;
	std::list<Visitor<T>*> visitors_;
	std::string id_;
};

#endif // PROPERTY_DYGA_H
