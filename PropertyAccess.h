#pragma once

#include <functional>

class PropertyAccess
{
public:
	template <typename TClass, typename TType>
	PropertyAccess(TClass* object, void (TClass::*setter)(const TType&), TType (TClass::*getter)())
	{
		using std::placeholders::_1;
		m_setter = &std::bind(setter, object, _1);

		typedef std::function < void(const TType&) > cipsko;

		cipsko d = std::bind(setter, object, _1);
		cipsko* dd = &d;
		m_setter = dd;

		d(12);
		(*dd)(13);
		//m_getter = &std::bind(getter, object);
	}
	
	template <typename T>
	void Set(const T& value)
	{
		typedef std::function < void(const T&) > cipsko;

		(*((cipsko*)m_setter))(value);
	}

	template <typename T>
	T Get()
	{
		return (*((std::function<T()>*)m_setter))();
	}

private:
	//void* m_setter;
	std::function m_setter;
	void* m_getter;
};

