//
//  bm25.hpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef utility_bm25_h
#define utility_bm25_h

class BM25 {
public:
    static double compute_bm25(double count, double weight = 1.0) {
        return (count * k) / (count + k * weight);
    }
    
private:
    constexpr static double k = 20;
};
#endif
