#include "bigInt.h"
#include <memory>

bigInt::bigInt()
{
	std::cout<<"enter into blank creator"<<std::endl;
	this->positive=true;
	this->size=1;
	this->number=new uint16_t[1];
	this->number[0]=1;
}

bigInt::bigInt(uint32_t numb)
{
	std::cout<<"enter into creator from uint"<<std::endl;
	this->size=returnNumbSize(numb);
	this->number=new uint16_t [this->size];
	for(unsigned int i=0;i<this->size;i++)
	{
		this->number[i]=numb%10;
		numb=numb/10;
	}
//	this->positive=checkPositive(this->number,this->size);
}

bigInt::bigInt(int numb)
{
	std::cout<<"enter into creator from int"<<std::endl;
	this->positive=numb>=0;
	if(numb<0)
		numb=numb*(-1);
	this->size=returnNumbSize(numb);
	this->number=new uint16_t [this->size];
	for(unsigned int i=0;i<this->size;i++)
	{
		this->number[i]=numb%10;
		numb=numb/10;
	}
}
/*
bigInt::bigInt(const bigInt &obj)
{
	std::cout<<"enter into bigInt bigInt creator"<<std::endl;
	std::cout<<obj.size<<std::endl;
	if(obj.size>5)
		;
	number=new uint16_t [obj.size];
	for(unsigned int i=0;i<obj.size;i++)
		number[i]=obj.number[i];
}
*/
bigInt::~bigInt()
{
	std::cout<<"enter into destructor"<<std::endl;
//	delete [] number;
}

