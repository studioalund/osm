/**
 *  OSM
 *  Copyright (C) 2019  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
#include <cstddef>
#include <functional>

namespace Container {
template<typename T> class array
{

private:
    T *m_data;
    std::size_t m_size;

public:
    array() : m_data(nullptr), m_size(0) {}
    array(std::size_t size, T value) : m_data(nullptr), m_size(0)
    {
        resize(size, value);
    }

    ~array()
    {
        delete[] m_data;
    }

    std::size_t size() const
    {
        return m_size;
    }

    //! reallocate memory for the array
    void resize(const std::size_t &size)
    {
        if (size != m_size) {
            T *data = new T[size];
            delete[] m_data;
            m_data = data;
            m_size = size;
        }
    }

    //! resize array and fill with value
    void resize(const std::size_t &size, const T &value)
    {
        resize(size);
        fill(value);
    }

    //! fill array with given value
    void fill(const T &value)
    {
        if (!m_data)
            return;

        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i] = value;
        }
    }

    T *pat(const unsigned int &i) const
    {
        assert(i < m_size);
        return &m_data[i];
    }

    T &operator [](const unsigned int &i)
    {
        assert(i < m_size);
        return m_data[i];
    }
    const T &operator [](const unsigned int &i) const
    {
        assert(i < m_size);
        return m_data[i];
    }

    void each(std::function<void(T *)> f)
    {
        if (!m_data)
            return;

        for (std::size_t i = 0; i < m_size; ++i) {
            f(&m_data[i]);
        }
    }
};
}

#endif // ARRAY_H
