/*************************************************************************
	> File Name: fileoffset1.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2015 11:20:39 PM CST
 ************************************************************************/

#include<iostream>
#include<iostream>
#include<fstream>
using namespace std;

int main(void)
{
    fstream output_file("./11111.txt", ofstream::in|ofstream::out|ofstream::ate);
    if(!output_file)
    {
        perror("output_file");
        exit(-1);
    }
    auto end_mark = output_file.tellg();
    int cnt = 0;
    std::string line;
    while(output_file && output_file.tellg()!=end_mark && getline(output_file, line))
    {
        auto curr_mark = output_file.tellg();
        cnt += line.size() + 1;
        output_file.seekp(0, fstream::end);
        output_file<<cnt;
        if(curr_mark != end_mark)
        {
            output_file << " ";
        }
        output_file.seekg(curr_mark);
    }

}
