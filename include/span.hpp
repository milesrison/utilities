#pragma once 

#include <cstdint>
#include <limits>
#include <ostream>
#include <utility>

template <typename T>
struct span
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

    const value_type range_minimum = std::numeric_limits<value_type>::min();
    const value_type range_maximum = std::numeric_limits<value_type>::max();

public:
    span() : m_minimum(range_minimum), m_maximum(range_maximum) {}
    span(value_type minimum, value_type maximum) : m_minimum(minimum), m_maximum(maximum) {}
    constexpr span(const span& span) = default;
    constexpr span(span&& span)      = default;

    span& operator=(const span& span)
    {
        m_minimum = span.m_minimum;
        m_maximum = span.m_maximum;
        return *this;
    }
    constexpr value_type size() const { return m_maximum - m_minimum + 1; }
    constexpr span normalize() const { return span(static_cast<value_type>(0), size() - 1); }
    constexpr value_type min() const { return m_minimum; }
    constexpr value_type max() const { return m_maximum; }
    template <typename _U>
    friend std::ostream& operator<<(std::ostream& os, const span<_U>& span)
    {
        os << span.min() << " .. " << span.max();
        return os;
    }
    template <typename _U>
    constexpr friend span<_U> operator&(const span<_U>& left, const span<_U>& right)
    {
        return span<_U>(std::max(left.m_minimum, right.m_minimum), std::min(left.m_maximum, right.m_maximum));
    }
    template <typename _U>
    constexpr friend span<_U> operator|(const span<_U>& left, const span<_U>& right)
    {
        return span<_U>(std::min(left.m_minimum, right.m_minimum), std::max(left.m_maximum, right.m_maximum));
    }
    template <typename _U>
    constexpr friend bool operator==(const span<_U>& left, const span<_U>& right)
    {
        return left.m_minimum == right.m_minimum && left.m_maximum == right.m_maximum;
    }
    template <typename _U>
    constexpr friend bool operator!=(const span<_U>& left, const span<_U>& right)
    {
        return !(left == right);
    }

private:
    value_type m_minimum;
    value_type m_maximum;
};
