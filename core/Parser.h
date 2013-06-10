/*
 *
 */

#pragma once

#include "Types.h"

////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Parser {
public:
	virtual Maybe<std::tuple<T, std::string>> operator() (const std::string& input) = 0;
protected:
private:
};

