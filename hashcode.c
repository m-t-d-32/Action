#define __External__C_Library
int _hashCode(int key)
{
    key += ~(key << 15);
    key ^=  (key >> 10);
    key +=  (key << 3);
    key ^=  (key >> 6);
    key += ~(key << 11);
    key ^=  (key >> 16);
	if (key<0) key=-key;
    return key;
}

int _str_hashCode(char * begin, int len)
{
	int key = 0;
	for (int i = 0; i < len; ++i)
	{
		key *= _hashCode(*(begin + i));
	}
	return key;
}

