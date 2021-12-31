


//////////////////////////////////////////////////////////////////////
//
// decoded_cdr.cpp: 
//			implementation of the decoded_cdr class.
// Interconnect Mediation Engine
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


#include "cdr.h"
#include "db_data_containers.h"
#include "defines.h"


extern 	cdr_decode raw_cdr;			// all the methods to extract data from a cdr


void decoded_cdr::init(int f_id, int f_pos)
{
	vaild=true;

	// cdr management
	file_id		= f_id;				// the number of the file
	file_pos	= f_pos;			// the bytes from start of cdr where file started

	// CDR values
	type_of_msc				= 0xf;;					// Always 4h
	type_of_call			= 0xf;;					// 8h, Ah
	call_termination_type	= 0xf;;					// 0h, 1h, 3h
	origin_of_call_indicator= 0xf;;					// 0h, 1h

	call_duration			= 0;

	call_data_format_number = 0;					// Within "List of service complements"

	circuit_allocation_time_stamp	= "";
	end_of_call_time_stamp			= "";
	msc_identity					= "";
	called_party_number				= "";
	called_party_number_noai		= 0;			// Nature of Address Indicator
	calling_party_number			= "";
	calling_party_number_noai		= 0;			// Nature of Address Indicator

	outgoing_trunk_group			= "";
	incoming_trunk_group			= "";
};

// unpack the bits
bool decoded_cdr::unpack(cdr_decode *cdr) 
{
	circuit_allocation_time_stamp = cdr->circuit_allocation_time_stamp; 
	
	// make Y2K compliant 50-99 in 1900 00-49 in 2000 
	if(circuit_allocation_time_stamp.substr(0,2) < "50")
		circuit_allocation_time_stamp = "20"+circuit_allocation_time_stamp;
	else
	{
		circuit_allocation_time_stamp = "19"+circuit_allocation_time_stamp;
	}
	
	// after Y2K fix YYYYMMDDHHMISS
	d_circuit_allocation_time.set_time((char*)circuit_allocation_time_stamp.c_str()+8);
	d_circuit_allocation_date.set_date((char*)circuit_allocation_time_stamp.c_str());
	

	type_of_msc = cdr->type_of_msc;
	if (type_of_msc != 0x04)
	{
		cout<<"Msc bad "<<type_of_msc<<endl;
	}
	
    type_of_call = cdr->type_of_call;
	if (type_of_call != 0x08 && type_of_call != 0x0A)
	{
		cout<<"type_of_call bad "<<type_of_call<<endl;
	}
	
	
    call_termination_type = cdr->call_termination_type;
	if (call_termination_type !=0x0 && call_termination_type != 0x01 && call_termination_type != 0x03)
	{
		cout<<"call_termination_type bad "<<call_termination_type<<endl;
	}
	
	
    origin_of_call_indicator = cdr->origin_of_call_indicator;
	if (origin_of_call_indicator != 0x0 && origin_of_call_indicator != 0x01)
	{
		cout<<"origin_of_call_indicator bad "<<origin_of_call_indicator<<endl;
	}
	
	
    charging_indicator = cdr->charging_indicator;
	if (charging_indicator != 0x0f )
	{
		cout<<"charging_indicator bad "<<charging_indicator<<endl;
	}
	
    required_tele_service = cdr->required_tele_service;
	if (required_tele_service != 0xff)
	{
		cout<<"required tele service bad "<<required_tele_service<<endl;
	}
	
    required_bearer_service = cdr->required_bearer_service;
	if ( required_bearer_service != 0xff)
	{
		cout<<"required_bearer_service bad "<<required_bearer_service<<endl;
	}
	
	call_duration = cdr->call_duration;
	if (call_duration < 0 || call_duration > 99999999)
	{
		cout<<"call_duration bad "<<call_duration<<endl;
		call_duration=0;
	}
	
	end_of_call_time_stamp	= cdr->end_of_call_time_stamp;

	call_data_format_number	= cdr->call_data_format_number;

	msc_identity				= cdr->msc_identity;

	
	if ((cdr->called_party_number_noai==1) && (strlen(cdr->called_party_number) > 0))	// International
	{
		called_party_number			= "0" ;
		called_party_number.append(cdr->called_party_number);
	//	strcat((char *)called_party_number.c_str(), cdr->called_party_number);
	}
	else
		called_party_number			= cdr->called_party_number;

	called_party_number_noai	= cdr->called_party_number_noai;

	
	if ((cdr->calling_party_number_noai==1) && (strlen(cdr->calling_party_number) > 0))	// International
	{
		calling_party_number		= "0";
		calling_party_number.append(cdr->calling_party_number);

	//	strcat((char *)calling_party_number.c_str(), cdr->calling_party_number);
	}
	else
		calling_party_number		= cdr->calling_party_number;

	calling_party_number_noai	= cdr->calling_party_number_noai;

	if ( strlen(cdr->outgoing_trunk_group) == 0 )
		outgoing_trunk_group = "Dummy1";
	else
		outgoing_trunk_group		= cdr->outgoing_trunk_group;

	if ( strlen(cdr->incoming_trunk_group) == 0 )
		incoming_trunk_group = "Dummy2";
	else
		incoming_trunk_group		= cdr->incoming_trunk_group;

	return true;
}


