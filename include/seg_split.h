#define LOGGER_LEVEL LL_WARN
#include "./jieba/cppjieba/src/MPSegment.hpp"
#include "./jieba/cppjieba/src/HMMSegment.hpp"
#include "./jieba/cppjieba/src/MixSegment.hpp"
using namespace CppJieba;
const char * const JIEBA_DICT_FILE = "./jieba/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "./jieba/cppjieba/dict/hmm_model.utf8";
const char * const USER_DICT_FILE = "./jieba/cppjieba/dict/user.dict.utf8";
MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE, USER_DICT_FILE);
