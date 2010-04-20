//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include <ctype.h>
#include "CmpiName.h"

using namespace std;
using namespace CmpiCpp;

CmpiName::CmpiName()
{
}

CmpiName::CmpiName(const char *name) : _name(name ? name : "")
{
}

CmpiName::CmpiName(const string &name) : _name(name)
{
}

CmpiName::CmpiName(const CmpiName &name) : _name(name.str())
{
}

CmpiName::~CmpiName()
{
}

string CmpiName::str() const
{
    return _name;
}

const char *CmpiName::c_str() const
{
    return _name.c_str();
}

size_t CmpiName::size() const
{
    return _name.size();
}

bool CmpiName::empty() const
{
    return _name.empty();
}

void CmpiName::assign(const string &name)
{
    _name.assign(name);
}

bool CmpiName::operator==(const CmpiName &name) const
{
    if (name.size() != this->size())
        return false;

    const char *a_data = name.str().data(), *b_data = this->str().data();

    for (size_t i = 0; i < this->size(); i++) {
        if (toupper(a_data[i]) != toupper(b_data[i]))
            return false;
    }

    return true;
}

bool CmpiName::operator!=(const CmpiName &name) const
{
    return !(*this == name);
}

bool CmpiName::operator<(const CmpiName &name) const
{
    if (name.size() > this->size())
        return true;

    const char *a_data = name.str().data(), *b_data = this->str().data();

    for (size_t i = 0; i < this->size(); i++) {
        if (toupper(a_data[i]) > toupper(b_data[i]))
            return true;
    }

    return false;
}

CmpiName &CmpiName::operator=(const CmpiName &rhs)
{
    if (this == &rhs) 
        return *this;

    _name.assign(rhs.str());

    return *this;
}

CmpiName::operator string() const
{
    return str();
}

ostream &CmpiCpp::operator<<(ostream &output, const CmpiName &obj)
{
    output << obj.str();
    return output;
}

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
