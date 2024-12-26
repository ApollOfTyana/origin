#pragma once
#include <utility>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class ExtArray
{
private:
	std::vector<T> extended_array;
	size_t _size;
public:
	ExtArray(std::initializer_list<T> l) : extended_array(l)
	{
		_size = l.size();
	}

	ExtArray(int size) : _size(size)
	{
		extended_array.resize(_size);
	}

	T& operator[](size_t index)
	{
		return extended_array[index];
	}

	size_t size()
	{
		return _size;
	}

	double mean()
	{
		double sum = 0;
		for (size_t i = 0; i < _size; i++)
		{
			sum += extended_array[i];
		}
		return sum / _size;
	}
	double mean(int s_ix, int e_ix)
    {
        if (s_ix >= e_ix || s_ix < 0 || e_ix > _size)
            throw std::invalid_argument("No true range");

        int count = e_ix - s_ix + 1;
        double sum = 0;
        for (int i = s_ix; i <= e_ix; ++i)
        {
            sum += extended_array[i];
        }
        return sum / count;
    }

	double median()
	{
		std::vector<T> temp_array;
		std::copy(extended_array.begin(), extended_array.end(), back_inserter(temp_array));
		std::sort(temp_array.begin(), temp_array.end());
		if (_size % 2 == 1)
		{
			return temp_array[_size / 2];
		}
		else
		{
			return static_cast<double>(temp_array[(_size / 2) - 1] + temp_array[_size / 2]) / 2;
		}
	}

	std::pair<T, int> mode()
	{
		T max = extended_array[0], cmax = 0, rmax = 0;
		for (int i = 0; i < _size; i++) 
		{
			if (cmax > rmax) 
			{
				rmax = cmax;
				max = extended_array[i - 1];
			}
			cmax = 0;
			for (int j = i; j < _size; j++)
			{
				if (extended_array[j] == extended_array[i])
				{
					cmax++;
				}
			}
		}
		return std::pair<T, int>(max, rmax);
	}

	template <typename U = T>
    typename std::enable_if<std::is_same<U, bool>::value || std::is_same<U, int>::value, size_t>::type
    checkSum()
    {
        using type = typename std::remove_reference<decltype(*this)>::type;
        if (!std::is_same<U, bool>::value && !std::is_same<U, int>::value)
            throw std::bad_typeid();

        size_t sum = 0;
        for (auto&& value : extended_array)
        {
            if constexpr (std::is_same<U, int>::value)
            {
                if (value != 0 && value != 1)
                    throw std::logic_error("Non-binary values in array");
            }
            sum += value ? 1 : 0;
        }
        return sum;
	}
};
