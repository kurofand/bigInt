#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class bigInt
{
	bool positive;
	uint16_t size;
	uint16_t *number;
	public:
		bigInt();
		bigInt(uint32_t numb);
		bigInt(uint1024_t numb);
		bigInt(int numb);
//		bigInt(const bigInt &obj);
		void show();
		bigInt operator=(const bigInt &obj);
//		bigInt operator=(const uint1024_t &numb);
//		bigInt& operator=(const int32_t numb);
		bigInt operator=(const int32_t numb);
		bigInt operator+(const bigInt &b);
		bigInt operator+(const int32_t numb);
		bigInt operator-(const bigInt &b);
		bool operator<(const bigInt &b);
		bool operator>(const bigInt &b);
		bool operator==(const bigInt &b);
		bool operator<=(const bigInt &b);
		bool operator>=(const bigInt &b);
		virtual ~bigInt();
	private:
		void deleteNulls();
		bool checkPositive(uint16_t *number, uint16_t size);
		bool moduleBigger(const bigInt &b, bool equal=false);
		bool moduleLower(const bigInt &b, bool equal=false);
		uint16_t* returnNumber();
//		uint16_t returnNumbSize(uint32_t numb);
//		uint16_t returnNumbSize(uint1024_t numb);
//		uint16_t* longlongToBigInt(uint1024_t numb);
};
uint16_t returnNumbSize(uint1024_t numb);
uint16_t* boostLongToBigInt(uint1024_t numb);
uint16_t* intToBigInt(int32_t numb);
