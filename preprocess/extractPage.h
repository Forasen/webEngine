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
    //:m_output(output)
    {
#if 0
        m_output.open(str);
        if(!m_output)
        {
            perror("m_output open!");
        }
        else
        {
            std::cout<<"Congratulation! file:"<<str<<"has been open successfully!"<<std::endl;
        }
#endif
    }

    ~extractPage()
    {
        //m_output.close();
    }
    void scanDir(std::string str, int depth)
    {
        //std::cout<<"scanDir() starting..."<<std::endl;
        int space = 1;
        DIR* dp;
        if((dp=opendir(str.c_str())) == NULL)
        {
            perror("opendir");
            exit(-1);
        }
        struct stat statbuf;
        struct dirent* entry;
        //memset(entry, 0, sizeof(*entry));
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
                //m_output << tmp;
                //std::cout<<tmp;
                //printf("%*s+ %s\n", depth, "", entry->d_name);
                //printf("%*s%s/", depth, "", entry->d_name);
                scanDir(entry->d_name, depth+space);
            }
            else
            {
                char tmp[1024];
                memset(tmp, 0, sizeof(tmp));
                //fprintf(m_output, "%*s- %s\n", depth, "", entry->d_name);
                sprintf(tmp, "%*s- %s\n", depth, "", entry->d_name);
                //m_output << tmp;
                m_vec_tmp.push_back(tmp);
                //std::cout<<tmp;
                //printf("%*s- %s\n", depth, "", entry->d_name);
                //printf("%*s%s\n", depth, "", entry->d_name);
            }
            //memset(entry, 0, sizeof(*entry));
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
    //int circulation_cnt = 0;
    for(auto it: m_vec_tmp)
    {
        /*
        circulation_cnt++;
        if(circulation_cnt <= 1)
        {
            
        std::cout<<"m_vec_tmp.size="<<m_vec_tmp.size()<<std::endl;
        std::cout<<"ouput_wholepath<<it"<<std::endl;
        }
        */
        output_wholepath<<it;
    }
}
void generate_ripepage(std::string outputripepage)
{

}

