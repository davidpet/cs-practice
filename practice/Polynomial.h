#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <vector>
#include <cmath>
using std::vector;
using std::pow;

template<class T> class Polynomial {	//T must act like a numeric type (including conversions to some numeric types so cmath will work)
public:
	//constructors
	Polynomial(unsigned int order=0) {coefficients.resize(order+1,0);}
	Polynomial(const float* coeff, unsigned int count) {for (unsigned int i = 0; i < count; i++) coefficients.push_back(coeff[i]);}

	//terms and order
	float& operator[](unsigned int term) {if (term > Order()) coefficients.resize(term+1,0);  return coefficients[term];}
	float operator[](unsigned int term) const {return coefficients[term];}
	unsigned int Order() const { return coefficients.size() - 1;}

	//function and calculus operators
	T operator()(const T& x) const		//f(x)
	{
		T acc = 0;

		for (unsigned int power = 0; power <= Order(); power++)
			acc += pow((float)x,(float)power) * coefficients[power];

		return acc;
	}
	T Diff(const T& left, const T& right) const {return (*this)(right)-(*this)(left);}		//diff between 2 values of x (f(x2)-f(x1))
	Polynomial operator>>(unsigned int count) const	//derivative
	{
		Polynomial newValue(*this);

		unsigned int oldOrder = Order();
		if (count > oldOrder)
		{
			newValue.coefficients.resize(1,0);
			return newValue;
		}
		for (unsigned int level = 0; level < count; level++)
		{
			unsigned int order = newValue.Order();
			for (unsigned int power = 0; power < order; power++)
				newValue.coefficients[power] = newValue.coefficients[power+1]*(power+1);

			newValue.coefficients.pop_back();
		}

		return newValue;
	}
	Polynomial operator<<(unsigned int count) const	//integral (can only do 1 level [everything else will clip to this] with constant of 0 at end)
	{
		Polynomial newValue(*this);

		if (count == 0)
			return newValue;

		newValue.coefficients.push_back(0);
		unsigned int order = Order();
		for (unsigned int power = 0; power <= order; power++)
			newValue.coefficients[power+1] = coefficients[power]/(power+1);

		newValue.coefficients[0] = 0;

		return newValue;
	}

	//ommitted: bit shift assignment operators, arithmetic with other polynomials

	//arithmetic with constants
	Polynomial operator+(const T& value) const {Polynomial newValue(*this);  newValue.coefficients[0] += value;  return newValue;}
	Polynomial operator-(const T& value) const {Polynomial newValue(*this);  newValue.coefficients[0] -= value;  return newValue;}
	Polynomial& operator+=(const T& value) {coefficients[0] += value;  return *this;}
	Polynomial& operator-=(const T& value) {coefficients[0] -= value; return *this;}

	Polynomial operator*(const T& value) const {Polynomial newValue(*this);  for (unsigned int i = 0; i <= Order(); i++) newValue.coefficients[i] *= value;  return newValue;}
	Polynomial operator/(const T& value) const {Polynomial newValue(*this);  for (unsigned int i = 0; i <= Order(); i++) newValue.coefficients[i] /= value;  return newValue;}
	Polynomial& operator*=(const T& value) {for (unsigned int i = 0; i <= Order(); i++) coefficients[i] *= value;  return *this;}
	Polynomial& operator/=(const T& value)  {for (unsigned int i = 0; i <= Order(); i++) coefficients[i] /= value;  return *this;}
private:
	vector<float> coefficients;	//index = term (reverse order of mathematics) [should be initialized to order 0 (length 1) in constructor]
};

#endif