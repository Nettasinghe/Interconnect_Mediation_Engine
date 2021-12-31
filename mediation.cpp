

///////////////////////////////////////////////////////////////////////////////////////////
// 
// Telco Switch Mediation Engine for Alcate SSP version (Interconnect Mediation Engine) –
// --------------------------------------------------------------------------
// Telecom Switches such as MSCs, GGSNs, SMSCs and VAS servers store subscribers Call Detail 
// Record (CDR) data in encoded formats of either proprietary or ASN.1. Switch Mediation Engine
// functions as the intermediary between the Telco Network and the Billing System by decoding 
// the CDRs and transforming (amalgamating, stitching and enhancing) them to the input format 
// expected by the Billing System.
// Interconnect Mediation Engine decodeds Alcatel GMSC CDRs in SSP version (which is proprietary).
//
///////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//
// mediation.cpp
// Interconnect Mediation Engine
// main method contains here
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////



#include "defines.h"
#include "cdr.h"
#include "db.h"
#include "db_data_containers.h"

#include <time.h>

cdr_buffer *cdr_store;

char debug_option[128];
bool debug = false;
int array_insert_size;

ofstream f_log("../logs/SSP_Mediation.log", ios::out | ios::app);


	decoded_cdr				*gsm_decoded_cdr;
	decoded_cdr				*gsm_cdr_block;

	cdr_decode raw_cdr;			// all the methods to extract data from a cdr
	int global_cdr_counter;

int main(int argc,char *argv[])
{
	char *ver = "1.0.5";

	cout<<"CDR Decoding  Engine for SSP "<<ver<<endl
	<<"Build Time "<<__DATE__<<" at "<<__TIME__<<endl
	<<"Millennium IT"<<endl
	<<"Colombo, Sri Lanka"<<endl<<endl;

	// Log start time
	char zTime[30];
	/*------- get time -------*/
	time_t t;
	time(&t);
	/*------- get time -------*/
	strftime(zTime, 30, "%Y%B%d%H%M%S", localtime(&t));
	f_log << " start time :" << zTime << endl;
	// Log start time -end



	// db data containers memory allocation startarray_insert_size
	cdr_store					= new cdr_buffer(1024*1024*70); // allocate space in memory for binary read of whole cdr file
	gsm_decoded_cdr				= new decoded_cdr;
	// db data containers memory allocation end
	
	// allocate space in memory for binary read of whole cdr file
	cdr_files cdr_f;

	//-------------- database logins and print file location -----------------------
	FILE *login;
	char cdr_login[128];
	char cdr_dump_location[128];

	// get config data
	if( (login  = fopen( "./ssp_cdr_eng.config", "r" )) == NULL )
	{
		printf( "The file 'ssp_cdr_eng.config' was not opened\n" );
		exit(0);
	}

	fscanf( login, "%s", cdr_login );
	fscanf( login, "%s", cdr_dump_location );
	fscanf( login, "%s", debug_option );
	fscanf( login, "%d", &array_insert_size );

	if( fclose( login ) )
		printf( "The file 'ssp_cdr_eng.config' was not closed\n" );

	if ( (strcmp(debug_option,"ON"))==0 )
		debug = true;

	gsm_cdr_block				= new decoded_cdr[array_insert_size]; // memory allocated after reading array_insert_size from file

//-------------- database logins and print file location -----------------------


	// login to cdr database
	cout <<"Debug Option = " <<debug_option << endl; 
	cout << "array_insert_size = " << array_insert_size << endl;

	
	printf("\nReady to connect to cdr data base\n");

	db_connect(cdr_login);

	cdr_f.db_read();		// read in list of cdrs files to be rated from database
	//cdr_f.print();

	cdr_f.init(cdr_dump_location);
	

	// cdr decoder performance measurement defs

	
		
	int	total_cdrs_decoded = 0;	// cumilative for this run over all cdr files
	int cdrs_pending_insert = 0;// must allways be less than block size
	int cdrs_inserted = 0;		// must allways be less than block size



	FILE *fp;
	cdr_file_statistics *s;		// the stuff is stored in a map so dont allocate storage,
								// this gives access to storage area in map, but must assign!!
	


	while(cdr_f.get_next_file(&fp,&s))			// get handle of cdr file
	{
		global_cdr_counter = 0;

		cdr_store->read_cdr_file(fp,s);			// read in whole file to buffer
		cout <<" cdr data "<<s->file_id<<endl;
		f_log <<" cdr data "<<s->file_id<<endl;
		raw_cdr.set_statistics_collector(s);	// direct statistics to file statistics area
		
		while(cdr_store->get_cdr_start())		// look for start of a cdr in the file
		{
			raw_cdr.decode(cdr_store->current);
		
			gsm_decoded_cdr->init(s->file_id, cdr_store->get_cdr_position());

			gsm_decoded_cdr->unpack(&raw_cdr);			// extract all the info from the file format rec
 
#ifdef CDR_PRINT
			cout << raw_cdr << endl;
#endif
			total_cdrs_decoded++;
			gsm_cdr_block[cdrs_pending_insert] = (*gsm_decoded_cdr);
			cdrs_pending_insert++;
			global_cdr_counter++;
			
			if (array_insert_size == cdrs_pending_insert)
			{
				cdrs_inserted += cdrs_pending_insert;
#ifdef DBLOG
				db_insert_decoded_cdr(cdrs_pending_insert);
#endif
				cdrs_pending_insert = 0;	// must allways be after the insert!!
			}
		}

//------------------------------------------------------------------------------------------------
		
		if(fclose(fp))
			cout<<"<ERROR> cant close cdr file"<<endl; // only valid files get here
		
		if (cdrs_pending_insert > 0)
		{
			cdrs_inserted += cdrs_pending_insert;
#ifdef DBLOG
			db_insert_decoded_cdr(cdrs_pending_insert);
#endif
			cdrs_pending_insert = 0;	// must allways be after the insert!!
		}

		cdr_f.db_update(*s);
		if(s->error_count > 0)
			cout<<"         Error count "<<s->error_count<<endl;
		cdr_store->init(); // rest all pointers
	};

#ifdef DBLOG
	// get any partial block size inserts
	if(cdrs_pending_insert > 0)
		db_insert_decoded_cdr(cdrs_pending_insert);
#endif
	
	db_disconnect();

		// Log end time
	/*------- get time -------*/
	//time_t t;
	time(&t);
	/*------- get time -------*/
	strftime(zTime, 30, "%Y%B%d%H%M%S", localtime(&t));
	f_log << " end time :" << zTime << endl;
	// Log start time -end

	return 0;

}


