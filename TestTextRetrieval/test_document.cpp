//
//  test_document.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "catch.hpp"
#include "document.h"
#include "config.h"

TEST_CASE("Document Class", "[doc]") {
    Document d(TEST_PATH);
    
    SECTION("Can get a path from the document") {
        REQUIRE(d.get_path() == TEST_PATH);
    }
    
    SECTION("Can set a path for the document") {
        d.set_path("new_path");
        REQUIRE(d.get_path() == "new_path");
    }
    
    SECTION("Can read from a file") {
        d.read_document();
        
        const vector<string> words = d.get_words();
        REQUIRE(words.size() == DOC_LENGTH);
        
        REQUIRE(words[0] == "hello");
        REQUIRE(words[1] == "hello");
        REQUIRE(words[2] == "i");
        REQUIRE(words[3] == "like");
        REQUIRE(words[4] == "tests");
    }
    
    SECTION("Can return document length") {
        d.read_document();
        
        REQUIRE(d.get_doc_length() == DOC_LENGTH);
    }
    
    SECTION("Can compute term frequencies") {
        d.read_document();
        d.compute_freqs();
        
        map<string, int> freqs = d.get_freqs();
        REQUIRE(freqs.size() == 4);
        
        REQUIRE(freqs.find("hello")->second == 2);
        REQUIRE(freqs.find("i")->second     == 1);
        REQUIRE(freqs.find("like")->second  == 1);
        REQUIRE(freqs.find("tests")->second == 1);
    }
}
