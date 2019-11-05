#include "../src/Object.h"
#include "../src/Events/PropertyDescriptor.h"

#include <iostream>

using namespace EventHandlerCpp;

class Person : public Object
{
	std::string _name;
	int _age;

public:
	Person() : Object(), _age(0) {}

	int GetAge() { return _age; }
	void SetAge(int age) {
		_age = age;
		OnPropertyChanged(&AgePD);
	}

private:
	static const ValuePropertyDescriptor AgePD;
};

const ValuePropertyDescriptor Person::AgePD
{
	L"Age",
	L"",
	static_cast<ValuePropertyDescriptor::Setter>(&SetAge),
	static_cast<ValuePropertyDescriptor::Getter>(&GetAge)
};

int main(void)
{
	std::cout << "Hello World!\n";

	Person person;
	person.GetPropertyChangedEvent().AddHandler([](Object* sender, PropertyChangedEventArgs* args)
	{
		const ValuePropertyDescriptor* PD = static_cast<const ValuePropertyDescriptor*>(args->GetPD());
		auto person = static_cast<Person*>(sender);
		auto value = (person->*(PD->_getValue))();
		std::cout << "Hello property changed!\n";
	});

	person.SetAge(10);

	std::cin.get();
	
	return 0;
}