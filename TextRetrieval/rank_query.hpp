//
//  rank_query.hpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/16/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef rank_query_hpp
#define rank_query_hpp

#include <vector>
#include <string>
#include "rank_vector.hpp"
#include "query.hpp"
#include "bm25.hpp"
#include "document_collection.hpp"
#include "inverted_index.hpp"

//typedef vector<vector<string>> Intersections;

using namespace std;

class RankQuery {
public:
    RankQuery(const InvertedIndex& index, Query query, DocumentCollection& collection)
    : m_InvertedIndex(index)
    , m_Collection(collection)
    , m_Query(query) { }
    
    const vector<RankVector>& get_rank_vectors() const
    { return m_RankVectors; }
    
    void compute_ranking();
    
private:
    DocumentCollection m_Collection;
    const InvertedIndex m_InvertedIndex;
    vector<RankVector> m_RankVectors;
    const Query m_Query;
};

#endif /* rank_query_hpp */
