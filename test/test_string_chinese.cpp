/*************************************************************************
> File Name: test_string_chinese.cpp
> Author: 
> Mail: 
> Created Time: Wed 22 Jul 2015 02:43:55 PM CST
************************************************************************/

#include<iostream>
#include<vector>
#include<unistd.h>
#include<fstream>
#include<sstream>
#include<string.h>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main(void)
{
    ifstream index_input("./C15-Energy65.txt");
    std::cout<<"open index_input success!"<<std::endl;
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

    std::string tmp_content;
    std::string tmp_line;
    //std::cout<<"tmpline:"<<tmp_line<<std::endl;
    //std::cout<<"line:"<<line_cnt<<", "<<tmp_content<<std::endl;
    //std::cout<<"line:"<<line_cnt<<", "<<tmp_line<<std::endl;
    //std::cout<<"before->tmpLine:"<<tmp_line<<std::endl;
    //std::cout<<"***********the article**************"<<std::endl;
    while(getline(index_input, index_line))
    {
        //memset(&index_content, 0, sizeof(index_content));
        index_content += index_line;
        index_content += "\n";
        //std::cout<<"inside:"<<index_content<<std::endl;
        if(index_line_cnt < 12)
        {
            if(index_line_cnt == 0)
            {
                first_tmp_title = index_line;
            }
            std::string flag_title = "【 标  题 】";
            std::cout<<"the flag_title.size="<<flag_title.size()<<std::endl;
            if(index_line_cnt<15 && ((index_line.substr(0, 16) == flag_title)))
            {

                std::cout<<"Congratulatin! index_line.substr(0, 16)== flag_title"<<std::endl;
                std::cout<<"index_line.substr(0, 16):"<<index_line.substr(0, 16)<<std::endl;
                for(int ind=16; ind<index_line.size(); ind++)
                {
                    index_title += index_line[ind];
                    std::cout<<"inside for index_title += index_line[ind]"<<std::endl;
                }
                //std::cout<<"hello, world(inside while(getline)"<<std::endl;
                std::cout<<"index_title:"<<index_title<<std::endl;
            }
            else
            {
                std::cout<<"inside else index_title!"<<std::endl;
                index_title = first_tmp_title;
            }
        }
        index_line_cnt++;
    }
    std:cout<<"****article**********"<<std::endl;
    std::cout<<index_content<<std::endl;
    index_doc +=  "<doctitle> "  + index_title + " </doctitle>\n<doccontent>\n" + index_content + "\n</doccontent>\n</doc>\n";

    //int docsize = index_doc.size();
    //output_lib << tmp;
    //std::cout<<tmp;
    //std::cout<<"inside handle_scan_dir : "<<tmp<<std::endl;
    //output_ripepage<<index_doc;
    //std::cout<<index_doc;

            //output_offset<<it.first<<"\t"<<docoffset<<"\t"<<docsize<<std::endl;
            //std::cout<<"************************"<<std::endl<<std::endl;
            ////std::cout<<it.first<<"\t"<<docoffset<<"\t"<<docsize<<std::endl;
            //docoffset = output_ripepage.tellg();
            //docoffset = output_ripepage.tellp();
            //std::string str = "hello";
            //std::string str = "【 标  题 】我是中国人民，我深深地爱着我的祖国！ I love my county!";
#if 0
            //std::cout<<"str.size="<<str.size()<<std::endl;
            //std::cout<<"substr(0, 16) : "<<str.substr(0, 16)<<std::endl;
            std::string flag = "【 标  题 】";
            std::cout<<"flag.size="<<flag.size()<<std::endl;
            if(str.substr(0, 16) == flag)
            //if(strcmp(str.substr(0, 16).c_str(), flag.c_str()) == 0)
            {
                std::cout<<"Congratulatin!"<<std::endl;
                std::cout<<"the flag is : "<<flag<<std::endl;
            }
            std::cout<<"substr(0, 18) : "<<str.substr(0, 19)<<std::endl;
            std::string title;
            for(int index=16; index<str.size(); index++)
            {
                title += str[index];
            }
            std::cout<<"title : "<<title<<std::endl;
            std::string index_doc;
            std::string content = "22222";
            index_doc += "<doc>\n<docid> " 
            + content
            + " <docid>\n<docurl> " 
            + "22222" 
            + " </docurl>\n<doctitle> " 
            + "33333" 
            + " </doctitle>\n<doccontent>\n" 
            + "44444" 
            + "\n</doccontent>\n</doc>";
            std::cout<<index_doc<<std::endl;
    //std::string str = "hellohow, world";
    std::string str = "hello worldh nihao hwo are we a";
    std::cout<<"str:"<<str<<std::endl;
    std::cout<<"size"<<"\t"<<"offset"<<std::endl;
    //std::cout<<"Enter a string: "<<std::endl;
    //std::cin>>str;
    stringstream ss(str);
    std::string word;
    while(ss >> word)
    {
        std::cout<<word<<".size="<<word.size()<<std::endl;       
        std::cout<<str.size()<<"\t"<<ss.tellg()<<std::endl;

    }
    std::cout<<"before ss>>word ss.tellg()="<<ss.tellg()<<std::endl;
    std::string word;
    ss>>word;
    std::cout<<"tellg() = "<<ss.tellg()<<std::endl;

    std::cout<<"gcount() = "<<ss.gcount()<<std::endl;


    int int_val = 10;
    //char* ch_int = static_cast<char*>(int_val);
    char str[10];
    sprintf(str, "%d\n", int_val);
    std::cout<<"ch_int(char*) : "<<str<<std::endl;
    std::string str_string = str;
    std::cout<<"str_string : "<<str_string<<std::endl;
    int aval = 5;
    aval += atoi(str);
    std::cout<<"aval="<<aval<<std::endl;

#endif
    return 0;
}
