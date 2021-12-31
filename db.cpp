
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned long magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[33];
};
static const struct sqlcxp sqlfpn =
{
    32,
    "d:\\src\\ssp_mediation_1.0.5\\db.pc"
};


static unsigned long sqlctx = 696942507;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
            void  *sqhstv[21];
   unsigned int   sqhstl[21];
            int   sqhsts[21];
            void  *sqindv[21];
            int   sqinds[21];
   unsigned int   sqharm[21];
   unsigned int   *sqharc[21];
   unsigned short  sqadto[21];
   unsigned short  sqtdso[21];
} sqlstm = {10,21};

// Prototypes
extern "C" {
  void sqlcxt (void **, unsigned long *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlcx2t(void **, unsigned long *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlbuft(void **, char *);
  void sqlgs2t(void **, char *);
  void sqlorat(void **, unsigned long *, void *);
}

// Forms Interface
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern "C" { void sqliem(char *, int *); }

 static const char *sq0005 = 
"select FILE_NAME ,CDR_FILE_ID_NO  from sys_interconnect_dump_files where DEC\
ODED_DATE is null            ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{10,4146,0,0,0,
5,0,0,1,0,0,32,56,0,0,0,0,0,1,0,
20,0,0,2,0,0,27,71,0,0,4,4,0,1,0,1,5,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
51,0,0,3,59,0,1,72,0,0,0,0,0,1,0,
66,0,0,4,0,0,30,84,0,0,0,0,0,1,0,
81,0,0,5,105,0,9,117,0,0,0,0,0,1,0,
96,0,0,5,0,0,13,123,0,0,2,0,0,1,0,2,5,0,0,2,3,0,0,
119,0,0,5,0,0,15,138,0,0,0,0,0,1,0,
134,0,0,6,229,0,5,184,0,0,6,6,0,1,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,
3,0,0,
173,0,0,7,0,0,29,195,0,0,0,0,0,1,0,
188,0,0,8,35,0,4,311,0,0,1,0,0,1,0,2,5,0,0,
207,0,0,9,525,0,3,319,0,0,21,21,0,1,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,
1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
306,0,0,10,0,0,29,345,0,0,0,0,0,1,0,
};




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <oraca.h>
#include <sqlcpr.h>
#include <sqlda.h>
#include <sqlca.h>

//#include "defines.h"				// CJN
#define CDR_INSERT_BLOCK_SIZE 1000	// CJN
//#define CDR_INSERT_BLOCK_SIZE 1


#ifndef ORA_PROC
#include "db.h"
#include "db_data_containers.h"
#include "cdr.h"
#include <fstream>
#endif

extern decoded_cdr *gsm_cdr_block;
extern bool debug;
extern int array_insert_size;
extern int global_cdr_counter;



#define BUF_LEN 	100
#define FETCH_SIZE	1000
#define BUF_LENTH	20		


/* EXEC SQL DECLARE CDR DATABASE; */ 
 
/* EXEC SQL DECLARE RATING DATABASE; */ 



/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char *login;
/* EXEC SQL END DECLARE SECTION; */ 



void sql_error(char *msg)
{
	cout << endl << msg << endl;
	sqlca.sqlerrm.sqlerrmc[sqlca.sqlerrm.sqlerrml] = '\0';
	oraca.orastxt.orastxtc[oraca.orastxt.orastxtl] = '\0';
	oraca.orasfnm.orasfnmc[oraca.orasfnm.orasfnml] = '\0';
	cout << sqlca.sqlerrm.sqlerrmc << endl;
	cout << "in " << oraca.orastxt.orastxtc << endl;
	cout << "on line " << oraca.oraslnr << " of " << oraca.orasfnm.orasfnmc
		<< endl << endl;
	
	//-- Roll back any pending changes and disconnect from Oracle.
	/* EXEC SQL ROLLBACK RELEASE; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 0;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	exit(1);
}


//-- Connect to ORACLE. 
void db_connect(char *in_login)
{
	login = in_login;  // a pointer assignment, in_login has the space acclocation

    /* EXEC SQL WHENEVER SQLERROR DO sql_error("ORACLE error--"); */ 


	//cout<<"\nConnecting to ORACLE  as: "<<login<<endl;
	cout<<"\nConnecting to ORACLE  "<<endl;
 
    /* EXEC SQL CONNECT :login; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 10;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )20;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)login;
    sqlstm.sqhstl[0] = (unsigned int  )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("ORACLE error--");
}


	/* EXEC SQL ALTER SESSION SET NLS_DATE_FORMAT="DD/MM/YYYY HH24:MI:SS"; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "alter SESSION SET NLS_DATE_FORMAT = \"DD/MM/YYYY HH24:MI:SS\"";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )51;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
 if (sqlca.sqlcode < 0) sql_error("ORACLE error--");
}

 
	cout<<"Connected  to Database"<<endl<<endl; 

}





void db_disconnect()
{
	cout<<"\nORACLE  database: DISCONNECT"<<endl;
	/* EXEC SQL COMMIT WORK RELEASE; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )66;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
 if (sqlca.sqlcode < 0) sql_error("ORACLE error--");
}

 
}	




// get cdr files
void cdr_files::db_read()
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	struct cdr_file_t
	{ 
		char file_name[BUF_LEN];			// varchar2(123)
		int file_id;					// called id_no in table number(9)
	} a[FETCH_SIZE]; 
	int rows_to_fetch, rows_before, rows_this_time; 

	/* EXEC SQL END DECLARE SECTION; */ 


	int i;

	rows_to_fetch = FETCH_SIZE;		// number of rows in each "batch"  
	rows_before = 0;				// previous value of sqlerrd[2]   
	rows_this_time = FETCH_SIZE;
	 
	/* EXEC SQL WHENEVER SQLERROR DO sql_error("ORACLE error:"); */ 


    /* EXEC SQL DECLARE c_cdr_file CURSOR FOR 

	SELECT	FILE_NAME,  CDR_FILE_ID_NO
	FROM	sys_interconnect_dump_files
	WHERE DECODED_DATE IS NULL; */ 

       
    /* EXEC SQL OPEN c_cdr_file; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 10;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = sq0005;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )81;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("ORACLE error:");
}

 
	/* EXEC SQL WHENEVER NOT FOUND CONTINUE; */ 

	/* EXEC SQL WHENEVER SQLERROR DO sql_error("ORACLE error:"); */ 
 

	while (rows_this_time == rows_to_fetch) 
	{ 
		/* EXEC SQL FETCH c_cdr_file INTO :a; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1000;
  sqlstm.offset = (unsigned int  )96;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)a->file_name;
  sqlstm.sqhstl[0] = (unsigned int  )100;
  sqlstm.sqhsts[0] = (         int  )sizeof(struct cdr_file_t);
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqharc[0] = (unsigned int   *)0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&a->file_id;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )sizeof(struct cdr_file_t);
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqharc[1] = (unsigned int   *)0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("ORACLE error:");
}

 		 
		rows_this_time = sqlca.sqlerrd[2] - rows_before; 
		rows_before = sqlca.sqlerrd[2]; 
		//printf(" this=%d before=%d to_fetch=%d\n", rows_this_time, rows_before, rows_to_fetch);


		cdr_file_statistics cd;
		cd.init();
		for(i=0; i<rows_this_time; i++)
		{
			cd.file_id = a[i].file_id;			
			insert(a[i].file_name, cd);
		}
	} 

    /* EXEC SQL CLOSE c_cdr_file; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 10;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )119;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error("ORACLE error:");
}

 
 
    printf("\n %d  cdr files loaded.\n\n",rows_before);
}



void cdr_files::db_update(cdr_file_statistics s)
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	struct cdr_file_t
	{ 
		 int valid_cdr_count;					//  number(7)
		 int error_count;						//	number(7)
		 int bytes_read;						//	number(9)
		 char first_cdr_date[BUF_LENTH];				//	varchar2(14)
		 char last_cdr_date[BUF_LENTH];				//	varchar2(14)
		 int rating_duration;
		 char rating_start_date[BUF_LENTH];	//	varchar2(14)

		 int id_no;						//	number(9)
 	} a; 

	/* EXEC SQL END DECLARE SECTION; */ 



//#ifndef code_skip

	 cout << "a.id_no :" <<a.id_no<<endl;
	 cout <<"s.file_id : "<<s.file_id<<endl;
	 a.id_no = s.file_id;
	 cout << "a.id_no :" <<a.id_no<<endl;
	 cout <<"s.file_id : "<<s.file_id<<endl;

	 a.valid_cdr_count = s.valid_cdr_count;
	 a.error_count = s.error_count;
	 a.bytes_read = s.bytes_read;
	 strcpy(a.first_cdr_date, s.first_cdr_date.c_str());
	 strcpy(a.last_cdr_date, s.last_cdr_date.c_str());
	 a.rating_duration = s.rating_duration;
	 strcpy(a.rating_start_date, s.rating_start_date.c_str());
	 
	 	
//#endif

	 /* EXEC SQL WHENEVER SQLERROR DO sql_error("ORACLE error:"); */ 

	 /* EXEC SQL	
	 UPDATE sys_interconnect_dump_files
	 SET 
		valid_cdr_count			= :a.valid_cdr_count, 
		error_count				= :a.error_count,
		bytes_read				= :a.bytes_read,
		first_cdr_date			= to_date(:a.first_cdr_date,'YYYYMMDDHH24MISS'),
		last_cdr_date			= to_date(:a.last_cdr_date,'YYYYMMDDHH24MISS'),
		decoded_date			= SYSDATE
	 WHERE cdr_file_id_no  = :a.id_no; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 6;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "update sys_interconnect_dump_files  set valid_cdr_count=:b0\
,error_count=:b1,bytes_read=:b2,first_cdr_date=to_date(:b3,'YYYYMMDDHH24MISS')\
,last_cdr_date=to_date(:b4,'YYYYMMDDHH24MISS'),decoded_date=SYSDATE where cdr_\
file_id_no=:b5";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )134;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&(a.valid_cdr_count);
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&(a.error_count);
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&(a.bytes_read);
  sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)(a.first_cdr_date);
  sqlstm.sqhstl[3] = (unsigned int  )20;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)(a.last_cdr_date);
  sqlstm.sqhstl[4] = (unsigned int  )20;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)&(a.id_no);
  sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("ORACLE error:");
}



	 /* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 10;
  sqlstm.arrsiz = 6;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )173;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("ORACLE error:");
}


 
    printf("\n cdr file id=%d log updated.\n\n", s.file_id);

}		






void db_insert_decoded_cdr(int cdr_count)
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 


	static struct db_cdr
	{	
		int		file_id;								//  number(9)
		int		file_pos;								//	number(9)
		int		type_of_msc;							//	number(3),
		int		type_of_call;							//  number(3),
		int		call_termination_type;					//  number(3),
		int		origin_of_call_indicator;				//  number(3),
		char	circuit_allocation_time_stamp[BUF_LEN];	//	date,		// call_time in db
		int		call_duration;							//	number(9),
		char	end_of_call_time_stamp[BUF_LEN];		//	varchar2(10),
		char	msc_identity[BUF_LEN];					//	varchar2(20),
		int		called_party_number_noai;				//	number(3),
		char	called_party_number[BUF_LEN];			//	varchar2(40),
		int		calling_party_number_noai;				//	number(3),
		char	calling_party_number[BUF_LEN];			//	varchar2(40),
		char	outgoing_trunk_group[BUF_LEN];			//	varchar2(10),
		char	incoming_trunk_group[BUF_LEN];			//	varchar2(10)
		int		service_type_id;						//  number(3)	// 50 - hard code
		char	calling_network[BUF_LEN];				//	varchar2(5)	// null
		char	called_network[BUF_LEN];				//	varchar2(5)	// null
		char	day_type_id[BUF_LEN];					//	varchar2(5)	// null
		char	mediated_time[BUF_LEN];				//	date			- sysdate
	} * a;

	char	med_system_date[20];  

	int rows_to_insert;
	
	/* EXEC SQL END DECLARE SECTION; */ 

	
	rows_to_insert = cdr_count;
	
	if((a = new db_cdr[array_insert_size])==NULL)
	{
		cout<<" cant allocate memory for cdr insert"<<endl;
		exit(0);
	}
	
	
	for(int j=0; j<array_insert_size; j++)
	{
		a[j].file_pos = 0;
	}
	
	for(int i=0; i<rows_to_insert; i++)
	{
		a[i].file_id			= gsm_cdr_block[i].file_id; 
		a[i].file_pos		= gsm_cdr_block[i].file_pos;
		a[i].type_of_msc		= gsm_cdr_block[i].type_of_msc;
		a[i].type_of_call	= gsm_cdr_block[i].type_of_call;
		a[i].call_termination_type	= gsm_cdr_block[i].call_termination_type;
		a[i].origin_of_call_indicator= gsm_cdr_block[i].origin_of_call_indicator;
		
		reng_date d=gsm_cdr_block[i].d_circuit_allocation_date;
		reng_time t=gsm_cdr_block[i].d_circuit_allocation_time;
		char buf[100];
		sprintf(buf,"%02d%s%02d%s%04d%s%02d%s%02d%s%02d",d.day,"/",d.month,"/",d.year," ",t.hour,":",t.min,":",t.second); 
		strcpy(a[i].circuit_allocation_time_stamp, buf);	

		a[i].call_duration	= gsm_cdr_block[i].call_duration;
		strcpy(a[i].end_of_call_time_stamp, gsm_cdr_block[i].end_of_call_time_stamp.substr(0,10) .c_str());
		strncpy(a[i].msc_identity, gsm_cdr_block[i].msc_identity.substr(0,20) .c_str(),20);
		a[i].called_party_number_noai = gsm_cdr_block[i].called_party_number_noai;
		strncpy(a[i].called_party_number, gsm_cdr_block[i].called_party_number.substr(0,40) .c_str(),40);
		a[i].calling_party_number_noai = gsm_cdr_block[i].calling_party_number_noai;
		strncpy(a[i].calling_party_number, gsm_cdr_block[i].calling_party_number.substr(0,40) .c_str(),40);

		strncpy(a[i].outgoing_trunk_group, gsm_cdr_block[i].outgoing_trunk_group.substr(0,10) .c_str(),10);
		strncpy(a[i].incoming_trunk_group, gsm_cdr_block[i].incoming_trunk_group.substr(0,10) .c_str(),10);

		a[i].service_type_id = 50;
		strcpy(a[i].calling_network, "");
		strcpy(a[i].called_network, "");	
		strcpy(a[i].day_type_id, "");
		
		if ( debug )
		{					
			cout <<"file_id						:" << a[i].file_id 					<< endl;
			cout <<"file_pos					:" << a[i].file_pos 				<< endl;
			cout <<"type_of_msc					:" << a[i].type_of_msc 				<< endl;
			cout <<"type_of_call				:"<< a[i].type_of_call				<< endl;
			cout <<"call_termination_type		:" << a[i].call_termination_type	<< endl;
			cout <<"origin_of_call_indicator	:" << a[i].origin_of_call_indicator	<< endl;
			cout <<"circuit_allocation_time_stamp	:" << a[i].circuit_allocation_time_stamp	<<	endl;
			cout <<"call_duration				:" << a[i].call_duration			<< endl;
			cout <<"end_of_call_time_stamp		:" << a[i].end_of_call_time_stamp	<< endl;
			cout <<"msc_identity				:" << a[i].msc_identity				<< endl;
			cout <<"called_party_number_noai	:" << a[i].called_party_number_noai	<< endl;
			cout <<"called_party_number			:" << a[i].called_party_number		<< endl;
			cout <<"calling_party_number_noai	:" << a[i].calling_party_number_noai<< endl;
			cout <<"calling_party_number		:" << a[i].calling_party_number		<< endl;
			cout <<"outgoing_trunk_group		:" << a[i].outgoing_trunk_group		<< endl;
			cout <<"incoming_trunk_group		:" << a[i].incoming_trunk_group		<< endl;
			cout <<"service_type_id				:" << a[i].service_type_id			<< endl;
			cout <<"calling_network				:" << a[i].calling_network 			<< endl;
			cout <<"called_network				:" << a[i].called_network			<< endl;
			cout <<"day_type_id					:" << a[i].day_type_id				<< endl;
		}
	}

	/* EXEC SQL
	select sysdate into :med_system_date from dual; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 6;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select sysdate into :b0  from dual ";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )188;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)med_system_date;
 sqlstm.sqhstl[0] = (unsigned int  )20;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
 if (sqlca.sqlcode < 0) sql_error("ORACLE error:");
}


	
	for(int k=0; k<array_insert_size; k++)
	{
		strcpy(a[k].mediated_time, med_system_date);
	}  

	/* EXEC SQL  FOR :rows_to_insert  INSERT INTO DYN_5_UDR 
	(
		file_id,
		file_pos,
		type_of_msc,
		type_of_call,
		call_termination_type,
		origin_of_call_indicator,
		circuit_allocation_time_stamp,
		call_duration,
		end_of_call_time_stamp,
		msc_identity,
		called_party_number_noai,
		called_party_number,
		calling_party_number_noai,
		calling_party_number,
		outgoing_trunk_group,
		incoming_trunk_group,
		service_type_id,
		calling_network,
		called_network,
		day_type_id,
		mediated_time
	) 
	VALUES (:a); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 21;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into DYN_5_UDR (file_id,file_pos,type_of_msc,type_of_\
call,call_termination_type,origin_of_call_indicator,circuit_allocation_time_st\
amp,call_duration,end_of_call_time_stamp,msc_identity,called_party_number_noai\
,called_party_number,calling_party_number_noai,calling_party_number,outgoing_t\
runk_group,incoming_trunk_group,service_type_id,calling_network,called_network\
,day_type_id,mediated_time) values (:s1 ,:s2 ,:s3 ,:s4 ,:s5 ,:s6 ,:s7 ,:s8 ,:s\
9 ,:s10 ,:s11 ,:s12 ,:s13 ,:s14 ,:s15 ,:s16 ,:s17 ,:s18 ,:s19 ,:s20 ,:s21 )";
 sqlstm.iters = (unsigned int  )rows_to_insert;
 sqlstm.offset = (unsigned int  )207;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&a->file_id;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&a->file_pos;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&a->type_of_msc;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&a->type_of_call;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&a->call_termination_type;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&a->origin_of_call_indicator;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)a->circuit_allocation_time_stamp;
 sqlstm.sqhstl[6] = (unsigned int  )100;
 sqlstm.sqhsts[6] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&a->call_duration;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)a->end_of_call_time_stamp;
 sqlstm.sqhstl[8] = (unsigned int  )100;
 sqlstm.sqhsts[8] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)a->msc_identity;
 sqlstm.sqhstl[9] = (unsigned int  )100;
 sqlstm.sqhsts[9] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&a->called_party_number_noai;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)a->called_party_number;
 sqlstm.sqhstl[11] = (unsigned int  )100;
 sqlstm.sqhsts[11] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&a->calling_party_number_noai;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)a->calling_party_number;
 sqlstm.sqhstl[13] = (unsigned int  )100;
 sqlstm.sqhsts[13] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)a->outgoing_trunk_group;
 sqlstm.sqhstl[14] = (unsigned int  )100;
 sqlstm.sqhsts[14] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)a->incoming_trunk_group;
 sqlstm.sqhstl[15] = (unsigned int  )100;
 sqlstm.sqhsts[15] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&a->service_type_id;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)a->calling_network;
 sqlstm.sqhstl[17] = (unsigned int  )100;
 sqlstm.sqhsts[17] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)a->called_network;
 sqlstm.sqhstl[18] = (unsigned int  )100;
 sqlstm.sqhsts[18] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)a->day_type_id;
 sqlstm.sqhstl[19] = (unsigned int  )100;
 sqlstm.sqhsts[19] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)a->mediated_time;
 sqlstm.sqhstl[20] = (unsigned int  )100;
 sqlstm.sqhsts[20] = (         int  )sizeof(struct db_cdr);
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
 if (sqlca.sqlcode < 0) sql_error("ORACLE error:");
}


	
	/* EXEC SQL COMMIT; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 10;
 sqlstm.arrsiz = 21;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )306;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
 if (sqlca.sqlcode < 0) sql_error("ORACLE error:");
}


	delete a;
}

