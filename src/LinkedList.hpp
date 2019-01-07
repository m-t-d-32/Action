#include <iostream>
#include "LinkedList.h"
#include "String.h"
#include "Type_NotCorrespond.h"

#ifndef LINKEDLIST__CPP
#define LINKEDLIST__CPP
namespace Action
{
    template <class T>
    LinkedList<T>::LinkedList()
    {
        m_size = 0;
        m_begin_address = m_end_address = NULL;
    }

    template <class T>
    LinkedList<T>::LinkedList(const LinkedList & another)
    {
        m_size = 0;
        m_begin_address = m_end_address = NULL;
        operator = (another);
    }

    template <class T>
    LinkedList<T> & LinkedList<T>::operator = (const LinkedList & another)
    {
        if(this == &another)
            return *this;
        Node * another_address_cursor = another.m_begin_address;
        Node * this_address_cursor;
        if(!another_address_cursor)
        {
            clear();
            return *this;
        }
        if(!m_begin_address)
        {
            m_begin_address = new Node(another_address_cursor->m_value);
            this_address_cursor = m_begin_address;
        }
        else
        {
            this_address_cursor = m_begin_address;
            while(another_address_cursor->m_address_next && this_address_cursor->m_address_next)
            {
                this_address_cursor->m_value = another_address_cursor->m_value;
                another_address_cursor = another_address_cursor->m_address_next;
                this_address_cursor = this_address_cursor->m_address_next;
            }
            this_address_cursor->m_value = another_address_cursor->m_value;
        }

        if(!(this_address_cursor->m_address_next))
        {
            another_address_cursor = another_address_cursor->m_address_next;
            while(another_address_cursor)
            {
                this_address_cursor->m_address_next = new Node(another_address_cursor->m_value);
                another_address_cursor = another_address_cursor->m_address_next;
                this_address_cursor = this_address_cursor->m_address_next;
            }
            m_end_address = this_address_cursor;
        }
        else
        {
            erase(this_address_cursor->m_address_next, end());
            m_end_address = this_address_cursor;
        }
        m_size = another.m_size;
        return *this;
    }

    template <class T>
    T LinkedList<T>::pop_back()
    {
        if(m_size <= 0)
            throw List_PtrOutOfRange();
        else
        {
            T return_value = m_end_address->m_value;
            erase(Pointer(this, m_end_address));
            return return_value;
        }
    }

    template <class T>
    void LinkedList<T>::push_back(const T & element)
    {
        Node *new_node = new Node(element);
        if(m_begin_address == NULL)
            m_end_address = m_begin_address = new_node;
        else
        {
            new_node->m_address_last = m_end_address;
            m_end_address->m_address_next = new_node;
            m_end_address = new_node;
        }
        ++m_size;
    }

    template <class T>
    T LinkedList<T>::at(const Integer & position) const
    {
        if(position < 0 || position >= m_size)
            throw List_PtrOutOfRange();

        const Node *address_cursor = m_begin_address;
        for(int i = 0; i < position; ++i)
            address_cursor = address_cursor->m_address_next;
        return address_cursor->m_value;
    }

    template <class T>
    T LinkedList<T>::front() const
    {
        if(m_size <= 0)
            throw List_PtrOutOfRange();
        else
            return m_begin_address->m_value;
    }

    template <class T>
    T LinkedList<T>::back() const
    {
        if(m_size <= 0)
            throw List_PtrOutOfRange();
        else
            return m_end_address->m_value;
    }

    template <class T>
    void LinkedList<T>::insert(Pointer position, const T & element)
    {
        Node * target_address = position.get_node();
        if(!target_address)
            throw List_PtrOutOfRange();

        Node *new_node = new Node(element);
        if(target_address == m_begin_address)
            m_begin_address = new_node;
        if(target_address->m_address_last)
        {
            target_address->m_address_last->m_address_next = new_node;
            new_node->m_address_last = target_address->m_address_last;
        }
        target_address->m_address_last = new_node;
        new_node->m_address_next = target_address;
        ++m_size;
    }

    template <class T>
    void LinkedList<T>::insert(const Integer & position, const T & element)
    {
        if(position < 0 || position > m_size)
            throw List_PtrOutOfRange();
        else if(position == m_size)
            push_back(element);
        Pointer pointer_cursor = begin();
        for(int i = 0; i < position; ++i)
            ++pointer_cursor;
        insert(pointer_cursor, element);
    }

