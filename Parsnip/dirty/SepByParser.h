/*
    Parsnip Parser Libary
	http://parsnip-parser.sf.net
	Copyright 2007 Alex Rubinsteyn
	-----------------------------------------------------------------------
	This file is part of Parsnip.

    Parsnip is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Parsnip is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Parsnip.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PARSNIP_SEP_BY_PARSER_H
#define PARSNIP_SEP_BY_PARSER_H

#include "Parser.h"

namespace Parsnip
{

template <typename Accumulator,  typename AccOut, typename In, typename ParserOut>
struct SepByParser : public IParser<In, AccOut>
{
	SepByParser(ptr<IParser<In, ParserOut> > p, ptr<IParser<In, void> > _sep, int _min, int _max) : parser(p), sep(_sep), min(_min), max(_max) 
	{
		this->setName("sepBy");
	}	
	
protected:
	virtual Result<AccOut> eval()
	{
		Accumulator acc;
		Result<ParserOut> result;
		
		//save position before trying to parse so we can restore it if we fail
		Reader<In>::IndexT lastPos = Reader<In>::pos();

		int i = 0;
		while (i < max && Reader<In>::hasNext()) {
			
			result = parser->parse();
			if (result) 
			{
				acc.accum( result.data());
			}
			else { break; }
			
			if (!sep->parse()) { break; }

			++i;
		} 
		
		if (i < min)
		{
			Reader<In>::set_pos(lastPos);	
			return Result<AccOut>::fail();
		}
		else
		{
			return Result<AccOut>::succeed(acc.result());		
	
		}
	}
	
	ptr<IParser<In, ParserOut> > parser; 
	ptr<IParser<In, void> > sep;
	int min, max;
};


template <typename Acc, typename In, typename Out, typename SepOut>
ptr<IParser<In, typename Acc::ResultType> > sepBy(ptr<IParser<In, Out> > data, ptr<IParser<In, SepOut> > sep, int min = 0, int max = INT_MAX)
{
	return new SepByParser<Acc, typename Acc::ResultType, In, Out>( data , skip(sep), min, max);
}


template <typename Acc, typename In, typename Out, typename SepOut>
ptr<IParser<In, typename Acc::ResultType> > sepBy1(ptr<IParser<In, Out> > data, ptr<IParser<In, SepOut> > sep,  int max = INT_MAX)
{
	return sepBy<Acc>(data, sep, 1, max);
}


template <typename Acc, typename In, typename Out, typename SepOut>
ptr<IParser<In, typename Acc::ResultType> > sepByAtleast(ptr<IParser<In, Out> > data, ptr<IParser<In, SepOut> > sep,  int min)
{
	return sepBy<Acc>(data, sep, min);
}


}

#endif