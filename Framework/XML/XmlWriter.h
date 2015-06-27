#pragma once

#include "../Utils/StringUtils.h"
#include <string>
#include <stack>
#include <string>
#include <sstream>
#include <assert.h>

class Element
{
public:
	std::string Name;
	bool HasChildren;

	Element(const std::string& name) :
		Name(name),
		HasChildren(false)
	{
	}
};

class XmlWriter
{
private:
	std::ostream *os;

	int identLevel;
	bool isElementBracketOpen;

	std::stack<Element> openElements;
	Element* currentElement;

	std::string Ident()
	{
		std::string ident = "";

		for (int i = 0; i < identLevel; i++)
			ident += "\t";

		return ident;
	}

	void CloseElementBracket()
	{
		*os << ">\n";

		isElementBracketOpen = false;
	}

	void UpdateCurrentElement()
	{
		if (openElements.size() != 0)
			currentElement = &openElements.top();
		else
			currentElement = NULL;
	}

public:
	XmlWriter(std::ostream *os, int identLevel) :
		currentElement(NULL)
	{
		this ->os = os;
		this ->identLevel = identLevel;

		isElementBracketOpen = false;
	}

	XmlWriter(int identLevel = 0) :
		currentElement(NULL)
	{
		this->os = new std::stringstream();
		this->identLevel = identLevel;

		isElementBracketOpen = false;
	}

	template <typename ValType>
	void CreateElement(const char *name, ValType data)
	{
		*os << Ident() << "<" << name << ">" << data << "</" << name << ">\n";
	}

	// wstawia kompletny element, np element = "<Element attrib1="val1" />";
	void CreateElementInline(const std::string& element)
	{
		if (isElementBracketOpen)
			CloseElementBracket();

		if (currentElement != NULL)
			currentElement->HasChildren = true;

		std::vector<std::string> lines;
		StringUtils::Split(element, "\n", lines);

		for (unsigned int i = 0; i < lines.size(); i++)
		{
			if (!lines[i].empty())
				*os << Ident() << lines[i] << "\n";
		}
	}

	template <typename ValType>
	void CreateElement(const char *name, const char *attribName, ValType attribValue)
	{
		OpenElement(name);
		WriteAttribute(attribName, attribValue);
		CloseElement();
	}

	template <typename A1Type, typename A2Type>
	void CreateElement(const char *name, const char *att1Name, A1Type att1Val, const char *att2Name, A2Type att2Val)
	{
		OpenElement(name);
		WriteAttribute(att1Name, att1Val);
		WriteAttribute(att2Name, att2Val);
		CloseElement();
	}

	void OpenElement(const char *name)
	{
		if (isElementBracketOpen)
			CloseElementBracket();

		if (currentElement != NULL)
			currentElement->HasChildren = true;

		*os << Ident() << "<" << name;

		openElements.push(Element(name));
		isElementBracketOpen = true;
		identLevel++;

		UpdateCurrentElement();
	}

	void CloseElement()
	{
		identLevel--;

		if (currentElement != NULL && !currentElement->HasChildren)
		{
			*os << " />\n";

			isElementBracketOpen = false;
		}
		else
		{
			if (isElementBracketOpen)
				CloseElementBracket();

			*os << Ident() << "</" << openElements.top().Name << ">\n";
		}

		openElements.pop();

		UpdateCurrentElement();
	}

	template <typename ValType>
	void WriteAttribute(const char *name, const ValType value)
	{
		assert(isElementBracketOpen == true);

		*os << " " << name << "=\"" << value << "\"";
	}

	template <typename ValType>
	void WriteElementCdata(const ValType data)
	{
		if (isElementBracketOpen)
			CloseElementBracket();

		*os << Ident() << "<![CDATA[" << data << "]]>\n";
	}

	template <typename ValType>
	void WriteElementData(const ValType data)
	{
		if (isElementBracketOpen)
			CloseElementBracket();

		*os << Ident() << data << "\n";
	}

	std::string GetAsText() const
	{
		return ((std::stringstream*)os)->str();
	}
};

template<>
void XmlWriter::WriteAttribute<std::string>(const char *name, const std::string value);

