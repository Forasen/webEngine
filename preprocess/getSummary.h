/*************************************************************************
> File Name: getSummary.h
> Author: 
> Mail: 
> Created Time: Sat 01 Aug 2015 05:12:03 PM CST
************************************************************************/

#ifndef _GETSUMMARY_H
#define _GETSUMMARY_H


std::string backup_getSummary(int docidSummary, int maxSummarySize, std::vector<std::string> vec_words)
/*vec_words为待查询的摘要的关键单词，必须确保单词在搜索序列中出现的顺序*/
/*maxSummarySize为返回的查询文章的行数*/
{
    /*打开offset.lib文件*/
    std::ifstream input_original_offset("./test_generate_page/offset.lib");
    if(!input_original_offset)
    {
        perror("input_original_offset");
        exit(-1);
    }
    std::map<int, std::pair<int, int> > map_original_offset;
    int num_int;
    int offset_int;
    int size_int;
    while(input_original_offset >> num_int >> offset_int>> size_int)
    {
        map_original_offset[num_int] = std::make_pair(offset_int, size_int);
    }
    /*打开new_offset.lib文件*/
    std::ifstream input_new_offset("./test_generate_page/new_offset.lib");
    if(!input_new_offset)
    {
        perror("input_new_offset");
        exit(-1);
    }
    std::map<int, std::pair<int, int> > map_new_offset;
    while(input_original_offset >> num_int >> offset_int>> size_int)
    {
        map_new_offset[num_int] = std::make_pair(offset_int, size_int);
    }

    std::string line_offset;

    /*提取new_offset.lib文件中的数据*/
    //!!std::map<int, std::pair<int, int> > tmp_map_offset;//用于存放new_offset.lib的结果

    //std::cout<<"111111111111111111111111111111111111111111"<<std::endl;
    //std::cout<<"num_int="<<num_int<<", offset_int="<<offset_int<<", size_int="<<size_int<<std::endl;
    doc_cnt++;
    auto it_new_original = map_original_offset.find(docidSummary);
    if(it_new_original == map_original_offset.end())
    {
        std::cout<<"Sorry! the new_offset docid not exist int original offset.lib"<<std::endl;
        std::cout<<"error: not found the docidSummary!"<<std::endl;
        exit(-1);
    }
    std::string curr_content;
    std::string real_curr_content;
    std::string line_content;
    int line_cnt = 0;//!!行计数器

    input_ripepage.seekg(it_new_original->second.first, std::fstream::beg);
    int curr_end_mark = it_new_original->second.first + it_new_original->second.second;
while(getline(input_ripepage, line_content) && ((input_ripepage.tellg()+19)<=curr_end_mark))
{
    line_cnt++;
    std::string real_line_content;
    for(auto it: line_content)
    {
        if(!isspace(it))
        {
            real_line_content += it;
        }
    }
    if(line_cnt >= 6)
    {
        real_curr_content += real_line_content;
    }
    #if 0
    if(line_cnt == 6)
    {
        std::cout<<"第6行为："<<line_content<<"\n"<<"文章序号为："<<(doc_cnt-1)<<std::endl;
    }
    #endif
}

        /*
        std::vector<std::string> tmp_vec_content;
        tmp_vec_content.push_back(real_curr_content);
        */
        //std::cout<<"before pre_m_map_stoplist.size++++++real_curr_content:"<<real_curr_content<<"*****"<<std::endl;
        //std::cout<<"tmp_vec_content.size="<<tmp_vec_content.size()<<std::endl;



//!!pre_m_map_stoplist[it_new_original->first] = tmp_vec_content;

                //std::cout<<"pre_m_map_stoplist.size="<<pre_m_map_stoplist.size()<<std::endl;
                /*************************************************************分割线*/

    /*对整篇文章进行分词，便于识别句子*/
    std::string docstr_split = wordSplit(docstr);
    //!!bool is_stopsentence(std::string aword)
    bool start_flag = false;
    bool end_flag = false;
    std::stringstream ss_doc_str(docstr_split);
    std::string doc_str_word;
    std::string line_sentence;//存储临时句子
    std::set<std::string> tmp_words;//存储临时单词
    std::vector<std::pair<std::string, std::set<std::string> > > tmp_return;
    bool first_word = false;
    while(ss_doc_str >> doc_str_word)
    {
        first_word = true;
        std::string tmp_unuseful;
        /*放在最前面一方第一个字符为句子的结束标记*/
        if(first_word)
        {
            first_word = false;
            if(is_stopsentence(doc_str_word))
            {
                start_flag = true;
                ss_doc_str >> tmp_unuseful;
            }
        }
        if(is_stopsentence(doc_str_word))
        {
            start_flag = true;
            ss_doc_str >> tmp_unuseful;
            //continue;
        }
        tmp_words.insert(doc_str_word);
        line_sentence += doc_str_word;
        if(start_flag = true)
        {
            /*一个句子结束，加入到tmp_return*/
            if(is_stopsentence(doc_str_word))
            {
                ss_doc_str >> tmp_unuseful;
                end_flag = true;
                tmp_return.push_back(std::make_pair(line_sentence, tmp_words));
                /*删除 line_sentence中存储的整个句子，为下次处理做准备*/
                line_sentence.erase(0);
                start_flag = false;
                end_flag = false;
            }
        }
    }
    //!!std::vector<std::string> vec_words//待输出摘录的关键字
    //!!std::set<std::pair<std::string, std::set<std::string> > > tmp_return;
    //!!bool sentenceSearchWord(std::set<std::string> sentence, std::string word)
    //!!不能采用默认的排序模版std::set<std::pair<std::string, std::set<std::string> > > tmp_return;
    //!!std:vector<std::pair<std::string, std::set<std::string> > > tmp_return;
    //std::string summary = "文章摘要：";
    char* summary = "文章摘要：";
    char tmp_summary[128];
    sprintf(tmp_summary, "...............\n第 %d 篇\n%s\n...............\n", docidSummary, summary);
    summary = tmp_summary;
    std::string summarySentences;
    //!!函数名：getSummary(int docidSummary, int maxSummarySize, std::vector<std::string> vec_words)
    int summary_cnt = 0;
    for(auto it_search:vec_words)
    {
        for(auto it_sentence: tmp_return)
        {
            if(sentenceSearchWord(it_sentence.second, it_search))
            {
                summary_cnt++;
                summarySentences += it_sentence.first;
                summarySentences += "\n";

                if(summary_cnt >= maxSummarySize)
                {
                    break;
                }
            }

        }
    }
    /*输出有换行符*/
    if(summarySentences[summarySentences.size()-1] != '\n')
    {
        summarySentences += "\n";
    }
    summarySentences = summary + summarySentences;
    //return tmp_return;
    return summarySentences;
}


