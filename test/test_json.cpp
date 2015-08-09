/*************************************************************************
	> File Name: test_json.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 30 Jul 2015 04:30:20 PM CST
 ************************************************************************/

#include<iostream>
#include "json.h"
using namespace std;

var jsonStr="{sid:'100', name:'jame', home: 'usa'}";

{
    key1: value1,
    key2: value2
}
[
    {
        key1: value1,
        key2: value2
    }
    {
        key3: value3,
        key4: value4
    }
]

var obj =
{
    1: "value1",
    "2": "value2",
    count: 3,
    person:
    [
        {
            id: 1,
            name: "张三"
        },
        {
            id: 2,
            name: "李四"
        }
    ],
    object: 
    {
        id: 1,
        msg: "对象里的对象"
    }
};

function readJson()
{
    alert(obj.1);
    alert(obj.2);
    alert(obj.person[0].name);
    //alert(obj.person[0]["name"]);
    alert(obj.person.object.msg);
}

function add()
{
    obj.sex = "男"
    //obj["sex"] = "男"
}

function update
{
    obj.count = 10;
    //obj["count"] = 10
}

function delete()
{
    delete obj.count;
    //delete obj["count"];
}

function traversal()
{
    for(var c in obj)
    {
        console.log(c + ":", obj[c]);
    }
}

function traveral()
{
    for(var c in obj)
    {
        console.log(c + obj[c]);
    }
}


int main(void)
{
    std::string res = fast_writer.write(root);
    std::cout<<res<<std::endl;
}
