#ifndef VISITOR_DYGA_H
#define VISITOR_DYGA_H

template<class T>
class Property;

template<class T>
class Visitor
{
public:
	virtual ~Visitor() {}
	virtual void call(Property<T>*) = 0;
};

#endif // VISITOR_DYGA_H
