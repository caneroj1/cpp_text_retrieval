//
//  query.hpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef query_hpp
#define query_hpp

#include <iostream>
#include <utility>
#include <sstream>
#include <vector>
#include <map>

#include "lowercase.h"

using namespace std;

class Query {
public:
    Query() { }
    
    Query(string query)
    : m_Query(query) { }
    
    void tokenize();
    void compute_freqs();
    size_t get_token_count() const { return m_Tokens.size(); }
    const vector<string>& get_tokens() const { return m_Tokens; }
    const map<string, int>& get_freqs() const { return m_TermFreqs; }
    
private:
    string m_Query;
    vector<string> m_Tokens;
    map<string, int> m_TermFreqs;
};

#endif /* query_hpp */
