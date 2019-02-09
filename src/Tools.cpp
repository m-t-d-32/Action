#include <iostream>
#include "Tools.h"
#include "Object.h"
#include "String.h"

namespace Action{

	int hash(INT64 key)
	{
		key += ~(key << 15);
		key ^= (key >> 10);
		key += (key << 3);
		key ^= (key >> 6);
		key += ~(key << 11);
		key ^= (key >> 16);
		if(key < 0)
			key = -key;
		return key;
	}

	int str_hash(const String & str)
	{
		int result = 1;
		for(int i = 0; i < str.length().get_int(); ++i)
		{
			result ^= hash(str.at(i));
		}
		if(result < 0)
		{
			result = -result;
		}
		return result;
	}
}