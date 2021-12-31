
/*

26 JUN 2003 - version = 1.0.1
	* Removed space character from Incoming Trunk Group & Outgoing Trunk Group

09 JUL 2003 - version = 1.0.2
	* 0 added to the beginning of called_party_number & calling_party_number
	  if respective NOAI=1 (International)

15 JUL 2003 - version = 1.0.3
	* bulk insertion to db and  writing to log file "../logs/SSP_Mediation.log"

15 SEP 2003 - version = 1.0.4
	* if outgoing_trunk_group & incoming_trunk_group are null, "Dummy1" and "Dummy2" 
		are appended.

23-feb-2004 ver 1.0.5
1) Insertion of mediated_time to DYN_5_UDR 
2) db logging of cdrs changed to insert any partial block size before updating sys_interconnect_dump_files 

Scripts:


CREATE TABLE SSP_DUMP_FILES ( 
  FILE_NAME           VARCHAR2 (100), 
  VALID_CDR_COUNT     NUMBER (7), 
  ERROR_COUNT         NUMBER (7), 
  BYTES_READ          NUMBER (9), 
  FIRST_CDR_DATE      DATE, 
  LAST_CDR_DATE       DATE, 
  CDR_FILE_ID_NO      NUMBER (9), 
  CDR_FILE_DATE       DATE, 
  TRANSFER_DATE       DATE, 
  RATING_DURATION     NUMBER (5), 
  RATING_START_DATE   DATE, 
  DECODED_DATE        DATE, 
  ARCHIVE_DATE        DATE, 
  ARCHIVE_PURGE_DATE  DATE)

CREATE TABLE SYS_INTERCONNECT_DUMP_FILES ( 
  FILE_NAME           VARCHAR2 (100), 
  VALID_CDR_COUNT     NUMBER (7), 
  ERROR_COUNT         NUMBER (7), 
  BYTES_READ          NUMBER (9), 
  FIRST_CDR_DATE      DATE, 
  LAST_CDR_DATE       DATE, 
  CDR_FILE_ID_NO      NUMBER (9), 
  CDR_FILE_DATE       DATE, 
  TRANSFER_DATE       DATE, 
  RATING_DURATION     NUMBER (5), 
  RATING_START_DATE   DATE, 
  DECODED_DATE        DATE, 
  ARCHIVE_DATE        DATE, 
  ARCHIVE_PURGE_DATE  DATE)


CREATE TABLE SSP_CDR ( 
  FILE_ID                        NUMBER (9)    NOT NULL, 
  FILE_POS                       NUMBER (9)    NOT NULL, 
  TYPE_OF_MSC                    NUMBER (3), 
  TYPE_OF_CALL                   NUMBER (3), 
  CALL_TERMINATION_TYPE          NUMBER (3), 
  ORIGIN_OF_CALL_INDICATOR       NUMBER (3), 
  CIRCUIT_ALLOCATION_TIME_STAMP  DATE, 
  CALL_DURATION                  NUMBER (9), 
  END_OF_CALL_TIME_STAMP         VARCHAR2 (10), 
  MSC_IDENTITY                   VARCHAR2 (20), 
  CALLED_PARTY_NUMBER_NOAI       NUMBER (3), 
  CALLED_PARTY_NUMBER            VARCHAR2 (40), 
  CALLING_PARTY_NUMBER_NOAI      NUMBER (3), 
  CALLING_PARTY_NUMBER           VARCHAR2 (40), 
  OUTGOING_TRUNK_GROUP           VARCHAR2 (10), 
  INCOMING_TRUNK_GROUP           VARCHAR2 (10))


CREATE TABLE DYN_5_UDR ( 
  FILE_ID                        NUMBER (9)    NOT NULL, 
  FILE_POS                       NUMBER (9)    NOT NULL, 
  TYPE_OF_MSC                    NUMBER (3), 
  TYPE_OF_CALL                   NUMBER (3), 
  CALL_TERMINATION_TYPE          NUMBER (3), 
  ORIGIN_OF_CALL_INDICATOR       NUMBER (3), 
  CALL_DURATION                  NUMBER (9), 
  END_OF_CALL_TIME_STAMP         VARCHAR2 (10), 
  MSC_IDENTITY                   VARCHAR2 (20), 
  CALLED_PARTY_NUMBER_NOAI       NUMBER (3), 
  CALLED_PARTY_NUMBER            VARCHAR2 (40), 
  CALLING_PARTY_NUMBER_NOAI      NUMBER (3), 
  CALLING_PARTY_NUMBER           VARCHAR2 (40), 
  OUTGOING_TRUNK_GROUP           VARCHAR2 (10), 
  INCOMING_TRUNK_GROUP           VARCHAR2 (10), 
  SERVICE_TYPE_ID                NUMBER (3)    DEFAULT 50 NOT NULL, 
  CALLING_NETWORK                VARCHAR2 (5), 
  CALLED_NETWORK                 VARCHAR2 (5), 
  DAY_TYPE_ID                    VARCHAR2 (5), 
  CIRCUIT_ALLOCATION_TIME_STAMP  DATE, 
  MEDIATED_TIME                  DATE)

Notes:

(1)  move to next record - overun error commented

(2) getbits: get n bits from position p - Anci C - K&R - page 49
	
unsigned	cdr_decode::getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n) ) & ~(~0 << n );
}


*/




