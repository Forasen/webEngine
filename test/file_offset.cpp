/*************************************************************************
	> File Name: file_offset.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2015 10:56:02 PM CST
 ************************************************************************/

#include<iostream>
#include<fstream>
using namespace std;

int main(void)
{
    fstream output("./fileoffset.txt", ofstream::in|ofstream::out|ofstream::ate);
    if(!output)
    {
        perror("output");
        exit(-1);
    }
    std::string line;
    int line_cnt = 0;
    auto end_mark = output.tellg();
    output.seekg(0, fstream::beg);
    while(output && output.tellg()!=end_mark && getline(output, line))
    {
        line_cnt += line.size() + 1;
        auto curr_mark = output.tellg();
        output.seekp(0, fstream::end);
        output << line_cnt;
        if(curr_mark != end_mark)
        {
            output<<" ";
        }
        output.seekg(curr_mark);
    }
    output.seekp(0, fstream::end);
    output<<"\n";

    return 0;
}
