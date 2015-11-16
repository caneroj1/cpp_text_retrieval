//
//  document.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/14/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "document.h"

void Document::read_document() {
    fstream f(m_Path);
    string line;
    
    m_Words.clear();
    while(getline(f, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' '))
            m_Words.push_back(lowercase(token));
    }
}

void Document::compute_freqs() {
    if (should_compute_freqs()) {
        for (string word : m_Words) {
            if (not_present(word))
                m_TermFrequencies.insert(new_term(word));
            else
                m_TermFrequencies.find(word)->second++;
        }
    }
}

Document Document::create_and_read(string path) {
    Document d(path);
    d.read_document();
    d.compute_freqs();
    return d;
}

double Document::pivoted_length_normalizer(size_t avg_doc_length) const {
    if (avg_doc_length == 0) return 0;
    int b = 1;
    return 1 - b + b * ((double)get_doc_length() / avg_doc_length);
}