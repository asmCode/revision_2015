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
		//using std::placeholders::_1;
		m_setter = new Setter<TClass, TType>(object, setter);
		m_getter = new Getter<TClass, TType>(object, getter);
	}

	~PropertyAccess()
	{
		delete m_setter;
		delete m_getter;
	}

	template <typename T>
	void Set(const T& value)
	{
		((Setter*)m_setter)->Set(value);
	}

	template <typename T>
	T Get()
	{
		return ((Getter*)m_getter)->Get();
	}

private:
	struct SetterBase
	{
		virtual ~SetterBase() {}
	};

	template <typename TClass, typename TType>
	struct Setter : public SetterBase
	{
		Setter(
			TClass* object,
			SetterPointer<TClass, TType> setter) :
			m_object(object),
			m_setter(setter) { }

		void Set(const TType& value)
		{
			(m_object->*m_setter)(value);
		}

		TClass* m_object;
		SetterPointer<TClass, TType> m_setter;
	};

	struct GetterBase
	{
		virtual ~GetterBase() {}
	};

	template <typename TClass, typename TType>
	struct Getter : public GetterBase
	{
		Getter(
			TClass* object,
			GetterPointer<TClass, TType> getter) :
			m_object(object),
			m_getter(getter) {}

		TType Get()
		{
			return (m_object->*m_getter)();
		}

		TType m_placeholder;
		TClass* m_object;
		GetterPointer<TClass, TType> m_getter;
	};

	SetterBase* m_setter;
	GetterBase* m_getter;
};

