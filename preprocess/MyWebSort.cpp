/*************************************************************************
> File Name: MyWebSort.h
> Author: 
> Mail: 
> Created Time: Tue 28 Jul 2015 04:27:11 PM CST
************************************************************************/

#ifndef _MYWEBSORT_H
#define _MYWEBSORT_H

#include<fstream>
#include<sstream>
#include<iostream>
#include<map>
#include<iterator>
#include<vector>
#include<set>
#include<utility>

#include "./extractPage.h"
#include "./MyInvertIndex.h"
#include "./MyRemoveDup.h"

#include "./MyNewPages.h"
#include "./MySplit.h"

class MyWebSort
{
    public:
    MyWebSort()
    {}
    ~MyWebSort()
    {}

    //void readInvertIndex(std::string invertfilename)
    std::map<std::string, std::map<int, std::pair<int, double> > > readInvertIndex(std::string invertfilename)
    {
        std::ifstream input_invert(invertfilename);
        if(!input_invert)
        {
            perror("input_invert");
            exit(-1);
        }

        std::map<std::string, std::map<int, std::pair<int, double> > > tmp_map_invert_index;

        std::string line_invert;
        while(getline(input_invert, line_invert))
        {
            std::stringstream ss_invert(line_invert);
            std::string tmp_word;

            ss_invert >> tmp_word;

            std::string docid_str;
            std::string freq_str;
            std::string weight_str;
            //!!std::map<std::string, std::map<int, std::pair<int, double> > > tmp_map_invert_index;
            std::map<int, std::pair<int, double> > tmp_map_mid;

            while(ss_invert >> docid_str >> freq_str >> weight_str)
            {
                int docid_int = atoi(docid_str.c_str());
                int freq_int = atoi(freq_str.c_str());
                double weight_double = atof(weight_str.c_str());

                tmp_map_mid[docid_int] = std::make_pair(freq_int, weight_double);
            }
            tmp_map_invert_index[tmp_word] = tmp_map_mid;
        }


        int circulation_cnt = 0;

        std::cout<<"tmp_map_invert_index(整个网页库的词语总数).size="<<tmp_map_invert_index.size()<<std::endl;
        /*
        for(auto it_f_1: tmp_map_invert_index)
        {
        //测试结果
        circulation_cnt++;
        if(circulation_cnt > 200 && circulation_cnt < 300)
        {
        //!!std::map<std::string, std::map<int, std::pair<int, double> > > tmp_map_invert_index;
        std::cout<<it_f_1.first<<"----->"<<std::endl;
        for(auto it_f_2: it_f_1.second)
        {
        std::cout<<"\t"<<it_f_2.first<<"\t"<<it_f_2.second.first<<"\t"<<it_f_2.second.second<<std::endl;
}
}
}
*/
//std::cout<<"before return index! tmp_map_invert_index.size="<<tmp_map_invert_index.size()<<std::endl;
return tmp_map_invert_index;

    }
    void handleSearch()
    {

        clock_t begin;
        clock_t end;
        begin = clock();

#if 0
        std::string scanning_dir_name = "./test_filedata";
        //std::string scanning_dir_name = "./filedata";

        std::string generate_dirfile = "./test_generate_page/scandir.dat";
        //std::string generate_dirfile = "./generate_page/scandir.dat";

        extractPage ep;
        ep.do_scanDir(scanning_dir_name, 0, generate_dirfile);

        std::string output_dir_file = "./test_generate_page/ripepage.lib";
        //std::string output_dir_file = "./generate_page/ripepage.lib";

        std::string outputoffset = "./test_generate_page/offset.lib";
        //std::string outputoffset = "./generate_page/offset.lib";
        ep.handle_scan_dir(scanning_dir_name, output_dir_file, outputoffset);
#endif

#if 0
        MyRemoveDup myremovedup; 
        myremovedup.removeDup();
        //myremovedup.display();
        MyInvertIndex myindex;
        //myindex.display();
        //void getInverIndex()
        myindex.handleInverIndex();
#endif

        //std::cout<<"HANDLING FOR TASKS..."<<std::endl;
        std::string task_str;
        std::cout<<"亲，百度一下看看神马情况：";
        std::cin>>task_str;

        MySplit mysplit;
        std::string task_res = mysplit.wordSplit(task_str);

        std::stringstream ss_result(task_res);
        std::string res_word;
        //std::cout<<"task_res(直接分词)："<<task_res<<std::endl;

        std::cout<<"@@对您刚输入的语句去停用词后的分词结果是：";
        while(ss_result >> res_word)
        {
            if(!mysplit.is_stopword(res_word))
            {
                std::cout<<res_word<<" ";
            }
        }
    std::cout<<std::endl;

    stringstream ss_task(task_res);
    std::string task_word;
    //std::string task_content;
    std::map<std::string, int> task_map_content;
    std::vector<std::string> task_vec_original_words;//未经排序的单词，保证单词的查询顺序
    while(ss_task >> task_word)
    {
        if(!mysplit.is_stopword(task_word)) 
        {
            //task_content += task_word;
            //task_content += " ";
            task_map_content[task_word]++;
            task_vec_original_words.push_back(task_word);
            //std::cout<<"分词："<<task_word<<std::endl;
        }
    }
    /*所有待查询单词的频数和权重*/
    std::map<std::string, std::pair<int, double> > task_invertindex;
    int words_cnt = task_map_content.size();
    for(auto it_task: task_map_content)
    {
        double task_idf = log((double)1 / (0.000001 + it_task.second));
        double task_weight = task_idf * it_task.second;
        task_invertindex[it_task.first] = std::make_pair(it_task.second, task_weight);
    }
    //MyWebSort myweb;
    //void readInvertIndex(std::string invertfilename)
    //std::string invertfile_name = "./test_generate_page/invertindex_test.lib";
    std::string invertfile_name = "./test_generate_page/invertindex.lib";
    //!!std::map<std::string, std::map<int, std::pair<int, double> > > readInvertIndex(std::string invertfilename)
    std::map<std::string, std::map<int, std::pair<int, double> > > words_map_inverindex 
    = readInvertIndex(invertfile_name);//获取文档库（已经去重）的所有单词统计结果
    //std::cout<<"after readInvertIndex@@words_map_inverindex.size="<<words_map_inverindex.size()<<std::endl;
    //!!std::map<std::string, std::pair<int, double> > task_invertindex;//存放待查询单词及对应的文章和权重
    std::map<std::string, std::set<int> > word_article;//存放待查询单词和对应的文章号
    /*根据任务里的多个单词，对统计结果进行查询*/
    /*22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222*/
    #if 0
    //std::cout<<"words_map_inverindex.size="<<words_map_inverindex.size()<<std::endl;
    //* 检测结果输出，不可删除！
    int cnt = 0;
    for(auto it_exa: words_map_inverindex)
    {
        cnt++;
        if(cnt > 100 && cnt < 110)
        {

            std::cout<<it_exa.first<<"----->"<<std::endl;
            for(auto it_in: it_exa.second)
            {
                std::cout<<"\t"<<it_in.first<<"\t"<<it_in.second.first<<"\t"<<it_in.second.second<<std::endl;
            }
        }
        //break;
    }
    #endif
    /*所有待查询单词的频数和权重*/
    //!!std::map<std::string, std::pair<int, double> > task_invertindex;
    for(auto it_task: task_invertindex)
    {
        //!!std::map<std::string, std::map<int, std::pair<int, double> > > words_map_inverindex 
        auto it_find = words_map_inverindex.find(it_task.first);
        //std::cout<<"it_task.first->"<<it_task.first<<std::endl;
        if(it_find == words_map_inverindex.end())
        {
            std::cout<<"Sorry! not find the task word!"<<std::endl;
            exit(-1);
        }
        /*对每一个单词和对应的多个文章序号进行处理*/
        std::set<int> tmp_set_docid;
        for(auto it_invertindex: it_find->second)
        {
            tmp_set_docid.insert(it_invertindex.first);
        }
        //!!std::map<std::string, std::set<int> > word_article;//存放待查询单词和对应的文章号
        word_article[it_task.first] = tmp_set_docid; 
        //word_article.insert(std::make_pair(it_task.first, tmp_set_docid));
    }
    /*不断循环求交集，知道所有的对比完为止，剩下最小的交集才是最后的结果*/
    /*如果有一次出现交集为0的情况则说明本次查询没有交集，作废*/
    std::vector<int> tmp_vec_intersection;//存放最后的交集结果，不可以房子for里面
    for(auto it_res=word_article.begin(); it_res!=word_article.end(); it_res++)
    {
        if(it_res == word_article.begin())
        {
            for(auto it_beg: it_res->second)
            {
                tmp_vec_intersection.push_back(it_beg);
            }
            continue;
        }
        std::vector<int> vec_mid;
        std::set_intersection(tmp_vec_intersection.begin(), tmp_vec_intersection.end(),
                              it_res->second.begin(), it_res->second.end(),
                              std::back_inserter(vec_mid));    

        tmp_vec_intersection.clear();
        tmp_vec_intersection = vec_mid;
        if(vec_mid.size() == 0)
        {
            std::cout<<"error: no search information! exit..."<<std::endl;
        }
    }
    //std::vector<int> tmp_vec_intersection;存放的为分词后的公共文章序号
    //!!std::map<std::string, std::map<int, std::pair<int, double> > > readInvertIndex(std::string invertfilename)
    //std::map<std::string, std::map<int, std::pair<int, double> > >& words_map_inverindex 
    //= myweb.readInvertIndex(invertfile_name);//获取文档库的所有单词统计结果

    /*
    * 根据readInvertIndex获取单词所在文章的权重
    */
    /*该查询请求的所有”网页库“文章的倒排索引，
    * 直接计算文章的cosine相似性，已排序，求交集*/
    std::map<int, std::set<std::pair<std::string, double> > > all_docs_query;
    //!!std::vector<int> tmp_vec_intersection;//存放最后的交集结果！
    for(auto it_docid: tmp_vec_intersection)
    {
        std::set<std::pair<std::string, double> > doc_res;//当前文章号的（所有待查询单词和对应的权重）的结果
        for(auto it11: word_article)//只要待查询的所有单词
        //!!std::map<std::string, std::set<int> > word_article;//存放待查询单词和对应的文章号
        {
            auto it_word = words_map_inverindex.find(it11.first);//查询对应的单词          
            if(it_word == words_map_inverindex.end())
            {
                perror("error: query words not found!");
                exit(-1);
            }
            auto it_article = it_word->second.find(it_docid);//依据查询到的单词查询文章序号
            //!!std::map<std::string, std::map<int, std::pair<int, double> > >& words_map_inverindex 
            if(it_article == it_word->second.end())
            {
                perror("error: the article of query words not found!");
                exit(-1);
            }
            //!!it11.first为单词，第二个参数为该单词对应的权重
            doc_res.insert(std::make_pair(it11.first, it_article->second.second));
        }
        /*存放文章序号、单词、权重*/
        all_docs_query[it_docid] = doc_res;
    }
    //!!std::map<std::string, std::pair<int, double> > task_invertindex;
    //!!存放待查询单词及对应的文章和权重
    //!!std::map<int, std::set<std::pair<std::string, double> > > all_docs_query;
    std::map<double, int> query_result;//所有的计算结果（cosin、docid）
    for(auto it_all: all_docs_query)
    {
        if(it_all.second.size() != task_invertindex.size())
        {
            std::cout<<"error! the count of datas not equal!!!!"<<std::endl;
            exit(-1);
        }
        double member = 0;
        double denominator_query = 0;
        double denominator_lib = 0;
        auto it_query=task_invertindex.begin();
        auto it_lib=it_all.second.begin();
        for(; it_query!=task_invertindex.end(), it_lib!=it_all.second.end();it_query++, it_lib++)
        {
            member += it_query->second.second * it_lib->second;
            denominator_query += pow(it_query->second.second, 2);
            denominator_lib += pow(it_lib->second, 2);
        }
        /*该查询请求和一篇文章的包含该所有词进行计算cosin*/
        denominator_query = sqrt(denominator_query);
        denominator_lib = sqrt(denominator_lib);
        double cosine = (double)member / ((denominator_query * denominator_lib));//防止分母为0
        query_result[cosine] = it_all.first;
    }


    std::cout<<"\n++++++++++++搜索引擎的结果++++++++++++"<<std::endl;
    std::cout<<"查询到的文章共有："<<query_result.size()<<"篇!"<<std::endl;
    for(auto it_last: query_result)
    {
        char* docid_str = "文章序号：";
        char* docconsin_str = "相似度：";
        printf("%-20s%5d\t%-20s%8d\n", docid_str, it_last.second, docconsin_str, it_last.first);
        //std::cout<<"文章序号："<<it_last.second<<"\t相似度："<<it_last.first<<"，"<<std::endl;
    }
    std::cout<<"++++++++++++++++++++++++++++++++++++++"<<std::endl;
    //!!std::set<std::pair<std::string, std::set<std::string> > > getSummary(int docidSummary, int maxSummarySize)
    //!!std::string getSummary(int docidSummary, int maxSummarySize, std::vector<std::string> vec_words)
    //!!std::map<double, int> query_result;//所有的计算结果（cosin、docid）
    //std::set<std::pair<std::string, std::set<std::string> > > set_doc_summary mysplit.getSummary(); 
    //!!22std::string getSummary(int docidSummary, int maxSummarySize, std::vector<std::string> vec_words)
    //!!std::vector<std::string> task_vec_original_words;//未经排序的单词，保证单词的查询顺序
    //for(auto it_last: query_result)
    //std::cout<<"query_result.size="<<query_result.size()<<std::endl;
    int doc_cnt = 0;
    int arr_docid[query_result.size()];
    int arr_index = query_result.size() - 1;
    int index_end = arr_index;
    /*将结果存放到数组里面，确保按降序排列*/
    for(auto it: query_result)
    {
        arr_docid[arr_index--] = it.second; 
        if(arr_index < -1)
        {
            std::cout<<"error: arr_index too small!"<<std::endl;
        }
    }
    //for(auto it_last=query_end; it_last!=query_start;  it_last--)
    //std::cout<<"index_end="<<index_end<<std::endl;
    /*循环将文章显示出来，不超过8篇*/
    for(int index=0; index<=index_end; index++)
    {
        doc_cnt++;
        if(doc_cnt > 8)
        {
            break;
        }
        //文章的优先顺序为倒序
        /*每篇显示4行摘录（包含关键词的语句），最后的参数为共同的关键词*/
        std::string str_result = mysplit.backup_getSummary(arr_docid[index], 4, task_vec_original_words);
        //std::string str_result = mysplit.getSummary_mending(arr_docid[index], 4, task_vec_original_words);
        //str_result里面已存在换行符，输出结果
        std::cout<<str_result;
        std::cout<<"^^^^^^^^^^^\n"<<std::endl;
        //!!std::map<std::string, std::set<int> > word_article;//存放待查询的所有单词和对应的文章号
        //std::cout<<"相似度："<<it_last.first<<"，"<<"文章号："<<it_last.second<<std::endl;
    }
    end = clock();
    double T = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout<<" ------------------------"<<std::endl;
    std::cout<<" 程序运行时间: "<<T<<"s"<<std::endl;
    std::cout<<" ------------------------"<<std::endl;
    }


};

