//
//  rank_vector.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "rank_vector.hpp"
#include <cassert>

double RankVector::rank_against(const RankVector& rv) {
    // at this point, both of the vectors should be the same length
    assert(m_RankVector.size() == rv.get_size());
    
    double res = 0;
    for (int i = 0; i < m_RankVector.size(); i++)
        res += m_RankVector[i] * rv[i];
    
    return res;
}