/*
 *
 */

#pragma once

#include "Parser.h"

class CharParser : public Parser<char> {
public:
	CharParser(char c)
	:matchchar(c)
	{}

	virtual Maybe<std::tuple<char, std::string>> operator() (const std::string& input) override
	{
		if (!input.empty() and input[0] == matchchar)
			return Just(std::make_tuple(matchchar, input.substr(1)));
		return Maybe<std::tuple<char, std::string>>(std::make_tuple('\0', input), false);
	}
protected:
private:
	char matchchar;
};
