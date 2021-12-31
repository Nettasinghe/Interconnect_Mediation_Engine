
//////////////////////////////////////////////////////////////////////
//
// cdr_decode.cpp: 
//			implementation of the cdr_decode class.
// Interconnect Mediation Engine
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


#include "cdr.h"
#include "defines.h"
#include "db_data_containers.h"

extern cdr_buffer *cdr_store;
extern ofstream f_log;


void cdr_decode::init()
{
	// init all buffers

	circuit_allocation_time_stamp[0]	='\0';
	end_of_call_time_stamp[0]			='\0';

	msc_identity[0]						='\0';
	called_party_number[0]				='\0';
	calling_party_number[0]				='\0';
	outgoing_trunk_group[0]				='\0';
	incoming_trunk_group[0]				='\0';
	
	valid = true;
}


bool cdr_decode::init_var_length_field(unsigned char *s)
{
	position_to_decode_from = s;
	record_length = *position_to_decode_from;
	checked_record_length = record_length;
	return true;
}

int  cdr_decode::get_read_field_length()
{
	return checked_record_length;
}

int  cdr_decode::get_move_field_length()
{
	return record_length;
}


int  cdr_decode::adjust_read_field_length(int a)
{
	checked_record_length=a;
	valid=false;
	return checked_record_length;
}


bool cdr_decode::is_over_run(int a)
{
	bool over_run = false;

	if (record_length > a)
	{
		over_run = true;
		statistics->error_count++;
	}
	return (over_run);
}


// ------------------------------ Fixed length---------------------------------
bool cdr_decode::get_circuit_allocation_time_stamp()
{
	U.get_BCD((cdr_start+cdr_start_of_circuit_allocation_time_stamp),
		circuit_allocation_time_stamp_LENGTH, circuit_allocation_time_stamp);

	// sieve for max and min cdr times in file (adds 5% extra to decode time)
	string min_max_time=circuit_allocation_time_stamp;

	// y2k
	if(min_max_time.substr(0,2) < "50")
		min_max_time = "20"+min_max_time;
	else
		min_max_time = "19"+min_max_time;

	if (min_max_time < statistics->first_cdr_date)
		statistics->first_cdr_date = min_max_time;
	
	if (min_max_time > statistics->last_cdr_date)
		statistics->last_cdr_date = min_max_time;

	return true;
}


bool cdr_decode::get_end_of_call_time_stamp()
{
	U.get_BCD( (cdr_start+cdr_start_of_end_of_call_time_stamp), end_of_call_time_stamp_LENGTH, 
		end_of_call_time_stamp);

	return true;
}



// ------------------------ variable length fields ----------------------------

bool cdr_decode::skip_mobile_station_identity()
{
	init_var_length_field(cdr_start+mobile_station_identity_POSITION);
	move_to_next_record(get_move_field_length());
	return true;
}


bool cdr_decode::skip_list_of_service_complements()
{
	init_var_length_field(position_to_decode_from);
	move_to_next_record(get_move_field_length());
	return true;
}


bool cdr_decode::skip_link_information()
{
	init_var_length_field(position_to_decode_from);
	move_to_next_record(get_move_field_length());
	return true;
}


bool cdr_decode::skip_mobile_subscriber_identity()
{
	init_var_length_field(position_to_decode_from);
	move_to_next_record(get_move_field_length());
	return true;
}


bool cdr_decode::get_msc_identity() // Mobile switching center
{
	init_var_length_field(position_to_decode_from);

	if(is_over_run(msc_identity_LENGTH))
	{
		f_log << "file_pos : " << cdr_store->get_cdr_position() << endl;
		f_log <<"WARN  msc_identity  overflow (truncated)"<<endl<<endl;;
		adjust_read_field_length(msc_identity_LENGTH);
		valid=false;
	}

	if(get_read_field_length())
		U.get_TBCD(position_to_decode_from+1+1, get_read_field_length()-1, msc_identity);

	move_to_next_record(get_move_field_length());

	return true;
}



