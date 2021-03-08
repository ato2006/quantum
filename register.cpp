#include "register.hpp"
#include <stdexcept>


// Credits: https://github.com/toddwildey/shors-python/blob/master/shors.py#L142
constexpr uint64_t Register::get()
{
	bool found;
	int value;
	float a, b, r = rand() / RAND_MAX;

	for (auto i = 0; i < std::powf(2, size); i++)
	{
		if (!found)
		{
			b += std::powf(_state[i].get_real(), 2) + std::powf(_state[i].get_imaginary(), 2);
			if (b > r && r > a)
			{
				for (auto j = 0; j < std::powf(2, size); j++)
				{
					_state[j].set(0, 0);
				}
			}
			_state[i].set(1, 0);
			value = i;
			found = true;
		}
		a += std::powf(_state[i].get_real(), 2) + std::powf(_state[i].get_imaginary(), 2);
	}
	return value;
}

Complex Register::get_state_probability(uint64_t state) const
{
	if (state >= std::powf(2, size))
		throw std::runtime_error("Provided state is invalid.");

	return _state[state];
}

void Register::set_state(Complex& state)
{
	for (auto i = 0; i < std::powf(2, size); i++)
		_state[i].set(state.get_real(), state.get_imaginary());
}

void Register::normalize()
{
	float a, b, c;
	for (auto i = 0; i < std::powf(2, size); i++)
		a += std::powf(_state[i].get_real(), 2) + std::powf(_state[i].get_imaginary(), 2);

	a = std::sqrtf(1 / b);

	for (auto i = 0; i < std::powf(2, size); i++)
	{
		b = _state[i].get_real() * a;
		c = _state[i].get_imaginary() * a;

		_state[i].set(b, c);
	}
}

void Register::equidistribute(uint64_t value)
{
	if (value >= std::powf(2, size))
		throw std::runtime_error("Provided value is invalid.");

	float e = std::sqrtf(1 / value);
	for (auto i = 0; i <= value; i++)
		_state[i].set(e, 0);
}

