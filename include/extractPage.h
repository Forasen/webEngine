/*********************************************
  > File  : extractPage.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Tue 21 Jul 2015 08:26:51 AM CST
 ********************************************/

#ifndef _EXTRACTPAGE_H
#define _EXTRACTPAGE_H

#include<stdio.h>
#include<iostream>
#include<cstring>
#include<dirent.h>
#include<cstdlib>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>

using namespace std;

class extractPage
{
    public:
        explicit extractPage()
        {}
        ~extractPage()
        {}
        void scanDir(std::string str, int depth)
        {
            int space = 1;
            DIR* dp;
            if((dp=opendir(str.c_str())) == NULL)
            {
                perror("opendir");
                exit(-1);
            }
            struct stat statbuf;
            struct dirent* entry;
            chdir(str.c_str());
            while((entry=readdir(dp)) != NULL)
            {
                if(-1 == lstat(entry->d_name, &statbuf))
                {
                    perror("stat");
                    exit(-1);
                }
                if(S_ISDIR(statbuf.st_mode))
                {
                    if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0)
                    {
                        continue;
                    }
                    char tmp[1024];
                    memset(tmp, 0, sizeof(tmp));
                    sprintf(tmp, "%*s+ %s\n", depth, "", entry->d_name);
                    m_vec_tmp.push_back(tmp);
                    scanDir(entry->d_name, depth+space);
                }
                else
                {
                    char tmp[1024];
                    memset(tmp, 0, sizeof(tmp));
                    sprintf(tmp, "%*s- %s\n", depth, "", entry->d_name);
                    m_vec_tmp.push_back(tmp);
                }
            }
            chdir("..");
            closedir(dp);
        }
        void do_scanDir(std::string str, int depth, std::string outputwholepath)
        {
            scanDir(str, depth);
            ofstream output_wholepath(outputwholepath);
            if(!output_wholepath)
            {
                perror("output_wholepath!");
                return;
            }
            for(auto it: m_vec_tmp)
            {
                output_wholepath<<it;
            }
        }
        void handle_scan_dir(std::string scan_dir, std::string outputripepage, std::string outputoffset)
        {
            int num_dir = 0;
            ifstream input_scandir("./test_generate_page/scandir.dat");
            if(input_scandir)
            {
                std::string line;
                int pre_num_space = 0;
                while(getline(input_scandir, line))
                {
                    int num_space = 0;
                    stringstream ss(line);
                    std::string flag;
                    std::string word;
                    ss >> flag;

                    bool start_flag = true;
                    int location = 0;
                    for(auto it: line)
                    {
                        if(isspace(it) && start_flag)
                        {
                            num_space++;
                        }
                        if(!isspace(it))
                        {
                            start_flag = false;
                        }
                        if(isalpha(it))
                        {
                            break;
                        }
                        location++;
                    }
                    for(int index=location; index!=line.size(); index++)
                    {
                        word += line[index];
                    }
                    int index = 0;

                    if(flag == "+")
                    {
                        if(num_space <= pre_num_space)
                        {
                            if(!m_vec_path.empty())
                            {
                                handle_vec_dir(m_vec_path, num_space);
                            }
                            word += "/";
                            m_vec_path.push_back(word);
                        }
                        else
                        {
                            word += "/";
                            m_vec_path.push_back(word);
                        }
                    }
                    if(flag == "-")
                    {
                        if(num_space <= pre_num_space)
                        {
                            if(!m_vec_path.empty())
                            {
                                handle_vec_dir(m_vec_path, num_space);
                            }
                        }
                        m_vec_path.push_back(word);
                        std::string temp_str;
                        for(auto it: m_vec_path)
                        {
                            temp_str += it;
                        }
                        m_map_path.insert({num_dir, temp_str});
                        num_dir++;
                    }
                    pre_num_space = num_space;
                }
            }
            else
            {
                perror("ifstream");
                exit(-1);
            }

            ofstream output_ripepage(outputripepage);

            if(!output_ripepage)
            {
                perror("ofstream output_ripepage");
                exit(-1);
            }

            ofstream output_offset(outputoffset);
            if(!output_offset)
            {
                perror("ofstream output_offset!");
                exit(-1);
            }
            int tmp_offset = 0;
            int docoffset = 0;
            int docsize_cnt = 0;
            for(auto it: m_map_path)
            {
                char tmp[1024];
                memset(tmp, 0, sizeof(1024));
                std::string dir_symbol = "/";
                std::string tmp_second = scan_dir + dir_symbol + it.second;
                sprintf(tmp, "%d\t%s\n", it.first, tmp_second.c_str());
                ifstream index_input(tmp_second);
                if(!index_input)
                {
                    perror("index_input error!");
                    exit(-1);
                }
                std::string index_line;
                int index_line_cnt = 0;
                std::string index_title;
                std::string first_tmp_title;
                std::string index_content;
                std::string index_doc;
                bool title_flag = false;
                while(getline(index_input, index_line))
                {
                    if(index_line_cnt == 0)
                    {
                        first_tmp_title = index_line;
                    }
                    index_content += index_line;
                    index_content = index_content.substr(0, index_content.size() -1);
                    index_content += "\n";

                    if(index_line_cnt < 13)
                    {

                        std::string flag_title = "【 标  题 】";
                        if((index_line.substr(0, 16) == flag_title))
                        {
                            for(int ind=16; ind<index_line.size(); ind++)
                            {
                                index_title += index_line[ind];
                            }
                            title_flag = true;
                        }

                    }
                    index_line_cnt++;
                }
                if(!title_flag)
                {
                    index_title = first_tmp_title;
                }
                char ch_docid[10];
                sprintf(ch_docid, "%d", it.first);
                std::string str_docid = ch_docid;

                index_title = index_title.substr(0, index_title.size() - 1);

                index_doc += "<doc>\n<docid> " 
                    + str_docid 
                    + " <docid>\n<docurl> " 
                    + it.second 
                    + " </docurl>\n<doctitle> " 
                    + index_title 
                    + " </doctitle>\n<doccontent>\n" 
                    + index_content + "\n</doccontent>\n</doc>\n";
                output_ripepage<<index_doc;
                int docsize = index_doc.size();
                output_offset<<it.first<<"\t"<<docoffset<<"\t"<<docsize<<std::endl;
                if(docsize <= 300)
                {
                    docsize_cnt++;
                    std::cout<<"(docsize<=300)docsize="<<docsize<<"path:"<<tmp_second<<std::endl;
                }
                docoffset = output_ripepage.tellp();
            }
            output_ripepage.close();
            output_offset.close();
            input_scandir.close();
        }
        void handle_vec_dir(std::vector<std::string>& vec, int num)
        {
            auto it = vec.begin();
            it += num;
            if(it < vec.end())
            {
                vec.erase(it, vec.end());
            }
            else
            {
                return;
            }
        }

    private:
        std::map<int, std::string> m_map_path;
        std::vector<std::string> m_vec_path;
        std::vector<std::string> m_vec_tmp;
};
#endif
