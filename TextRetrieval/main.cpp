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
#include "rank_query.hpp"

using namespace std;

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
        
        RankQuery rq(intersections, q, collection);
        rq.compute_ranking();
        
        const vector<RankVector> rankings = rq.get_rank_vectors();
        
        for (int i = 0; i < rankings.size(); i++) {
            cout << "Document #" << rankings[i].get_doc_id() << ": has score ";
            cout << rankings[i].get_ranking() << endl;
        }
        
        cout << "\n" << endl;
    }
    
    return 0;
}
