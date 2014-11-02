#include "Property.hpp"
#include "Visitor.hpp"

#include "gtest/gtest.h"

namespace {

class SuccessVisitor : public Visitor<int>
{
public:
	SuccessVisitor() {};
	virtual ~SuccessVisitor() {};

	void call(Property<int>* prop) {
		success = true;
	}

	bool success = false;
};

class FailVisitor : public Visitor<int>
{
public:
	FailVisitor() {};
	virtual ~FailVisitor() {};

	void call(Property<int>* prop) {
		FAIL() << "This Visitor shouldn't have been called!";
	}
};

// The fixture for testing class Foo.
class PropertyVisitorTest : public ::testing::Test
{
protected:
	PropertyVisitorTest()
		: prop0(0, "Property 0"),
		  prop1(1, "Property 1"),
		  prop2(2, "Property 2")
	{
	}

	Property<int> prop0;
	Property<int> prop1;
	Property<int> prop2;
	SuccessVisitor success0;
	SuccessVisitor success1;
	FailVisitor fail0;
};

TEST_F(PropertyVisitorTest, AssignmentAndRetrieval) {

	ASSERT_EQ(prop2.get(), 2);

	int val = prop1;
	ASSERT_EQ(val, 1);

	prop0.set(42);
	ASSERT_EQ(prop0.get(), 42);

	prop1 = 1337;
	ASSERT_EQ(prop1.get(), 1337);
}

TEST_F(PropertyVisitorTest, Subscription) {
	prop0.subscribe(&success0);
	prop0 = 10;
	
	ASSERT_TRUE(success0.success) << "The Visitor wasn't called!";

	prop1.subscribe(&success0);
	prop1.subscribe(&success1);
	prop1 = 42;
	ASSERT_TRUE(success0.success) << "The first Visitor wasn't called!";
	ASSERT_TRUE(success1.success) << "The second Visitor wasn't called!";

	Property<int>::Visitor_ID id = prop2.subscribe(&fail0);
	prop2.unsubscribe(id);
	prop2 = 1337;
}

}  // namespace
