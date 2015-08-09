#include "seg.h"
#include<fstream>
#include<sstream>
#include<ctime>

int main(int argc, char ** argv)
{
    clock_t begin;
    clock_t end;
    begin = clock();
    MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE, USER_DICT_FILE);

    std::vector<std::string> word;

    std::ifstream input("./test_generate_page/ripepage.lib");
    if(!input)
    {
        std::cout<<"error: input!"<<std::endl;
        exit(-1);
    }
    std::string line;
    std::string real_content;
    while(getline(input, line))
    {
        real_content += line;
        real_content += "\n";
    }
    //std::string real_content;
    //std::cin>>real_content;
    seg.cut(real_content, word);

    /*
    std::vector<std::string>::iterator iter=word.begin();
    for(iter;iter!=word.end();iter++)
    {
        std::cout<<*iter;
    }
    */
    std::cout<<"分词后的文章为："<<std::endl;
    std::string str_res;
    for(auto it: word)
    {
        str_res += it;
        str_res += " ";
    }
    std::cout<<str_res<<std::endl;
    end = clock();
    double res = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"共用时："<<res<<std::endl;
    return EXIT_SUCCESS;
}
