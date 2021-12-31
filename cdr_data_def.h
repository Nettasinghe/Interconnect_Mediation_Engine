
//////////////////////////////////////////////////////////////////////
//
// cdr_data_defs.h: 
// header file Interconnect Mediation Engine
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


// All the constants that are required for the CDR Broker

#define 	RECORD_FILLER 'F'
#define 	CDR_FILL_PATTERN 0x00


static const int	SIGNATURE_LENGTH=5;
static const int	SIGNATURE_OFFSET = 1;  
static const int	CDR_BUF_LENGTH = 300;

// #define VERBOSE

// CDR field positions
static const int  CDR_FIXED_LENGTH = 22;

static const int  circuit_allocation_time_stamp_LENGTH=6;
static const int  end_of_call_time_stamp_LENGTH=5;

static const int  cdr_start_of_end_of_call_time_stamp=(18-1);
static const int  cdr_start_of_circuit_allocation_time_stamp=(9-1);
static const int  cdr_start_of_type_of_msc=(3-1);
static const int  cdr_start_of_call_termination_type=(4-1);
static const int  cdr_start_of_origin_of_call_indicator=(6-1);
static const int  cdr_start_of_required_tele_service=(7-1);
static const int  cdr_start_of_required_bearer_service=(8-1);
static const int  cdr_start_of_call_duration=(15-1);
static const int  cdr_start_of_call_data_format_number=(27-1);


// variable

static const int  conversation_duration_POSITION=(15-1);
static const int  conversation_duration_LENGTH=(3);


static const int  mobile_station_identity_POSITION=(23-1);
static const int  msc_identity_POSITION=(33-1);
static const int  msc_identity_LENGTH=(1+9);

static const int  called_party_number_LENGTH=(1+17);

static const int  calling_party_number_LENGTH=(1+17);
static const int  outgoing_trunk_group_LENGTH=(1+5);
static const int  incoming_trunk_group_LENGTH=(1+7);