#endif

/*
int main(void)
{
MyWebSort myweb;
//void readInvertIndex(std::string invertfilename)
std::string invertfile_name = "./test_generate_page/invertindex_test.lib";
myweb.readInvertIndex(invertfile_name);

    return 0;
}
*/

#if 0
int main(void)
{     
    MyWebSort myweb;
    myweb.handleSearch();

#if 0
    std::string scanning_dir_name = "./test_filedata";
    //std::string scanning_dir_name = "./filedata";

    std::string generate_dirfile = "./test_generate_page/scandir.dat";
    //std::string generate_dirfile = "./generate_page/scandir.dat";

    extractPage ep;
    ep.do_scanDir(scanning_dir_name, 0, generate_dirfile);

    std::string output_dir_file = "./test_generate_page/ripepage.lib";
    //std::string output_dir_file = "./generate_page/ripepage.lib";

    std::string outputoffset = "./test_generate_page/offset.lib";
    //std::string outputoffset = "./generate_page/offset.lib";
    ep.handle_scan_dir(scanning_dir_name, output_dir_file, outputoffset);
#endif

#if 0
    MyRemoveDup myremovedup; 
    myremovedup.removeDup();
    //myremovedup.display();
    MyInvertIndex myindex;
    //myindex.display();
    //void getInverIndex()
    myindex.handleInverIndex();
#endif

    return 0;
}



