//
//  inverted_index.hpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/20/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef inverted_index_hpp
#define inverted_index_hpp

#include "document_collection.hpp"
#include "index_object.hpp"
#include <boost/optional.hpp>

using namespace std;

class InvertedIndex {
public:
    explicit InvertedIndex(DocumentCollection& col);
    
    boost::optional<const IndexObject&> index_into(const string& key) const
    {
        auto f = m_IndexMap.find(key);
        if (f == m_IndexMap.end())
            return boost::optional<const IndexObject&>();
        return boost::make_optional<const IndexObject&>(f->second);
    }
    
private:
    map<string, IndexObject> m_IndexMap;
};

#endif /* inverted_index_hpp */
