//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2 of the License.
//   
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//   
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiArray.h"
#include "CmpiInstance.h"
#include "CmpiProvider.h"
#include "CmpiDateTime.h"
#include "CmpiObjectPath.h"

using namespace std;
using namespace CmpiCpp;

CmpiProvider::CmpiProvider() 
    : _name(NULL), _refcount(0)
{
    pthread_mutex_init(&_refcount_lock, NULL);
}

CmpiProvider::~CmpiProvider()
{
    pthread_mutex_destroy(&_refcount_lock);
}

const char * 
CmpiProvider::getName() const
{
    return _name;
}

void
CmpiProvider::setName(const char *name)
{
    _name = name;
}

int
CmpiProvider::incRefcount()
{
    pthread_mutex_lock(&_refcount_lock);
    int result = ++(_refcount);
    pthread_mutex_unlock(&_refcount_lock);

    return result;
}

int
CmpiProvider::decRefcount()
{
    pthread_mutex_lock(&_refcount_lock);
    int result = --(_refcount);
    pthread_mutex_unlock(&_refcount_lock);

    return result;
}

int 
CmpiProvider::getRefcount() const
{
    return _refcount;
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
