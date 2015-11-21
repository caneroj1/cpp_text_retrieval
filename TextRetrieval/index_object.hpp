//
//  index_object.hpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/20/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef index_object_hpp
#define index_object_hpp

#include <vector>
#include <algorithm>

using namespace std;

typedef uint32_t uint;

class IndexObject {
public:
    IndexObject()
    : m_postingsList()
    , m_idf(0)
    , m_tf(0) { }
    
    IndexObject(double idf, uint tf)
    : m_idf(idf)
    , m_tf(tf) { }
    
    IndexObject(double idf, uint tf, uint initialID)
    : IndexObject(idf, tf)
    { m_postingsList.push_back(initialID); }
    
    void add_to_postings_list(uint id)
    { m_postingsList.push_back(id); }
    
    void increase_tf(uint tf)
    { m_tf += tf; }
    
    size_t number_of_docs() const
    { return m_postingsList.size(); }
    
    const vector<uint>& get_postings_list() const
    { return m_postingsList; }
    
    const double& get_idf() const
    { return m_idf; }
    
    void remove_duplicates()
    {
        sort(m_postingsList.begin(), m_postingsList.end());
        m_postingsList.resize(distance(m_postingsList.begin(),
                                       unique(m_postingsList.begin(),
                                              m_postingsList.end())));
    }
    
private:
    vector<uint> m_postingsList;    // postings list
    double m_idf;                   // inverse doc frequency
    uint m_tf;                      // overall term frequency
};

#endif /* index_object_hpp */