void generate_offset(std::string outputoffset)
{

}
void handle_scan_dir(std::string scan_dir, std::string outputripepage, std::string outputoffset)
{
    int num_dir = 0;
    //std::map<int, std::string> map_path;
    //std::vector<std::string> vec_path;
    #if 0
    std::string dir_name = "./tmp1";
    std::string filename = "./scandir.dat";
    #endif

    ifstream input_scandir("./test_generate_page/scandir.dat");
    //ifstream input_scandir("./generate_page/scandir.dat");
    if(input_scandir)
    {
        //std::cout<<"open input success!"<<std::endl;
        std::string line;
        int pre_num_space = 0;
        while(getline(input_scandir, line))
        {
            //std::cout<<"inside while(handle_scan_dir)..."<<std::endl;
            //std::cout<<"line->"<<line<<std::endl;
            int num_space = 0;
            //for(auto it: line)
            //int length = str
            stringstream ss(line);

            std::string flag;
            std::string word;
            ss >> flag;
            /*handle the existing directory*/
#if 0
            while(isspace(line[index]))
            {
                num_space++;
                index++;
            }
#endif
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
#if 0
            std::string tmp_word;
            while(ss >> tmp_word)
            {
                word += tmp_word;
            }
            std::cout<<"word:"<<word<<std::endl;
#endif
            //std::cout<<"line.size() = "<<line.size()<<std::endl;
            //for(int index=0; index<line.size(); index++)
            //for(auto it: line)
            //while(isspace(it.c_str()))
            //while(isspace(it))
            int index = 0;
            //std::cout<<"line("<<line.size()<<"):["<<line<<"]has "<<num_space<<" spaces!"<<std::endl;
#if 0
            std::cout<<std::endl;
            printf("%8d\n", pre_num_space);
            printf("%-20s%0d spaces!\n", line.c_str(), num_space);
            printf("%8d\n", num_space);
#endif
#if 0
            if(num_space == 0)
            {
                m_vec_path.push_back("./");
            }
#endif
            if(flag == "+")
            {
                if(num_space <= pre_num_space)
                {
                    if(!m_vec_path.empty())
                    {
                        handle_vec_dir(m_vec_path, num_space);
                    }
                    if(num_space == 0)
                    {
                        //m_vec_path.push_back("./");
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
                if(num_space == 0)
                {
                    //m_vec_path.push_back("./");
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
        //ofstream output_lib("./tmp/ripepage.lib");
        //ofstream output_lib(output_file);

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
                //memset(&index_content, 0, sizeof(index_content));
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
                    //std::cout<<"Sorry! inside for-else(title):"<<index_title<<std::endl;
                    }
            //std::cout<<"after while title:"<<index_title<<std::endl;
            //std::cout<<index_content<<std::endl;
            //std::cout<<"before the <doctitle></doctitle>title:"<<index_title<<std::endl;
            char ch_docid[10];
            sprintf(ch_docid, "%d", it.first);
            std::string str_docid = ch_docid;

            /*handle the ^M*/
            index_title = index_title.substr(0, index_title.size() - 1);

            index_doc += "<doc>\n<docid> " 
                        + str_docid 
                        + " <docid>\n<docurl> " 
                        + it.second 
                        + " </docurl>\n<doctitle> " 
                        + index_title 
                        + " </doctitle>\n<doccontent>\n" 
                        + index_content + "\n</doccontent>\n</doc>\n";
            //std::cout<<"after the <doctitle></doctitle>title:"<<index_title<<std::endl;
            output_ripepage<<index_doc;
            int docsize = index_doc.size();
            output_offset<<it.first<<"\t"<<docoffset<<"\t"<<docsize<<std::endl;
            if(docsize <= 300)
            {
                docsize_cnt++;
                std::cout<<"(docsize<=300)docsize="<<docsize<<"path:"<<tmp_second<<std::endl;
            }
            //docoffset = output_ripepage.tellg();
            docoffset = output_ripepage.tellp();
        }
        //std::cout<<"docsize_cnt="<<docsize_cnt<<std::endl;
        output_ripepage.close();
        output_offset.close();
        input_scandir.close();
        }
    void handle_vec_dir(std::vector<std::string>& vec, int num)
    {
        //std::cout<<"handle_vec_dir() starting ..."<<std::endl;
        auto it = vec.begin();
        it += num;
        if(it < vec.end())
        {
            //std::cout<<"vec.erase()"<<std::endl;
            vec.erase(it, vec.end());
#if 0
            std::cout<<"after vec.erase:";
            for(auto it_inner: vec)
            {
                std::cout<<it_inner;
            }
            std::cout<<std::endl;
#endif
        }
        else
        {
            return;
        }
    }

    void do_ripepage()
    {
        /*m_vec_tmp*/ 
    #if 0
            bool start_flag = true;
            int location = 0;
            for(auto it: m_vec_tmp)
            {
                ifstream it.second
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
        #endif
    }

    private:
        //std::vector<std::string> m_vec_dir;
        //std::string filename = "./scandir.dat";
        //ofstream m_output("./scandir.dat");
        //ofstream m_output;
        //ofstream m_output(filename);
        std::map<int, std::string> m_map_path;
        std::vector<std::string> m_vec_path;
        std::vector<std::string> m_vec_tmp;
        };
        #endif
#if 0
    void show_file(std::string file)
    {
        std::cout<<"calling ... show_file"<<std::endl;
        ifstream input_1(file);
        std::string line;
        if(input_1)
        {
            while(getline(input_1, line))
            {
                std::cout<<line<<std::endl;
            }
        }
        else
        {
            std::cout<<"sorry! open input scandir.dat!"<<std::endl;
            return;
        }
        input_1.close();
    }
#endif
#if 0
int main(void)
{
    #if 0
    std::string dir_name;
    std::cout<<"Enter a dir name : ";
    std::cin>>dir_name;
    std::cout<<"the result is >>>>>>"<<std::endl;
    #endif

    //std::string dir_name = "./filedata";
    std::string dir_name = "./tmp_file_data/";
    //std::string dir_name = "./tmp1/C15-Energy65.txt";
    std::string filename = "./scandir.dat";
    //std::string filename = "./scandir.dat";

    extractPage ep;
    //ep.scanDir(dir_name, 0);
    ep.do_scanDir(dir_name, 0, filename);

    //std::string output_dir_file = "./tmp/dir_file.dat";
#if 0
    std::string output_dir_file = "./tmp/ripepage.lib";
    std::string outputoffset = "./tmp/offset.lib";
#endif
    std::string output_dir_file = "./tmp2_test_page/ripepage.lib";
    std::string outputoffset = "./tmp2_test_page/offset.lib";
    ep.handle_scan_dir(dir_name, output_dir_file, outputoffset);

    return 0;
}

#endif
#if 0
int main(void)
{
    #if 0
    std::string dir_name;
    std::cout<<"Enter a dir name : ";
    std::cin>>dir_name;
    std::cout<<"the result is >>>>>>"<<std::endl;
    #endif

    //std::string dir_name = "./test_filedata";
    std::string dir_name = "./filedata";
    //std::string filename = "./test_generate_page/scandir.dat";
    std::string outputscandir_wholepath = "./generate_page/scandir.dat";

    extractPage ep;
    ep.do_scanDir(dir_name, 0, outputscandir_wholepath);

#if 1//normal file
    std::string outputripepage = "./generate_page/ripepage.lib";
    std::string outputoffset = "./generate_page/offset.lib";
#endif

#if 0//test file 
    std::string output_dir_file = "./test_generate_page/ripepage.lib";
    std::string outputoffset = "./test_generate_page/offset.lib";
#endif 
    ep.handle_scan_dir(dir_name, outputripepage, outputoffset);

    return 0;
}



#endif
