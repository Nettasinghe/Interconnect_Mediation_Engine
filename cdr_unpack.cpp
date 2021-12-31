
//////////////////////////////////////////////////////////////////////
// cdr_unpack.cpp: 
//			implementation of the cdr_unpack class.
// Interconnect Mediation Engine
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


#include "cdr.h"
#include "defines.h"
#include "db_data_containers.h"

#include <ctype.h>

extern cdr_buffer *cdr_store;
extern cdr_decode raw_cdr;	
extern ofstream f_log;


// upacks all the condensed data into ascii strings
//	a) BCD	= Binary coded decimal
//	b) TBCD	= Telephony binary coded decimal, BCD with swapped digits)
//	c) BIN	= Plain binary
//  d) HEXA = Hex same as binary



unsigned char unpack::get_most_significant_nibble(unsigned char a)
{
	return( a>>4);
}


unsigned char unpack::get_least_significant_nibble(unsigned char a)
{
	return( a & 0x0f);
}


// The decimal digits are swapped compared BCD
unsigned char unpack::get_TBCD(unsigned char a)
{
	unsigned char MSN, LSN;
	LSN=get_most_significant_nibble(a);
	MSN=get_least_significant_nibble(a);

	return( (MSN*10) | LSN);
}


unsigned char unpack::get_BIN(unsigned char a)
{
	return (a);
}


// put in ascii digit string a cdr format bcd record
// the conversion terminates when a non digit character is found
char* unpack::get_BCD(unsigned char *a, int length, char *buf)
{
	int k;
	unsigned char b,c;
	for(k=0; k<length*2; k++)
	{
		b = *(a+k/2);		// the byte must be visited twice to get both digits.
							// implicit rounding to floor during integer divison does this

		if (!(k%2))			// odd (not even) digit, this sequence is swapped in TBCD conversion
			b = b >> 4;		// most significant nibble 
		else			
			b = b & 0x0f;	// least significant nibble

		c = b+'0';			// get ASCII digit

		if (!isdigit(c))
		{
			// 0xf if the end of record filler in the  cdr spec
			if (!(0xf == b || 0xa==b || 0xc==b)) 
			{
				f_log << "file_pos : " << cdr_store->get_cdr_position() << endl;
				f_log <<"<ERROR> BCD value not a digit = {"<<c<<"}"<<endl<<endl;
			}
			break;
		}
		buf[k]=c;
	}
	buf[k]='\0';		// for loop exits with k= length*2 +1 
						// or breaks with K set to 1+last decoded char position 
	return buf;
}

// put in ascii digit string a cdr format Telephony BCD record
// the conversion terminates when a non digit character is found
char* unpack::get_TBCD(unsigned char *a, int length, char *buf)
{
	int k;
	unsigned char b,c;
	for(k=0; k<length*2; k++)
	{
		b = *(a+k/2);		// the byte must be visited twice to get both digits.
							// implicit rounding to floor during integer divison does this
		
		if (k%2)			// even digit, this sequence is swapped in BCD conversion
			b = b >> 4;		// most significant nibble 
		else			
			b = b & 0x0f;	// least significant nibble  
		
		c = b+'0';			// get ASCII digit

		if (!isdigit(c))
		{
			// 0xf is the end of record filler in the  cdr spec
			// others characters arrive but no body has explained how yet!
			// does not seem to do any harm so suppress errors may not be wise (ajit)
			if (!(0xf==b || 0xa==b || 0xc==b) ) 
			{
				f_log << "file_pos : " << cdr_store->get_cdr_position() << endl;
				f_log <<"<ERROR> TBCD value not a digit = {"<<c<<"}"<<endl<<endl;
			}
			break;
		}
		buf[k]=c;
	}
	buf[k]='\0';			// for loop exits with k= length*2 +1 
							// or breaks with K set to 1+last decoded char position 

	return buf;
}


int unpack::get_HEXA(unsigned char *a, int length)
{
	int val=0;


	val = int(*a)*256+int(*(a+1));

	return val;
}


// copy ascii characters around
char* unpack::get_ASCII(unsigned char *a, int length, char *buf)
{
	int i;
	for(i=0; i<length; i++)
	{
		buf[i]=a[i];
	}
	buf[i] ='\0';
	return buf;
}

// copy ascii characters around - but null terminates when space character found
char* unpack::get_ASCII_without_space(unsigned char *a, int length, char *buf)
{
	int i;
	for(i=0; i<length; i++)
	{
		if (a[i] == 32)
		{
			buf[i] ='\0';
			return buf;
		}
		buf[i]=a[i];
	}
	buf[i] ='\0';
	return buf;
}


