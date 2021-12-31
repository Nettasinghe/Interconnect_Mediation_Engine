
//////////////////////////////////////////////////////////////////////
//
// reng_date_time.cpp: 
//			implementation of the reng_date_time class.
// Interconnect Mediation Engine
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////

#include "db_data_containers.h"
#include "defines.h"

#include <stdlib.h>
#include <stdio.h>


bool reng_time::set_time(int h, int m, int s)
{
	bool valid=true;
	if (h>=0 && h < 24)
	{
		hour=h;
	}
	else
	{
		cout<<"bad hour specifier "<<h<<endl;
		h=0;
		valid=false;
	}
	
	if (m>=0 && m < 60)
	{
		min=m;
	}
	else
	{
		cout<<"bad minute specifier "<<m<<endl;
		m=0;
		valid=false;
	}
	
	if( s>=0 && s < 60)
	{
		second=s;
	}
	else
	{
		cout<<" bad second value "<<s<<endl;
		s=0;
		valid=false;
	}
	return valid;
}


bool reng_time::operator < (const reng_time  &s) const
{
	if(hour < s.hour)
		return true;
	if ((hour == s.hour) && (min < s.min))
		return true;
	if ((hour == s.hour) && (min == s.min) && (second < s.second))
		return true;
	
	return false;
}


void reng_time::Print() 
{
	char buf[32];
	sprintf(buf,"%02d%02d%02d",hour,min,second);
	cout<<buf<<endl;
}

void reng_time::init()
{
	hour=0;
	min=0;
	second=0;
}

void reng_date::init()
{
	year=1972;
	month=07;
	day=10;
}


reng_time reng_time::operator+ (int s)  const
{
	div_t d_s, d_h, d_m;
	reng_time t;
	
	t =* this;

	if (s >= 3600)
		cout<<" time Wrap round "<<endl;
	
	if (s < 0)
	{
		cout<<" Cant decrement secs "<<endl;
		exit(1);
	}
	
	d_s = div(s,60);
	
	if (d_s.quot==0)
	{
		t.second += d_s.rem;
		return t;
	}
	else
		t.second = d_s.rem;

	
	d_m = div(d_s.quot+t.min, 60);
	
	if (d_m.quot == 0)
	{
		t.min += d_s.quot;
		return t;
	}
	else
		t.min=d_m.rem;
	
	d_h = div(d_m.quot+t.hour, 24);
	
	if (d_m.quot == 0)
	{
		t.hour += d_h.rem;
		return t;
	}
	else
		t.hour = d_h.rem;


	return t;
}



bool reng_time::set_h_m(const char *t)
{
	bool valid=true;
	
	if(strlen(t) != 4)
	{
		set_time(0,0,0);
		valid=false;
		cout<<"bad string to convert in set_h_m "<<t<<endl;
		
	}
	else
	{
		char h_buf[3] ;
		strncpy(h_buf,t,2);
		h_buf[2]='\0';
		valid = set_time(atoi(h_buf), atoi(t+2), 0);
	}
	
	return valid;
}



bool reng_time::set_time(char *t)
{
	bool valid=true;
	
	if(strlen(t) != 6)
	{
		set_time(0,0,0);
		valid=false;
		cout<<"bad string to convert in set_time "<<t<<endl;
		return valid;
	}

		char hm_buf[5] ;
		strncpy(hm_buf,t,4);
		hm_buf[4]='\0';
		valid=set_h_m(hm_buf);
		second=atoi(t+4);
		return valid;
}


bool reng_date::set_date(char *dte)
{
	bool valid=true;
	//YYYYMMDD
	int y,m,d;
	char buf[20];
	if(strlen(dte) < 8)
	{
		cout<<" Not enough characters for year conversion {"<<dte<<"} "<<endl;
		set_date(1972,7,10);
		return false;
	}

	strcpy(buf,dte);
	buf[4]='\0';
	y=atoi(buf);

	strcpy(buf,dte);
	buf[4+2]='\0';
	m=atoi(buf+4);

	strcpy(buf,dte);
	buf[4+2+2]='\0';
	d=atoi(buf+4+2);

	valid=set_date(y,m,d);
	return valid;
}



bool reng_date::set_date(int y, int m, int d)
{
	bool valid=true;
	if (y >= MIN_YEAR && y < MAX_YEAR)
	{
		year = y;
	}
	else
	{
		cout<<"bad year specifier "<<y<<endl;
		y = MIN_YEAR;
		valid = false;
	}
	
	if (m >= 1 && m <= 12)
	{
		month = m;
	}
	else
	{
		cout<<"bad month specifier "<<m<<endl;
		m = 1;
		valid = false;
	}
	
	// put in addtional calander checks here (Ajit)
	if( d >= 1 && d <= 31)
	{
		day=d;
	}
	else
	{
		cout<<" bad day value "<<d<<endl;
		d = 1;
		valid = false;
	}
	return valid;
}



// time in format
bool reng_time::set_from_db(char *t, int secs)
{
	bool k;
	k = set_h_m(t);
	*this = *this + secs;
	return k;
}


ostream& operator<<(ostream& out, reng_time t)
{

	char buf[32];
	sprintf(buf,"%02d%02d%02d",t.hour, t.min, t.second);

    out<<buf;
    return(out);
}


ostream& operator<<(ostream& out, reng_date t)
{

	char buf[32];
	sprintf(buf,"%04d%02d%02d",t.year, t.month, t.day);

    out<<buf;
    return(out);
}


ostream& operator<<(ostream& out, reng_date_time x)
{
	char buf[52];
	sprintf(buf,"%04d%02d%02d-%02d%02d%02d",
		x.date.year, x.date.month, x.date.day, x.time.hour, x.time.min, x.time.second);

	out<<buf;
	return(out);
}



bool reng_date::operator < (const reng_date  &s) const
{
	if(year < s.year)
		return true;
	if ((year == s.year) && (month < s.month))
		return true;
	if ((year == s.year) && (month == s.month) && (day < s.day))
		return true;
	
	return false;
}


// sets a string in YYYYMMDDHH24MISS format
bool reng_date_time::set_date_time(char * a)
{
	string t=a;
	bool result=true;

	if( t.length() != 14)
	{
		cout<<" ERROR Bad length in date time conversion"<<endl;
		return false;
	}

	string s_date=t.substr(0,8);
	string s_time=t.substr(8,6);

	result &= date.set_date((char*)s_date.c_str());
	result &= time.set_time((char*)s_time.c_str());
	return result;
}

                                   
bool reng_date_time::operator < (const reng_date_time  &s) const
{
	if(date.year < s.date.year)
		return true;
	if ((date.year == s.date.year) && (date.month < s.date.month))
		return true;
	if ((date.year == s.date.year) && (date.month == s.date.month) && (date.day < s.date.day))
		return true;

	// date is equal compare times
	if((date.year == s.date.year) && (date.month == s.date.month) && (date.day == s.date.day))
	{
		if(time.hour < s.time.hour)
			return true;
		if ((time.hour == s.time.hour) && (time.min < s.time.min))
			return true;
		if ((time.hour == s.time.hour) && (time.min == s.time.min) && (time.second < s.time.second))
			return true;
	}

	return false;
}

	


