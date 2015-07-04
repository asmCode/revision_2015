#pragma once

class PropertyWrapperBase
{
public:
	virtual ~PropertyWrapperBase() {}
};

template <typename TType>
class PropertyWrapper : public PropertyWrapperBase
{
public:
	virtual void Set(const TType& value) = 0;
	virtual TType Get() const = 0;
};

template <typename TClass, typename TType>
class PropertyWrapperT : public PropertyWrapper<TType>
{
public:
	using SetterPointer = void (TClass::*)(const TType&);
	using GetterPointer = TType(TClass::*)() const;

	PropertyWrapperT(
		TClass* object,
		SetterPointer setter,
		GetterPointer getter) :
		m_object(object),
		m_setter(setter),
		m_getter(getter) { }

	void Set(const TType& value)
	{
		(m_object->*m_setter)(value);
	}

	TType Get() const
	{
		return (m_object->*m_getter)();
	}

private:
	TClass* m_object;
	SetterPointer m_setter;
	GetterPointer m_getter;
};

