//
//  rank_query.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/16/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "rank_query.hpp"
#include <boost/range/adaptor/indexed.hpp>

using namespace boost::adaptors;

void RankQuery::compute_ranking() {
    for (auto words : m_Intersections
         | indexed(1)) {
        
        // get the ranking vector for the query string
        vector<double> qv;
        for (const string& word : words.value())
            qv.push_back(m_Query.get_freqs().find(word)->second);
        
        RankVector queryRank(qv);
        const Document& doc = m_Collection.get_docs()[words.index() - 1];
        vector<double> vec;
        for (const string& word : words.value()) {
            double tf = doc.get_freqs().find(word)->second;
            
            tf = BM25::compute_bm25(tf,
                                    doc.pivoted_length_normalizer(
                                            m_Collection.get_avg_doc_length()));
            
            tf *= m_Collection.get_idf(word);
            
            vec.push_back(tf);
        }
        
        RankVector rv(vec);
        rv.set_doc_id(words.index());
        rv.set_ranking(rv.rank_against(queryRank));
        m_RankVectors.push_back(rv);
    }
    
    sort(m_RankVectors.begin(), m_RankVectors.end(),
         [](const RankVector& l, const RankVector& r) {
             return (l.get_ranking() > r.get_ranking());
         });
}