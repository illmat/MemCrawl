#include <sstream>

int string2int( const std::string& a )
{
    // Convert a string representation of a number into a floating point value.
    // Throws an int if the string contains anything but whitespace and a valid
    // numeric representation.
    //
    int result;
    std::string s( a );

    // Get rid of any trailing whitespace
    s.erase( s.find_last_not_of( " \f\n\r\t\v" ) + 1 );

    // Read it into the target type
    std::istringstream ss( s );
    ss >> result;

    // Check to see that there is nothing left over
    if (!ss.eof())
        throw 1;

    return result;
}
