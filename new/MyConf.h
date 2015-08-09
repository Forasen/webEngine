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
			/*read from configure!*/
			if(!m_fIn)
			{
				fprintf(stderr, "error: conf open!\n");
				exit(1);
			}


            //std::cout<<"+++++++++++conf.dat has been open+++++++++"<<std::endl;

			std::string line;
			std::string key, value;
			while(getline(m_fIn, line))
			{
				stringstream ss(line);
				ss>>key>>value;
				m_map_conf.insert(make_pair(key, value));
			}
			m_fIn.close();

			/*read from dict*/
			m_fIn.open(m_map_conf["dict"].c_str());
			if(!m_fIn)
			{
                fprintf(stderr, "error: dict open!\n");
				exit(1);
			}
			while(getline(m_fIn, line))
			{
				/*transform upper into lower*/
#if 0
				for(auto& it: line)
				{
					if(!isalpha(it))
					{
						it = ' ';
					}
					if(isupper(it))
					{
						it += 32;
					}
				}
#endif
				stringstream ss(line);
				std::string str_value;
				ss >> key >> str_value;//assume the word is already existing as (word, frequnce)
				int int_value = atoi(str_value.c_str());
				m_vec_dict.push_back(make_pair(key, int_value));
				for(std::size_t index=0; index<m_vec_dict.size(); index++)
				{
					index_to_map(index, m_map_index_vec);                
				}
			}
			m_fIn.close();
		}
		void index_to_map(std::size_t& i, std::map<std::string, std::set<int> > &map_char_index)
		{
			std::string word, character;
			word = m_vec_dict[i].first;
			for(std::size_t index=0; index<word.size(); index++)
			{
				int tmp = word[index];
				if(tmp>0 && tmp<255)//handle a chinese character
				{
					character = word.substr(index, 1);
				}
				else
				{
					character = word.substr(index, 2);
				}
				map_char_index[character].insert(i);//the sequence is unique for every word
			}
		}

		void show_index()
		{
			std::cout<<"show_index()"<<std::endl;
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
			std::cout<<"show_conf()"<<std::endl;
			for(auto it: m_map_conf)
			{
				std::cout<<it.first<<"\t\t"<<it.second<<std::endl;
			}
		}

		void show_vec()
		{
			std::cout<<"show_vec()"<<std::endl;
			int cnt = 0;
			for(auto it: m_vec_dict)
			{
				std::cout<<it.first<<"\t"<<it.second<<"\t"<<cnt<<std::endl;
				cnt++;
			}
		}

		~MyConf()
		{

		}
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
