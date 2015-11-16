//
//  test_document_collection.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "catch.hpp"
#include "document_collection.hpp"
#include "config.h"

TEST_CASE("Document Collection Class", "[doc_collection]") {
    Document d1 = Document::create_and_read(TEST_PATH);
    Document d2 = Document::create_and_read(TEST2_PATH);
    vector<Document> docs = { d1, d2 };
    DocumentCollection collection(docs);
    
    SECTION("Can store a number of documents") {
        REQUIRE(collection.get_num_docs() == NUMBER_DOCS);
    }
    
    SECTION("Can compute average doc length") {
        REQUIRE(collection.get_avg_doc_length() == AVG_DOC_LENGTH);
    }
    
    SECTION("Can add a new document to the collection") {
        collection.add_new_doc(Document(TEST2_PATH));
        REQUIRE(collection.get_num_docs() == NUMBER_DOCS + 1);
    }
    
    SECTION("Can recompute average doc length") {
        collection.add_new_doc(Document::create_and_read(TEST2_PATH));
        size_t avg_doc_length = ((AVG_DOC_LENGTH * NUMBER_DOCS) + DOC2_LENGTH)/(NUMBER_DOCS + 1);
        REQUIRE(collection.get_avg_doc_length() == avg_doc_length);
    }
    
    SECTION("Can compute document frequencies") {
        collection.compute_freqs();
        
        map<string, int> freqs = collection.get_doc_freqs();
        REQUIRE(freqs.size() > 0);
        
        REQUIRE(collection.get_doc_frequency("hello") == 2);
    }
    
    SECTION("Can return inverse document frequencies") {
        collection.compute_freqs();
        
        REQUIRE(collection.get_idf("hello") == Catch::Detail::Approx(0.17609));
    }
    
    SECTION("Returns 0 for words not in the collection") {
        REQUIRE(collection.get_idf("collection") == 0);
    }
}
