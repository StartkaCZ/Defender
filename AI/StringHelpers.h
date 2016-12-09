#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

#include "StringHelpers.inl"
#endif // BOOK_STRINGHELPERS_HPP
