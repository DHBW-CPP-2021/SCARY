#include "CoutLogPolicy.h"
#include <iostream>


void CoutLogPolicy::open_ostream() const
{
    // nothing to do here
}

void CoutLogPolicy::close_ostream() const
{
    // nothing to do here
}

void CoutLogPolicy::write(std::string const &msg) const
{
    std::cout << msg;
}
