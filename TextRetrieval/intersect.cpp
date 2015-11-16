//
//  intersect.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "intersect.h"

vector<vector<string>> Intersect::get_intersection(const Query& q,
                                                   const DocumentCollection& dc) {
    vector<vector<string>> intersections;
    
    for (const Document& doc : dc.get_docs()) {
        vector<string> intersectedTokens;
        const map<string, int>& freqs = doc.get_freqs();
        for (string token : q.get_tokens()) {
            if (freqs.find(token) != freqs.end())
                intersectedTokens.push_back(token);
        }
        
        intersections.push_back(intersectedTokens);
    }
    
    return intersections;
}
