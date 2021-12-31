
//////////////////////////////////////////////////////////////////////
//
// cdr_buffer.cpp: 
//			implementation of the cdr_buffer class.
// Interconnect Mediation Engine
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


#include "cdr.h"
#include "defines.h"


// from 5 th byte in CDR
#define CIRCUIT_OFFSET 4  // 4 bytes from 0xff to start of circuit allocation time stamp
#define CALL_OFFSET 13    // 13 bytes from 0xff to start of call time stamp
#define FF_OFFSET 4		  // 4 bytes from start of cdr to 0xff


unsigned char bcd_to_int(unsigned char a)
{
	return ((unsigned char) ((((a & 0xf0)>>4)*10) + (a & 0x0f)));
}


// open a vaild file pointer and collects a bit of statistics as well
bool cdr_buffer::read_cdr_file(FILE *fp, cdr_file_statistics *s)
{
	bool found = false;
	// read_cdr_file();
	bytes_read = fread(buffer, sizeof(unsigned char), buffer_size, fp);
	statistics = s;
	statistics->bytes_read = bytes_read;

	if(bytes_read == 0)
	{
		return false;
	}
	else if (bytes_read == buffer_size)
	{
		cout<<"<ERROR> possible cdr buffer overflow "<<bytes_read<<endl;
		return false;
		//exit(1);
	}

	data_end = buffer + bytes_read;
	current =  buffer;

	return found; // all data files read
}


void cdr_buffer::init()
{
	bytes_read		= 0;
	current			= buffer;
	data_end		= buffer;
	cdr_length		= 0;
	cdr_count		= 0;
	cdr_position	= 0;				// location of cdr from start of file

// inialise buffer area, useful for debugging only
//	for(unsigned char* a=buffer; a<end_of_buffer; a++)
//		*a=0x00;
}

// object lives for lifetime of program
cdr_buffer::cdr_buffer(int size)
{
	buffer_size = size;
	buffer = new unsigned char[buffer_size];
	if (!buffer)
	{
		cout<<"ERR: FATAL cant allocate "<<buffer_size/1024<<" KB  for CDR buffer"<<endl;
		exit(1);
	}

	end_of_buffer = buffer+buffer_size;
	init();
}


class cdr_tm
{
public:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	
	bool check_from_year();
	bool check_from_month();
};


bool cdr_tm::check_from_month()
{
	bool valid = true;
	if ( !(month >=1 && month <= 12))
		valid = false;
	else if ( !(day >=1 && day <= 31))
		valid = false;
	else if (!(hour >= 0 && hour <= 23))
		valid = false;
	else if (!(min >=0 && min <= 59 ))
		valid = false;
	else if (!(sec >= 0 && sec <= 59))
		valid = false;
	
	return valid;
}


bool cdr_tm::check_from_year()
{
	bool valid=check_from_month();

	if (!(year >= 0 && year <= 99))
		valid = false;
	
	return valid;
}


// see ALCATEL document 
// Feature specification ALCATEL 1000 E10 
// Local Operation and Maintenance
// Call Records Format (GSM)
// search for start signature
bool cdr_buffer::get_cdr_start()
{
	// The cdr start signature (*=don't care nibble, x is hex)
	// length is five bytes
	//     0x**    0x11    0x**    0x0*	   0xff  
	//		0		1		2		3		4   <- location in array
	//			   -3			   -1		0    = current and offsets from current
	
	unsigned char *b_ptr; // buffer pointer
	
	unsigned char record_length;
	if(cdr_length ==0)
		b_ptr = current + FF_OFFSET - 1;	// max look back is 3 subtract 1 for auto increment (b++)
	else								// as you enter the while loop 
		b_ptr = current + cdr_length;
	
	cdr_tm circuit, call;
	
	do {
		b_ptr++;
		
		if(*b_ptr != 0xff)		// move along till 0xff is found
			continue;
		
		if ( (*(b_ptr-1) & 0xf0)==0x00 && *(b_ptr-3)==0x11)	// pattern match
		{
			// sanity of length must be greater than fixed portion of
			// 22 bytes, typically 44 to 77 bytes
			if (*(b_ptr-4) < 22)
				continue;
			else
				record_length = *(b_ptr-4);
			
			if(data_end >= b_ptr+cdr_length-4)
			{
				// circuit allocation time stamp
				// offset is from 5 the byte in cdr which has value 0xff, our first anchor point
				circuit.year	= bcd_to_int( *(b_ptr+CIRCUIT_OFFSET));
				circuit.month	= bcd_to_int( *(b_ptr+CIRCUIT_OFFSET+1));
				circuit.day		= bcd_to_int( *(b_ptr+CIRCUIT_OFFSET+2));
				circuit.hour	= bcd_to_int( *(b_ptr+CIRCUIT_OFFSET+3));
				circuit.min		= bcd_to_int( *(b_ptr+CIRCUIT_OFFSET+4));
				circuit.sec		= bcd_to_int( *(b_ptr+CIRCUIT_OFFSET+5));
				
			//	if (!circuit.check_from_year())
			//		continue;
				
				// call time stamp
				call.month	= bcd_to_int( *(b_ptr+CALL_OFFSET));
				call.day	= bcd_to_int( *(b_ptr+CALL_OFFSET+1));
				call.hour	= bcd_to_int( *(b_ptr+CALL_OFFSET+2));
				call.min	= bcd_to_int( *(b_ptr+CALL_OFFSET+3));
				call.sec	= bcd_to_int( *(b_ptr+CALL_OFFSET+4));
				
			//	if (!call.check_from_month())
			//		continue;

				// check cdr does not exceed file end
				if(b_ptr-FF_OFFSET+record_length > data_end)
				{
					cout<<"WARN ------------PARTIAL CDR----------"<<endl;
					statistics->reject_cdr_count++;
					continue;
				}
				
				//	all dates seem to pass initial sanity check
				current		= b_ptr - FF_OFFSET;
				cdr_length	= record_length; // are we missing a one here ?
				cdr_count++;
				statistics->valid_cdr_count++;
				cdr_position = current - buffer;

				return true;  // cdr start signature found
			}
		}
	}while (b_ptr < data_end);

	return false;
}


// current must be at start of cdr 
// or else premature exit
void cdr_buffer::print_cdr_in_hex()
{
	int k=0;
	
	for(unsigned char *i=current; i<=current+cdr_length; i++)
	{
		if(i > data_end)
		{
			printf(" ERR: Out of vaild data sequence ");
			return;
		}
		if (!(k%8))
			printf("   ");
		if (!(k%16))
			printf("\n %04x  ",i-buffer);
		printf(" %02x",(int)(*i));
		k++;
	}
	printf("\n");
}

int cdr_buffer::get_cdr_position()
{
	return cdr_position;
}

