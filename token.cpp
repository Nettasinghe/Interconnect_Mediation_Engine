

//////////////////////////////////////////////////////////////////////
//
// token.cpp: 
//			implementation of the token class.
// Interconnect Mediation Engine
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


#include "db_data_containers.h"
#include "defines.h"


token::token(string f_name)
{
	token_state = T_UNDEF;
	file_name = f_name;
}	

bool token::is_runable(void)
{
	if( (token_file  = fopen( file_name.c_str(), "r" )) == NULL )
	{
		printf( "The file %s does not exsist\n",file_name.c_str() );
		return false;
	}
	char buf[80];
	fscanf(token_file, "%s", buf );
	
	if( fclose(token_file) )
		printf( "The file %s was not closed\n",file_name.c_str() );

	token_state = code_token(buf);

	return(token_state == T_OFF);
}


bool token::set_token(e_token_state a)
{
	if( (token_file  = fopen( file_name.c_str(), "w" )) == NULL )
	{
		printf( "ERROR: file %s could not be opened to set state\n",file_name.c_str() );
		return false;
	}
	
	fprintf(token_file, "%s", decode_token(a).c_str() );
	
	if( fclose(token_file) )
	{
		printf( "file %s was not closed after set state\n",file_name.c_str() );
		return false;
	}

	return(true);
}

e_token_state token::code_token(string a)
{
	if("ON"==a)
		token_state = T_ON;
	else if ("OFF"==a)
		token_state = T_OFF;
	else 
		token_state = T_UNDEF;

	return token_state;
}

string token::decode_token(e_token_state a)
{
	switch(a)
	{
	case T_ON:
		token_text="ON";
		break;
	case T_OFF:
		token_text="OFF";
		break;
	case T_UNDEF:
		token_text="UNDEF";
		break;
	default:
		token_text="UNDEF";
	}
	return token_text;
}




