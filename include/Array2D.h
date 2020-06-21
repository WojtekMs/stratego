#ifndef ARRAY2D_H_
#define ARRAY2D_H_

#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Array
{
    std::vector<T> data;
    void check_range(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= data.size()) {
            std::cerr << "KABOOM !" << std::endl;
            throw std::out_of_range("Invalid COLUMN access");
        }
    }

public:
    explicit Array(int size) : data(size)
    {
    }
    T &operator[](int idx)
    {
        check_range(idx);
        return data[idx];
    }
    const T &operator[](int idx) const
    {
        check_range(idx);
        return data[idx];
    }
};

template <typename T>
class Array2D
{
    std::vector<Array<T>> data;
    void check_range(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= data.size()) {
            std::cerr << "KABOOM !" << std::endl;
            throw std::out_of_range("Invalid ROW access");
        }
    }

public:
    explicit Array2D(int width, int height) : data(height, Array<T>(width)) {}
    Array<T> &operator[](int idx)
    {
        check_range(idx);
        return data[idx];
    }
    const Array<T> &operator[](int idx) const
    {
        check_range(idx);
        return data[idx];
    }
};

template <>
class Array<bool>
{
public:
    class my_bool
    {
    public:
        bool value;
        my_bool(bool val = false) : value(val){};
        inline friend std::ostream &operator<<(std::ostream &stream, my_bool rhs);
        inline operator bool() const;
        inline operator bool();
        
    };

private:
    std::vector<my_bool> data;
    void check_range(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= data.size()) {
            std::cerr << "KABOOM !" << std::endl;
            throw std::out_of_range("Invalid COLUMN access");
        }
    }

public:
    explicit Array(int size) : data(size)
    {
    }
    my_bool &operator[](int idx)
    {
        check_range(idx);
        return data[idx];
    }
    const my_bool &operator[](int idx) const
    {
        check_range(idx);
        return data[idx];
    }
};

std::ostream &operator<<(std::ostream &stream, Array<bool>::my_bool rhs)
{
    stream << rhs.value;
    return stream;
}

Array<bool>::my_bool::operator bool() const {
    return (const bool)value;
}

Array<bool>::my_bool::operator bool() {
    return value;
}


template <>
class Array2D<bool>
{
    std::vector<Array<Array<bool>::my_bool>> data;
    void check_range(int idx) const
    {
        if (idx < 0 || static_cast<size_t>(idx) >= data.size()) {
            std::cerr << "KABOOM !" << std::endl;
            throw std::out_of_range("Invalid ROW access");
        }
    }

public:
    explicit Array2D(int width, int height) : data(height, Array<Array<bool>::my_bool>(width)) {}
    Array<Array<bool>::my_bool> &operator[](int idx)
    {
        check_range(idx);
        return data[idx];
    }
    const Array<Array<bool>::my_bool> &operator[](int idx) const
    {
        check_range(idx);
        return data[idx];
    }
};

#endif /* ARRAY2D_H_ */
