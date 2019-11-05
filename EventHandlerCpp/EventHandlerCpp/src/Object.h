#pragma once

#include "Events/PropertyDescriptor.h"

namespace EventHandlerCpp
{
	class Object : public IPropertyChanged, public IPropertyChanging
	{
		PropertyChangedEventHandler _propertyChanged;

	public:
		PropertyChangedEventHandler& GetPropertyChangedEvent() { return _propertyChanged; }

	protected:
		virtual void OnPropertyChanged(const PropertyDescriptor* pd) override
		{
			const auto& handlers = _propertyChanged.GetHandlers();
			for (uint32_t i = 0; i < handlers.size(); i++)
			{
				auto args = PropertyChangedEventArgs(pd);
				handlers[i](this, &args);
			}
		}

		virtual void OnPropertyChanging(const PropertyDescriptor* pd) override
		{

		}
	};
}
