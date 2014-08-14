#include "MPComp.h"
#include "CompSearch.h"
#include "MPLua.h"

using namespace std;

void Rule::addP()
{
	std::vector<sub_Rule> s;
	SR.push_back(s);
}

void Rule::addsubRule(int num, std::string v)
{
	if(SR.size() > num)
	{
		sub_Rule s;
		s.v = v;
		s.s = 0;
		SR[num].push_back(s);
	}
}

void main_Rule::addRule()
{
	Rule r;
	rs.push_back(r);
}

void main_Rule::addaddRule(std::string n, int s)
{
	add_Rule a;
	a.name = n;
	a.state = s;
	ar.push_back(a);
}

Rule *main_Rule::getRule(int num)
{
	if(rs.size() > num)
		return &rs[num];
}

add_Rule *main_Rule::getaddRule(int num)
{
	if(ar.size() > num)
		return &ar[num];
}



std::string Replace( std::string String1, std::string String2, std::string String3 )
{
    std::string::size_type  Pos( String1.find( String2 ) );

    while( Pos != std::string::npos )
    {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }

    return String1;
}



void LoadSRule(std::vector<std::string> &cs, int &nm,Rule &r)
{
	bool flag = true;
	while(flag)
	{
		
		std::vector<sub_Rule> SR;
		
		LoadSubRule(cs, nm, SR);

		r.SR.push_back(SR);

		
		if(!AddCount(cs, nm))
			return;
		else if(cs[nm] == "}")
		{
			flag = false;
			return;
		}
		
	}
}


void LoadHRule(std::vector<std::string> &cs, int &nm,std::vector<Rule> &rs)
{
	bool flag = true;
	while(flag)
	{
		Rule r;
		
		
		

		while(true)
		{
			
			if(cs[nm] == "{")
				break;
			else if(cs[nm] == "}")
				break;
			else if(!AddCount(cs, nm))
			{
				flag = false;
				return;
			}
		}


		if(!AddCount(cs, nm))
			return;
		

		LoadSRule(cs,nm,r);
		rs.push_back(r);

		if(!AddCount(cs, nm))
			return;
		else if(cs[nm] == "}")
		{
			flag = false;
			return;
		}
		
		
	}
}

bool AddCount(std::vector<std::string> &cs, int &nm)
{
	nm++;
	if(cs.size() <= nm)
	{
		return false;
	}
	return true;
}

void LoadAddRule(std::vector<std::string> &cs, int &nm,std::vector<add_Rule> &ar)
{
	

	bool flag = true;
	while(flag)
	{
		add_Rule ae;
		ae.name = cs[nm];
		
		if(!AddCount(cs, nm))
			return;
		if(cs[nm] == "‚È‚µ"){
			ae.state = -1;
		}
		else if(cs[nm] == "CREATED"){
			ae.state = RTC::CREATED_STATE;
		}
		else if(cs[nm] == "INACTIVE"){
			ae.state = RTC::INACTIVE_STATE;
		}
		else if(cs[nm] == "ACTIVE"){
			ae.state = RTC::ACTIVE_STATE;
		}
		else if(cs[nm] == "ERROR"){
			ae.state = RTC::ERROR_STATE;
		}
		
		
		
		ar.push_back(ae);

		if(!AddCount(cs, nm))
			return;
		if(cs[nm] == ";")
		{
			flag = false;
			return;
		}
		else if(cs[nm] == "}")
		{
			flag = false;
			return;
		}
		
		
	}
}

void LoadSubRule(std::vector<std::string> &cs, int &nm,std::vector<sub_Rule> &sr)
{
	bool flag = true;
	while(flag)
	{
		sub_Rule rs;
		
		rs.v = cs[nm];
		

		
		
		sr.push_back(rs);

		


		if(!AddCount(cs, nm))
			return;
		else if(cs[nm] == ";")
		{
			flag = false;
			return;
		}
		else if(cs[nm] == "}")
		{
			flag = false;
			return;
		}
		
		
	}
}

bool LoadMainRule(std::vector<main_Rule> &rs, std::string Name)
{
	string c_f = GetExtension(Name);
	if(c_f == "lua")
	{
		return LoadMainRule_Lua(rs, Name);
	}
	else
	{
		
		std::ifstream ifs( Name.c_str() , ios::in | ios::binary );
		if(!ifs)return false;

		
		int type = 0;
		while(!ifs.eof())
		{  
			char c;
			ifs.read( ( char * ) &c, sizeof( char ) );
			if(c == 0)
			{
				type = 1;
			}
			
		}
		ifs.seekg(0, ios_base::beg);
		ifs.seekg(0, ios_base::beg);


		

		if(type == 0)
		{
			
			ifs.close();
			ifs.open(Name.c_str());

			std::vector<std::string> cs;

			string hoge;

			while(getline( ifs, hoge ))
			{
				

				string token;
				istringstream stream( hoge );

				while(getline( stream, token, ' ' ))
				{
					std::string tmp = Replace(token, "	", "");
					cs.push_back(Replace(tmp, " ", ""));
					//std::cout << cs[cs.size()-1] << std::endl;
					
				}
			}

			for(int i=0;i < cs.size();i++)
			{
				
			}

			

			for(int i=0;i < cs.size();i++)
			{
				
				if(cs[i] == "{")
				{
					
					
					main_Rule mr;

					while(true)
					{
						if(!AddCount(cs, i))
							break;
						if(cs[i] == "{")
							break;
					}
					
					if(!AddCount(cs, i))
						return false;

					
					LoadAddRule(cs, i, mr.ar);

					
					

					while(true)
					{
						if(!AddCount(cs, i))
							break;
						if(cs[i] == "{")
							break;
					}
					if(!AddCount(cs, i))
						break;



					LoadHRule(cs, i, mr.rs);

					while(true)
					{
						if(!AddCount(cs, i))
							break;
						if(cs[i] == "}")
							break;
					}
					
					rs.push_back(mr);

					
				}
			}
				
		}
		else
		{
			int m;
			ifs.read( (char*)&m, sizeof(m) );
			for(int h=0;h < m;h++)
			{

				main_Rule R;
				int w;
				ifs.read( (char*)&w, sizeof(w) );
				for(int i=0;i < w;i++)
				{
					add_Rule ar;

					string s;
					s = ReadString( ifs );
					ar.name = s;

					int v;
					ifs.read( (char*)&v, sizeof(v) );
					ar.state = v;
					
					
					
					R.ar.push_back(ar);

				}


				int c;
				ifs.read( (char*)&c, sizeof(c) );
				

				for(int i=0;i < c;i++)
				{
					Rule r;
					
					int d;
					ifs.read( (char*)&d, sizeof(d) );

					

					
					for(int j=0;j < d;j++)
					{
						int e;
						ifs.read( (char*)&e, sizeof(e) );

						vector<sub_Rule> SRs;

						

						
						

						for(int k=0;k < e;k++)
						{
							sub_Rule SR;
							string s;
							s = ReadString( ifs );


							SR.v = s;

							SR.s = 0;

							
							SRs.push_back(SR);
						}
						r.SR.push_back(SRs);
					}

					

					R.rs.push_back(r);
				}
				rs.push_back(R);
			}
		}

		ifs.close();
	}

	return true;

	
}


