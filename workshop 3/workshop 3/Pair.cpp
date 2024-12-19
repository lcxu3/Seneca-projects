#include <iostream>
#include "Pair.h"
namespace seneca {
    const std::string& Pair::getKey() const {
        return m_key;
    }

    const std::string& Pair::getValue() const {
        return m_value;
    }

    Pair::Pair(const std::string& key, const std::string& value) : m_key(key), m_value(value) {}

    bool Pair::operator==(const Pair& p) const {
        return m_key == p.m_key && m_value == p.m_value;
    }

    bool Pair::operator!=(const Pair& p) const {
        return !(*this == p);
    }
	std::ostream& operator<<(std::ostream& os, const Pair& p)
	{
		os << "[" << p.getKey() << "][" << p.getValue() << "]";
		return os;
	}
}