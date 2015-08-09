/*********************************************
  > File  : MyInvertIndex.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Tue 21 Jul 2015 08:26:51 AM CST
 ********************************************/
#ifndef _MYINVERTINDEX_H
#define _MYINVERTINDEX_H

#include<cmath>

#include "MyRemoveDup.h"
#include "extractPage.h"

class MyInvertIndex
{
public:
    MyInvertIndex()
    {
        m_map_statistic = mremove.getStatisticWord_All();
    }
    ~MyInvertIndex(){}
    void handleInverIndex()
    {
        std::multimap<std::string, std::pair<int, std::pair<int, double> > > tmp_map_pair_invert_index;
        int total_doc_cnt = m_map_statistic.size();
        std::map<std::string, int> tmp_map_weblib_df;
        for(auto it_map: m_map_statistic)
        {
            for(auto it_vec: it_map.second)
            {
                tmp_map_weblib_df[it_vec.first] += it_vec.second;
            }
        }
        for(auto it_map: m_map_statistic)
        {
            std::set<std::pair<int, double> > tem_set;
            std::map<std::string, std::pair<int, double> > tmp_map_word_weight;
            int total_words_cnt = it_map.second.size();
            double tmp_word_article_idf;
            double tmp_article_total_weight = 0;
            for(auto it_vec: it_map.second)
            {
                auto it_find_res = tmp_map_weblib_df.find(it_vec.first);
                if(it_find_res  == tmp_map_weblib_df.end())
                {
                    std::cout<<"ERROR! THE WORD NOT EXIST!"<<std::endl;
                    exit(-1);
                }
                int tmp_word_article_df = it_find_res->second;
                tmp_word_article_idf = log((double)total_doc_cnt / (tmp_word_article_df + 0.000001)); 
                std::pair<int, double> tmp_pair;
                double tmp_tf = (double)it_vec.second / (total_words_cnt + 0.000001);
                double tmp_pre_word_weight = tmp_tf * tmp_word_article_idf;
                tmp_article_total_weight += pow(tmp_pre_word_weight, 2);
                tmp_map_word_weight[it_vec.first] = std::make_pair(it_vec.second, tmp_pre_word_weight);
            }
            double tmp_article_denominator = sqrt(tmp_article_total_weight);
            for(auto& it_tmp_map_weight: tmp_map_word_weight)
            {
                double tmp_real_word_weight =  (double)it_tmp_map_weight.second.second / tmp_article_denominator;

                tmp_map_pair_invert_index.insert(
                        std::make_pair(it_tmp_map_weight.first, 
                            std::make_pair(it_map.first, 
                                std::make_pair(it_tmp_map_weight.second.first, tmp_real_word_weight))));

            }
        for(auto it_weblib: tmp_map_weblib_df)
        {
            std::map<int, std::pair<int, double> > tmp_map;
            for(auto beg=tmp_map_pair_invert_index.lower_bound(it_weblib.first),
                     end=tmp_map_pair_invert_index.upper_bound(it_weblib.first);
                beg!=end; beg++)
            {
                tmp_map[beg->second.first] = std::make_pair(beg->second.second.first, beg->second.second.second);
            }
                m_map_invert_index[it_weblib.first] = tmp_map;
        }
        std::ofstream output_invertindex("./test_generate_page/invertindex.lib");
        if(!output_invertindex)
        {
            perror("output_invertindex");
            exit(-1);
        }
        for(auto it_f_1: m_map_invert_index)
        {
            output_invertindex<<it_f_1.first<<"\t";
            for(auto it_f_2: it_f_1.second)
            {
                output_invertindex<<it_f_2.first<<"\t"<<it_f_2.second.first<<"\t"<<it_f_2.second.second<<"\t";
            }
            output_invertindex<<std::endl;
        }
    }
     std::map<std::string, std::map<int, std::pair<int, double> > >& getInverIndex()
     {
        return m_map_invert_index;
     }
    void display()
    {
        int cnt = 0;
        for(auto it: m_map_statistic)
        {
            cnt++;
            std::cout<<"from MyInvertIndex: article_num="<<it.first<<std::endl;
            for(auto it22: it.second)
            {
                std::cout<<it22.first<<"\t"<<it22.second<<std::endl;
            }
            if(cnt >= 1)
            {
                break;
            }
        }
    }
private:
    std::map<int, std::vector<std::pair<std::string, int> > > m_map_statistic;
    MyRemoveDup mremove;
    std::map<std::string, std::map<int, std::pair<int, double> > > m_map_invert_index;
};