bool cdr_decode::get_called_party_number()  
{
	init_var_length_field(position_to_decode_from);

	if(is_over_run(called_party_number_LENGTH))
	{
		f_log << "file_pos : " << cdr_store->get_cdr_position() << endl;
		f_log <<"WARN  called_party_number  overflow (truncated)"<<endl<<endl;;
		adjust_read_field_length(called_party_number_LENGTH);
		valid=false;
	}

	called_party_number_noai = *(position_to_decode_from+1);
	// *$$$ ****
	// get the  3 $ bits, mask out the 5 * bits
	called_party_number_noai = ( called_party_number_noai >> 4 ) & 0x07;

	if(get_read_field_length())
	{
		U.get_TBCD(position_to_decode_from+1+1, get_read_field_length()-1, called_party_number);
	}
	move_to_next_record(get_move_field_length());


	return true;
}



bool cdr_decode::get_calling_party_number()  
{
	init_var_length_field(position_to_decode_from);
	
	if(is_over_run(calling_party_number_LENGTH))
	{
		f_log << "file_pos : " << cdr_store->get_cdr_position() << endl;
		f_log <<"WARN  ms_location_identity  overflow (truncated)"<<endl;
		adjust_read_field_length(calling_party_number_LENGTH);
		valid=false;
	}

	calling_party_number_noai = *(position_to_decode_from+1);
	// *$$$ ****

	// get the  3 $ bits, mask out the 5 * bits
	calling_party_number_noai = ( calling_party_number_noai >> 4 ) & 0x07;
	
	U.get_TBCD(position_to_decode_from+1+1, get_read_field_length()-1, calling_party_number);

	move_to_next_record(get_move_field_length());
	
	return true;
}



bool cdr_decode::skip_ms_location_identity_extension() 
{
	init_var_length_field(position_to_decode_from);
	move_to_next_record(get_move_field_length());
	return true;
}



bool cdr_decode::get_outgoing_trunk_group() 
{
	init_var_length_field(position_to_decode_from);

	if(is_over_run(outgoing_trunk_group_LENGTH))
	{
		f_log << "file_pos : " << cdr_store->get_cdr_position() << endl;
		f_log <<"WARN  outgoing_trunk_group  overflow (truncated)"<<endl<<endl;
		adjust_read_field_length(outgoing_trunk_group_LENGTH);
		valid=false;
	}

	if(get_read_field_length()>1)
		U.get_ASCII_without_space((position_to_decode_from+1), get_read_field_length(), outgoing_trunk_group);

	move_to_next_record(get_move_field_length());

	return true;
}


bool cdr_decode::get_incoming_trunk_group() 
{
	init_var_length_field(position_to_decode_from);

	if(is_over_run(incoming_trunk_group_LENGTH))
	{
		f_log << "file_pos : " << cdr_store->get_cdr_position() << endl;
		f_log <<"WARN  incoming_trunk_group  overflow (truncated)"<<endl<<endl;
		adjust_read_field_length(incoming_trunk_group_LENGTH);
		valid=false;
	}

	if(get_read_field_length()>1)
		U.get_ASCII_without_space((position_to_decode_from+3), (5), incoming_trunk_group);

	move_to_next_record(get_move_field_length());

	return true;
}

// very crude 
int cdr_decode::get_three_byte_binary(unsigned char * a) 
{
	return a[0]*256*256+a[1]*256+a[2];
}

int cdr_decode::get_four_byte_binary(unsigned char * a) 
{
	return a[0]*256*256*256+a[1]*256*256+a[2]*256+a[3];
}



