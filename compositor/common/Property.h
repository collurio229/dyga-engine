#ifndef PROPERTY_DYGA_H
#define PROPERTY_DYGA_H

#include <iostream>
#include <list>
#include "Visitor.h"

template <class T>
class Property
{
public:
	Property(T value, String id_ = "")
		: value_(value) {}
	Property~() {}

	void set(T new_val)
	{
		value_ = new_val;

		update_();
	}

	T get()
	{
		return value_;
	}

	String getId()
	{
		return id_;
	}

	list<Visitor<T>*>::iterator subscribe(Visitor<T>* visitor)
	{
		visitors_.push_front(visitor);

		return visitors_.begin();
	}

	void unsubscribe(list<Visitor<T>*>::iterator id)
	{
		visitors_.erase(id);
	}
private:
	void update_() {
		for (auto it = visitors_.begin(); it != visitors.end(); it++) {
			(it*)->call(this);
		}
	}
	T value_;
	list<Visitor<T>*> visitors_;
	String id_;
};

#endif // PROPERTY_DYGA_H
