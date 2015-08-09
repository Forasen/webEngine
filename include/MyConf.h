/*********************************************
  > File  : MyConf.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Sat 11 Jul 2015 10:47:13 PM CST
 ********************************************/

#ifndef _MYCONF_H
#define _MYCONF_H

#include<iostream>
#include<map>
#include<iterator>
#include<vector>
#include<fstream>
#include<sstream>
#include<set>
#include<stdlib.h>
#include<utility>
#include<cstring>

using namespace std;

class MyConf
{
	public:
		friend class MyTask;
		MyConf(const std::string& name)
			:m_fIn(name.c_str())
		{
			if(!m_fIn)
			{
				fprintf(stderr, "error: conf open!\n");
				exit(1);
			}
			std::string line;
			std::string key, value;
			while(getline(m_fIn, line))
			{
				stringstream ss(line);
				ss>>key>>value;
				m_map_conf.insert(make_pair(key, value));
			}
			m_fIn.close();

			m_fIn.open(m_map_conf["dict"].c_str());
			if(!m_fIn)
			{
                fprintf(stderr, "error: dict open!\n");
				exit(1);
			}
			while(getline(m_fIn, line))
			{
				stringstream ss(line);
				std::string str_value;
				ss >> key >> str_value;
				int int_value = atoi(str_value.c_str());
				m_vec_dict.push_back(make_pair(key, int_value));
				for(std::size_t index=0; index<m_vec_dict.size(); index++)
				{
					index_to_map(index, m_map_index_vec);                
				}
			}
			m_fIn.close();
		}
		void index_to_map(int ind, std::map<std::string, std::set<int> >& map_char_index)
		{
			std::string word;
            std::string ch;
			word = m_vec_dict[ind].first;
			for(int index=0; index<word.size();)
			{
				int tmp = word[index];
				if(tmp>0 && tmp<255)
				{
					ch = word.substr(index, 1);
                    index++;
				}
				else
				{
					ch = word.substr(index, 3);
                    index += 3;
				}
				map_char_index[ch].insert(ind);
			}
		}
		void show_index()
		{
			std::cout<<"size = "<<m_map_index_vec.size()<<std::endl;
			for(auto it: m_map_index_vec)
			{
				std::cout<<"ch : "<<it.first<<"\t-> ";
				for(auto it_set: it.second)
				{
					std::cout<<it_set<<" ";
				}
				std::cout<<std::endl;
			}
		}

		void show_conf()
		{
			for(auto it: m_map_conf)
			{
				std::cout<<it.first<<"\t\t"<<it.second<<std::endl;
			}
		}

		void show_vec()
		{
			int cnt = 0;
			for(auto it: m_vec_dict)
			{
				std::cout<<it.first<<"\t"<<it.second<<"\t"<<cnt<<std::endl;
				cnt++;
			}
		}

		~MyConf(){}
		std::map<std::string, std::string>& get_conf_map()
		{
			return m_map_conf;
		}

		std::map<std::string, std::string> m_map_conf;
	private:
		std::vector<std::pair<std::string, int> > m_vec_dict;
		std::map<std::string, std::set<int> > m_map_index_vec;
		ifstream m_fIn;
};
#endif
