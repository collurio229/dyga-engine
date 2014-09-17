#ifndef PROPERTY_DYGA_H
#define PROPERTY_DYGA_H

#include <iostream>
#include <list>
#include "Visitor.h"

/*
 * The Property class acts as a smart type of Variables, which can
 * inform other classes, namely those derived from Visitor,
 * if the Property's value has changed.
 *
 * The Property class will be used as the main communication tool
 * between the single Game Engine Modules.
 */
template <class T>
class Property
{
public:
	/*
	 * List iterator acts as id for subscribed Visitors,
	 * which they can use to unsubscribe themself
	 */
	typedef typename std::list<Visitor<T>*>::iterator Visitor_ID;

	/*
	 * Constructor assigning the value and the ID of the Property.
	 * The ID should be used, if a Visitor subscribes to more than one
	 * Property of the same type, to distinguish between those
	 */
	Property(T value, std::string id = "")
		: value_(value) {}

	/*
	 * Destructor.
	 */
	~Property() {}

	/*
	 * The Override of the assignment operator allows code like
	 * Property<int> prop(0, "foobar");
	 * prop = 24;
	 *
	 * It is especially handy if the Property is a public member Variable
	 * of a class, because it circumvents code like class.property.set(foo).
	 */
	Property& operator= (const T to_assign)
	{
		this->set(to_assign);

		return *this;
	}

	/*
	 * Sets a new value and calls als subscribed Visitors.
	 */
	void set(T new_val)
	{
		value_ = new_val;

		update_();
	}

	/*
	 * Returns saved value.
	 */
	T get()
	{
		return value_;
	}

	/*
	 * Returns the Property ID.
	 */
	std::string getId()
	{
		return id_;
	}

	/*
	 * Subscribes a Visitor of the same type to the property.
	 * The returned Visitor_ID can be used to unsubscribe again.
	 */
	Visitor_ID subscribe(Visitor<T>* visitor)
	{
		visitors_.push_front(visitor);

		return visitors_.begin();
	}

	/*
	 * Unsubscribe Visitor from the Property.
	 * The method simply erases the list element represented from the Visitor_ID iterator.
	 */
	void unsubscribe(Visitor_ID id)
	{
		// All other iterators aren't changed from deleting an element from the list
		visitors_.erase(id);
	}

	/*
	 * Used to notify all subscribed Visitors from a change in the Property.
	 * Calls the call method of all Visitors.
	 */
	void update_() {
		for (auto it = visitors_.begin(); it != visitors_.end(); it++) {
			(*it)->call(this);
		}
	}

private:
	T value_;
	std::list<Visitor<T>*> visitors_;
	std::string id_;
};

#endif // PROPERTY_DYGA_H
