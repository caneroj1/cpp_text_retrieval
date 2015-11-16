//
//  config.h
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef config_h
#define config_h

#include <boost/preprocessor/stringize.hpp>

#define NUMBER_DOCS 2

#define TEST_PATH BOOST_PP_STRINGIZE(/Users/jcanero/Code/Repositories/c++/TextRetrieval/TestTextRetrieval/test_document.txt)
#define DOC_LENGTH 5

#define TEST2_PATH BOOST_PP_STRINGIZE(/Users/jcanero/Code/Repositories/c++/TextRetrieval/TestTextRetrieval/test_document2.txt)
#define DOC2_LENGTH 6

#define AVG_DOC_LENGTH ((DOC_LENGTH + DOC2_LENGTH)/NUMBER_DOCS)

#endif /* config_h */
