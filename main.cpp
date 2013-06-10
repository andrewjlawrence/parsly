
#include "Parsly.h"

#include <string>
#include <iostream>

using namespace std;
using namespace Parsly;

int main()
{
	CharParser c('t');
	StringParser s("tes");
	auto result = s(std::string("test"));

	if (result)
		cout << std::get<0>(*result) << endl << std::get<1>(*result) << endl;
}

/*
 * Haskell syntax:

csvFile :: GenParser Char st [[String]]
csvFile = 
    do result <- many line
       eof
       return result
 */

