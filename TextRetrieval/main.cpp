//
//  main.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/14/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include <iostream>
#include "document_collection.hpp"
#include "query.hpp"
#include "bm25.hpp"
#include "intersect.h"
#include "rank_vector.hpp"

using namespace std;

typedef vector<vector<string>> Intersections;

int main(int argc, const char * argv[]) {
    cout << "Initializing Documents" << endl;
    
    DocumentCollection collection;
    string basePath = argv[1];
    collection.add_new_doc(Document::create_and_read(basePath + "doc1"));
    collection.add_new_doc(Document::create_and_read(basePath + "doc2"));
    collection.add_new_doc(Document::create_and_read(basePath + "doc3"));
    collection.add_new_doc(Document::create_and_read(basePath + "doc4"));
    
    cout << "Computing Document Frequencies" << endl;
    
    collection.compute_freqs();
    
    cout << "---------- Start Text Retrieval ----------\n\n";
    
    string query;
    while (true) {
        cout << "Query > ";
        getline(cin, query);
        
        Query q(query);
        q.tokenize();
        q.compute_freqs();
        // get intersections
        Intersections intersections = Intersect::get_intersection(q, collection);
        
        // for each intersection, let's get the ranking
        vector<RankVector> rankingsPerDoc;
        int count = 0;
        for (vector<string> words : intersections) {
            
            // get the ranking vector for the query string
            vector<double> qv;
            for (string word : words)
                qv.push_back(q.get_freqs().find(word)->second);
        
            RankVector queryRank(qv);
            const Document& doc = collection.get_docs()[count];
            vector<double> vec;
            for (string word : words) {
                double tf = doc.get_freqs().find(word)->second;
                
                tf = BM25::compute_bm25(tf,
                doc.pivoted_length_normalizer(collection.get_avg_doc_length()));
                
                tf *= collection.get_idf(word);
                
                vec.push_back(tf);
            }
            
            RankVector rv(vec);
            rv.set_doc_id(count + 1);
            rv.set_ranking(rv.rank_against(queryRank));
            rankingsPerDoc.push_back(rv);
            count++;
        }

        sort(rankingsPerDoc.begin(), rankingsPerDoc.end(),
             [](const RankVector& l, const RankVector& r) {
                 return (l.get_ranking() > r.get_ranking());
             });
        
        for (int i = 0; i < rankingsPerDoc.size(); i++) {
            cout << "Document #" << rankingsPerDoc[i].get_doc_id() << ": has score ";
            cout << rankingsPerDoc[i].get_ranking() << endl;
        }
        
        cout << "\n" << endl;
    }
    
    return 0;
}
