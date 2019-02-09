#include <iostream>
#include "Object.h"
#include "String.h"
#include "ArrayList.hpp"
#include "Type_NotCorrespond.h"
#include <cstring>
#include "Tools.h"

namespace Action
{
    String::String()
    {
        push_back('\0');
    }

    String::String(const char * chars_value)
    {
        while(*chars_value)
        {
            push_back(*chars_value);
            ++chars_value;
        }
        push_back('\0');
    }

    void String::append(char char_value)
    {
        ArrayList<char>::insert(length(), char_value);
    }

    void String::append(const String & string_value)
    {
        ArrayList<char>::insert(length(), string_value, 0, string_value.length());
    }

    String String::operator += (char char_value)
    {
        append(char_value);
        return *this;
    }

    String String::operator += (const String & string_value)
    {
        append(string_value);
        return *this;
    }

    void String::clear()
    {
        ArrayList<char>::clear();
        push_back('\0');
    }

    void String::insert(Integer position, char char_value)
    {
        ArrayList<char>::insert(position, char_value);
    }

    void String::insert(Integer position, const String & string_value)
    {
        ArrayList<char>::insert(position, string_value, 0, string_value.length());
    }

    Integer String::find(char char_value, Integer begin) const
    {
        for (int i = begin.get_int(); i < length().get_int(); ++i)
        {
            if (at(i) == char_value)
                return i;
        }
        return -1;
    }

    Integer String::find(const String & string_value, Integer begin) const
    {
        int this_length = length().get_int(), another_length = string_value.length().get_int();
        if(another_length == 0 || this_length - begin.get_int() < another_length)
            return -1;
        int * nexts = new int[another_length + 1];
        nexts[0] = 0;
        int src_index = 0, dest_index = 0;
        while(dest_index != another_length)
        {
            if(string_value.at(src_index) == string_value.at(dest_index + 1))
            {
                nexts[++dest_index] = ++src_index;
            }
            else if(!src_index)
            {
                nexts[++dest_index] = 0;
            }
            else
            {
                src_index = nexts[src_index - 1];
            }
        }
        for(int i = begin.get_int(); i <= this_length - another_length;)
        {
            bool found = true;
            for(int j = 0; j < another_length; ++j)
            {
                if(at(i + j) != string_value.at(j))
                {
                    i += (j == 0 ? 1 : j - nexts[j - 1]);
                    found = false;
                    break;
                }
            }
            if(found)
            {
                delete []nexts;
                return i;
            }
        }
        delete []nexts;
        return -1;
    }

    String & String::operator = (const String & another_string)
    {
        this->ArrayList<char>::operator = (another_string);
        return *this;
    }

    void String::print(std::ostream & print_stream) const
    {
        print_stream << c_str();
    }

    int String::hash_code() const
    {
        return str_hash(*this);
    }

    Boolean String::operator == (const Action::Object & another_one) const
    {
        try
        {
            const String & another_string = dynamic_cast<const String &>(another_one);
            return Boolean(strcmp(m_data, another_string.m_data) == 0);
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }

    Boolean String::compare_to(const Object & another_one) const
    {
        try
        {
            const String & another_string = dynamic_cast<const String &>(another_one);
            return Boolean(strcmp(m_data, another_string.m_data) < 0);
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }

    String operator + (const String & str_1, const String & str_2)
    {
        String return_value = str_1;
        return_value.append(str_2);
        return return_value;
    }
    String operator + (const String & str_1, const char * str_2)
    {
        return str_1 + String(str_2);
    }
    String operator + (const char * str_1, const String & str_2)
    {
        return String(str_1) + str_2;
    }

    ArrayList<String> String::split(const String & delims) const{
        ArrayList<String> result;
        String temp;
        for (int i = 0; i < length(); ++i){
            if (delims.find(at(i)) != -1){
                if (temp.at(0)){
                    result.push_back(temp);
                    temp.clear();
                }
            }
            else {
                temp += at(i);
            }
        }
        if (temp.at(0)){
            result.push_back(temp);
        }
        return result;
    }

    ArrayList<String> String::split(char delim) const{
        ArrayList<String> result;
        String temp;
        for (int i = 0; i < length(); ++i){
            if (delim == at(i)){
                if (temp.at(0)){
                    result.push_back(temp);
                    temp.clear();
                }
            }
            else {
                temp += at(i);
            }
        }
        if (temp.at(0)){
            result.push_back(temp);
        }
        return result;
    }

    ArrayList<String> String::split_long(const String & delim) const{
        ArrayList<String> result;
        String temp;
        Integer begin = 0, end = 0;
        while (begin < length()){
            end = find(delim, begin);
            if (end == -1) {
                end = length();
            }
            if (end > begin){
                for (Integer i = begin; i < end; ++i){
                    temp += at(i);
                }
                result.push_back(temp);
                temp.clear();
            }
            begin = end + delim.length();
        }
        return result;
    }

    String String::slice(Integer begin, Integer end) const{
        String result;
        if (begin < 0) begin += length();
        if (end < 0) end += length();
        for (Integer i = begin; i < end; ++i){
            result += at(i);
        }
        return result;
    }
    
    String String::lstrip(char delim) const {
        Integer begin = 0;
        for (; begin < length(); ++begin){
            if (at(begin) != delim) break;
        }
        return right(length() - begin);
    }
    
    String String::rstrip(char delim) const {
        Integer end = length() - 1;
        for (; end >= 0; --end) {
            if (at(end) != delim) break;
        }
        return left(end + 1);
    }
    
    String String::strip(char delim) const {
        Integer begin = 0, end = length() - 1;
        for (; begin < length(); ++begin){
            if (at(begin) != delim) break;
        }
        for (; end >= 0; --end){
            if (at(end) != delim) break;
        }
        return slice(begin, end + 1);
    }
        
    String String::lstrip(const String & delims) const{
        Integer begin = 0;
        for (; begin < length(); ++begin){
            if (delims.find(at(begin)) == -1) break;
        }
        return right(length() - begin);
    }
    
    String String::rstrip(const String & delims) const{
        Integer end = length() - 1;
        for (; end >= 0; --end) {
            if (delims.find(at(end)) == -1) break;
        }
        return left(end + 1);
    }
    
    String String::strip(const String & delims) const{
        Integer begin = 0, end = length() - 1;
        for (; begin < length(); ++begin){
            if (delims.find(at(begin)) == -1) break;
        }
        for (; end >= 0; --end) {
            if (delims.find(at(end)) == -1) break;
        }
        return slice(begin, end + 1);
    }
    
    String String::left(Integer _length) const{
        if (_length <= 0) return "";
        else if (_length >= length()) return *this;
        else return slice(0, _length);
    }
    
    String String::right(Integer _length) const{
        if (_length <= 0) return "";
        else if (_length >= length()) return *this;
        else return slice(length() - _length, length());
    }
}
