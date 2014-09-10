#include <list>
#include "Visitor.h"

template <class T>
class Property
{
public:
	Property(T value)
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

	list<Visitor*>::iterator subscribe(Visitor* visitor)
	{
		visitors_.push_front(visitor);

		return visitors_.begin();
	}

	void unsubscribe(list<Visitor*>::iterator id)
	{
		visitors_.erase(id);
	}
private:
	void update_() {
		for (auto it = visitors_.begin(); it != visitors.end(); it++) {
			(it*)->call();
		}
	}
	T value_;
	list<Visitor*> visitors_;
};
