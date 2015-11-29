#include "Conversions.h"

string DP::ConvertToString(unsigned int value,unsigned int base,CharacterConversion convert)
{
	char reversedOutput[sizeof(unsigned int)*8+1];
	int length = 0;

	div_t res;
	while (value != 0)
	{
		res = div((int)value,(int)base);
		char c = convert(res.rem);
		reversedOutput[length++] = c;
		value = res.quot;
	}
	reversedOutput[length] = NULL;
	_strrev(reversedOutput);

	return string(reversedOutput);
}

string DP::ConvertToExcel(unsigned int value)
{
	//convert to 0-based and convert to base 26 with letter for numbers
	string output = ConvertToString(value-1,26,ConvertExcel);
	//after the single digit cases, the highest digit is always 1 too high because it rolls over to A from nothing even though lower digits roll over to A
	if (output.length() > 1)
		output[0] -= 1;
	
	return output;
}