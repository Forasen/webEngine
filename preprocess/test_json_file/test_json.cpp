/*************************************************************************
> File Name: test_json.cpp
> Author: 
> Mail: 
> Created Time: Wed 05 Aug 2015 04:52:22 PM CST
************************************************************************/

#include<iostream>
#include<map>
#include<vector>
#include "../json/json.h"
using namespace std;

#if 0
std::string json_read(std::string str_buf)
{
    std::cout<<"inside json_read(std::string str_buf)222222"<<std::endl;
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(str_buf, root))
    {
        std::cout<<"*******************"<<std::endl;
        std::cout<<"开始从json对象里读取数据"<<std::endl;
        std::string parse_buf = root["content"].asString();
        std::cout<<"读取到的数据为："<<parse_buf<<std::endl;
        return parse_buf;
    }
}

std::string json_handle_string(std::string str)
{
    Json::Value root;
#if 0
    Json::Value arr;
    for(auto it: docs_map)
    {
        Json::Value elem;

        std::string title = it.first;
        std::string summary= it.second;
        elem["title"] = title;
        elem["summary"] = summary;
        arr.append(elem);
    }
    root["files"] = arr;
    Json::StyledWriter stylewriter;
#endif
    root["content"] = Json::Value("hello, Json!");

    Json::StyledWriter stylewriter;
    return stylewriter.write(root);
}
std::string json_handle(std::map<std::string, std::string> docs_map)
{
    Json::Value root;
    Json::Value arr;
    for(auto it: docs_map)
    {
        Json::Value elem;

        std::string title = it.first;
        std::string summary= it.second;
        elem["title"] = title;
        elem["summary"] = summary;
        arr.append(elem);
    }
    root["files"] = arr;
    Json::StyledWriter stylewriter1;

    return stylewriter1.write(root);
}
#endif

int main(void)
{
#if 0
    std::map<std::string, std::string> tmp_map;
    tmp_map.insert(std::make_pair("a", "aaaaa"));
    tmp_map.insert(std::make_pair("b", "bbbbb"));
    tmp_map.insert(std::make_pair("c", "ccccc"));
    tmp_map.insert(std::make_pair("d", "ddddd"));
    tmp_map.insert(std::make_pair("e", "eeeee"));
#endif

    Json::Value root_write;
    root_write["content"] = Json::Value("hello, world");
    Json::StyledWriter styledwriter;
    std::string w_str = styledwriter.write(root_write);
    std::cout<<"已经封装的json为："<<std::endl;
    std::cout<<w_str<<std::endl;

    Json::Value root_read;
    Json::Reader reader;
    std::string recv_buf;
    if(reader.parse(w_str, root_read))
    {
        std::cout<<"开始读取数据..."<<std::endl;
        recv_buf = root_read["content"].asString();
    }
    std::cout<<"从json对象中读取到的数据为："<<std::endl;
    std::cout<<recv_buf<<std::endl;

    return 0;
}
