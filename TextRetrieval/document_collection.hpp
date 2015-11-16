//
//  document_collection.hpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef file_parsing_document_collection_hpp
#define file_parsing_document_collection_hpp

#include "document.h"
#include <numeric>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

class DocumentCollection {
public:
    DocumentCollection()
    : m_Documents()
    , m_AvgDocLength(0) { }
    
    DocumentCollection(const vector<Document>& ds)
    : m_Documents(ds)
    , m_AvgDocLength(0) { }
    
    DocumentCollection(const vector<Document>& ds, size_t l)
    : m_Documents(ds)
    , m_AvgDocLength(l) { }
    
    void compute_freqs();
    const map<string, int>& get_doc_freqs() { return m_DocFreqs; }
    
    int get_doc_frequency(const string& word);
    double get_idf(const string& word);
    
    size_t get_avg_doc_length();
    size_t add_new_doc(const Document& d) {
        m_Documents.push_back(d);
        m_AvgDocLength = 0;
        return get_avg_doc_length();
    }
    
    size_t get_num_docs() const { return m_Documents.size(); }
    const vector<Document>& get_docs() const { return m_Documents; }
    
private:
    vector<Document> m_Documents;
    size_t m_AvgDocLength;
    map<string, int> m_DocFreqs;
    
    bool shouldComputeDocLengths() const
    { return m_AvgDocLength == 0 && m_Documents.size() > 0; }
    
    bool shouldComputeDocFreqs() const
    { return m_DocFreqs.size() == 0 && m_Documents.size() > 0; }
    
    bool shouldAddWord(const map<string, bool>& m, const string& word) const
    { return m.find(word) == m.end() ? true : false; }
};

#endif /* file_parsing_document_collection_hpp */
