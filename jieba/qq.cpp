#include<iomanip>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<utility>
#include<string>
#include<unistd.h>
#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/dir.h>
#include<dirent.h>
#include<fcntl.h>
#include<locale.h>
#include<set>
#include<map>
#include<vector>
#include"../../include/seg.h"//这个是你自己的seg.ｈ文件路径
#define WORD_NUM 100
struct CMypair
{
    std::string m_word;
    int m_cnt;
    CMypair(std::string word,int cnt):m_word(word),m_cnt(cnt){}
    bool operator<(const CMypair& right)const 
    {
        return m_cnt>right.m_cnt;
    }
};
void trim_space(std::string& line) //去除空格换行符等符号
    int start=0;
    std::string exclude="\a\n\t\r\v\b\f";
    while((start=(line.find_first_of(exclude,start)))!=std::string::npos)
    {
        line.erase(start, 1);
        start++;
    }
}
int correct(const std::string& line)
{
    if(line.find_first_of("(",0)!=std::string::npos&&line.find_first_of(")",0)!=std::string::npos)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void stop_to_set(std::set<std::string>& stoplist,const std::string& stop_path)//将停用词放入一个set集合中
{
    std::string line;
    std::ifstream stop(stop_path.c_str());
    while(getline(stop,line))
    {
        std::string temp;
        std::istringstream ss(line);
        ss>>temp;
        stoplist.insert(temp);
    }
    stop.close();
}
void trim(const std::string& src_path,const std::string& des_path)//将初始文档的空格行去掉
{
    std::ifstream fin(src_path.c_str());
    std::ofstream fout(des_path.c_str());
    std::string line;
    while(getline(fin,line))
    {
        trim_space(line);
        if(line.empty())
        {
            continue;
        }
        fout<<line<<std::endl;
    }
    fin.close();
    fout.close();
}
//将一个的所有的记录存放的容器vector遍历，将每条记录进行分词统计，放入一个map中，同时输出到磁盘文件中
void get_freq(MixSegment& seg,std::set<std::string>& stoplist,std::vector<std::string>& record,std::map<std::string,int>& f_word_freq,std::ofstream& f_name_talk)
{
    std::vector<std::string>::iterator iter=record.begin();
    std::map<std::string,int> word_freq;
    std::priority_queue<CMypair> top10;
    std::string exclude="\a\n\t\r\v\b\f ";
    for(iter;iter!=record.end();iter++)
    {
        std::vector<std::string> temp;
        seg.cut(*iter,temp);
        std::vector<std::string>::iterator w_iter=temp.begin();
        for(w_iter;w_iter!=temp.end();w_iter++)
        {
            if(stoplist.count(*w_iter)>0||(*w_iter).find_first_of(exclude,0)!=std::string::npos)
            {
                continue;
            }
            word_freq[*w_iter]++;
        }
    }
    std::map<std::string,int>::iterator iter1=word_freq.begin();
    for(iter1;iter1!=word_freq.end();iter1++)//利用优先级队列将每个人出现的前30个高频词汇导出来
    {
        CMypair* apair=new CMypair(iter1->first,iter1->second);
        if(top10.size()<WORD_NUM)
        {
            top10.push(*apair);
        }
        else
        {
            if(top10.top()<*apair)
            {
                continue;
            }
            else
            {
                top10.pop();
                top10.push(*apair);
            }
        }
    }
    std::vector<CMypair> word_freq_vec;
    while(top10.size())
    {
        std::pair<std::string,int> apair=make_pair(top10.top().m_word,top10.top().m_cnt);
        CMypair* apair1=new CMypair(top10.top().m_word,top10.top().m_cnt);
        word_freq_vec.push_back(*apair1);
        f_word_freq.insert(apair);
        top10.pop();
    }
    std::vector<CMypair>::reverse_iterator r_iter=word_freq_vec.rbegin();
    for(r_iter;r_iter!=word_freq_vec.rend();r_iter++)
    {
        f_name_talk<<std::left<<setw(10)<<r_iter->m_word<<std::right<<setw(5)<<r_iter->m_cnt<<std::endl;
    }
}
void pic_smile_rank(std::map<std::string,int>& pic_map,const std::string& file_path)//表情统计
{
    std::priority_queue<CMypair> top10;
    std::map<std::string,int>::iterator iter1=pic_map.begin();
    for(iter1;iter1!=pic_map.end();iter1++)
    {
        CMypair* apair=new CMypair(iter1->first,iter1->second);
        if(top10.size()<WORD_NUM)
        {
            top10.push(*apair);
        }
        else
        {
            if(top10.top()<*apair)
            {
                continue;
            }
            else
            {
                top10.pop();
                top10.push(*apair);
            }
        }
    }
    std::vector<CMypair> word_freq_vec;
    while(top10.size())
    {
        CMypair* apair1=new CMypair(top10.top().m_word,top10.top().m_cnt);
        word_freq_vec.push_back(*apair1);
        top10.pop();
    }
    std::vector<CMypair>::reverse_iterator r_iter=word_freq_vec.rbegin();
    std::ofstream fout(file_path.c_str());
    for(r_iter;r_iter!=word_freq_vec.rend();r_iter++)
    {
        //fout<<std::left<<setw(50)<<r_iter->m_word<<std::right<<setw(15)<<r_iter->m_cnt<<std::endl;
        fout<<r_iter->m_word<<": "<<r_iter->m_cnt<<std::endl;
    }
}
void record_rank(std::map<std::string,int>& record,std::ofstream& f_record)//聊天记录条数排行
{
    std::priority_queue<CMypair> top10;
    std::map<std::string,int>::iterator iter1=record.begin();
    for(iter1;iter1!=record.end();iter1++)
    {
        CMypair* apair=new CMypair(iter1->first,iter1->second);
        if(top10.size()<WORD_NUM)
        {
            top10.push(*apair);
        }
        else
        {
            if(top10.top()<*apair)
            {
                continue;
            }
            else
            {
                top10.pop();
                top10.push(*apair);
            }
        }
    }
    std::vector<CMypair> word_freq_vec;
    while(top10.size())
    {
        CMypair* apair1=new CMypair(top10.top().m_word,top10.top().m_cnt);
        word_freq_vec.push_back(*apair1);
        top10.pop();
    }
    std::vector<CMypair>::reverse_iterator r_iter=word_freq_vec.rbegin();
    for(r_iter;r_iter!=word_freq_vec.rend();r_iter++)
    {
        //fout<<std::left<<setw(50)<<r_iter->m_word<<std::right<<setw(15)<<r_iter->m_cnt<<std::endl;
        f_record<<r_iter->m_word<<"聊天纪录共"<<r_iter->m_cnt<<"条"<<std::endl;
    }
}
int get_qq(const std::string& name,std::string& qq)//获取每个人的qq号
{
    int bg=name.find("(",0);
    int ed=name.find(")",0);
    if(bg!=std::string::npos&&ed!=std::string::npos)
    {
        qq=name.substr(bg+1,ed-bg-1);
        return 1;
    }
    else
    {
        return 0;
    }
}
int name_cmp(const std::string& name1,const std::string& name2)//名字比较，用来合并修改昵称的人qq聊天记录
{
    std::string qq1;
    std::string qq2;
    if(get_qq(name1,qq1)&&get_qq(name2,qq2))
    {
        if(qq1==qq2)
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

void make_record(const std::string& src_path,const std::string& path,std::map<std::string,std::string>& name_set)
{
    std::ifstream fin(src_path.c_str());
    std::string dir_path=path;
    std::string line;
    std::map<std::string,std::vector<std::string> > shutup;
    std::vector<std::string> record;
    MixSegment seg(JIEBA_DICT_FILE,HMM_DICT_FILE,USER_DICT_FILE);
    std::set<std::string> stoplist;
    std::priority_queue<CMypair> top10;
    stop_to_set(stoplist,"../../data/stop.txt");
    while(getline(fin,line))
    {
        record.push_back(line);
    }
    std::map<std::string,std::string> map_record;
    for(size_t index=0;index!=record.size();)//将所有记录放入map<std::string,std::string>结构中
    {
        if(index+1>record.size()||index>record.size())
        {
            break;
        }
        std::pair<std::string,std::string> apair=make_pair(record[index],record[index+1]);
        map_record.insert(apair);
        index=index+2;
    }
    std::map<std::string,std::string>::iterator iter=map_record.begin();
    std::map<std::string,std::set<std::vector<std::string> > >  name_record;
    for(iter;iter!=map_record.end();iter++)//提取每个人的qq聊天时间日期和qq
    {
        std::istringstream ss(iter->first);
        std::string date;
        std::string time;
        std::string name;
        ss>>date>>time>>name;
        std::vector<std::string> temp;
        temp.push_back(date);
        temp.push_back(time);
        temp.push_back(iter->second);//iter->first 是date time name,iter->second是聊天记录
        name_record[name].insert(temp);//每个人的qq就是map的key，value就是date，time，iter->second组成的三元素vector的string数组
    }
    std::map<std::string,std::set<std::vector<std::string> > >::iterator n_iter=name_record.begin();
    std::map<std::string,std::set<std::vector<std::string> > > correct_record;
    std::map<int,std::string> record_index;
    int name_id=0;
    for(n_iter;n_iter!=name_record.end();n_iter++)//去重用的，暂时可以不看
    {
        std::string name=n_iter->first;
        if(correct(name))
        {
            correct_record[name]=n_iter->second;
            record_index[name_id++]=name;
        }
    }
    std::stringstream s_dup;
    s_dup<<dir_path<<"/redunt.doc";
    std::ofstream f_dup(s_dup.str().c_str());
    for(int index_i=correct_record.size()-1;index_i>=0;index_i--)//冒泡排序合并记录。可以暂时不看
    {
        for(int index_j=index_i-1;index_j>=0;index_j--)
        {
            std::string name_i=record_index[index_i];
            std::string name_j=record_index[index_j];
            if(name_cmp(name_i,name_j))
            {
                //std::cout<<name_i<<"-->"<<name_j<<std::endl;
                f_dup<<name_i<<"-->"<<name_j<<std::endl;
                correct_record[name_i].insert(correct_record[name_j].begin(),correct_record[name_j].end());
                correct_record[name_j].clear();
            }
        }//correct_record就是去重合并后的记录
    f_dup.close();
    int num=0;
    std::map<std::string,int> pic_map;
    std::map<std::string,int> smile_map;
    std::map<std::string,int> record_total;
    std::stringstream talk;
    talk<<dir_path<<"/outline/total_talk.doc";
    std::ofstream f_record(talk.str().c_str());
    for(n_iter=correct_record.begin();n_iter!=correct_record.end();n_iter++)//遍历每个人的聊天记录，每次遍历输出一个人聊天记录
    {
        std::string name=n_iter->first;
        if(!(n_iter->second).empty())
        {
            std::string name_qq;
            get_qq(name,name_qq);//提取每个人的qq号
            name_set[name_qq]=name;//将qq号作为key，
            std::stringstream name_talk;
            name_talk<<dir_path<<"/"<<name<<".doc";//输出每个人的聊天记录
            std::ofstream f_name_talk(name_talk.str().c_str());//输出每个记录的文件流对象
            std::vector<std::string> talk_record;
            std::map<std::string,int> f_word_freq;
            f_name_talk<<n_iter->first<<"的聊天纪录 : "<<"总共"<<(n_iter->second).size()<<"条纪录"<<std::endl;
            record_total[n_iter->first]=n_iter->second.size();
            f_name_talk<<"-----------------------聊天纪录----------------------"<<std::endl;
            std::set<std::vector<std::string> >::iterator t_iter=(n_iter->second).begin();
            for(t_iter;t_iter!=(n_iter->second).end();t_iter++)
            {
                f_name_talk<<(*t_iter)[0]<<" "<<(*t_iter)[1]<<" :"<<(*t_iter)[2]<<std::endl;//输出每条记录，
                talk_record.push_back((*t_iter)[2]);
            }
            f_name_talk<<"-----------------------高频词汇-----------------------"<<std::endl;
            f_name_talk<<std::left<<setw(10)<<"词汇"<<std::right<<setw(8)<<"次数"<<std::endl;
            get_freq(seg,stoplist,talk_record,f_word_freq,f_name_talk);
            if(f_word_freq.count("图片")>0)//在每个人的记录中找图片
            {
                pic_map[name]=f_word_freq["图片"];
            }
            if(f_word_freq.count("表情")>0)//在每个人的记录中找表情
            {
                smile_map[name]=f_word_freq["表情"];
            }
            num++;
        }
    }
    record_rank(record_total,f_record);
    f_record.close();
    std::stringstream ss;
    ss<<dir_path<<"/outline/pic_total.doc";//输出图片总的统计
    std::string pic_path=ss.str();
    ss.clear();
    pic_smile_rank(pic_map,pic_path);
    std::stringstream ss1;
    ss1<<dir_path<<"/outline/smile_total.doc";//输出表情总的统计
    std::string smile_path=ss1.str();
    pic_smile_rank(smile_map,smile_path);
    std::cout<<"总共"<<num<<"qq群成员纪录"<<std::endl;
    fin.close();
}
int gbk2utf8(char *utfstr,const char *srcstr,int maxutfstrlen)//gbk 转utf-8
{
    if(NULL==srcstr)
    {
        printf("bad parameter\n");
        return -1;
    }

    if(NULL==setlocale(LC_ALL,"zh_CN.gbk"))
    {
        printf("bad parameter\n");
        return -1;
    }
    int unicodelen=mbstowcs(NULL,srcstr,0);
    if(unicodelen<=0)
    {
        printf("can not transfer!!!\n");
        return -1;
    }
    wchar_t *unicodestr=(wchar_t *)calloc(sizeof(wchar_t),unicodelen+1);
    mbstowcs(unicodestr,srcstr,strlen(srcstr));
    if(NULL==setlocale(LC_ALL,"zh_CN.utf8"))
    {
        printf("bad parameter\n");
        return -1;
    }
    int utflen=wcstombs(NULL,unicodestr,0);
    if(utflen<=0)
    {
        printf("can not transfer!!!\n");
        return -1;
    }
    else if(utflen>=maxutfstrlen)
    {
        printf("dst str memory not enough\n");
        return -1;
    }
    wcstombs(utfstr,unicodestr,utflen);
    utfstr[utflen]=0;
    free(unicodestr);
    return utflen;
}

int main(int argc,char** argv)
{
    //trim(argv[1],argv[2]);
    std::map<std::string,std::string> name_set;
    make_record(argv[1],argv[2],name_set);//argv[1]是源文件argv[2]是输出目录，这个目录要提前建好，该目录下还要建一个子目录outline
    std::map<std::string,std::string>::iterator iter=name_set.begin();
    for(iter;iter!=name_set.end();iter++)
    {
        std::cout<<"QQ号: "<<iter->first<<"   QQ名称: "<<iter->second<<std::endl;
    }
}
