
//////////////////////////////////////////////////////////////////////
//
// cdr.h: 
// header file for Interconnect Mediation Engine classses
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


#pragma warning(disable:4786)
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <iso646.h>
#include <fstream>
using namespace std;

#include "cdr_data_def.h"
// comment to disable cdr filter
//#define CDR_FILTER

// File handling
// Referances
//   a) C++ Primer Third edition Stanly B.Lippman Section 20 (page 1063-1121)
//   b) 

class LocateCDR;
class cdr_file_statistics;

class imsi_filter
{
public:
	set<string> valid_imsi_list;
	
	bool is_valid_imsi(string a);
	bool read_imsi_file(string name);
	void print();
};

class unpack
{
public:
	unsigned char get_most_significant_nibble(unsigned char a);
	unsigned char get_least_significant_nibble(unsigned char a);
	unsigned char get_TBCD(unsigned char a);
	unsigned char get_BIN(unsigned char a);
	char* get_BCD(unsigned char *a, int length, char *buf);
	char* get_TBCD(unsigned char *a, int length, char *buf);
	int get_HEXA(unsigned char *a, int length);
	char* get_ASCII(unsigned char *a, int length, char *buf);
	char* get_ASCII_without_space(unsigned char *a, int length, char *buf);
};

class no_identity
{
public:
	int ext;
	char id[256];
	void init();
};

ostream& operator<<(ostream& out, no_identity x);


// walks the pointer in the buffer of the cdr_buffer classes 
class cdr_decode
{
	unsigned char*	position_to_decode_from;
	unsigned char* cdr_start;
	int record_length;
	int checked_record_length;
	int cdr_length;
	cdr_file_statistics *statistics;
	bool valid;

	void init();

public:
	
	unpack U;   // a buffer to put the upacked stuff into
	
	bool init_var_length_field(unsigned char *s);
	int  get_field_length();
	int  get_move_field_length();
	int  adjust_read_field_length(int a);
	bool is_over_run(int a);
	int  get_read_field_length();
	
	bool move_to_next_filed(int length);
	bool move_to_next_record(int length);
	
	// Fixed legth Arrrays
	char circuit_allocation_time_stamp[circuit_allocation_time_stamp_LENGTH*2+1];
	char end_of_call_time_stamp[end_of_call_time_stamp_LENGTH*2+1];

	// Variable length Arrays
	char msc_identity[msc_identity_LENGTH*2+1];
	char called_party_number[called_party_number_LENGTH*2+1];
	char calling_party_number[calling_party_number_LENGTH*2+1];
	char outgoing_trunk_group[outgoing_trunk_group_LENGTH*2+1];
	char incoming_trunk_group[incoming_trunk_group_LENGTH*2+1];
	
	
	int type_of_msc;
	int type_of_call;
	int call_termination_type;
	int origin_of_call_indicator;
	int charging_indicator;
	int required_tele_service;
	int required_bearer_service;
	int call_duration;
	int call_data_format_number;

	int	called_party_number_noai;	// Nature of Address Indicator
	int	calling_party_number_noai;	// Nature of Address Indicator
	
	
	
	// fixed
	bool get_circuit_allocation_time_stamp();
	bool get_end_of_call_time_stamp();
	
	// Variable
	bool skip_mobile_station_identity();
	bool skip_list_of_service_complements();
	bool skip_link_information();
	bool skip_mobile_subscriber_identity();
	bool get_msc_identity();
	bool get_called_party_number();
	bool get_calling_party_number();					// ms_location_identity
	bool skip_ms_location_identity_extension();
	bool get_outgoing_trunk_group();
	bool get_incoming_trunk_group();	

	int get_three_byte_binary(unsigned char * a);
	int get_four_byte_binary(unsigned char * a);
	bool get_ints();
	
	int decode(unsigned char *K); //, imsi_filter *F);
	void set_statistics_collector(cdr_file_statistics *s);
};

ostream& operator<<(ostream& out, cdr_decode x);


class file_locations
{
private:
	string path;
	string path_and_name;
public:	
	void init(string i);
	char* get_full_file_name(string i);
};

unsigned char bcd_to_int(unsigned char a);

class cdr_file_statistics
{
public:
	int file_id;
	int valid_cdr_count;
	int error_count;
	int bytes_read;
	int reject_cdr_count;
	string first_cdr_date;		// date of newest cdr
	string last_cdr_date;		// date of oldest cdr
	string rating_start_date;
	int rating_duration;
	void init();
};
ostream& operator<<(ostream& out, cdr_file_statistics x);


typedef map <string, cdr_file_statistics, less<string> > DUMP_DEF;
// read in list of cdr file names

class cdr_files
{
//private:
public:
	DUMP_DEF dumps;
	DUMP_DEF::iterator open_file_name_iter;
	FILE *cdr_dump_file;
	cdr_file_statistics *statistics;	// from files container
	bool file_open;						// there is a vaild open cdr data file
	int reads_from_file;				// number of times the file has been accessed, when 1 upstream buffers are flushed
	int bytes_read;						// the data raed per read
	long total_bytes_read;				// applies to all data file, total for the whole rating run
	int  file_id;						// The CDR file inventory number
	long file_position;					// start of cdr from begining of the cdr file (in bytes)

	file_locations active_file;
public:
	bool read_cdr_dump_file_list(char *name);
	bool open_cdr_dump_file(char *name);
	bool insert(string file_name, cdr_file_statistics s);
	void db_read();
	void db_update(cdr_file_statistics s);
	bool get_next_file(FILE **fp, cdr_file_statistics **s); // bad coupling here
	int get_first_file_id();
public:
	void print();
	bool init(string path);
	int get_cdr_location();

	~cdr_files();
};


// The methods will vary for different CDR types in
// the inherited classes
// length = leading_guard + trailing_guard + buffer_length
class cdr_buffer
{
private:
	cdr_file_statistics *statistics;// useage statistics
	int bytes_read;					// bytes read in by block read
	int cdr_count;
	int cdr_position;				// location of cdr from start of file
	int buffer_size;				// size of buffer in bytes
	unsigned char cdr_length;

public:
	unsigned char *buffer;			// start of cdr buffer 
	unsigned char *current;			// read pointer {buffer <= current <= (buffer+length)}
	unsigned char *data_end;		// the end of the requested data sequence { buffer <= data_end <= (buffer+length)}
									// used for walking current pointer only
	unsigned char *end_of_buffer;	// end of allocated space for buffer. used for verifcation only
	bool get_cdr_start(); // =0		// locate a new cdr
public:

	bool read_cdr_file(FILE *fp, cdr_file_statistics *s);
	bool get_new_cdr();
	void print_cdr_in_hex();
	cdr_buffer(int size);
	void init();
	int get_cdr_position();
};


class cdr_rejects
{
public:
	string start_date;
	string end_date;

	class cdr_id
	{
	public:
		int file_id;
		int file_position;
		bool operator < (const cdr_id &s) const;
	};

	set<cdr_id> reject_cdr_list;
	bool read_reject_date_range_file(string name);
	bool is_reject(int file_id, int file_pos);
	void insert(int file_id, int file_pos);
	bool sanitize_date(string dte);
	void print();
	void db_read();
};


