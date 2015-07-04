#pragma once

#include "../PropertyWrapper.h"
#include "PropertyType.h"
#include <Utils/MapUtils.h>
#include <map>
#include <vector>
#include <string>

class PropertyContainer
{
private:
	struct Property
	{
	public:
		Property(
			const std::string& name,
			PropertyType type,
			PropertyWrapperBase* propertyWrapper) :
			m_name(name),
			m_type(type),
			m_propertyWrapper(propertyWrapper) {}

		const std::string& GetName() const { return m_name; }
		PropertyType GetType() const { return m_type; }

		template <typename TType>
		void Set(const TType& value)
		{
			((PropertyWrapper<TType>*)m_propertyWrapper)->Set(value);
		}

		template <typename TType>
		TType Get()
		{
			return ((PropertyWrapper<TType>*)m_propertyWrapper)->Get();
		}

	private:
		std::string m_name;
		PropertyType m_type;
		PropertyWrapperBase* m_propertyWrapper;
	};

	using PropertyMap = std::map < std::string, Property* >;

public:
	template <typename TClass, typename TType>
	void AddProperty(
		const std::string& name,
		PropertyType type,
		TClass* object,
		typename PropertyWrapperT<TClass, TType>::SetterPointer setter,
		typename PropertyWrapperT<TClass, TType>::GetterPointer getter)
	{
		PropertyWrapperBase* propertyWrapper = new PropertyWrapperT<TClass, TType>(object, setter, getter);
		Property* prop = new Property(name, type, propertyWrapper);
		m_propertyMap[name] = prop;
	}

	Property* GetProperty(const std::string& name)
	{
		return MapUtils::Find<std::string, Property*>(m_propertyMap, name);
	}

	void GetProperties(std::vector<Property*>& properties)
	{
		for (PropertyMap::iterator it = m_propertyMap.begin(); it != m_propertyMap.end(); ++it)
			properties.push_back(it->second);
	}

private:
	PropertyMap m_propertyMap;
};
