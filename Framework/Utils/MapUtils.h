#pragma once

#include <map>
#include <stddef.h>

class MapUtils
{
public:
	template <typename TKey, typename TVal>
	static TVal Find(std::map<TKey, TVal>& map, const TKey& key)
	{
		std::map<TKey, TVal>::iterator it = map.find(key);
		if (it == map.end())
			return NULL;

		return it->second;
	}

	template <typename TKey, typename TVal>
	static bool HasKey(std::map<TKey, TVal>& map, const TKey& key)
	{
		return map.find(key) != map.end();
	}
};
