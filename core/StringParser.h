/*
 *
 */
#pragma once

#include "Parser.h"

class StringParser : public Parser<std::string> {
public:
	StringParser(const std::string& str)
	: matchStr(str)
	{}

	StringParser(std::string&& str)
	: matchStr(str)
	{}

	virtual Maybe<std::tuple<std::string, std::string>> operator() (const std::string& input) override {
		if (!input.empty()
			and std::equal(
				input.begin(),
				input.begin() + std::min(input.size(), matchStr.size()),
				matchStr.begin())) 
		{
			return Just(std::make_tuple(matchStr, input.substr(matchStr.size())));
		}
		return None(std::make_tuple(std::string(""), input));
	}
protected:
private:
	std::string matchStr;
};
