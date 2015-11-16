//
//  document_collection.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "document_collection.hpp"

size_t DocumentCollection::get_avg_doc_length() {
    if (shouldComputeDocLengths()) {
        size_t res = accumulate(m_Documents.begin(), m_Documents.end(), 0,
                     [](int sum, const Document& d) {
                         return d.get_doc_length() + sum;
                     });
        m_AvgDocLength = res / m_Documents.size();
    }
    
    return m_AvgDocLength;
}

void DocumentCollection::compute_freqs() {
    if (shouldComputeDocFreqs()) {
        map<string, bool> shouldIncrementMap;
        for (const Document& d : m_Documents) {
            shouldIncrementMap.clear();
            for (string word : d.get_words()) {
                if (shouldAddWord(shouldIncrementMap, word)) {
                    auto item = m_DocFreqs.find(word);
                    if (item == m_DocFreqs.end())
                        m_DocFreqs.insert(make_pair(word, 1));
                    else
                        item->second++;
                    shouldIncrementMap.insert(make_pair(word, false));
                }
            }
        }
    }
}

int DocumentCollection::get_doc_frequency(const string& word) {
    if (shouldComputeDocFreqs())
        compute_freqs();
    
    auto item = m_DocFreqs.find(word);
    return item != m_DocFreqs.end() ? item->second : 0;
}

double DocumentCollection::get_idf(const string& word) {
    if (shouldComputeDocFreqs())
        compute_freqs();
    
    double frequency = get_doc_frequency(word);
    
    return frequency != 0 ?
    log10((get_num_docs() + 1) / frequency) :
    frequency;
        
}