#include "CompSearch.h"


using namespace RTC;
using namespace std;




void WriteString(string a, ofstream &ofs)
{
	int s = a.size()+1;
	ofs.write( (char*)&s, sizeof(s) );
	ofs.write( a.c_str(), s );
}

string ReadString(ifstream &ifs)
{
	string a;
	int s;
	ifs.read( (char*)&s, sizeof(s) );

	char *st = new char[s];
	ifs.read( st, s );

	a = st;

	delete st;

	return a;
}

string GetExtension(string &path)
{
	string ext;
    size_t pos1 = path.rfind('.');
	if(pos1 != string::npos){
        ext = path.substr(pos1+1, path.size()-pos1);
        string::iterator itr = ext.begin();
        while(itr != ext.end()){
            *itr = tolower(*itr);
            itr++;
        }
        itr = ext.end()-1;
        while(itr != ext.begin()){
            if(*itr == 0 || *itr == 32){
                ext.erase(itr--);
            }
            else{
                itr--;
            }
        }
    }
 
    return ext;
}

string ExtractPathWithoutExt(string &fn)
{
    string::size_type pos;
	if((pos = fn.find_last_of(".")) == string::npos){
        return fn;
    }
 
    return fn.substr(0, pos);
}

string ExtractFileName(string &path)
{
	
    string fn;
    string::size_type fpos;
    if((fpos = path.find_last_of("/")) != string::npos){
        fn = path.substr(fpos+1);
    }
    else if((fpos = path.find_last_of("\\")) != string::npos){
		fn = path.substr(fpos+1);
		
	}
	else{
		fn = path;
	}
	
 
	fn = ExtractPathWithoutExt(fn);
	
 
	return fn;
}