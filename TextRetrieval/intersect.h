//
//  intersect.h
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef intersect_h
#define intersect_h

#include <string>
#include <vector>

#include "query.hpp"
#include "document_collection.hpp"

using namespace std;

class Intersect {
public:
    static vector<vector<string>> get_intersection(const Query& q,
                                                  const DocumentCollection& dc);
};

#endif /* intersect_h */