#endif










void test()
{

#if 0
    clock_t begin;
    clock_t end;
    begin = clock();

    #if 0
    std::string scanning_dir_name = "./test_filedata";
    //std::string scanning_dir_name = "./filedata";

    std::string generate_dirfile = "./test_generate_page/scandir.dat";
    //std::string generate_dirfile = "./generate_page/scandir.dat";

    extractPage ep;
    ep.do_scanDir(scanning_dir_name, 0, generate_dirfile);

    std::string output_dir_file = "./test_generate_page/ripepage.lib";
    //std::string output_dir_file = "./generate_page/ripepage.lib";

    std::string outputoffset = "./test_generate_page/offset.lib";
    //std::string outputoffset = "./generate_page/offset.lib";
    ep.handle_scan_dir(scanning_dir_name, output_dir_file, outputoffset);
    #endif

    #if 1
    MyRemoveDup myremovedup; 
    myremovedup.removeDup();
    //myremovedup.display();
    MyInvertIndex myindex;
    //myindex.display();
    //void getInverIndex()
    myindex.handleInverIndex();
    #endif

    //std::cout<<"HANDLING FOR TASKS..."<<std::endl;
    std::string task_str;
    std::cout<<"亲，百度一下看看神马情况：";
    std::cin>>task_str;

    MySplit mysplit;
    std::string task_res = mysplit.wordSplit(task_str);

    std::stringstream ss_result(task_res);
    std::string res_word;
    //std::cout<<"task_res(直接分词)："<<task_res<<std::endl;

    std::cout<<"@@对您刚输入的语句去停用词后的分词结果是：";
    while(ss_result >> res_word)
    {
        if(!mysplit.is_stopword(res_word))
        {
            std::cout<<res_word<<" ";
        }
    }
std::cout<<std::endl;

    stringstream ss_task(task_res);
    std::string task_word;
    //std::string task_content;
    std::map<std::string, int> task_map_content;
    std::vector<std::string> task_vec_original_words;//未经排序的单词，保证单词的查询顺序
    while(ss_task >> task_word)
    {
        if(!mysplit.is_stopword(task_word)) 
        {
            //task_content += task_word;
            //task_content += " ";
            task_map_content[task_word]++;
            task_vec_original_words.push_back(task_word);
            //std::cout<<"分词："<<task_word<<std::endl;
        }
    }
    /*所有待查询单词的频数和权重*/
    std::map<std::string, std::pair<int, double> > task_invertindex;
    int words_cnt = task_map_content.size();
    for(auto it_task: task_map_content)
    {
        double task_idf = log((double)1 / (0.000001 + it_task.second));
        double task_weight = task_idf * it_task.second;
        task_invertindex[it_task.first] = std::make_pair(it_task.second, task_weight);
    }
    MyWebSort myweb;
    //void readInvertIndex(std::string invertfilename)
    //std::string invertfile_name = "./test_generate_page/invertindex_test.lib";
    std::string invertfile_name = "./test_generate_page/invertindex.lib";
    //!!std::map<std::string, std::map<int, std::pair<int, double> > > readInvertIndex(std::string invertfilename)
    std::map<std::string, std::map<int, std::pair<int, double> > > words_map_inverindex 
    = myweb.readInvertIndex(invertfile_name);//获取文档库（已经去重）的所有单词统计结果
    //std::cout<<"after readInvertIndex@@words_map_inverindex.size="<<words_map_inverindex.size()<<std::endl;
    //!!std::map<std::string, std::pair<int, double> > task_invertindex;//存放待查询单词及对应的文章和权重
    std::map<std::string, std::set<int> > word_article;//存放待查询单词和对应的文章号
    /*根据任务里的多个单词，对统计结果进行查询*/
    /*22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222*/
    #if 0
    //std::cout<<"words_map_inverindex.size="<<words_map_inverindex.size()<<std::endl;
    //* 检测结果输出，不可删除！
    int cnt = 0;
    for(auto it_exa: words_map_inverindex)
    {
        cnt++;
        if(cnt > 100 && cnt < 110)
        {

            std::cout<<it_exa.first<<"----->"<<std::endl;
            for(auto it_in: it_exa.second)
            {
                std::cout<<"\t"<<it_in.first<<"\t"<<it_in.second.first<<"\t"<<it_in.second.second<<std::endl;
            }
        }
        //break;
    }
    #endif
    /*所有待查询单词的频数和权重*/
    //!!std::map<std::string, std::pair<int, double> > task_invertindex;
    for(auto it_task: task_invertindex)
    {
        //!!std::map<std::string, std::map<int, std::pair<int, double> > > words_map_inverindex 
        auto it_find = words_map_inverindex.find(it_task.first);
        //std::cout<<"it_task.first->"<<it_task.first<<std::endl;
        if(it_find == words_map_inverindex.end())
        {
            std::cout<<"Sorry! not find the task word!"<<std::endl;
            exit(-1);
        }
        /*对每一个单词和对应的多个文章序号进行处理*/
        std::set<int> tmp_set_docid;
        for(auto it_invertindex: it_find->second)
        {
            tmp_set_docid.insert(it_invertindex.first);
        }
        //!!std::map<std::string, std::set<int> > word_article;//存放待查询单词和对应的文章号
        word_article[it_task.first] = tmp_set_docid; 
        //word_article.insert(std::make_pair(it_task.first, tmp_set_docid));
    }
    /*不断循环求交集，知道所有的对比完为止，剩下最小的交集才是最后的结果*/
    /*如果有一次出现交集为0的情况则说明本次查询没有交集，作废*/
    std::vector<int> tmp_vec_intersection;//存放最后的交集结果，不可以房子for里面
    for(auto it_res=word_article.begin(); it_res!=word_article.end(); it_res++)
    {
        if(it_res == word_article.begin())
        {
            for(auto it_beg: it_res->second)
            {
                tmp_vec_intersection.push_back(it_beg);
            }
            continue;
        }
        std::vector<int> vec_mid;
        std::set_intersection(tmp_vec_intersection.begin(), tmp_vec_intersection.end(),
                              it_res->second.begin(), it_res->second.end(),
                              std::back_inserter(vec_mid));    

        tmp_vec_intersection.clear();
        tmp_vec_intersection = vec_mid;
        if(vec_mid.size() == 0)
        {
            std::cout<<"error: no search information! exit..."<<std::endl;
        }
    }
    //std::vector<int> tmp_vec_intersection;存放的为分词后的公共文章序号
    //!!std::map<std::string, std::map<int, std::pair<int, double> > > readInvertIndex(std::string invertfilename)
    //std::map<std::string, std::map<int, std::pair<int, double> > >& words_map_inverindex 
    //= myweb.readInvertIndex(invertfile_name);//获取文档库的所有单词统计结果

    /*
    * 根据readInvertIndex获取单词所在文章的权重
    */
    /*该查询请求的所有”网页库“文章的倒排索引，
    * 直接计算文章的cosine相似性，已排序，求交集*/
    std::map<int, std::set<std::pair<std::string, double> > > all_docs_query;
    //!!std::vector<int> tmp_vec_intersection;//存放最后的交集结果！
    for(auto it_docid: tmp_vec_intersection)
    {
        std::set<std::pair<std::string, double> > doc_res;//当前文章号的（所有待查询单词和对应的权重）的结果
        for(auto it11: word_article)//只要待查询的所有单词
        //!!std::map<std::string, std::set<int> > word_article;//存放待查询单词和对应的文章号
        {
            auto it_word = words_map_inverindex.find(it11.first);//查询对应的单词          
            if(it_word == words_map_inverindex.end())
            {
                perror("error: query words not found!");
                exit(-1);
            }
            auto it_article = it_word->second.find(it_docid);//依据查询到的单词查询文章序号
            //!!std::map<std::string, std::map<int, std::pair<int, double> > >& words_map_inverindex 
            if(it_article == it_word->second.end())
            {
                perror("error: the article of query words not found!");
                exit(-1);
            }
            //!!it11.first为单词，第二个参数为该单词对应的权重
            doc_res.insert(std::make_pair(it11.first, it_article->second.second));
        }
        /*存放文章序号、单词、权重*/
        all_docs_query[it_docid] = doc_res;
    }
    //!!std::map<std::string, std::pair<int, double> > task_invertindex;
    //!!存放待查询单词及对应的文章和权重
    //!!std::map<int, std::set<std::pair<std::string, double> > > all_docs_query;
    std::map<double, int> query_result;//所有的计算结果（cosin、docid）
    for(auto it_all: all_docs_query)
    {
        if(it_all.second.size() != task_invertindex.size())
        {
            std::cout<<"error! the count of datas not equal!!!!"<<std::endl;
            exit(-1);
        }
        double member = 0;
        double denominator_query = 0;
        double denominator_lib = 0;
        auto it_query=task_invertindex.begin();
        auto it_lib=it_all.second.begin();
        for(; it_query!=task_invertindex.end(), it_lib!=it_all.second.end();it_query++, it_lib++)
        {
            member += it_query->second.second * it_lib->second;
            denominator_query += pow(it_query->second.second, 2);
            denominator_lib += pow(it_lib->second, 2);
        }
        /*该查询请求和一篇文章的包含该所有词进行计算cosin*/
        denominator_query = sqrt(denominator_query);
        denominator_lib = sqrt(denominator_lib);
        double cosine = (double)member / ((denominator_query * denominator_lib));//防止分母为0
        query_result[cosine] = it_all.first;
    }


    std::cout<<"\n++++++++++++搜索引擎的结果++++++++++++"<<std::endl;
    std::cout<<"查询到的文章共有："<<query_result.size()<<"篇!"<<std::endl;
    for(auto it_last: query_result)
    {
        char* docid_str = "文章序号：";
        char* docconsin_str = "相似度：";
        printf("%-20s%5d\t%-20s%8d\n", docid_str, it_last.second, docconsin_str, it_last.first);
        //std::cout<<"文章序号："<<it_last.second<<"\t相似度："<<it_last.first<<"，"<<std::endl;
    }
    std::cout<<"++++++++++++++++++++++++++++++++++++++"<<std::endl;
    //!!std::set<std::pair<std::string, std::set<std::string> > > getSummary(int docidSummary, int maxSummarySize)
    //!!std::string getSummary(int docidSummary, int maxSummarySize, std::vector<std::string> vec_words)
    //!!std::map<double, int> query_result;//所有的计算结果（cosin、docid）
    //std::set<std::pair<std::string, std::set<std::string> > > set_doc_summary mysplit.getSummary(); 
    //!!22std::string getSummary(int docidSummary, int maxSummarySize, std::vector<std::string> vec_words)
    //!!std::vector<std::string> task_vec_original_words;//未经排序的单词，保证单词的查询顺序
    //for(auto it_last: query_result)
    //std::cout<<"query_result.size="<<query_result.size()<<std::endl;
    int doc_cnt = 0;
    int arr_docid[query_result.size()];
    int arr_index = query_result.size() - 1;
    int index_end = arr_index;
    /*将结果存放到数组里面，确保按降序排列*/
    for(auto it: query_result)
    {
        arr_docid[arr_index--] = it.second; 
        if(arr_index < -1)
        {
            std::cout<<"error: arr_index too small!"<<std::endl;
        }
    }
    //for(auto it_last=query_end; it_last!=query_start;  it_last--)
    //std::cout<<"index_end="<<index_end<<std::endl;
    /*循环将文章显示出来，不超过8篇*/
    for(int index=0; index<=index_end; index++)
    {
        doc_cnt++;
        if(doc_cnt > 8)
        {
            break;
        }
        //文章的优先顺序为倒序
        /*每篇显示4行摘录（包含关键词的语句），最后的参数为共同的关键词*/
        std::string str_result = mysplit.backup_getSummary(arr_docid[index], 4, task_vec_original_words);
        //std::string str_result = mysplit.getSummary_mending(arr_docid[index], 4, task_vec_original_words);
        //str_result里面已存在换行符，输出结果
        std::cout<<str_result;
        std::cout<<"^^^^^^^^^^^\n"<<std::endl;
        //!!std::map<std::string, std::set<int> > word_article;//存放待查询的所有单词和对应的文章号
        //std::cout<<"相似度："<<it_last.first<<"，"<<"文章号："<<it_last.second<<std::endl;
    }
    end = clock();
    double T = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout<<" ------------------------"<<std::endl;
    std::cout<<" 程序运行时间: "<<T<<"s"<<std::endl;
    std::cout<<" ------------------------"<<std::endl;
#endif
}
