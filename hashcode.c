#define __External__C_Library__HASHCODE
#include <stdio.h>

int _hashCode(int key)
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

int _str_hashCode(char * begin, int len)
{
    int result = 1;
    int i;
    for(i = 0; i < len; ++i)
    {
        result ^= _hashCode(* (begin + i));
    }
    if(result < 0)
    {
        result = -result;
    }
    return result;
}

