/*********************************************
  > File  : MyJson.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Tue 21 Jul 2015 08:26:51 AM CST
 ********************************************/

#ifndef _MYJSON_H
#define _MYJSON_H

#include<map>
#include<cstring>

#include "./../json/json.h"

class MyJson
{
public:
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
        Json::StyledWriter stylewriter;

        return stylewriter.write(root);
    }
    void json_handle_reader(std::string str_map)
    {
        Json::Value root;
        Json::Reader reader;
        if(reader.parse(str_map, root))
        {
            if(!root["files"].isNull())
            {
                Json::Value arr_files = root["files"];
                int files_size = root["files"].size();
                for(int index=0; index<files_size; index++)
                {
                    std::string title_str = arr_files[index]["title"].asString(); 
                    std::string summary_str = arr_files[index]["summary"].asString();
                    std::cout<<"文章的标题为："<<title_str<<std::endl;
                    std::cout<<summary_str<<std::endl;
                }
            }
        }
    }
    std::string json_handle_str(std::string str)
    {
        Json::Value root;
        Json::Value arr;
        root["content"] = str;
        Json::StyledWriter stylewriter;

        return stylewriter.write(root);
    }
    
    std::string json_read(std::string str_buf)
    {
        Json::Reader reader;
        Json::Value root;
        if(reader.parse(str_buf, root))
        {
            std::string parse_buf = root["content"].asString();
            std::cout<<"读取到的数据为："<<parse_buf<<std::endl;
            return parse_buf;
        }
    }

    std::string resNull()
    {
        Json::Value root;
        Json::Value arr;
        Json::Value elem;

        elem["title"] = "408 bad error!";
        elem["summary"] = "NO RESULT!亲，下次再查询吧！";
        arr.append(elem);
        root["files"] = arr;
        Json::StyledWriter stylewriter;

        return stylewriter.write(root);
    }
};
#endif
