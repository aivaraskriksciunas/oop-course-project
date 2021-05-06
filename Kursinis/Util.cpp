#include "Util.h"

std::string trim_line( std::string line )
{
	int begin = line.find_first_not_of( " \r\t\n" );
	int end;

	for ( end = line.size() - 1; end >= begin; end-- )
	{
		if ( line[end] > 32 ) break;
	}

	return line.substr( begin, end - begin + 1 );
}