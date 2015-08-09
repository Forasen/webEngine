#include "seg.h"

int main(int argc, char ** argv)
{
    MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE, USER_DICT_FILE);
    std::vector<std::string> word;
    std::cout<<"请输入文件名：";
    std::string filename;
    std::cin>>filename;
    std::ifstream input("./C15-Energy01.txt");
    if(!input)
    {
        std::cout<<"error: input!"<<std::endl;
    }
    std::string line_content;
    std::string real_content;
    while(getline(input, line_content))
    {
        real_content += line_content;
        real_content += "\n";
    }
    seg.cut(real_content, word);
    std::cout<<"分词前的文章为："<<std::endl;
    std::cout<<real_content<<"\n"<<std::endl;
    std::vector<std::string>::iterator iter=word.begin();
    /*
    std::cout<<"分词后的文件为："<<std::endl;
    for(iter;iter!=word.end();iter++)
    {
        std::cout<<*iter<<std::endl;
    }
    */
    return EXIT_SUCCESS;
}
