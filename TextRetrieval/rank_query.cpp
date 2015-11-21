//
//  rank_query.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/16/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "rank_query.hpp"
#include <boost/range/adaptor/indexed.hpp>
#include <algorithm>

using namespace boost::adaptors;
using namespace std;

void RankQuery::compute_ranking() {
    vector<uint> documentIDs;
    
    const vector<string>& tokens = m_Query.get_tokens();

    auto optIdxObj = m_InvertedIndex.index_into(tokens.front());
    if (optIdxObj)
        documentIDs = optIdxObj->get_postings_list();
    
    for (auto iter = tokens.begin() + 1;
         iter != tokens.end();
         iter++)
    {
        auto optIdxObj = m_InvertedIndex.index_into(*iter);
        
        if (!optIdxObj)
            continue;
        
        vector<uint> intersectedIDs;
        const vector<uint>& ids = optIdxObj->get_postings_list();
        set_union(documentIDs.begin(), documentIDs.end(),
                  ids.begin(), ids.end(), back_inserter(intersectedIDs));
        
        documentIDs = intersectedIDs;
    }
    
    sort(documentIDs.begin(), documentIDs.end());
    documentIDs.resize(distance(documentIDs.begin(),
                                unique(documentIDs.begin(),
                                       documentIDs.end())));
    
    vector<double> qv;
    for (const string& word : tokens)
        qv.push_back(m_Query.get_freqs().find(word)->second);
    
    RankVector queryRank(qv);
    for (const uint& docID : documentIDs) {
        
        
        const Document& doc = m_Collection.get_docs()[docID - 1];
        vector<double> vec;
        for (const string& word : tokens) {
            auto optIdxObj = m_InvertedIndex.index_into(word);
            
            if (!optIdxObj) {
                vec.push_back(0);
                continue;
            }
            
            auto f = doc.get_freqs().find(word);
            if (f == doc.get_freqs().end()) {
                vec.push_back(0);
                continue;
            }
            
            double tf = f->second;
            tf = BM25::compute_bm25(tf,
                                    doc.pivoted_length_normalizer(
                                          m_Collection.get_avg_doc_length()));
            
            tf *= optIdxObj->get_idf();
            
            vec.push_back(tf);
        }
        
        
        RankVector rv(vec);
        rv.set_doc_id(docID);
        rv.set_ranking(rv.rank_against(queryRank));
        m_RankVectors.push_back(rv);

    }
    
    sort(m_RankVectors.begin(), m_RankVectors.end(),
         [](const RankVector& l, const RankVector& r) {
             return (l.get_ranking() > r.get_ranking());
         });
}