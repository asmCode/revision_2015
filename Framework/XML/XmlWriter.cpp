#include "XmlWriter.h"

template<>
void XmlWriter::WriteAttribute(const char *name, const std::string value)
{
	WriteAttribute(name, value.c_str());
}

