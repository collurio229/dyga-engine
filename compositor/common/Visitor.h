#ifndef VISITOR_DYGA_H
#define VISITOR_DYGA_H

template<class T>
class Property;

/*
 * Basic Interface for Visitor classes.
 * The Visitor interface is used to subscribe to a Property.
 * If the Property changes, it calls the call method of all subscribed Visitors.
 */
template<class T>
class Visitor
{
public:
	virtual ~Visitor() {}
	virtual void call(Property<T>* prop) = 0;
};

#endif // VISITOR_DYGA_H
