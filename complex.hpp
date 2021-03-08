#pragma once

struct Complex
{
	explicit constexpr Complex() : real(0), imaginary(0) {}
	explicit Complex(float r, float i) : real(r), imaginary(i) {}

	[[nodiscard("Must be used with appropriate context.")]] inline constexpr float get_real() const
	{
		return real;
	}

	[[nodiscard("Must be used with appropriate context.")]] inline constexpr float get_imaginary() const
	{
		return imaginary;
	}

	inline constexpr void set(float real, float imaginary)
	{
		this->real = real;
		this->imaginary = imaginary;
	}

	inline constexpr Complex& operator+(const Complex& other) 
	{ 
		real += other.get_real();
		imaginary += other.get_imaginary();
		return *this;
	}

	inline constexpr Complex& operator=(const Complex& other)
	{
		real = other.get_real();
		imaginary = other.get_imaginary();
		return *this;
	}

	inline constexpr Complex& operator*(const Complex& other)
	{
		real = real * other.get_real() - imaginary * other.get_imaginary();
		imaginary = real * other.get_imaginary() + imaginary * other.get_real();
		return *this;
	}

	inline constexpr bool operator==(const Complex & other)
	{
		return imaginary == other.get_imaginary() && real == other.get_real();
	}

private:
	float real, imaginary;
};

