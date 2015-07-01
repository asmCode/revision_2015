#pragma once

#include <functional>

class PropertyAccess
{
public:
	template <typename TClass, typename TType> using SetterPointer = void (TClass::*)(const TType&);
	template <typename TClass, typename TType> using GetterPointer = TType(TClass::*)();

	template <typename TClass, typename TType>
	PropertyAccess(
		TClass* object,
		SetterPointer<TClass, TType> setter,
		GetterPointer<TClass, TType> getter)
	{
		using std::placeholders::_1;
		m_setter = new Setter<TType>(std::bind(setter, object, _1));
		m_getter = new Getter<TType>(std::bind(getter, object));
	}

	~PropertyAccess()
	{
		delete m_setter;
		delete m_getter;
	}

	template <typename T>
	void Set(const T& value)
	{
		((Setter<T>*)m_setter)->m_setter(value);
	}

	template <typename T>
	T Get()
	{
		return ((Getter<T>*)m_getter)->m_getter();
	}

private:
	struct Base
	{
		virtual ~Base() {}
	};

	template <typename TType>
	struct Setter : public Base
	{
		Setter(std::function < void(const TType&) > setter) { m_setter = setter; }

		std::function < void(const TType&) > m_setter;
	};

	template <typename TType>
	struct Getter : public Base
	{
		Getter(std::function < TType() > getter) { m_getter = getter; }

		std::function < TType() > m_getter;
	};

	Base* m_setter;
	Base* m_getter;
};

