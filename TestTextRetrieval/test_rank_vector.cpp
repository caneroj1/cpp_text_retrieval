//
//  test_rank_vector.cpp
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#include "catch.hpp"

#include "rank_vector.hpp"

TEST_CASE("Testing Rank Vector class", "[rank_vec]") {
    RankVector fv(vector<double> {1, 2, 3, 4, 5});
    
    SECTION("Can use [] operator to get an element") {
        REQUIRE(fv[1] == 2);
    }
    
    SECTION("Can use [] operator to change an element") {
        fv[1] = 100;
        REQUIRE(fv[1] == 100);
    }
}