    template <class T>
    void LinkedList<T>::insert(const Integer & position, const Integer & count, const T & element)
    {
        if(position < 0 || position >= m_size)
            throw List_PtrOutOfRange();

        Pointer pointer_cursor = begin();
        int i;
        for(i = 0; i < position; ++i)
            ++pointer_cursor;
        for(i = 0; i < count; ++i)
            insert(pointer_cursor, element);
    }

    template <class T>
    void LinkedList<T>::erase(Pointer position)
    {
        Node * target_address = position.get_node();
        if(!target_address)
            throw List_PtrOutOfRange();

        if(target_address == m_begin_address)
            m_begin_address = target_address->m_address_next;
        if(target_address == m_end_address)
            m_end_address = target_address->m_address_last;
        if(target_address->m_address_next)
            target_address->m_address_next->m_address_last = target_address->m_address_last;
        if(target_address->m_address_last)
            target_address->m_address_last->m_address_next = target_address->m_address_next;
        delete target_address;
        --m_size;
    }

    template <class T>
    void LinkedList<T>::erase(Pointer begin, Pointer end)
    {
        if(!(begin.get_node()))
            throw List_PtrOutOfRange();

        Pointer pointer_cursor = begin;
        while(pointer_cursor != end)
        {
            Pointer temp_next = Pointer(this, (pointer_cursor.get_node())->m_address_next);
            erase(pointer_cursor);
            pointer_cursor = temp_next;
        }
    }

    template <class T>
    void LinkedList<T>::erase(const Integer & position)
    {
        if(position < 0 || position >= m_size)
            throw List_PtrOutOfRange();

        Pointer pointer_cursor = begin();
        for(int i = 0; i < position; ++i)
            ++pointer_cursor;
        erase(pointer_cursor);
    }

    template <class T>
    void LinkedList<T>::erase(const Integer & position, const Integer & count)
    {
        if(position < 0 || position + count >= m_size
                || count < 0)
            throw List_PtrOutOfRange();

        Pointer pointer_cursor = begin();
        int i;
        for(i = 0; i < position; ++i)
            ++pointer_cursor;
        for(i = 0; i < count; ++i)
        {
            Pointer temp_next = pointer_cursor.next();
            erase(pointer_cursor);
            pointer_cursor = temp_next;
        }
    }

    template <class T>
    T & LinkedList<T>::operator [](const Integer & position)
    {
        if(position < 0 || position >= m_size)
            throw List_PtrOutOfRange();

        Pointer pointer_cursor = begin();
        for(int i = 0; i < position; ++i)
            ++pointer_cursor;
        return *pointer_cursor;
    }

    template <class T>
    Boolean LinkedList<T>::operator == (const Object & another_one) const
    {
        try
        {
            const LinkedList<T> & another_linkedlist = dynamic_cast<const LinkedList<T> &>(another_one);
            if(size() != another_linkedlist.size())
            {
                return Boolean::False;
            }
            Node *this_address_cursor = m_begin_address, *another_address_cursor = another_linkedlist.m_begin_address;
            while(this_address_cursor && another_address_cursor)
            {
                if(this_address_cursor->m_value != another_address_cursor->m_value)
                    return Boolean::False;
                this_address_cursor = this_address_cursor->m_address_next;
                another_address_cursor = another_address_cursor->m_address_next;
            }
            return Boolean::True;
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }

    template <class T>
    void LinkedList<T>::clear()
    {
        if(m_begin_address)
            erase(begin(), end());
    }

    template <class T>
    Integer LinkedList<T>::find(const T & iArgOfObject) const
    {
        if(!m_begin_address)
            return -1;
        int index = 0;
        for(const Node * address_cursor = m_begin_address; address_cursor != NULL; address_cursor = address_cursor->m_address_next)
        {
            if(address_cursor->m_value == iArgOfObject)
                return index;
            ++index;
        }
        return -1;
    }

    template <class T>
    String LinkedList<T>::get_name() const
    {
        return "Action::LinkedList";
    }

    template <class T>
    String LinkedList<T>::to_string() const
    {
        String rtn = "[";
        for(const Node * address_cursor = m_begin_address; address_cursor != NULL; address_cursor = address_cursor->m_address_next)
        {
            rtn += ((Object &)(address_cursor->m_value)).to_string();
            if(address_cursor != m_end_address)
            {
                rtn += ",";
            }
        }
        rtn += "]";
        return rtn;
    }
    template <class T>
    LinkedList<T>::~LinkedList()
    {
        clear();
    }
}
#endif /* LINKEDLIST__CPP */
