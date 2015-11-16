//
//  query.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "query.hpp"

void Query::tokenize() {
    stringstream ss(m_Query);
    string token;
    while (getline(ss, token, ' '))
        m_Tokens.push_back(lowercase(token));
}

void Query::compute_freqs() {
    for (string token : m_Tokens) {
        if (m_TermFreqs.find(token) == m_TermFreqs.end())
            m_TermFreqs.insert(make_pair(token, 1));
        else
            m_TermFreqs.find(token)->second++;
    }
}