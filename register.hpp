#pragma once

#include "complex.hpp"
#include <cstdint>
#include <cmath>
#include <vector>

struct Register
{
	constexpr uint64_t get();
	Complex get_state_probability(uint64_t state) const;
	void set_state(Complex& state);
	void normalize();
	void equidistribute(uint64_t value);
	
	constexpr Register() : size(0) {}
	inline Register(uint64_t size) : size(size)
	{
		_state.resize(std::powf(2, size));
	}

	inline constexpr int get_size() const
	{
		return size;
	}

private:
	uint64_t size;
	std::vector<Complex> _state;
};