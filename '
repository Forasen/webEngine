/*************************************************************************
> File Name: MyRemoveDup.h
> Author: 
> Mail: 
> Created Time: Sat 25 Jul 2015 08:33:04 AM CST
************************************************************************/

#ifndef _MYREMOVEDUP_H
#define _MYREMOVEDUP_H

//#include<map>
//#include<cstring>
//#include<vector>
#include<queue>
#include<unordered_map>
#include<utility>

#include<algorithm>
#include<iterator>

#include<map>
#include "./MySplit.h"
#include "./extractPage.h"
//#include "./MyResult.h"
//#include "./MyCompare.h"
class article1
{
    public:
    int article_num;
    bool article_flag;
};

using namespace std;

class MyRemoveDup
{
    public:
    #if 0
    MyRemoveDup(MySplit& mysplit)
    :m_map_split(mysplit.getMapSplit())
    {}
    #endif

    #if 1
    MyRemoveDup()
    //:m_map_split(mysplit.getMapSplit())
    {
        m_map_split = mysplit.getMapSplit();
        //std::cout<<"calling function: MyRemoveDup()"<<std::endl;
    }
    #endif
    ~MyRemoveDup()
    {}

    //MyRemoveDup& operator=(const )
    void display()
    {

        //std::cout<<"calling class MyRemoveDup!!!!!!!!!*&*&*&*&*&*&*&*&*&*&*&"<<std::endl;
        std::cout<<"m_map_split.size="<<m_map_split.size()<<std::endl;
        for(auto it_first: m_map_split)
        {
            //std::cout<<"(inside for(auto it_first: m_map_stoplist))"<<std::endl;
            std::cout<<"article num="<<it_first.first<<std::endl;
            for(auto it_second: it_first.second)
            {
                std::cout<<it_second;
            }
            std::cout<<std::endl;
        }
    }
    std::map<int, std::vector<std::pair<std::string, int> > > getStatisticWord()
    //void getStatisticWord()
    {
        std::map<int, std::vector<std::pair<std::string, int> > > tmp_map_vec_article;
        //
        //int article_no;
        //std::unordered_map<std::string, int> article_word;
        //
        for(auto it_first: m_map_split)
        {
            std::map<std::string, int> tmp_map_str;
            for(auto it_second: it_first.second)
            {
                std::stringstream ss_word(it_second);
                std::string word;
                while(ss_word >> word)
                {
                    tmp_map_str[word]++; 
                }
                //resTmp.article_word = tmp_map_str;
                //resTmp.article_word.insert(tmp_map_str.begin(), tmp_map_str.end());
                //resTmp.article_word(tmp_map_str.begin(), tmp_map_str.end());
                /*
                for(auto it: tmp_map_str)
                {
                //std::cout<<it.first<<"\t"<<it.second<<std::endl;
            }
                */
            }
            std::multimap<int, std::string> tmp_invert;
            //std::cout<<"tmp_map_str.size="<<tmp_map_str.size()<<std::endl;
            for(auto it_str: tmp_map_str)
            {
                tmp_invert.insert(std::make_pair(it_str.second, it_str.first));
            }
            std::vector<std::pair<std::string, int> > tmp_vec;
            auto it_tmp_inv = tmp_invert.end();
            auto it_map_start = tmp_invert.begin();
            //it_tmp_inv = it_tmp_inv - 11;
            int count = 10;
            while(count)
            {
                it_tmp_inv--;
                count--;
            }
            //auto it_curr = tmp_invert.erase(it_map_start, it_tmp_inv);
            for(; it_tmp_inv!=tmp_invert.end(); it_tmp_inv++)
            {
                tmp_vec.push_back(std::make_pair(it_tmp_inv->second, it_tmp_inv->first));
            }
            //*****std::map<int, std::vector<std::pair<std::string, int> > > tmp_map_vec_article;
            tmp_map_vec_article[it_first.first] = tmp_vec;

            /*
            std::unordered_multimap<std::string, int> tmp_normal;
            for(auto it_normal: tmp_invert)
            {
            tmp_normal.insert(std::make_pair(it_normal.second, it_normal.first));
        }
            */

        }
        /*
        for(auto it_first: tmp_map_article)
        {
        std::cout<<"article@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:"<<it_first.first<<std::endl;
        std::cout<<"WORD"<<"\t"<<"FREQ"<<std::endl;
        for(auto it_second: it_first.second)
        {
        std::cout<<it_second.first<<"\t"<<it_second.second<<std::endl;
        }
        }
        for(auto it_first: tmp_map_article)
        {
        std::cout<<"article%%%%%%%%%%%%%%%%%%%%%%%%:"<<it_first.first<<std::endl;
        std::cout<<"WORD"<<"\t"<<"FREQ"<<std::endl;
        for(auto it_second: it_first.second)
        {
        std::cout<<it_second.first<<"\t"<<it_second.second<<std::endl;
        }
        }
        */
        return tmp_map_vec_article;
    }
    void display_map()
    {
        //std::cout<<"calling void display_map()*************$$$$$$$$$$$$$$$$$$"<<std::endl;
        //std::unordered_map<int, std::unordered_map<std::string, int> >& statistic_word = getStatisticWord();  
        std::map<int, std::vector<std::pair<std::string, int> > > statistic_word = getStatisticWord();  
        std::map<int, std::set<std::string> > map_com;
        //std::map<std::pair<int, bool>, std::set<std::string> > map_com;
        //std::string unflag = "unhandled";
        //std::string flag = "handled";

        //std::map<int, std::unordered_map<std::string, int> > tmp_map_article;
        for(auto it: statistic_word)
        {
            std::set<std::string> set_com;
            //std::map<std::string, int> tmp_map_word;
            //std::cout<<"article_no:"<<it.first<<std::endl; 

            for(auto it_1: it.second)
            {
                //tmp_map_word.insert(make_pair(it_1.first, it_1.second));
                //std::cout<<it_1.first<<"\t"<<it_1.second<<std::endl;
                set_com.insert(it_1.first);
            }

            //set_com.insert(unflag);
            /*
            for(auto it: set_com)
            {
            std::cout<<it<<",";
        }
            std::cout<<std::endl;
            */
            /*
            for(auto it_2: tmp_map_word)
            {
            std::cout<<it_2.first<<"\t"<<it_2.second<<std::endl;
        }
            */
            //article1  tmp_article;
            //tmp_article.article_num = it.first;
            //tmp_article.article_flag = false;
            //bool tmp_flag = false;
            //std::pair<int, bool> tmp_pair(std::make_pair(it.first, tmp_flag));
            map_com[it.first] = set_com;
            //map_com.insert(std::make_pair(tmp_article, set_com));
        }
        //auto it11=map_com.begin();
        //auto it11_end_pre = --it11->second.end();
        //int for_1_cnt = 0;

        //for(auto it11=map_com.begin(); it11!=map_com.end() && (!(it11->first.second)); it11++)
        for(auto it11=map_com.begin(); it11!=map_com.end(); it11++)
    {
        //for_1_cnt++;

        //auto it22_end_pre = --it22->second.end();
        //int for_2_cnt = 0;
        auto it22 = (++it11);
        //for(; it22!=map_com.end() && (!(it22->first.second)); it22++)
        if(it22 != map_com.end())
        {

            for(; it22!=map_com.end(); it22++)
            {
                std::vector<std::string> tmp_vec_intersection;
                std::cout<<"before tmp_vec_intersection.size="<<tmp_vec_intersection.size()<<std::endl;
                //for_2_cnt++;
                std::cout<<"article_num="<<it11->first<<" @VS@ article_num="<<it22->first<<std::endl;
                
                std::cout<<"it11->second...";
                for(auto it55: it11->second)
                {
                    std::cout<<it55<<", ";
                }
                std::cout<<std::endl;
                std::cout<<"it22->second...";
                for(auto it66: it22->second)
                {
                    std::cout<<it66<<", ";
                }
                std::cout<<std::endl;
                std::set_intersection(it11->second.begin(), it11->second.end(),
                                      it22->second.begin(), it22->second.end(),
                                      std::back_inserter(tmp_vec_intersection));
                if(tmp_vec_intersection.size() >= 1)
                {
                    std::cout<<"calling : if(tmp_vec_intersection.size()>=1) and intersection.size="<<tmp_vec_intersection.size()<<std::endl;
                    for(auto it_vec: tmp_vec_intersection)
                    {
                        std::cout<<it_vec<<",";
                    }
                    std::cout<<std::endl;
                    std::cout<<"---------------------------------"<<std::endl;
                    /*
                    if(it22!=map_com.end())
                    {

                    std::cout<<"map_com.erase called!"<<std::endl;
                    map_com.erase(it22);
                    std::cout<<"it22:"<<it22->first.first<<",";
                    for(auto it33: it22->second)
                    {
                    std::cout<<it33<<", ";
                }
                    std::cout<<"HAS BEEN DEL!"<<std::endl;
                    //it22->first.second = true;
                }
                    */
                }
                //std::cout<<"for_2_cnt="<<for_2_cnt<<std::endl;
            }

        }
    }
    //std::cout<<"for_1_cnt="<<for_1_cnt<<std::endl;
    std::cout<<"map_com.size="<<map_com.size()<<std::endl;

        /*
        for(auto it1: map_com)
        {
        std::string flag_str = "unhandled";
        if(it1.first.second)
        {
        flag_str = "handled";
        }
        std::cout<<"article_num="<<it1.first.first<<", article_flag:"<<flag_str<<std::endl;
        for(auto it2: it1.second)
        {
        std::cout<<it2<<",";
        }
        std::cout<<std::endl;
        std::cout<<"---------------------------------------"<<std::endl;
        }
        */

        //std::cout<<"mZ="<<statistic_word.size()<<std::endl;
        /*
        auto itfirst = statistic_word.begin();
        auto itsecond = itfirst->second.begin();
        for(; itfirst!=statistic_word.end(); itfirst++)
        {
        std::cout<<"article777777777777777777777777777%%%%%%%%%%%%%%%%%%%%%%%%:"<<itfirst->first<<std::endl;
        std::cout<<"WORD"<<"\t"<<"FREQ"<<std::endl;
        for(; itsecond!=itfirst->second.end(); itsecond++)
        {
        std::cout<<itsecond->first<<"\t"<<itsecond->second<<std::endl;
        }

        }
        for(auto it_first: statistic_word)
        {
        std::cout<<"article%%%%%%%%%%%%%%%%%%%%%%%%:"<<it_first.first<<std::endl;
        std::cout<<"WORD"<<"\t"<<"FREQ"<<std::endl;
        for(auto it_second: it_first.second)
        {
        std::cout<<it_second.first<<"\t"<<it_second.second<<std::endl;
        }
        }
        */
    }
        std::size_t nBytesCode(const char ch)
        {
            std::size_t nBytes = 0;
            if(ch & (1 << 7))
            {
                if((ch & 0xF0)==0xC0 || (ch & 0xF0) == 0xD0)
                {
                    nBytes = 2;
                }
                else if((ch & 0xF0) == 0xE0)
                {
                    nBytes = 3;
                }
                else if((ch & 0xF0) == 0xF0)
                {
                    nBytes = 4;
                }
                else if((ch & 0xFF) == 0xFE)
                {
                    nBytes = 6;
                }
            }
            else 
            {
                nBytes = 1;
            }
            return nBytes;
        }
        double getSimilarity(std::string doc1, std::string doc2)
        {

        }
        private:

    //std::unordered_map<int, std::vector<std::string> > m_map_split;
    std::map<int, std::vector<std::string> > m_map_split;
    MySplit mysplit;
    /*
    std::priority_queue<std::unordered_map<int, std::unordered_map<std::string, int> >,
    std::vector<std::unordered_map<int, std::unordered_map<std::string, int> > >,
    MyCompare> 
    m_top_word;
    */
    //std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> m_queue_top_word;
    };

int main(void)
{     
    //MySplit mysplit;
    //MyRemoveDup myremovedup(mysplit); 


    #if 0

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
    #endif

    MyRemoveDup myremovedup; 
    myremovedup.display_map();
    //myremovedup.display();

    return 0;
}

#endif
