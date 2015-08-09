#include "include/Application.hpp"

using namespace CppJieba;

#if 1

//class Segment: public MixSegment
class Segment: public CppJieba::Application
{
    CppJieba::Application app("./dict/jieba.dict.utf8",
                              "./dict/hmm_model.utf8",
                              "./dict/user.dict.utf8",
                              "./dict/idf.utf8",
                              "./dict/stop_words.utf8");

    private:
};
#endif

class Split
{
    std::string wordSplit(std::string& str)
    {
        //MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE, USER_DICT_FILE);
        std::vector<std::string> split_words;
        app.cut(str, split_words);
        std::string sResult;
        for(auto it: split_words)
        {
            sResult += it;
            sResult += " ";
        }
        return sResult;
    }
    
};

int main(int argc, char** argv) {
    std::string jieba_dict = "./dict/jieba.dict.utf8";
    std::string hmm_model = "./dict/hmm_model.utf8";
    std::string user_dict = "./dict/user.dict.utf8";
    std::string idf = "./dict/idf.utf8";
    std::string stop_word = "./dict/stop_words.utf8";
    CppJieba::Application app("./dict/jieba.dict.utf8",
                              "./dict/hmm_model.utf8",
                              "./dict/user.dict.utf8",
                              "./dict/idf.utf8",
                              "./dict/stop_words.utf8");
    vector<string> words;
    string result;
    string s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";

    cout << "\n\e[32m" << "[demo] METHOD_MIX" << "\e[0m\n"; // colorful
    app.cut(s, words, METHOD_MIX);
    //cout << join(words.begin(), words.end(), "/") << endl;
    cout << join(words.begin(), words.end(), " ") << endl;

    #if 0
    cout << "\n\e[32m" << "[demo] METHOD_MP" << "\e[0m\n"; // colorful
                                                    app.cut(s, words, METHOD_MP);
                                                    cout << join(words.begin(), words.end(), "/") << endl;

                                                    cout << "\n\e[32m" << "[demo] METHOD_HMM" << "\e[0m\n"; // colorful
                                                                                                     app.cut(s, words, METHOD_HMM);
                                                                                                     cout << join(words.begin(), words.end(), "/") << endl;

                                                                                                     cout << "\n\e[32m" << "[demo] METHOD_FULL" << "\e[0m\n"; // colorful
                                                                                                                                                       app.cut(s, words, METHOD_FULL);
                                                                                                                                                       cout << join(words.begin(), words.end(), "/") << endl;

                                                                                                                                                       cout << "\n\e[32m" << "[demo] METHOD_QUERY" << "\e[0m\n"; // colorful
                                                                                                                                                                                                          app.cut(s, words, METHOD_QUERY);
                                                                                                                                                                                                          cout << join(words.begin(), words.end(), "/") << endl;

                                                                                                                                                                                                          cout << "\n\e[32m" << "[demo] TAGGING" << "\e[0m\n"; // colorful
                                                                                                                                                                                                                                                        vector<pair<string, string> > tagres;
                                                                                                                                                                                                                                                        app.tag(s, tagres);
                                                                                                                                                                                                                                                        cout << s << endl;
                                                                                                                                                                                                                                                        cout << tagres << endl;;

                                                                                                                                                                                                                                                        cout << "\n\e[32m" << "[demo] KEYWORD" << "\e[0m\n"; // colorful
                                                                                                                                                                                                                                                                                                      vector<pair<string, double> > keywordres;
                                                                                                                                                                                                                                                                                                      app.extract(s, keywordres, 5);
                                                                                                                                                                                                                                                                                                      cout << s << endl;
                                                                                                                                                                                                                                                                                                      cout << keywordres << endl;
                                                                                                                                                                                                                                                                                                      #endif
                                                                                                                                                                                                                                                                                                      return EXIT_SUCCESS;
                                                                                                                                                                                                                                                                                                     }
