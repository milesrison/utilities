
#include <cstdint>

template <typename T, size_t capacity>
struct small_ring_stack
{
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    small_ring_stack() : m_tail(0), m_size(0) {}
    value_type& push()
    {
        // m_data[m_tail] = value;
        size_type n = m_tail;
        m_tail      = (m_tail + 1) % capacity;
        if (m_size < capacity)
        {
            ++m_size;
        }
        return m_data[n];
    }
    void push(const value_type& value)
    {
        m_data[m_tail] = value;
        m_tail         = (m_tail + 1) % capacity;
        if (m_size < capacity)
        {
            ++m_size;
        }
    }
    bool try_pop(value_type& value)
    {
        if (m_size > 0)
        {
            m_tail = (m_tail + (capacity - 1)) % capacity;
            m_size--;
            value = m_data[m_tail];
            return true;
        }
        return false;
    }
    const value_type& pop()
    {
        if (m_size > 0)
        {
            m_tail = (m_tail + (capacity - 1)) % capacity;
            m_size--;
            return m_data[m_tail];
        }
        else
        {
            static value_type empty;
            return empty;
        }
    }
    void clear()
    {
        m_tail = 0;
        m_size = 0;
    }
    size_type size() const { return m_size; }
    bool empty() const { return m_size != 0; }
    value_type operator[](size_type back_index) const // 0 = last inserted, 1 = previous...
    {
        if (back_index < m_size)
        {
            return m_data[(m_tail + (capacity - 1) - back_index) % capacity];
        }
        else
        {
            return T();
        }
    }

private:
    value_type m_data[capacity];
    size_type m_tail;
    size_type m_size;
};
