/*************************************************************************
> File Name: test_summary.cpp
> Author: 
> Mail: 
> Created Time: Wed 29 Jul 2015 04:15:37 PM CST
************************************************************************/

#include<iostream>
using namespace std;
Summarizer(originalText, maxSummarySize):
    　　　　// 计算原始文本的词频，生成一个数组，比如[(10,'the'), (3,'language'), (8,'code')...]
    　　　　wordFrequences = getWordCounts(originalText)
    　　　　// 过滤掉停用词，数组变成[(3, 'language'), (8, 'code')...]
    　　　　contentWordFrequences = filtStopWords(wordFrequences)
    　　　　// 按照词频进行排序，数组变成['code', 'language'...]
    　　　　contentWordsSortbyFreq = sortByFreqThenDropFreq(contentWordFrequences)
    　　　　// 将文章分成句子
    　　　　sentences = getSentences(originalText)
    　　　　// 选择关键词首先出现的mZmZ    　　　　setSummarySentences = {}
    　　　　foreach word in contentWordsSortbyFreq:
        　　　　　　firstMatchingSentence = search(sentences, word)
        　　　　　　setSummarySentences.add(firstMatchingSentence)
        　　　　　　if setSummarySentences.size() = maxSummarySize:
            　　　　　　　　break
            　　　　// 将选中的句子按照出现顺序，组成摘要
            　　　　summary = ""
            　　　　foreach sentence in sentences:
                　　　　　　if sentence in setSummarySentences:
                    　　　　　　　　summary = summary + " " + sentence
                    　　　　return summary
