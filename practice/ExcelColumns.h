#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

class Digit {
	public:
		Digit() {
			setClippedValue(0);
		}

		Digit(unsigned int digit) {
			setValue(digit);
		}

		operator char() const{
			return digit;
		}

		Digit& operator++(int dummy) {
			setValue(getValue() + 1);
			return *this;
		}

		Digit operator+(const Digit &otherDigit) {
			return Digit(getValue() + otherDigit.getValue());
		}

		Digit& operator+=(const Digit &otherDigit) {
			setValue(getValue() + otherDigit.getValue());
			return *this;
		}

		Digit& operator--(int dummy) {
			unsigned int value = getValue();
			if (value == 0)
				setValue(MAX_VALUE);
			else
				setValue(value - 1);

			return *this;
		}

		bool Overflowed() {
			return overflow;
		}

	private:
		void setValue(unsigned int newValue) {
			div_t ret = std::div(newValue, 26);
			setClippedValue(ret.rem);
			overflow = ret.quot > 0;
		}

		void setClippedValue(unsigned int newDigit) {
			digit = newDigit + 'A';
		}

		unsigned int getValue() const {
			return digit - 'A';
		}

		char digit;
		bool overflow;
		const static unsigned int MAX_VALUE = 'Z' - 'A';
};

class ExcelColumn {
	public:
		ExcelColumn() {
			digits.push_back(Digit());
		}

		ExcelColumn& operator++(int dummy) {
			bool overflow = true;

			for (std::vector<Digit>::iterator iter = digits.begin(); iter != digits.end(); iter++) {
				Digit &digit = *iter;

				digit++;
				overflow = digit.Overflowed();
				if (!overflow)
					break;
			}
			if (overflow)
				digits.push_back(Digit());

			return *this;
		}

		friend std::ostream& operator<<(std::ostream &output, ExcelColumn &column);
	private:
		std::vector<Digit> digits;
};

std::ostream& operator<<(std::ostream &output, ExcelColumn &column) {
	for (std::vector<Digit>::reverse_iterator iter = column.digits.rbegin(); iter != column.digits.rend(); iter++)
		output << (char)(*iter);

	return output;
}

class ExcelSimulation {
	public:
		ExcelSimulation():
		  index(0)
		{
		}

		void AdvanceToNextColumn() {
			column++;
			index++;
		}

		friend std::ostream& operator<<(std::ostream &output, ExcelSimulation &excelSimulation);

		static const std::string HeaderTitles;
	private:/* ///////Incorrect version from interview
		std::string computePredictedColumn() {		//tried to do a base-26 conversion from 0-based index with adjustment on last digit.  made sense when I thought about it
			unsigned int val = index;				//A-ZY worked fine, but ZZ was something like AA@.  It was mostly the higher boundary conditions that showed trouble and not normal values
			std::string output;

			output.insert(0, 1, (char)((val % 26) + 'A'));
			while (val /= 26)
				output.insert(0, 1, (char)((val % 26) + 'A' - 1));

			return output;
		}
		*/	//////Correct version found in a few minutes by looking at the behavior on paper at home and trying a few hard scenarios
		std::string computePredictedColumn() {
			unsigned int val = index + 1;		//convert to 1-based index (found it hard to come to this conclusion since I like 0-based so much)
			std::string output;

			while (val) {			//when this value empties out there will be no more digits to print
				unsigned int currentChar = val % 26;	//rightmost digit is like base 26 but 0 means Z because A means 1 and a true 26 is impossible
				if (currentChar == 0)
					currentChar = 26;

				output.insert(0, 1, currentChar - 1 + 'A');		//we know this digit already so write it (1 = A, 2 = B, ... 26 = Z)

				val /= 26;					//next digit up logic is like base 26 conversion
				if (val && currentChar == 26)	 //if the digit we wrote was Z, we have to steal one from the next digit because that 26 has already been counted
					val -= 1;						//however, we do not steal from 0
			}							//didn't think too hard about why stealing one from 0 to make 0 is ok, but it works out in the boundary conditions and for high numbers of digits

			return output;				//going the other way would be simpler: just multiply the 1-based value of each digit by 26 to the power of that place and add all up
											//that's almost like a base-26 string to number conversion, except that none of the digits will be 0 and some of them will be 26, which is not normal
		}

		ExcelColumn column;
		unsigned int index;
};

std::ostream& operator<<(std::ostream &output, ExcelSimulation &excelSimulation) {
	std::string predictedColumn = excelSimulation.computePredictedColumn();

	return output << '\t' << excelSimulation.column << '\t' << excelSimulation.index << '\t' << excelSimulation.index + 1 << '\t' << predictedColumn << std::endl;
}

const std::string ExcelSimulation::HeaderTitles = "Excel\t0-based index\t1-based index\tAlgorithm\n";
