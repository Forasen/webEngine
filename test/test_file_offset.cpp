/*************************************************************************
	> File Name: test_file_offset.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2015 10:42:39 PM CST
 ************************************************************************/

#include<iostream>
#include<fstream>
using namespace std;

int main(void)
{
    fstream output("./offset.txt", fstream::ate|fstream::in|fstream::out);
    if(!output)
    {
        perror("output");
        exit(1);
    }
    std::string line;
    int line_cnt = 0;
    auto end_mark = output.tellg();
    std::cout<<"auto end_mark="<<end_mark<<std::endl;
    output.seekg(0, fstream::beg);
    while(output && output.tellg() != end_mark && getline(output, line))
    {
        line_cnt += line.size() + 1;
        auto curr_mark = output.tellg();
        output.seekp(0, fstream::end);
        output << line_cnt;
        if(curr_mark != end_mark)
        {
            output << " ";
        }
        output.seekg(curr_mark);
    }
    output.seekp(0, fstream::end);
    output << "\n";
    int curr_end_mark = output.tellg();
    std::cout<<"curr_end_mark="<<curr_end_mark<<std::endl;
    output.seekg(0, fstream::beg);
    std::string line1;
    while(getline(output, line1) && output.tellg()!=curr_end_mark)
    {
        std::cout<<line1<<std::endl;
    }
    return 0;
}