bigInt::bigInt(uint1024_t numb)
{
	std::cout<<"enter into creator from int1024"<<std::endl;
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

uint16_t* bigInt::returnNumber()
{
	std::cout<<"enter into returnNumber"<<std::endl;
	uint16_t* arr=new uint16_t[this->size];
	for(uint16_t i=0;i<this->size;i++)
		arr[i]=this->number[i];
	return arr;

}

bigInt bigInt::operator=(const bigInt &obj)
{
	std::cout<<"called bigInt equal"<<std::endl;
//	std::cout<<&obj<<std::endl;
	delete [] number;
//	std::cout<<"size="<<obj.size<<std::endl;
	size=obj.size;
	number=new uint16_t [size];
//	std::cout<<"address:"<<obj.number<<std::endl;
//	std::cout<<"show numb"<<std::endl;
	for(unsigned int i=0;i<size;i++)
	{
//		std::cout<<obj.number[i]<<std::endl;
		number[i]=obj.number[i];
	}
//	std::cout<<"showed numb"<<std::endl;
	positive=obj.positive;
	return *this;
}

bigInt bigInt::operator+(const bigInt &b)
{
	std::shared_ptr<bigInt> bufInt(new bigInt);
//	std::cout<<"after declaration of variable"<<std::endl;
	bufInt->size=this->size;
//	std::cout<<"after setting a size"<<std::endl;
	bufInt->number=this->returnNumber();
	bufInt->positive=this->positive;
	std::cout<<"enter into plus overload"<<std::endl;
	if(this->size<b.size)
	{
		for(unsigned int i=bufInt->size;i<=b.size;i++)
			bufInt->number[i]=0;
		bufInt->size=b.size;
	}

	for(unsigned int i=0;i<bufInt->size;i++)
	{
		bufInt->number[i]=bufInt->number[i]+b.number[i];
//		std::cout<<"this->number["<<i<<"]="<<this->number[i]<<std::endl;
		if(bufInt->number[i]>9)
		{
			uint16_t buf=bufInt->number[i];
			bufInt->number[i+1]=buf+1;
//			std::cout<<"this->number["<<i<<"+1]="<<this->number[i+1]<<std::endl;
			bufInt->number[i]=buf%10;
//			std::cout<<"this->number["<<i<<"]="<<this->number[i]<<std::endl;
		}
	}
//	std::cout<<bufInt<<std::endl;
	return *bufInt;
}
//there is a problem - if it changes this, left argument will be changed
bigInt bigInt::operator+(const int32_t numb)
{
	std::cout<<"enter into int plus overload"<<std::endl;
	bigInt lInt;
	bigInt rInt=numb;
	lInt.size=this->size;
	lInt.number=this->returnNumber();
	lInt.positive=this->positive;
	std::shared_ptr<bigInt> resInt(new bigInt);
	*resInt=lInt+rInt;
	return *resInt;
}

bigInt bigInt::operator-(const bigInt &b)
{
	std::shared_ptr<bigInt> resInt(new bigInt);
	bigInt a;
	a.size=this->size;
	a.number=this->returnNumber();
	a.positive=this->positive;
	if(!a.positive&&!b.positive)
		*resInt=a+b;
	return *resInt;
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

bool bigInt::operator<(const bigInt &b)
{
	if((this->positive)&&(b.positive))
		if(this->size>b.size)
			return false;
		else
			if(this->size<b.size)
				return true;
			else
			/*{
				unsigned int count=0;
				for(unsigned int i=this->size-1;i>=0;i--)
					if(this->number[i]>b.number[i])
						return false;
					else
						if(this->number[i]<b.number[i])
							count++;
				if(count==this->size)
					return true;
				else
					return false;
			}*/
			return this->moduleLower(b);
	else
		if((!this->positive)&&(b.positive))
			return true;
		else
			if((this->positive)&&(!b.positive))
				return false;
			else
				if(this->moduleBigger(b))
					return true;
				else
					return false;
}

bool bigInt::operator>(const bigInt &b)
{
	if(this->positive&&b.positive)
		return this->moduleBigger(b);
	else
		if((!this->positive)&&(b.positive))
			return false;
		else
			if((this->positive)&&(!b.positive))
				return true;
			else
				if(this->moduleLower(b))
					return true;
				else
					return false;
}

bool bigInt::operator==(const bigInt &b)
{
	if((this->size==b.size)&&(this->positive==b.positive))
	{
		for(int i=this->size-1;i>=0;i--)
			if(this->number[i]!=b.number[i])
				return false;
		return true;
	}
	else
		return false;
}

bool bigInt::operator>=(const bigInt &b)
{
	if(this->positive&&b.positive)
		if(this->size<b.size)
			return false;
		else
			if(this->size>b.size)
				return true;
			else
				return moduleBigger(b, true);
	else
		if((this->positive)&&(!b.positive))
			return true;
		else
			if((!this->positive)&&(b.positive))
				return false;
			else
				/*if(this->moduleBigger(b, true))
					return true;
				else
					return false;*/
				return moduleLower(b, true);
}

bool bigInt::operator<=(const bigInt &b)
{
	if(this->positive&&b.positive)
		if(this->size>b.size)
			return false;
		else
			if(this->size<b.size)
				return true;
			else
			{
				return moduleLower(b, true);
				unsigned int count=0;
				for(unsigned int i=this->size;i>=0;i--)
					if(this->number[i]>b.number[i])
						return false;
					else
						count++;
				if(count==this->size)
					return true;
				else
					return false;
			}
	else
		if(!this->positive&&b.positive)
			return true;
		else
			if(this->positive&&!b.positive)
				return false;
			else
				return moduleBigger(b, true);
}

bool bigInt::moduleBigger(const bigInt &b, bool equal)
{
	if(this->size<b.size)
		return false;
	else
		if(this->size>b.size)
			return true;
		else
		{
			unsigned int count=0;
			for(int i=this->size-1;i>=0;i--)
				if(this->number[i]<b.number[i])
					return false;
				else
				{
					count++;
					if((this->number[i]>b.number[i])&&(!equal))
						count++;
				}
			if(((count>this->size)&&(!equal))||((count==this->size)&&(equal)))
				return true;
			else
				return false;
		}
}

bool bigInt::moduleLower(const bigInt &b, bool equal)
{
	std::cout<<"enter modulelower"<<std::endl;
	if(this->size>b.size)
		return false;
	else
		if(this->size<b.size)
			return true;
		else
		{
			unsigned int count=0;
			for(int i=this->size-1;i>=0;i--)
				if(this->number[i]>b.number[i])
					return false;
				else
				{
					count++;
					if((this->number[i]<b.number[i])&&(!equal))
						count++;
				}
			if(((count>this->size)&&(!equal))||((count==this->size)&&(equal)))
				return true;
			else
				return false;
		}
}
