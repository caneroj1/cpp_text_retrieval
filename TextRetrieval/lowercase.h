//
//  lowercase.h
//  TextRetrieval
//
//  Created by Joseph Canero on 11/15/15.
//  Copyright © 2015 jcanero. All rights reserved.
//

#ifndef lowercase_h
#define lowercase_h

#include <boost/algorithm/string/case_conv.hpp>
#include <string>

inline std::string lowercase(const std::string& str)
{ return boost::to_lower_copy(str); }

#endif /* lowercase_h */