// all the stuff is in the fixed length portion of the cdr
bool cdr_decode::get_ints() 
{
	type_of_msc					= U.get_most_significant_nibble( *(cdr_start+cdr_start_of_type_of_msc));              
	type_of_call				= U.get_least_significant_nibble( *(cdr_start+cdr_start_of_type_of_msc));
	call_termination_type		= U.get_least_significant_nibble(*(cdr_start+cdr_start_of_call_termination_type));
	origin_of_call_indicator	= U.get_most_significant_nibble(*(cdr_start+cdr_start_of_origin_of_call_indicator));  
	//----------------------------------------------------------------------------------------
	charging_indicator			= U.get_least_significant_nibble(*(cdr_start+cdr_start_of_origin_of_call_indicator));
	required_tele_service		= U.get_BIN( *(cdr_start+cdr_start_of_required_tele_service));
	required_bearer_service		= U.get_BIN( *(cdr_start+cdr_start_of_required_bearer_service));
	//-----------------------------------------------------------------------------------------
	call_duration				= get_three_byte_binary(cdr_start+cdr_start_of_call_duration);
	//call_data_format_number		= get_four_byte_binary(cdr_start+cdr_start_of_call_data_format_number);

	return true;
}


bool cdr_decode::move_to_next_record(int length)
{
	position_to_decode_from += (length+1);

	// check if length of CDR is exceded
	// asssumes linear address space 
	if(position_to_decode_from > (cdr_start+cdr_length))
	{
		//cout << "file_id : " << gsm_decoded_cdr->file_id << "  " << "file_pos : " << gsm_decoded_cdr->file_pos << endl;
		//cout<<"CDR Overun ERROR {"<<hex<<(int)position_to_decode_from<<"} {"<<(int)(cdr_start+cdr_length)<<"}"<<dec<<endl;
	}
	return true;
}



void cdr_decode::set_statistics_collector(cdr_file_statistics *s)
{
	statistics = s;
}



int cdr_decode::decode(unsigned char *buf) //imsi_filter *F
{
	init();  // all the variables
	cdr_start	= buf;
	cdr_length	= *buf;
	
	// Fixed length
	get_circuit_allocation_time_stamp();
	get_end_of_call_time_stamp();
	get_ints();
	
	// variable length, must be called in order
	skip_mobile_station_identity();
	skip_list_of_service_complements();
	skip_link_information();
	skip_mobile_subscriber_identity();
	get_msc_identity();
	get_called_party_number();
	get_calling_party_number();					// ms_location_identity
	skip_ms_location_identity_extension();
	get_outgoing_trunk_group();
	get_incoming_trunk_group();					// info_from_fixed_network
	
	return 1;
}



ostream& operator<<(ostream& out, cdr_decode x)
{
	// fixed length data
	out<<"type of msc       = {"<<x.type_of_msc<<"}"<<endl;
	out<<"type of call      = {"<<hex<<x.type_of_call<<"}"<<dec<<endl;
	out<<"termination type  = {"<<hex<<x.call_termination_type<<"}"<<dec<<endl;
	out<<"origin of call ind= {"<<x.origin_of_call_indicator<<"}"<<endl;
	//out<<"charging indicator= {"<<x.charging_indicator<<"}"<<endl;
	//out<<"tele service      = {"<<hex<<x.required_tele_service<<"}"<<dec<<endl;
	//out<<"bearer service    = {"<<x.required_bearer_service<<"}"<<endl;
	out<<"cir time          = {"<<x.circuit_allocation_time_stamp<<"}"<<endl;
	out<<"call duration     = {"<<x.call_duration<<"}"<<endl;
	out<<"end of call time  = {"<<x.end_of_call_time_stamp<<"}"<<endl;
	//out<<"calldata format no= {"<<x.call_data_format_number<<"}"<<endl;
	
	// Variable length Arrays
	out<<"msc				= {"<<x.msc_identity<<"}"<<endl;		
	out<<"called party      = {"<<x.called_party_number<<"}"<<endl;
	out<<"called party noai = {"<<x.called_party_number_noai<<"}"<<endl;
	out<<"calling party     = {"<<x.calling_party_number<<"}"<<endl;
	out<<"called party noai = {"<<x.calling_party_number_noai<<"}"<<endl;
	out<<"out trunk group   = {"<<x.outgoing_trunk_group<<"}"<<endl;
	out<<"in trunk group    = {"<<x.incoming_trunk_group<<"}"<<endl;

	return out;
}








