#pragma once

#include "Event.h"
#include <vector>

namespace EventHandlerCpp
{
	class Object;

	struct PropertyDescriptor
	{
		const wchar_t* const _name;
		const wchar_t* const _description;

	protected:
		PropertyDescriptor(const wchar_t* name, const wchar_t* description)
			: _name(name), _description(description)
		{}
	};

	class PropertyChangedEventArgs : public EventArgs
	{
		const PropertyDescriptor* _propertyDescriptor;

	public:
		PropertyChangedEventArgs(const PropertyDescriptor* pd)
			: _propertyDescriptor(pd) {}

		const PropertyDescriptor* GetPD() const { return _propertyDescriptor; }
	};

	struct ValuePropertyDescriptor : public PropertyDescriptor
	{
		using base = PropertyDescriptor;

		typedef void(Object::*Setter)(int value);
		typedef int(Object::*Getter)(void);

		Setter const _setValue;
		Getter const _getValue;

		ValuePropertyDescriptor(const wchar_t* name, const wchar_t* description, Setter setValue, Getter getValue)
			: base(name, description), _setValue(setValue), _getValue(getValue)
		{
		}
	};

	class IPropertyChanged
	{
		virtual void OnPropertyChanged(const PropertyDescriptor* pd) = 0;
	};

	class IPropertyChanging
	{
		virtual void OnPropertyChanging(const PropertyDescriptor* pd) = 0;
	};

	typedef void(*PropertyChangedHandler)(Object* sender, PropertyChangedEventArgs* args);


	class PropertyChangedEventHandler
	{
		std::vector<PropertyChangedHandler> _handlers;

	public:
		void AddHandler(PropertyChangedHandler handler)
		{
			_handlers.push_back(handler);
		}

		const std::vector<PropertyChangedHandler>& GetHandlers() const { return _handlers; }
	};

}