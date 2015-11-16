//
//  rank_vector.hpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef rank_vector_hpp
#define rank_vector_hpp

#include <vector>

using namespace std;


class RankVector {
public:
    RankVector()
    : m_RankVector() { }
    
    RankVector(vector<double> v)
    : m_RankVector(v) { }
    
    double rank_against(const RankVector& rv);
    const vector<double>& get_rank_vector() const { return m_RankVector; }
    
    size_t get_size() const { return m_RankVector.size(); }
    
    inline const double operator[](size_t idx) const
    { return m_RankVector[idx]; }
    
    inline double& operator[](size_t idx)
    { return m_RankVector[idx]; }
    
    void set_ranking(double r) { m_Ranking = r; }
    double get_ranking() const { return m_Ranking; }
    
    void set_doc_id(int id) { m_DocID = id; }
    int get_doc_id() const { return m_DocID; }
    
private:
    vector<double> m_RankVector;
    double m_Ranking;
    int m_DocID;
};

#endif /* rank_vector_hpp */
