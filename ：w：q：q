/*************************************************************************
	> File Name: test_json.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Aug 2015 09:17:49 AM CST
 ************************************************************************/

#include<iostream>
#include "./json/json.h"
using namespace std;

int main()
{
    
    

    const char* str = "{\"praenomen\":\"Gaius\",
    \"nomen\":\"Juluis\", \"cognomen\":\"Caezar\",\"born\":-100, \"died\":-44}";

    Json::Reader reader;
    Json::Value root;

    if(reader.parse(str, root))
    {
        std::string praenomen = root["praenomen"].asString();
        std::string nomen = root["nomen"].asString();
        std::string cognomen = root["cognomeni"].asString();
        int born = root["born"].asInt();
        int died = root["died"].asInt();

        std::cout<<praenomen + " " + cognomen
                <<" was born in year:"<<born
                <<", died in year:"<<died<<std::endl;
    }
}


