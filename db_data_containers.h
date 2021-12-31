
//////////////////////////////////////////////////////////////////////
//
// db_data_containers.h: 
// header file for Interconnect Mediation Engine classe definitions 
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


#pragma warning(disable:4786)

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <stdio.h>

using namespace std;


static const int MIN_YEAR = 1949;
static const int MAX_YEAR = 2051;

typedef enum {T_UNDEF, T_ON, T_OFF} e_token_state;



class reng_time;

class reng_time
{
public:
	int hour;
	int min;
	int second;
	bool set_time(int h, int m, int s=0);
	bool set_time(char *t);
	bool set_h_m(const char *t);
	bool set_from_db(char *t, int secs);

	bool operator < (const reng_time  &s) const;
	reng_time operator+ (int s) const;
	void Print();
	void init();
};


ostream& operator<<(ostream& out, reng_time x);

class reng_date
{
public:
	int year;
	int month;
	int day;
	bool operator < (const reng_date  &s) const;
	bool set_date(int y, int m, int d);
	bool set_date(char *d);
	void init();
};

ostream& operator<<(ostream& out, reng_date x);


class reng_date_time
{
public:
	reng_date date;
	reng_time time;
	bool set_date_time(char *d);
	bool operator < (const reng_date_time  &s) const;
};

ostream& operator<<(ostream& out, reng_date_time x);




// CDR -- begin ---------------------------------------------------------------
class cdr_decode;

class decoded_cdr
{
public:
	bool vaild;

	int file_id;			// the number of the file
	int file_pos;			// the bytes from start of cdr where file started

	// call detail
	int type_of_msc;					// Always 4h
	int type_of_call;					// 8h, Ah
	int call_termination_type;			// 0h, 1h, 3h
	int origin_of_call_indicator;		// 0h, 1h

	//---------------------------------------------------------------
	int charging_indicator;				// Not Applicable - Always F
	int required_tele_service;			// Not Used - Always FF
	int required_bearer_service;		// Not Used - Always FF
	//---------------------------------------------------------------

	int call_duration;

	int call_data_format_number;		// Within "List of service complements"

	string	circuit_allocation_time_stamp;
	string	end_of_call_time_stamp;
	string	msc_identity;
	string	called_party_number;
	int		called_party_number_noai;	// Nature of Address Indicator
	string	calling_party_number;
	int		calling_party_number_noai;	// Nature of Address Indicator

	string	outgoing_trunk_group;
	string	incoming_trunk_group;

	

	bool unpack(cdr_decode *a);
	void init(int f_id, int f_pos);

	reng_time d_circuit_allocation_time;
	reng_date d_circuit_allocation_date;

};


class token
{
public:
	e_token_state token_state;
	string file_name;
	string token_text;

	FILE *token_file;

	bool set_token(e_token_state a);
	token(string f_name);
	bool is_runable(void);
	e_token_state code_token(string a);
	string decode_token(e_token_state a);
};




