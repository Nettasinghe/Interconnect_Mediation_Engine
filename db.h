
//////////////////////////////////////////////////////////////////////
//
// db.h: 
// header file for Interconnect Mediation Engine database access methods
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////



void	db_connect(char *in_login); 
void	db_disconnect(); 
//void	db_insert_decoded_cdr();
void	db_insert_decoded_cdr(int cdr_count);






