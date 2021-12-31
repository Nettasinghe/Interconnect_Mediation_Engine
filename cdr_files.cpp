
//////////////////////////////////////////////////////////////////////
//
// cdr_files.cpp: 
//			implementation of the cdr_files class.
// Interconnect Mediation Engine
// developer - Chandika Nettasinghe
// development - 2003
//
//////////////////////////////////////////////////////////////////////


#include "cdr.h"
#include "defines.h"


extern int  data_size;
extern ofstream f_log;


cdr_files::~cdr_files()
{
	/*
	if(file_open)
	{
		fclose(cdr_dump_file);
		cout<<"INFO: closed last cdr dump file possible grace-less exit"<<endl;
	}
	*/
}

// The cdr file list must be in the same directory as the
// cdr dump files;
// the file data structure re uses the
//		a) drive
//		b) directory
// of the cdr file list specification to locate the
// cdr dump files
// does
//		1) read in file names
//		2) check files for exsistance
//		3) opens first file
bool cdr_files::init(string path)
{
	total_bytes_read=0;
	reads_from_file=0;
	active_file.init(path);
	open_file_name_iter=dumps.begin();
	return true;
}



// gets the next cdr file in list
//bool get_next_file(FILE **fp)
bool cdr_files::get_next_file(FILE **fp, cdr_file_statistics **s) // bad coupling here TODO
{
	if(open_file_name_iter != dumps.end())
	{
		char* fname = active_file.get_full_file_name((*open_file_name_iter).first);
		
		*fp=fopen(fname,"rb");
		*s = &(*open_file_name_iter).second;

		while (NULL==*fp)
		{
			cout<<"ERR: CDR File "<< fname <<" could not be opend "<<endl;
			f_log <<"ERR: CDR File "<< fname <<" could not be opend "<<endl;

			open_file_name_iter++; // next file
			if(open_file_name_iter == dumps.end())
			{
				cout<<"INFO: All cdr files in list  read"<<endl;
				f_log <<"INFO: All cdr files in list  read"<<endl;
				return false;
			}

			char* fname = active_file.get_full_file_name((*open_file_name_iter).first);
			*fp=fopen(fname,"rb");
			*s = &(*open_file_name_iter).second;
		}
		open_file_name_iter++; // next file
		cout<<" OPENED "<<fname<<endl;
		f_log <<" OPENED "<<fname<<endl;
		return true;
	}
	else
	{
		cout<<"INFO: All cdr files in list  read"<<endl;
		f_log <<"INFO: All cdr files in list  read"<<endl;
	}
	return false;
}


bool cdr_files::read_cdr_dump_file_list(char *name)
{
	ifstream cdr_dumps(active_file.get_full_file_name(name));
	
	if (!cdr_dumps)
	{
		cerr<<"Unable to open CDR File list {"<<active_file.get_full_file_name(name)<<"}"<<endl;
		exit(1);
		//return false;
	}
	
	string cdr_file_name;
	cdr_file_statistics a;
	// temp number generator
	int i=1;

	a.init();

	while (cdr_dumps >> cdr_file_name)
	{
		a.file_id=i++;
		dumps[cdr_file_name] = a;
	}
	
	cdr_dumps.close();

	if(dumps.empty())
	{
		cout<<"INFO: No CDR data files to rate"<<endl;
		return false;
	}
	else
	{
		cout<<"INFO: CDR File count = "<<dumps.size()<<endl;
	}

	// Put in check to verify exsistance of these files (TODO Ajit)
	open_file_name_iter = dumps.begin();
	return true;
}


void cdr_files::print()
{
	DUMP_DEF::iterator i;
	for(i=dumps.begin(); i!=dumps.end(); i++)
	{
		cout<<(*i).first<<" -> "<<(*i).second.file_id<<endl;
		//printf("%s\n",(*i).first.c_str());
	}
}


bool cdr_files::insert(string file_name, cdr_file_statistics s)
{
	pair<DUMP_DEF::iterator, bool> p=dumps.insert(make_pair(file_name,s));
	if (p.second == false)
	{
		cout<<"<ERROR>: Duplicate cdr file name "<<file_name<<endl;
		return false;
	}
	return true;
}

// gives first file id of the set of cdr files to be processed
int cdr_files::get_first_file_id()
{
	DUMP_DEF::iterator i;
	int id=-1;
	i=dumps.begin();
	if(i!=dumps.end())
	{
		id = (*i).second.file_id;
	}
	return id;
}
