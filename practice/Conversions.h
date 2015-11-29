#ifndef CONVERSIONS
#define CONVERSIONS

#include <cstring>
#include <string>
#include <cmath>
using namespace std;

namespace DP {
		typedef char(*CharacterConversion)(char);

		inline char ConvertNormal(char input)
		{
			if (input <= 9)
				return input + '0';

			return input - 10 + 'A';
		}

		inline char ConvertExcel(char input)
		{
			return input + 'A';
		}

		string ConvertToString(unsigned int value, unsigned int base=10, CharacterConversion convert=ConvertNormal);

		string ConvertToExcel(unsigned int value);
}

#endif