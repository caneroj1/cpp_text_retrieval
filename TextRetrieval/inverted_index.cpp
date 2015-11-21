//
//  inverted_index.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/20/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "inverted_index.hpp"

InvertedIndex::InvertedIndex(DocumentCollection& col) {
    const vector<Document>& docs = col.get_docs();
    
    for (int i = 0; i < docs.size(); i++) {
        const Document& doc = docs[i];
        for (const string& word : doc.get_words()) {
            auto found = m_IndexMap.find(word);
            if (found == m_IndexMap.end()) {
                int tf = doc.get_freqs().find(word)->second;
                double idf = col.get_idf(word);
                m_IndexMap.insert(make_pair(word,
                                            IndexObject(idf,
                                                        tf,
                                                        i + 1)));
            } else {
                IndexObject& idxObj = m_IndexMap.find(word)->second;
                idxObj.add_to_postings_list(i + 1);
                idxObj.increase_tf(doc.get_freqs().find(word)->second);
            }
        }
    }
    
    for (auto& pair : m_IndexMap)
        pair.second.remove_duplicates();
}