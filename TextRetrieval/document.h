//
//  document.h
//  TextRetrieval
//
//  Created by Joseph Canero on 11/14/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef file_parsing_document_h
#define file_parsing_document_h

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 
#include <map>
#include <utility>

#include "lowercase.h"

using namespace std;

class Document {
public:
    Document()
    : m_Path() { }
    
    Document(string p)
    : m_Path(p) { }
    
    void read_document();
    void compute_freqs();
    void set_path(string p) { m_Path = p; }
    const string& get_path() const { return m_Path; }
    size_t get_doc_length() const { return m_Words.size(); }
    
    static Document create_and_read(string path);
    
    const vector<string>& get_words() const
    { return m_Words; }
    
    const map<string, int>& get_freqs() const
    { return m_TermFrequencies; }
    
    double pivoted_length_normalizer(size_t avg_doc_length) const;
    
private:
    string m_Path;
    vector<string> m_Words;
    map<string, int> m_TermFrequencies;
    
    bool should_compute_freqs() const
    { return !m_Words.empty() && m_TermFrequencies.empty(); }
    
    bool not_present(const string& word) const
    { return m_TermFrequencies.find(word) == m_TermFrequencies.end(); }
    
    pair<string, int> new_term(const string& word) const
    { return make_pair(word, 1); }
};

#endif /* file_parsing_document_h */
