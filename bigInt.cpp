#include "bigInt.h"

bigInt::bigInt()
{
	std::cout<<"enter into creator"<<std::endl;
	this->positive=true;
	this->size=1;
	this->number=new uint16_t[1];
	this->number[0]=1;
}

bigInt::bigInt(uint32_t numb)
{
	std::cout<<"enter into creator"<<std::endl;
	this->size=returnNumbSize(numb);
	this->number=new uint16_t [this->size];
	for(unsigned int i=0;i<this->size;i++)
	{
		this->number[i]=numb%10;
		numb=numb/10;
	}
	this->positive=checkPositive(this->number,this->size);
}

bigInt::~bigInt()
{
	std::cout<<"enter into destructor"<<std::endl;
	delete [] number;
}

bigInt::bigInt(uint1024_t numb)
{
	std::cout<<"enter into creator"<<std::endl;
	this->size=returnNumbSize(numb);
	this->number=new uint16_t [this->size];
	this->number=boostLongToBigInt(numb);
}

uint16_t returnNumbSize(uint1024_t numb)
{
	std::cout<<"enter into returnNumbSize"<<std::endl;
	uint16_t size;
	if(numb<0)
		numb=numb*-1;
//	std::cout<<"returnNumbSize inner numb"<<std::endl<<numb<<std::endl;
	for(size=0;numb>0;size++)
		numb=numb/10;
//	std::cout<<"returnNumbSize inner size"<<std::endl<<size<<std::endl;
	return size;
}

bool bigInt::checkPositive(uint16_t *number, uint16_t size)
{
	std::cout<<"enter into checkPositive"<<std::endl;
	if(this->number[this->size-1]>0)
		return true;
	else
		return false;
}

bigInt bigInt::operator=(const bigInt &obj)
{
	std::cout<<"called bigInt equal"<<std::endl;
	delete [] number;
	size=obj.size;
	number=new uint16_t [size];
	for(unsigned int i=0;i<size;i++)
	{
		number[i]=obj.number[i];
	}
	positive=obj.positive;
	return *this;
}

bigInt bigInt::operator+(const bigInt &b)
{
	std::cout<<"enter into plus overload"<<std::endl;
	if(this->size<b.size)
	{
		for(unsigned int i=this->size;i<=b.size;i++)
			this->number[i]=0;
		this->size=b.size;
	}

	for(unsigned int i=0;i<=this->size;i++)
		{
			this->number[i]=this->number[i]+b.number[i];
			if(this->number[i]>9)
			{
				this->number[i+1]++;
				this->number[i]=this->number[i]%10;
			}
		}
	return *this;
}

bigInt bigInt::operator+(const int32_t numb)
{
	uint16_t *arr;//intToBigInt(numb);
//	std::cout<<"array="<<arr<<std::endl;
	uint8_t numbSize=returnNumbSize(numb);
	arr=new uint16_t [numbSize];
	arr=intToBigInt(numb);
	if(this->size<numbSize)
	{
		for(unsigned int i=this->size; i<=numbSize; i++)
			this->number[i]=0;
		this->size=numbSize;
	}

	for(unsigned int i=0;i<=this->size;i++)
	{
		this->number[i]=this->number[i]+arr[i];
		if(this->number[i]>9)
		{
			this->number[i+1]++;
			this->number[i]=this->number[i]%10;
		}
	}
	delete arr;
	return *this;
}

bigInt bigInt::operator-(const bigInt &b)
{

	return *this;
}
/*bigInt bigInt::operator=(const uint1024_t &numb)
{
	delete [] number;
	size=returnNumbSize(numb);
	number=new uint16_t [size];
	number=boostLongToBigInt(numb);
	positive=checkPositive(number,size);
	return *this;
}*/

bigInt bigInt::operator=(const int32_t numb)
{
	std::cout<<"called int equal"<<std::endl;
	delete [] number;
	size=0;
//	std::cout<<"before size"<<std::endl;
	size=returnNumbSize(numb);
//	std::cout<<this->number<<std::endl;
//	std::cout<<"numb to big int "<<*intToBigInt(numb)<<std::endl;
	number=intToBigInt(numb);
//	for(unsigned i=0;i<size;i++)
//		std::cout<<"new number["<<i<<"]= "<<number[i]<<std::endl;
	positive=checkPositive(number, size);
//	for(unsigned int i=0;i<size;i++)
//		std::cout<<"after checkPositive number["<<i<<"]= "<<number[i]<<std::endl;
	return *this;
//	return this;
}/**/

uint16_t  *intToBigInt(int32_t numb)
{
	std::cout<<"enter into intToBigInt"<<std::endl;
	uint16_t* res;
	uint8_t size=returnNumbSize(numb);
	res=new uint16_t [size];
	for(unsigned int i=0;i<size;i++)
	{
//		std::cout<<"int to big int iteration numb%10 "<<numb%10<<std::endl<<"new numb"<<numb/10<<std::endl;
		res[i]=numb%10;
//		std::cout<<"res "<<res[i]<<std::endl;
		numb=numb/10;
	}
//	std::cout<<"result res "<<*res<<std::endl;
//	for(unsigned int i=0;i<size;i++)
//		std::cout<<"res["<<i<<"]= "<<res[i]<<std::endl;
	return res;
}

uint16_t *boostLongToBigInt(uint1024_t numb)
{
	std::cout<<"enter into boostLongToBigInt"<<std::endl;
	uint16_t size=returnNumbSize(numb);
	uint16_t *mas=new uint16_t [size];
	for(unsigned int i=0;i<size;i++)
	{
		int a;
		if(numb%10==0)
			a=0;
		else
			if(numb%10==1)
				a=1;
			else
				if(numb%10==2)
					a=2;
				else
					if(numb%10==3)
						a=3;
					else
						if(numb%10==4)
							a=4;
						else
							if(numb%10==5)
								a=5;
							else
								if(numb%10==6)
									a=6;
								else
									if(numb%10==7)
										a=7;
									else
										if(numb%10==8)
											a=8;
										else
											a=9;
		mas[i]=a;
		numb=numb/10;
	}
	return mas;
}

void bigInt::show()
{
//	std::cout<<"show body"<<std::endl;
//	std::cout<<"before show size"<<std::endl;
//	std::cout<<"size="<<this->size<<std::endl;
//	std::cout<<"after show size"<<std::endl;
	for(int i=size-1;i>=0;i--)
		std::cout<<"number["<<i<<"]= "<<number[i]<<std::endl;
//	std::cout<<"reverce out"<<std::endl;
//	for(unsigned int i=0;i<size;i++)
//		std::cout<<"number["<<i<<"]= "<<number[i]<<std::endl;
	std::cout<<std::endl;
}
